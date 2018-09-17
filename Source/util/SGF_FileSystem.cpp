/*
  SGF - Super Game Fabric  Super Game Fabric
  Copyright (C) 2010-2011 Rasputtim <raputtim@hotmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

  */
 

#include <sstream>
#include <iostream>
#include <stdio.h>
#ifndef _INC_DIRENT
#define _INC_DIRENT //remove perl stupid redefinitions
#endif
#include <dirent.h>
#ifdef _WIN32

#include <direct.h> // for getcwd
#include "../win_external_libs/dirent.h"
#else
#include <unistd.h>
#endif // for getcwd
#include <stdlib.h>// for MAX_PATH
#include <iterator>

#include "7z.h"
#include "unzip.h"
#include "7zAlloc.h"
#include "7zCrc.h"
#include "7zFile.h"

#include "util/SGF_Debug.h"
#include "util/SGF_Utf.h"
#include "util/SGF_Util.h"
#include "configuration/SGF_Configuration.h"
#include "exceptions/SGF_FileExceptions.h"
#include "util/SGF_FileSystem.h"



//http://legacy.imatix.com/html/sfl/


#ifdef _WIN32
#define _WIN32_IE 0x400
#include <shlobj.h>  //for SHGetSpecialFolderPathA
#endif


using namespace std;



namespace SGF{

namespace Filesystem{

File::File(){
}
        
File::~File(){
}
/*
static const string correctSlashes( const string &str ){
    //Debug::debug(Debug::filesystem,__FUNCTION__) << "Filesystem::correctSlashes() string  "<<str  << endl;
	string tempStr = str;
    if (DIR_SEPARATOR == '\\' ) {
		if( tempStr.find('/') != string::npos ){
			for( int i = tempStr.size()-1; i>-1; --i){
			if( tempStr[i] == '/' )tempStr[i] = '\\';
			}
		}
	}else if (DIR_SEPARATOR == '/' ) {
		if( tempStr.find('\\') != string::npos ){
			for( int i = tempStr.size()-1; i>-1; --i){
			if( tempStr[i] == '\\' )tempStr[i] = '/';
			}
		}
	}
	//Debug::debug(Debug::filesystem,__FUNCTION__) << "Filesystem::correctSlashes() string  "<<tempStr  << endl;
    return tempStr;
}
*/

//trava para tornar a criação da instância Storage thread safe.
//Util::Thread::LockObject fileSystemLock;

static bool isZipFile(const CAbsolutePath & path){
    return path.path().find(".zip") != string::npos;
}

static bool is7zFile(const CAbsolutePath & path){
    return path.path().find(".7z") != string::npos;
}

static string userDirectory_str(){

	ostringstream str;
#ifdef WIN32
	str <<"";
#else
	str << getenv("HOME") << "/.sge/";
#endif
	return str.str();
}



template <class X>
static void append(vector<X> & destination, const vector<X> & source){
    /*
    for (typename vector<X>::const_iterator it = source.begin(); it != source.end(); it++){
        destination.push_back(*it);
    }
    */
    copy(source.begin(), source.end(), back_insert_iterator<vector<X> >(destination));
}



/* For 7z */
class LzmaContainer{
public:
    LzmaContainer(const string & path, const CAbsolutePath & start):
    path(path),
    start(start){
        allocator.Alloc = SzAlloc;
        allocator.Free = SzFree;
        allocatorTemporary.Alloc = SzAllocTemp;
        allocatorTemporary.Free = SzFreeTemp;
        if (InFile_Open(&archiveStream.file, path.c_str())){
            /* Error */
        }

        FileInStream_CreateVTable(&archiveStream);
        LookToRead_CreateVTable(&lookStream, False);

        lookStream.realStream = &archiveStream.s;
        LookToRead_Init(&lookStream);

        CrcGenerateTable();

        SzArEx_Init(&database);
        int ok = SzArEx_Open(&database, &lookStream.s, &allocator, &allocatorTemporary);
        if (ok == SZ_OK){
            /* Can read files */
            UInt16 * name = NULL;
            int tempSize = 0;
            for (int index = 0; index < database.db.NumFiles; index++){
                size_t offset = 0;
                size_t outSizeProcessed = 0;
                const CSzFileItem * file = database.db.Files + index;
                size_t length;
                if (file->IsDir){
                    continue;
                }
                length = SzArEx_GetFileNameUtf16(&database, index, NULL);
                if (length > tempSize){
                    delete[] name;
                    name = new UInt16[length];
                    memset(name, 0, length);
                }

                SzArEx_GetFileNameUtf16(&database, index, name);
                files[Utf::utf16_to_utf8(name)] = index;
            }

            delete[] name;
        }
    }

    void readFile(const CAbsolutePath & path, unsigned char ** buffer, size_t * size){
        CIsolatedPath find(path.remove(start));
        *buffer = 0;
        *size = 0;
        if (files.find(find.path()) != files.end()){
            int index = files[find.path()];
            UInt32 block = 0;
            size_t offset = 0;
            size_t processed = 0;
            int ok = SzArEx_Extract(&database, &lookStream.s, index,
                                    &block, buffer, size, &offset, &processed,
                                    &allocator, &allocatorTemporary);
            if (ok != SZ_OK){
                Debug::debug(Debug::error,__FUNCTION__) << "Could not read file from 7z archive: " << path.path() << endl;
                return;
            }
            if (offset != 0){
                memmove(*buffer, *buffer + offset, processed);
            }

            /* The original size is the size of the block buffer, but we only care
             * about the size of the actual file.
             */
            *size = processed;
        }
    }

    vector<string> getFiles(){
        vector<string> names;
        for (map<string, int>::iterator it = files.begin(); it != files.end(); it++){
            names.push_back(it->first);
        }
        return names;
    }

    string getPath() const {
        return path;
    }

    string getMount() const {
        return start.path();
    }

    long getModificationTime(const CAbsolutePath & path){
        if (files.find(path.path()) != files.end()){
            int index = files[path.path()];
            const CSzFileItem * file = database.db.Files + index; 
            if (file->MTimeDefined){
                CNtfsFileTime time = file->MTime;

                /* Divide by 10 million here? */
                return (time.Low | ((UInt64)time.High << 32)) / 10000000;

                /*
                unsigned year, mon, day, hour, min, sec;
                UInt64 v64 = (time.Low | ((UInt64)time.High << 32)) / 10000000;
                Byte ms[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
                unsigned t;
                UInt32 v;
                sec = (unsigned)(v64 % 60); v64 /= 60;
                min = (unsigned)(v64 % 60); v64 /= 60;
                hour = (unsigned)(v64 % 24); v64 /= 24;

                v = (UInt32)v64;

                const int PERIOD_4 = (4 * 365 + 1);
                const int PERIOD_100 = (PERIOD_4 * 25 - 1);
                const int PERIOD_400 = (PERIOD_100 * 4 + 1);

                year = (unsigned)(1601 + v / PERIOD_400 * 400);
                v %= PERIOD_400;

                t = v / PERIOD_100; if (t ==  4) t =  3; year += t * 100; v -= t * PERIOD_100;
                t = v / PERIOD_4;   if (t == 25) t = 24; year += t * 4;   v -= t * PERIOD_4;
                t = v / 365;        if (t ==  4) t =  3; year += t;       v -= t * 365;

                if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)){
                    ms[1] = 29;
                }

                for (mon = 1; mon <= 12; mon++){
                    unsigned s = ms[mon - 1];
                    if (v < s)
                        break;
                    v -= s;
                }

                day = (unsigned)v + 1;
                struct tm outTime;
                memset(&outTime, 0, sizeof(outTime));
                outTime.tm_sec = sec;
                outTime.tm_min = min;
                outTime.tm_hour = hour;
                outTime.tm_mday = day;
                outTime.tm_mon = mon;
                / * tm_year The number of years since 1900. * /
                outTime.tm_year = year - 1900;
                outTime.tm_isdst = -1;
                return mktime(&outTime);
                */
            }
        }

        return 0;
    }

    virtual ~LzmaContainer(){
        SzArEx_Free(&database, &allocator);
        File_Close(&archiveStream.file);
    }

    string path;
    CAbsolutePath start;

    CFileInStream archiveStream;
    CLookToRead lookStream;
    CSzArEx database;
    ISzAlloc allocator;
    ISzAlloc allocatorTemporary;

    /* Map the filename to its index in the 7z database */
    map<string, int> files;
};
/* overlays:
 * add x/y.zip
 * y.zip contains
 *   example.txt
 * try to read x/example.txt, goto y.zip
 * or y.zip could contain y/
 * 
 * z.zip contains
 *   example.txt
 *
 * how can you prevent two zip files from providing the same files?
 */
class ZipContainer{
public:
    ZipContainer(const string & path, const Filesystem::CAbsolutePath & start):
    path(path),
    start(start),
    locked(false){
        zipFile = unzOpen(path.c_str());
        if (zipFile == NULL){
            throw Exception::Filesystem::CException(__FILE__, __LINE__, "Could not open zip file");
        }

        if (unzGoToFirstFile(zipFile) != UNZ_OK){
            throw Exception::Filesystem::CException(__FILE__, __LINE__, "Could not get to first file");
        }

        do{
            char filename[1024];
            unz_file_info fileInfo;
            unzGetCurrentFileInfo(zipFile, &fileInfo, filename, sizeof(filename), NULL, 0, NULL, 0);
            files.push_back(string(filename));

        } while (unzGoToNextFile(zipFile) != UNZ_END_OF_LIST_OF_FILE);

        /*
        zlib_filefunc64_32_def functions;
        functions.open_file_func = __real_open;
        functions.tell_file_func = __real_lseek;
        functions.seek_file_func = __real_lseek;
        */
        /*
        unzFile zip = unzOpen(path.c_str());
        unz_global_info info;
        if (unzGetGlobalInfo(zip, &info) == UNZ_OK){
            Debug::debug(Debug::error,__FUNCTION__) << "Entries: " << info.number_entry << endl;
        }

        if (unzGoToFirstFile(zip) != UNZ_OK){
            throw Exception(__FILE__, __LINE__, "Could not get to first file");
        }
        do{
            char filename[1024];
            unz_file_info fileInfo;
            unzGetCurrentFileInfo(zip, &fileInfo, filename, sizeof(filename), NULL, 0, NULL, 0);
            Debug::debug(Debug::error,__FUNCTION__) << "Got file " << filename << endl;
            Debug::debug(Debug::error,__FUNCTION__) << " Compressed " << fileInfo.compressed_size << " uncompressed " << fileInfo.uncompressed_size << endl;

        } while (unzGoToNextFile(zip) != UNZ_END_OF_LIST_OF_FILE);
        unzClose(zip);
        */
    }

    ~ZipContainer(){
        if (zipFile != NULL){
            unzClose(zipFile);
        }
    }

    string getPath() const {
        return path;
    }

    string getMount() const {
        return start.path();
    }

    long modificationTime(){
        char filename[1024];
        unz_file_info fileInfo;
        unzGetCurrentFileInfo(zipFile, &fileInfo, filename, sizeof(filename), NULL, 0, NULL, 0);
        struct tm outTime;
        memset(&outTime, 0, sizeof(outTime));
        outTime.tm_sec = fileInfo.tmu_date.tm_sec;
        outTime.tm_min = fileInfo.tmu_date.tm_min;
        outTime.tm_hour = fileInfo.tmu_date.tm_hour;
        outTime.tm_mday = fileInfo.tmu_date.tm_mday;
        outTime.tm_mon = fileInfo.tmu_date.tm_mon;
        /* tm_year The number of years since 1900. */
        outTime.tm_year = fileInfo.tmu_date.tm_year - 1900;
        outTime.tm_isdst = -1;
        return mktime(&outTime);
    }

    void findFile(const CAbsolutePath & file){
        CIsolatedPath find(file.remove(start));
        if (unzLocateFile(zipFile, find.path().c_str(), 2) != UNZ_OK){
            Debug::debug(Debug::error,__FUNCTION__) << "Could not find " << find.path() << endl;
        } else {
			Debug::debug(Debug::filesystem,__FUNCTION__) << "Found " << find.path() << " in zip file " << path << endl;
        }
    }

    int currentFileSize(){
        char filename[1024];
        unz_file_info fileInfo;
        unzGetCurrentFileInfo(zipFile, &fileInfo, filename, sizeof(filename), NULL, 0, NULL, 0);
        return fileInfo.uncompressed_size;
    }

    int read(char * buffer, int size){
        // Debug::debug(Debug::error,__FUNCTION__) << "offset before read " << unzGetOffset(zipFile) << " tell " << unztell(zipFile) << endl;
        int got = unzReadCurrentFile(zipFile, buffer, size);
        // Debug::debug(Debug::error,__FUNCTION__) << "offset after read " << unzGetOffset(zipFile) << " tell " << unztell(zipFile) << endl;
        if (got <= 0){
			throw Exception::Filesystem::CException(__FILE__, __LINE__, "Could not read bytes from zip");
        }
        return got;
    }

    long tell(){
        return unztell(zipFile);
    }

    void open(const CAbsolutePath & file){
        if (locked){
            ::std::ostringstream out;
            char filename[1024];
            unz_file_info fileInfo;
            unzGetCurrentFileInfo(zipFile, &fileInfo, filename, sizeof(filename), NULL, 0, NULL, 0);
            out << "Could not open zip file entry " << file.path() << " because a zip file is already open: " << filename;
            throw Exception::Filesystem::CException(__FILE__, __LINE__, out.str());
        }
        findFile(file);
        if (unzOpenCurrentFile(zipFile) != UNZ_OK){
            ::std::ostringstream out;
            out << "Could not open zip file entry " << file.path();
            throw Exception::Filesystem::CException(__FILE__, __LINE__, out.str());
        }
        locked = true;
    }

    void close(){
        unzCloseCurrentFile(zipFile);
        locked = false;
    }

    vector<string> getFiles() const {
        return files;
    }

protected:
    /* Path to the zip file itself */
    const string path;
    /* Where overlay starts */
    const CAbsolutePath start;

    unzFile zipFile;
    vector<string> files;
    /* Only one file can be opened at a time, so if another file is opened
     * while locked=true then throw an error
     */
    bool locked;
};

class ZipFile: public File {
public:
    ZipFile(const CAbsolutePath & path, const Util::CReferenceCount<ZipContainer> & zip):
        path(path),
        zip(zip),
        atEof(false),
        position(0){
            zip->open(path);
        }

    virtual ~ZipFile(){
        zip->close();
    }

    long getModificationTime(){
        return zip->modificationTime();
    }

    Token * location(){
        Token * head = new Token();
        *head << "container";
        /* container zipfile mount-point file-inside-zip */
        *head << zip->getPath();
        *head << zip->getMount();
        *head << path.path();
        return head;
    }
        
    long seek(long where, int whence){
        /* It seems that minizip is not capable of seeking in a specific file in a zip
         * container so we have to re-open the file and read `position' bytes to
         * emulate the seek behavior.
         */
        switch (whence){
            case SEEK_SET: {
                if (where >= position){
                    /* Read bytes until we hit the offset */
                    position += skipBytes(where - position);
                } else {
                    zip->close();
                    zip->open(path);
                    /* re-open file and read where bytes */
                    position = skipBytes(where);
                }
                break;
            }
            case SEEK_CUR: {
                position += skipBytes(where);
                break;
            }
            case SEEK_END: {
                return seek(getSize() + where, SEEK_SET);
                break;
            }
        }
        if (position > getSize()){
            position = getSize();
        }
        atEof = position == getSize();

        return position;
    }
        
    bool eof(){
        return atEof;
    }
        
    long tell(){
        return zip->tell();
    }

    void reset(){
        /* TODO or nothing..? */
    }

    bool canStream(){
        return false;
    }

    bool good(){
        /* FIXME */
        return true;
    }

    File & operator>>(unsigned char & c){
        readLine((char*) &c, 1);
        return *this;
    }
        
    int getSize(){
        return zip->currentFileSize();
    }
        
    int readLine(char * output, int size){
        try{
            int read = zip->read(output, size);
            position += read;
            return read;
        } catch (const Exception::Filesystem::CException & nomore){
            atEof = true;
            return 0;
        }
    }

    protected:
        /* skips `bytes'.
         * returns number of bytes skipped (may be less than bytes)
         */
    int skipBytes(int bytes){
        char dummy[1024];
        int total = 0;
        while (bytes > 0){
            /* Calls the zip file directly here so we don't mess up position */
            int read = zip->read(dummy, bytes > sizeof(dummy) ? sizeof(dummy) : bytes);
            total += read;
            if (read == 0){
                return total;
            }
            bytes -= read;
        }
        return total;
    }

    const CAbsolutePath path;
    const Util::CReferenceCount<ZipContainer> zip;
    bool atEof;
    /* keep track of bytes read so we can seek easier */
    int position;
};
//=======StringFile==================

StringFile::StringFile(const std::string & start):
data(start),
stream(start){
    stream >> noskipws;
}

Token * StringFile::location(){
    Token * head = new Token();
    *head << "<string file>";
    return head;
}

long StringFile::getModificationTime(){
    /* FIXME: maybe return INT_MAX or something? */
    return 0;
}

void StringFile::reset(){
    /* TODO or nothing..? */
}

int StringFile::readLine(char * output, int size){
    stream.read(output, size);
    return stream.gcount();
}

bool StringFile::canStream(){
    return true;
}

int StringFile::getSize(){
    return data.size();
}

long StringFile::tell(){
    return stream.tellg();
}

long StringFile::seek(long position, int whence){
    switch (whence){
        case SEEK_SET: stream.seekg(position, ios::beg); break;
        case SEEK_CUR: stream.seekg(position, ios::cur); break;
        case SEEK_END: stream.seekg(position, ios::end); break;
    }
    return stream.tellg();
}

bool StringFile::eof(){
    return stream.eof();
}

bool StringFile::good(){
    return stream.good();
}

File & StringFile::operator>>(unsigned char & c){
    stream >> c;
    return *this;
}

StringFile::~StringFile(){
}
//============== Endianes Readers =========================


/* will read upto 'length' bytes unless a null byte is seen first */
string EndianReader::readStringX(int length){
    ostringstream out;
    uint8_t letter = readByte1();
    while (letter != 0 && length > 0){
        out << letter;
        letter = readByte1();
        length -= 1;
    }
    return out.str();
}

/* unconditionally reads 'length' bytes */
std::string EndianReader::readString2(int length){
    ostringstream out;
    vector<uint8_t> bytes = readBytes(length);
    for (vector<uint8_t>::iterator it = bytes.begin(); it != bytes.end(); it++){
        char byte = *it;
        if (byte == 0){
            break;
        }
        out << *it;
    }
    return out.str();
}
            
void EndianReader::seekEnd(streamoff where){
    internal->seekEnd(where);
}

void EndianReader::seek(streampos where){
    internal->seek(where);
}

int EndianReader::position(){
    return internal->tell();
}
            
void EndianReader::readBytes(uint8_t * out, int length){
    internal->read((char*) out, length);
}

vector<uint8_t> EndianReader::readBytes(int length){
    vector<uint8_t> bytes;
    for (int i = 0; i < length; i++){
        uint8_t byte = 0;
        internal->read((char*) &byte, 1);
        if (internal->eof()){
            throw Eof();
        } else {
        }
        bytes.push_back(byte);
    }
    return bytes;
}

EndianReader::Internal::Internal(){
}

EndianReader::Internal::~Internal(){
}

bool EndianReader::StreamInternal::eof(){
    return stream.eof();
}

int EndianReader::StreamInternal::read(char * data, int length){
    stream.read(data, length);
    return stream.gcount();
}

void EndianReader::StreamInternal::seekEnd(std::streamoff where){
    stream.seekg(where, ios::end);
}

void EndianReader::StreamInternal::seek(std::streamoff where){
    stream.seekg(where);
}

int EndianReader::StreamInternal::tell(){
    return stream.tellg();
}

EndianReader::StreamInternal::~StreamInternal(){
}

bool EndianReader::FileInternal::eof(){
    return file->eof();
}

void EndianReader::FileInternal::seekEnd(std::streamoff where){
    file->seek(where, SEEK_END);
}

void EndianReader::FileInternal::seek(std::streamoff where){
    file->seek(where, SEEK_SET);
}

int EndianReader::FileInternal::read(char * data, int length){
    return file->readLine(data, length);
}

int EndianReader::FileInternal::tell(){
    return file->tell();
}

EndianReader::FileInternal::~FileInternal(){
}




//========


Descriptor::Descriptor(){
}

Descriptor::~Descriptor(){
}

class ZipDescriptor: public Descriptor {
public:
    ZipDescriptor(const CAbsolutePath & path, const Util::CReferenceCount<ZipContainer> & container):
    path(path),
    container(container){
    }

    CAbsolutePath path;
    Util::CReferenceCount<ZipContainer> container;

    using Descriptor::open;
    virtual Util::CReferenceCount<File> open(File::Access mode){
        return Util::CReferenceCount<File>(new ZipFile(path, container));
    }

    virtual ~ZipDescriptor(){
    }
};

/* Extracts an entire file from a 7z archive into memory */
class LzmaFile: public File {
public:
    LzmaFile(const CAbsolutePath & path, const Util::CReferenceCount<LzmaContainer> & container):
    path(path),
    container(container),
    position(0),
    memory(NULL),
    size(0){
        container->readFile(path, &memory, &size);
    }

    virtual ~LzmaFile(){
        SzFree(NULL, memory);
    }

    bool eof(){
        return position >= size;
    }

    virtual bool good(){
        return memory != NULL;
    }

    virtual int getSize(){
        return size;
    }

    virtual bool canStream(){
        return true;
    }

    virtual void reset(){
        /* nothing */
    }

    virtual long tell(){
        return position;
    }

    virtual Token * location(){
        Token * head = new Token();
        *head << "container";
        /* container zipfile mount-point file-inside-zip */
        *head << container->getPath();
        *head << container->getMount();
        *head << path.path();
        return head;

    }

    virtual long getModificationTime(){
        return container->getModificationTime(path);
    }

    virtual long seek(long position, int whence){
        switch (whence){
            case SEEK_SET: this->position = position; break;
            case SEEK_CUR: this->position += position; break;
            case SEEK_END: this->position = this->size + position; break;
        }
        if (this->position < 0){
            this->position = 0;
        }
        if (this->position > size){
            this->position = size;
        }
        return this->position;
    }

    virtual File & operator>>(unsigned char & out){
        if (this->position < size){
            out = memory[position];
            position += 1;
        }
        return *this;
    }

    virtual int readLine(char * output, int size){
        if (size > (this->size - this->position)){
            size = this->size - this->position;
        }
        memmove(output, memory + this->position, size);
        this->position += size;
        return size;
    }

protected:
    const CAbsolutePath path;
    const Util::CReferenceCount<LzmaContainer> container;
    /* keep track of bytes read so we can seek easier */
    int position;
        
    unsigned char * memory;
    size_t size;
};

class LzmaDescriptor: public Descriptor {
public:
    LzmaDescriptor(const CAbsolutePath & path, const Util::CReferenceCount<LzmaContainer> & container):
    path(path),
    container(container){
    }

    CAbsolutePath path;
    Util::CReferenceCount<LzmaContainer> container;

    using Descriptor::open;
    virtual Util::CReferenceCount<File> open(File::Access mode){
        return Util::CReferenceCount<File>(new LzmaFile(path, container));
    }

    virtual ~LzmaDescriptor(){
    }
};

/* Keep this updated with all the supported container types */
bool isContainer(const CAbsolutePath & path){
	return checkExtension( path.path()) == "zip" ||
           checkExtension( path.path()) == "7z";
}

vector<std::string> containerTypes(){
    vector<string> types;
    types.push_back("zip");
    types.push_back("7z");
    return types;
}

std::string readFile(const CAbsolutePath & path){
    Util::CReferenceCount<Filesystem::File> file = Filesystem::getInstance().open(path);
    if (file != NULL){
        char * data = new char[file->getSize() + 1];
        file->readLine(data, file->getSize());
        data[file->getSize()] = 0;
        std::string out(data);
        delete[] data;
        return out;
    }
    std::ostringstream out;
    out << "Could not open file " << path.path();
	throw Exception::Filesystem::CException(__FILE__, __LINE__, out.str());
}

//======================CStorage==========================

CStorage::CStorage(){
}

CStorage::~CStorage(){
}

vector<Filesystem::CAbsolutePath> CStorage::getFiles(const Filesystem::CAbsolutePath & dataPath, const Filesystem::CRelativePath & find, bool caseInsensitive){
    if (find.isFile()){
        return getFiles(dataPath, find.path(), caseInsensitive);
    }

    /* split the path into its consituent parts
     * a/b/c -> a/b and c
     * search for a/b, then search for c in the results
     */
    Filesystem::CRelativePath directory = find.getDirectory();
    Filesystem::CRelativePath file = find.getFilename();

    vector<Filesystem::CAbsolutePath> more = getFiles(dataPath, directory, caseInsensitive);
    vector<Filesystem::CAbsolutePath> out;
    for (vector<Filesystem::CAbsolutePath>::iterator it = more.begin(); it != more.end(); it++){
        Filesystem::CAbsolutePath path = *it;
        /* if its not a directory then we can't keep searching */
        if (isDirectory(path.path())){
            vector<Filesystem::CAbsolutePath> findMore = getFiles(path, file, caseInsensitive);
            out.insert(out.end(), findMore.begin(), findMore.end());
        }
    }
    return out;
}

Util::CReferenceCount<CStorage> self;

CStorage & getInstance(){
//	 Util::Thread::ScopedLock scoped(fileSystemLock);
	Debug::debug(Debug::filesystem,__FUNCTION__)  << " BEGIN" << endl;
	if (self != NULL){
        return *self;
    }
	Debug::debug(Debug::filesystem,__FUNCTION__)  << " - CREATING NEW FILESYSTEM OBJECT" << endl;
    self = new CGameFileSystem(Util::getDataPath2());
    return *self;
}

bool hasInstance(){
    // return true;
    return self != NULL;
}

CStorage & setInstance(const Util::CReferenceCount<CStorage> & what){
    self = what;
    return *self;
}


} //END NAMESPACE FILESYSTEM


//===============  CGameFileSystem =================

CGameFileSystem::CGameFileSystem(const AbsolutePath & path):
dataPath(path){
	Debug::debug(Debug::filesystem,__FUNCTION__) << "  CONSTRUCTOR dataPath:  "<< dataPath.path()<< endl;

}


#ifdef _WIN32


Filesystem::CAbsolutePath CGameFileSystem::userDirectory(){
    ostringstream str;
    char path[MAX_PATH];
    SHGetSpecialFolderPathA(0, path, CSIDL_APPDATA, false);
    str << path << "";
    return Filesystem::CAbsolutePath(str.str());
}

Filesystem::CAbsolutePath CGameFileSystem::configFile(){
	return CConfiguration::getEngineConfigFile();
}
#else
Filesystem::CAbsolutePath CGameFileSystem::configFile(){
    ostringstream str;
    /* what if HOME isn't set? */
    str << getenv("HOME") << "/.sgfgamerc";
    return Filesystem::CAbsolutePath(str.str());
}

Filesystem::CAbsolutePath CGameFileSystem::userDirectory(){
    ostringstream str;
    /* what if HOME isn't set? */
    str << getenv("HOME") << "/.sge/";
    return Filesystem::CAbsolutePath(str.str());
}
#endif

vector<Filesystem::CAbsolutePath> CGameFileSystem::findDirectories(const Filesystem::CRelativePath & path) {
   typedef vector<Filesystem::CAbsolutePath> Paths;
    Paths dirs;

    Paths main_dirs = findDirectoriesIn(dataPath.join(path));
    Paths user_dirs = findDirectoriesIn(userDirectory().join(path));
    Paths here_dirs = findDirectoriesIn(Filesystem::CAbsolutePath(path.path()));

    dirs.insert(dirs.end(), main_dirs.begin(), main_dirs.end());
    dirs.insert(dirs.end(), user_dirs.begin(), user_dirs.end());
    dirs.insert(dirs.end(), here_dirs.begin(), here_dirs.end());

    return dirs;

}

vector<Filesystem::CAbsolutePath> CGameFileSystem::findDirectoriesIn(const Filesystem::CAbsolutePath & path){
    vector<Filesystem::CAbsolutePath> dirs;
    DIR * dir = opendir(path.path().c_str());
    if (dir == NULL){
        return dirs;
    }

    struct dirent * entry = readdir(dir);
    while (entry != NULL){
        if (string(entry->d_name) != "." && string(entry->d_name) != ".."){
            string total = path.path() + "/" + entry->d_name;
            if (Filesystem::isDirectory(total)){
                dirs.push_back(Filesystem::CAbsolutePath(total));
            }
        }
        entry = readdir(dir);
    }

    closedir(dir);

    return dirs;
}

Filesystem::CRelativePath CGameFileSystem::cleanse(const Filesystem::CAbsolutePath & path){
    string str = path.path();
    if (str.find(dataPath.path()) == 0){
        str.erase(0, dataPath.path().length());
    } else if (str.find(userDirectory().path()) == 0){
        str.erase(0, userDirectory().path().length());
    }
    return Filesystem::CRelativePath(str,false);
}

vector<Filesystem::CAbsolutePath> CGameFileSystem::getAllDirectories(const Filesystem::CAbsolutePath & path){
	vector<Filesystem::CAbsolutePath> all = findDirectoriesIn(path);
    vector<Filesystem::CAbsolutePath> final;
    append(final, all);
    for (vector<Filesystem::CAbsolutePath>::iterator it = all.begin(); it != all.end(); it++){
        vector<Filesystem::CAbsolutePath> more = getAllDirectories(*it);
        append(final, more);
    }
    return final;
}
vector<Filesystem::CAbsolutePath> CGameFileSystem::getFilesRecursive(const Filesystem::CAbsolutePath & dataPath, const string & find, bool caseInsensitive){
    vector<Filesystem::CAbsolutePath> directories = getAllDirectories(dataPath);
    directories.push_back(dataPath);
    vector<Filesystem::CAbsolutePath> files;
    for (vector<Filesystem::CAbsolutePath>::iterator it = directories.begin(); it != directories.end(); it++){
        vector<Filesystem::CAbsolutePath> found = getFiles(*it, find, caseInsensitive);
        append(files, found);
    }
    return files;
}

#if 0
Filesystem::CAbsolutePath CGameFileSystem::lookup(const Filesystem::CRelativePath path){
    vector<Filesystem::CAbsolutePath> places;

#define push(x) try{ places.push_back(x); } catch (const Filesystem::CIllegalPath & fail){ }
    push(dataPath.join(path));
    push(userDirectory().join(path));
    push(Filesystem::CAbsolutePath(path.path()));
#undef push

    /* start error stuff early */
    ostringstream out;
    out << "Cannot find " << path.path() << ". I looked in ";
    bool first = true;
    for (vector<Filesystem::CAbsolutePath>::iterator it = places.begin(); it != places.end(); it++){
        Filesystem::CAbsolutePath & final = *it;
        if (::Filesystem::readable(final.path())){
            return final;
        }
        if (!first){
            out << ", ";
        } else {
            first = false;
        }
        out << "'" << final.path() << "'";
    }

    // out << "Cannot find " << path.path() << ". I looked in '" << dataPath.join(path).path() << "', '" << userDirectory().join(path).path() << "', and '" << path.path() << "'";

    throw NotFound(__FILE__, __LINE__, out.str());


#if 0
    /* first try the main data directory */
    Filesystem::CAbsolutePath final = dataPath.join(path);
    if (::System::readable(final.path())){
        return final;
    }
    /* then try the user directory, like ~/.sge */
    final = userDirectory().join(path);
    if (::System::readable(final.path())){
        return final;
    }
    /* then just look in the cwd */
    if (::System::readable(path.path())){
        return Filesystem::CAbsolutePath(path.path());
    }

    ostringstream out;
    out << "Cannot find " << path.path() << ". I looked in '" << dataPath.join(path).path() << "', '" << userDirectory().join(path).path() << "', and '" << path.path() << "'";

    throw NotFound(__FILE__, __LINE__, out.str());
#endif
}
#endif

Filesystem::CAbsolutePath CGameFileSystem::lookup(const Filesystem::CPath *path){
    Debug::debug(Debug::filesystem,__FUNCTION__) << " Will try to find: '" << path->path() << "'" << endl;
	if (path->getType()=="relative") {
	//Fisrt Try the path.
	if (((RelativePath *)path)->isComplete && path->exist()) {
		return Filesystem::CAbsolutePath(((RelativePath *)path)->completePath());
	}else if (((RelativePath *)path)->isComplete && !path->exist()) {
    Debug::debug(Debug::filesystem,__FUNCTION__) << "---------VERIFY IF IMPLEMETATION IS CORRECT 1----------------" <<endl;
	ostringstream out;
	//Debug::debug(Debug::error,__FUNCTION__) << "Cannot find " << path.path() << ". I looked in '" << dataPath.join(path).path() << "', '" << userDirectory().join(path).path() << "', and '" << path.path() << "'"<<endl;
	out << "CAbsolutePath lookup: CANNOT FIND " << ((RelativePath *)path)->path() << ". I looked in '" << dataPath.join(*(RelativePath *)path).path() << "', '" << userDirectory().join(*(RelativePath *)path).path() << "', and '" << ((RelativePath *)path)->path() << "'"<<endl;
	throw ::SGF::Exception::Filesystem::CNotFound(__FILE__, __LINE__, out.str());
		
	}else if (!((RelativePath *)path)->isComplete && path->exist()) {
		Debug::debug(Debug::filesystem,__FUNCTION__) << "---------VERIFY IF IMPLEMETATION IS CORRECT 2----------------" <<endl;
		// SÓ TEM QUE COMPLETAR O CAMINHO E RETORNAR
		Filesystem::CAbsolutePath(((RelativePath *)path)->path());
	}else if  (!((RelativePath *)path)->isComplete && !path->exist()) {
  		Filesystem::CAbsolutePath final;
		/* first try the current directory */
		final.localJoin(*(RelativePath *)path);
		Debug::debug(Debug::filesystem,__FUNCTION__) << "Try in current directory : '" << final.path() << "'" << endl;
		if (final.exist()) return final;
		Debug::debug(Debug::filesystem,__FUNCTION__) << " Try in current directory NOT FOUND: " << endl;
	    Debug::debug(Debug::filesystem,__FUNCTION__) << "--------------------------------------------------------" <<endl;
	    Debug::debug(Debug::filesystem,__FUNCTION__) << " Try in Main Data directory : "<< endl;
		/* then try the main data directory */
		Filesystem::CAbsolutePath dataP = dataPath.join(*(RelativePath *)path);
		Debug::debug(Debug::filesystem,__FUNCTION__) << "  Try in Main  Data directory dataPAth From CGameFilesystem:  "<< dataP.path()<< endl;

		if (dataP.exist()) return dataP;

		Debug::debug(Debug::filesystem,__FUNCTION__) << " Try in Main Data directory NOT FOUND: " << endl;
		Debug::debug(Debug::filesystem,__FUNCTION__) << "--------------------------------------------------------" <<endl;
	    Debug::debug(Debug::filesystem,__FUNCTION__) << " Try in Main GAmeEngine directory " << endl;
		/* then try the main GameEngine directory */
		final = Util::getGamePath();
		final.localJoin(*(RelativePath *)path);

		Debug::debug(Debug::filesystem,__FUNCTION__) << " Try in Main GAmeEngine directory : '" << final.path() << "'" << endl;
		if (final.exist()) return final;
		Debug::debug(Debug::filesystem,__FUNCTION__) << " Try in Main GameEngine NOT FOUND: " << endl;
		Debug::debug(Debug::filesystem,__FUNCTION__) << "--------------------------------------------------------" <<endl;
	   	Debug::debug(Debug::filesystem,__FUNCTION__) << " Try in User directory : '" << final.path() << "'" << endl;

		/* then try the user directory, like ~/.sge */
		final = userDirectory().join(*(RelativePath *)path);
		if (final.exist()) return final;
       Debug::debug(Debug::filesystem,__FUNCTION__) << " Try in User CDirectory NOT FOUND: " << endl;
	   Debug::debug(Debug::filesystem,__FUNCTION__) << "--------------------------------------------------------" <<endl;
	   Debug::debug(Debug::filesystem,__FUNCTION__) << " Try in CWD only - IS NOT A ABSOLUTE PATH : '" << final.path() << "'" << endl;
		/* then just look in the cwd */
		final = Filesystem::CAbsolutePath(((RelativePath *)path)->path());
		if (final.exist()) return final;

		ostringstream out;
		//Debug::debug(Debug::error,__FUNCTION__) << "Cannot find " << path.path() << ". I looked in '" << dataPath.join(path).path() << "', '" << userDirectory().join(path).path() << "', and '" << path.path() << "'"<<endl;
		out << "CAbsolutePath lookup: CANNOT FIND " << ((RelativePath *)path)->path() << ". I looked in '" << dataPath.join(*(RelativePath *)path).path() << "', '" << userDirectory().join(*(RelativePath *)path).path() << "', and '" << ((RelativePath *)path)->path() << "'"<<endl;
		throw ::SGF::Exception::Filesystem::CNotFound(__FILE__, __LINE__, out.str());
		}
	}
}

Filesystem::CAbsolutePath CGameFileSystem::findInsensitive(const Filesystem::CIsolatedPath & newpath){
	Debug::debug(Debug::filesystem,__FUNCTION__) << "findInsensitive: '" << newpath.path() << "'" << endl;
	/* try sensitive lookup first */
    Filesystem::CRelativePath path(newpath.path());
	Debug::debug(Debug::filesystem,__FUNCTION__) << "Trying sensitive Lookup First: '"  << endl;
	if(path.exist()) return path;

    Debug::debug(Debug::filesystem,__FUNCTION__) << "Trying geting base directory: '"  << endl;
    /* get the base directory */
    RelativePath temp = path.getDirectory();
    Filesystem::CAbsolutePath directory = lookup(&temp);
    return lookupInsensitive(directory, newpath.getFilename());
}
Filesystem::CAbsolutePath CGameFileSystem::findInsensitive(const Filesystem::CAbsolutePath & newpath){
	Debug::debug(Debug::filesystem,__FUNCTION__) << "findInsensitive: '" << newpath.path() << "'" << endl;

	return findInsensitive(Filesystem::CIsolatedPath(newpath.path()));
}

//! Dado um diretorio, procura cada arquivo neste diretório e compara com o nome do arquivo passado
Filesystem::CAbsolutePath CGameFileSystem::lookupInsensitive(const Filesystem::CAbsolutePath & directory, const Filesystem::CIsolatedPath & path){
    Debug::debug(Debug::filesystem,__FUNCTION__) << "lookupInsensitive: Must verify de existence of the file inside de directory:'" << endl;
	Debug::debug(Debug::filesystem,__FUNCTION__) << "lookupInsensitive: CAbsolutePAth= '" << directory.path()<< "'"<<" file :"<< path.path() << endl;

	if (path.path() == ""){
        throw ::SGF::Exception::Filesystem::CNotFound(__FILE__, __LINE__, "Given empty path to lookup");

    }
	if (path.isFile()){
        vector<Filesystem::CAbsolutePath> all = getFiles(directory, "*", true);
        for (vector<Filesystem::CAbsolutePath>::iterator it = all.begin(); it != all.end(); it++){
            Filesystem::CAbsolutePath & check = *it;
			Debug::debug(Debug::filesystem,__FUNCTION__) << "File: '"<<check.getFilename().path() <<" and file2: "<< path.path() << endl;

            if (Filesystem::CInsensitivePath(check.getFilename()) == path){
               Debug::debug(Debug::filesystem,__FUNCTION__) << "lookupInsensitive: Returning= '" << check.path() << endl;

				return check;
            }
        }

        ostringstream out;
        out << "lookupInsensitive: Cannot find " << path.path() << " in " << directory.path();
        // Debug::debug(Debug::filesystem,__FUNCTION__) << out;
		throw ::SGF::Exception::Filesystem::CNotFound(__FILE__, __LINE__, out.str());

    } else {

		return lookupInsensitive(lookupInsensitive(directory, path.firstDirectory()), path.removeFirstDirectory());
    }
}

Filesystem::CAbsolutePath CGameFileSystem::find(const Filesystem::CIsolatedPath & path){

	Debug::debug(Debug::filesystem,__FUNCTION__) << "  -  Path to find: " << path.path() <<endl;
	if (path.isEmpty()){
        throw ::SGF::Exception::Filesystem::CNotFound(__FILE__, __LINE__, "No path given");

    }
	Filesystem::CRelativePath newPath(path.path(),false);
    Filesystem::CAbsolutePath out = lookup(&newPath);
    /*if (isDirectory(out.path())){
		  return Filesystem::CAbsolutePath(out.path() + "/");
    }
    return Filesystem::CAbsolutePath(out.path());
	*/
	return out;
}

Filesystem::CAbsolutePath CGameFileSystem::find(const Filesystem::CRelativePath & path){

	Debug::debug(Debug::filesystem,__FUNCTION__) << "  -  Path to find: " << path.path() <<endl;
	if (path.isEmpty()){
        throw ::SGF::Exception::Filesystem::CNotFound(__FILE__, __LINE__, "No path given");

    }
	Filesystem::CAbsolutePath out = lookup(&path);
    /*if (isDirectory(out.path())){
		  return Filesystem::CAbsolutePath(out.path() + "/");
    }
    return Filesystem::CAbsolutePath(out.path());
	*/
	return out;
}

//====================NormalFile =============================


class NormalFile: public Filesystem::File {
public:
    NormalFile(const Filesystem::CAbsolutePath & path, Access mode = Read):
        path(path){
            ios_base::openmode iosMode = fstream::in;
            switch (mode){
                case Read: iosMode = fstream::in; check(path); break;
                case Write: iosMode = fstream::out; break;
                case ReadWrite: iosMode = fstream::in | fstream::out; check(path); break;
            }

            in.open(path.path().c_str(), iosMode | fstream::binary);
            if (in.good()){
                in >> noskipws;
            }
        }

    Token * location(){
        Token * head = new Token();
        *head << "file";
        *head << path.path();
        return head;
    }

    /* Throws NotFound if path doesnt exist */
    void check(const Filesystem::CAbsolutePath & path){
		if (!path.exist()){
            ostringstream out;
            out << "Could not find '" << path.path() << "'";
            throw Exception::Filesystem::CNotFound(__FILE__, __LINE__, out.str());
        }
    }

    long getModificationTime(){
        return 0;//::System::getModificationTime(path.path());
    }

    bool canStream(){
        return true;
    }

    long tell(){
        return in.tellg();
    }

    void reset(){
        in.clear();
    }

    long seek(long position, int whence){
        switch (whence){
            case SEEK_SET: in.seekg(position, ios::beg); break;
            case SEEK_CUR: in.seekg(position, ios::cur); break;
            case SEEK_END: in.seekg(position, ios::end); break;
        }
        return in.tellg();
    }

    bool eof(){
        return in.eof();
    }

    int getSize(){
        streampos here = in.tellg();
        in.seekg(0, ios::end);
        int length = in.tellg();
        in.seekg(here, ios::beg);
        return length;
    }

    bool good(){
        return in.good();
    }

    Filesystem::File & operator>>(unsigned char & c){
        in >> c;
        return *this;
    }

    int readLine(char * output, int size){
        in.read(output, size);
        return in.gcount();
    }

    ~NormalFile(){
        in.close();
    }

protected:
    const Filesystem::CAbsolutePath path;
    std::fstream in;
};

//============================================================
bool CGameFileSystem::exists(const Filesystem::CRelativePath & path){
    try{
		Debug::debug(Debug::filesystem,__FUNCTION__) << " Will verify is this file exists: " << path.path() << endl;
		Filesystem::CAbsolutePath absolute = find(path);
        return true;
    } catch (const ::SGF::Exception::Filesystem::CNotFound & found){
        return false;
    }
}

bool CGameFileSystem::exists(const Filesystem::CAbsolutePath & path){

	   return Filesystem::readable(path.path());
}

vector<Filesystem::CAbsolutePath> CGameFileSystem::getFiles(const Filesystem::CAbsolutePath & dataPath, const string & find, bool caseInsensitive){
    Util::Thread::ScopedLock scoped(lock);
	vector<Filesystem::CAbsolutePath> files;
	vector<string> filesvector;
	Filesystem::getFiles(dataPath.path(),find, filesvector);
	//Debug::debug(Debug::menu,__FUNCTION__) << "FOUND: "<< filesvector.size()<<" files." << endl;
   
	for (vector<string>::iterator it = filesvector.begin(); it!=filesvector.end(); ++it) {
		// Debug::debug(Debug::menu,__FUNCTION__) << "FOUND: "<< (*it) << endl;
   
          files.push_back(Filesystem::CAbsolutePath((*it)));
	}
	Debug::debug(Debug::menu,__FUNCTION__) << "FOUND: "<< files.size()<<" files." << endl;
   
   
  return files;

}


vector<Filesystem::CAbsolutePath> CGameFileSystem::getContainerFilesRecursive(const Filesystem::CAbsolutePath & dataPath){
    vector<Filesystem::CAbsolutePath> out;

    vector<Filesystem::CAbsolutePath> zips = getFilesRecursive(dataPath, "*.zip");
    out.insert(out.end(), zips.begin(), zips.end());
    zips = getFilesRecursive(dataPath, "*.7z");
    out.insert(out.end(), zips.begin(), zips.end());

    return out;
}
        
vector<Filesystem::CAbsolutePath> CGameFileSystem::getContainerFiles(const AbsolutePath & dataPath){
    vector<Filesystem::CAbsolutePath> out;

    vector<Filesystem::CAbsolutePath> zips = getFiles(dataPath, "*.zip");
    out.insert(out.end(), zips.begin(), zips.end());
    zips = getFiles(dataPath, "*.7z");
    out.insert(out.end(), zips.begin(), zips.end());

    return out;
}

vector<Filesystem::CAbsolutePath> CGameFileSystem::getContainerFiles(const Filesystem::CRelativePath & path){
    vector<Filesystem::CAbsolutePath> out;

    vector<Filesystem::CAbsolutePath> zips = getFiles(path, "*.zip", false);
    out.insert(out.end(), zips.begin(), zips.end());
    zips = getFiles(path, "*.7z", false);
    out.insert(out.end(), zips.begin(), zips.end());

    return out;
}
#if 0
Filesystem::CAbsolutePath CGameFileSystem::findContainer(const Filesystem::CRelativePath & dataPath){
    try{
        return find(Filesystem::CIsolatedPath(dataPath.path() + ".zip"));
    } catch (const Exception::Filesystem::CNotFound & fail){
    }

    try{
        return find(Filesystem::CIsolatedPath(dataPath.path() + ".7z"));
    } catch (const Exception::Filesystem::CNotFound & fail){
    }

    throw Exception::Filesystem::CNotFound(dataPath.path(), __LINE__, __FILE__);
}
#endif
Filesystem::CAbsolutePath CGameFileSystem::findContainer(const Filesystem::CIsolatedPath & dataPath){
    try{
        return find(dataPath.join(".zip"));
    } catch (const ::SGF::Exception::Filesystem::CNotFound & fail){
    }

    try{
        return find(dataPath.join(".7z"));
    } catch (const ::SGF::Exception::Filesystem::CNotFound & fail){
    }

    throw ::SGF::Exception::Filesystem::CNotFound(dataPath.path(), __LINE__, __FILE__);
}
void CGameFileSystem::overlayFile(const AbsolutePath & where, Util::CReferenceCount<Filesystem::LzmaContainer> container){
    virtualDirectory.addFile(where, Util::CReferenceCount<Filesystem::LzmaDescriptor>(new Filesystem::LzmaDescriptor(where, container)));
}

void CGameFileSystem::overlayFile(const AbsolutePath & where, Util::CReferenceCount<Filesystem::ZipContainer> zip){
    virtualDirectory.addFile(where, Util::CReferenceCount<Filesystem::ZipDescriptor>(new Filesystem::ZipDescriptor(where, zip)));
}

void CGameFileSystem::unoverlayFile(const AbsolutePath & where){
    virtualDirectory.removeFile(where);
}
template <class Container>
static void addOverlayFiles(CGameFileSystem & system, const Filesystem::CAbsolutePath & where, const Util::CReferenceCount<Container> & container){
    vector<string> files = container->getFiles();
    for (vector<string>::const_iterator it = files.begin(); it != files.end(); it++){
        string path = *it;
        Debug::debug(Debug::filesystem,__FUNCTION__) << "Add overlay to " << where.join(Filesystem::CIsolatedPath(path)).path() << endl;
        system.overlayFile(where.join(Filesystem::CIsolatedPath(path)), container);
    }
}
void CGameFileSystem::addOverlay(const Filesystem::CAbsolutePath & container, const Filesystem::CAbsolutePath & where){
    if (isZipFile(container)){
        Debug::debug(Debug::filesystem,__FUNCTION__) << "Opening zip file " << container.path() << endl;
        addOverlayFiles(*this, where, Util::CReferenceCount<Filesystem::ZipContainer>(new Filesystem::ZipContainer(container.path(), where)));
    } else if (is7zFile(container)){
        addOverlayFiles(*this, where, Util::CReferenceCount<Filesystem::LzmaContainer>(new Filesystem::LzmaContainer(container.path(), where)));
    }
}

void CGameFileSystem::removeOverlay(const Filesystem::CAbsolutePath & container, const Filesystem::CAbsolutePath & where){
    Util::CReferenceCount<Filesystem::ZipContainer> zip(new Filesystem::ZipContainer(container.path(), where));
    vector<string> files = zip->getFiles();
    for (vector<string>::const_iterator it = files.begin(); it != files.end(); it++){
        string path = *it;
        Debug::debug(Debug::filesystem,__FUNCTION__) << "Remove overlay from " << where.join(Filesystem::CRelativePath(path)).path() << endl;
        unoverlayFile(where.join(Filesystem::CRelativePath(path)));
    }
}

Util::CReferenceCount<Filesystem::File> CGameFileSystem::open(const AbsolutePath & path, Filesystem::File::Access mode){
    Util::CReferenceCount<Filesystem::Descriptor> descriptor = virtualDirectory.lookup(path);
    if (descriptor != NULL){
        return descriptor->open(mode);
    } else {
        return Util::CReferenceCount<Filesystem::File>(new NormalFile(path, mode));
    }
}



vector<string> CGameFileSystem::containerFileList(const Filesystem::CAbsolutePath & container){
    Util::CReferenceCount<Filesystem::ZipContainer> zip(new Filesystem::ZipContainer(container.path(), Filesystem::CAbsolutePath()));
    return zip->getFiles();
}


} //end SGF