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

#ifndef  ___SGF___GAME_FILE_SYSTEM
#define ___SGF___GAME_FILE_SYSTEM

#include <exception>
#include <string>


#include <vector>
#include <list>
#include <iostream>
#include <sstream>

#include "../SGF_Config.h"
#if defined(_WIN32)
#include <io.h>
#elif defined(LINUX) && !defined(ANDROID)
#include <sys/io.h>
#elif defined(ANDROID)

#endif

#include "SGF_UtilStructs.h"
#include "SGF_Pointer.h"
#include "../util/SGF_Token.h"
#include "../util/SGF_FilesystemBase.h"
#include "../util/SGF_Path.h"
#include "../util/SGF_Thread.h"

#ifndef BYTE
typedef unsigned char       BYTE;
#endif
using namespace std;
namespace SGF {
namespace Filesystem{
	class Eof: public std::exception {
        public:
            Eof(){
            }

            virtual ~Eof() throw (){
            }
    };
	/* Abstraction for files. Should be used instead of FILE, ifstream, SDL_RWOps, anything else */
    class File{
    public:
        enum Access{
            Read,
            Write,
            ReadWrite
        };

        File();
        virtual ~File();

        /* Returns the number of bytes read */
        virtual int readLine(char * output, int size) = 0;

        /* Mostly for normal files, reset their error flags so
         * we can seek after eof
         */
        virtual void reset() = 0;

        /* true if the underlying object can be streamed. generally
         * this should be true if the object can be kept around while other files
         * of the same type can be opened.
         * zip files aren't streamable because only one zip entry can be
         * open at a time so it must be closed as soon as possible.
         */
        virtual bool canStream() = 0;

        virtual long getModificationTime() = 0;

        /* seek to an absolute position */
        virtual long seek(long position, int whence) = 0;

        virtual int getSize() = 0;

        virtual long tell() = 0;

        /* Returns a token that represents the path. For normal files it will just be
         * a single string containing the path -- "data/x/y/z.txt"
         * For zip files it will be (container "x/y/z.zip" "mount/point" "a.txt")
         */
        virtual Token * location() = 0;

        /* if the file is at eof and can't read anymore */
        virtual bool eof() = 0;

        /* if the file can still be read */
        virtual bool good() = 0;

        /* read one unsigned byte */
        virtual File & operator>>(unsigned char &) = 0;
    };
    
    class EndianReader{
        public:
            EndianReader(const Util::CReferenceCount<Filesystem::File> & file){
                internal = new FileInternal(file);
            }
            
            EndianReader(ifstream & stream){
                internal = new StreamInternal(stream);
            }

            class Internal{
            public:
                Internal();
                virtual bool eof() = 0;
                virtual int read(char * data, int length) = 0;
                virtual void seekEnd(::std::streamoff where) = 0;
                virtual void seek(::std::streamoff where) = 0;
                virtual int tell() = 0;
                virtual ~Internal();
            };

            class StreamInternal: public Internal {
            public:
                StreamInternal(::ifstream & stream):
                stream(stream){
                }
                
                virtual bool eof();
                virtual int read(char * data, int length);
                virtual void seekEnd(::std::streamoff where);
                virtual void seek(::std::streamoff where);
                virtual int tell();
                virtual ~StreamInternal();

                /* Yes, use a reference here */
                ::ifstream & stream;
            };

            class FileInternal: public Internal {
            public:
                FileInternal(const Util::CReferenceCount<Filesystem::File> & file):
                file(file){
                }

                virtual bool eof();
                virtual void seekEnd(::std::streamoff where);
                virtual void seek(::std::streamoff where);
                virtual int read(char * data, int length);
                virtual int tell();
                virtual ~FileInternal();

                Util::CReferenceCount<Filesystem::File> file;
            };

            virtual ~EndianReader(){
            }

            virtual int8_t readByte1(){
                return convert(readBytes(sizeof(int8_t)));
            }

            virtual int16_t readByte2(){
                return convert(readBytes(sizeof(int16_t)));
            }

            virtual int32_t readByte4(){
                return convert(readBytes(sizeof(int32_t)));
            }

            virtual string readStringX(int length);
            virtual string readString2(int length);
            virtual void readBytes(uint8_t * out, int length);

            virtual void seekEnd(::std::streamoff where);
            virtual void seek(::std::streampos where);

            virtual int position();

        protected:
            virtual int32_t convert(const vector<uint8_t> & bytes) = 0;

            vector<uint8_t> readBytes(int length);
                
            Util::CReferenceCount<Internal> internal;
    };

    /* combines bytes b0 b1 b2 b3 as b0 + b1*2^8 + b2*2^16 + b3*2^24 */
    class LittleEndianReader: public EndianReader {
        public:
            LittleEndianReader(const Util::CReferenceCount<Filesystem::File> & file):
            EndianReader(file){
            }

            LittleEndianReader(::ifstream & stream):
            EndianReader(stream){
            }

        protected:
            virtual int32_t convert(const vector<uint8_t> & bytes){
                uint32_t out = 0;
                for (vector<uint8_t>::const_reverse_iterator it = bytes.rbegin(); it != bytes.rend(); it++){
                    out = (out << 8) + *it;
                }
                return out;
            }
    };

    /* combines bytes b0 b1 b2 b3 as b0*2^24 + b1*2^16 + b2*2^8 + b3 */
    class BigEndianReader: public EndianReader {
        public:
            BigEndianReader(const Util::CReferenceCount<Filesystem::File> & file):
            EndianReader(file){
            }
            
            BigEndianReader(::ifstream & stream):
            EndianReader(stream){
            }

        protected:
            virtual int32_t convert(const vector<uint8_t> & bytes){
                uint32_t out = 0;
                for (vector<uint8_t>::const_iterator it = bytes.begin(); it != bytes.end(); it++){
                    out = (out << 8) + *it;
                }
                return out;
            }
    };

    class LzmaContainer;
    class ZipContainer;
   
    class StringFile: public File {
    public:
        StringFile(const string & start);
        virtual int readLine(char * output, int size);
        virtual bool eof();
        virtual bool good();
        virtual int getSize();
        virtual long getModificationTime();
        virtual bool canStream();
        virtual void reset();
        virtual long tell();
        virtual Token * location();
        virtual long seek(long position, int whence);
        virtual File & operator>>(unsigned char &);
        virtual ~StringFile();

    protected:
        string data;
        ::std::istringstream stream;
    };

    /* Contains information about an abstract File. */
    class Descriptor{
    public:
        Descriptor();

        virtual Util::CReferenceCount<File> open(File::Access mode) = 0;

        virtual ~Descriptor();
    };

    class Traverser;
    class CDirectory{
    public:
        CDirectory();
        virtual ~CDirectory();
    
        /* Finds any path in the given directory that matches find, files and directories */
        vector<CAbsolutePath> findFiles(const CAbsolutePath & dataPath, const string & find, bool caseInsensitive);
        /* Only finds directories */
        vector<CAbsolutePath> findDirectories(const CAbsolutePath & dataPath, const string & find, bool caseInsensitive);

        void addFile(const CAbsolutePath & path, const Util::CReferenceCount<Descriptor> & file);
        void removeFile(const CAbsolutePath & path);

        /* FIXME: maybe filenames() should just return files? */
        /* Files + directories */
        vector<string> filenames() const;
        /* Just directories */
        vector<string> directoryNames() const;

        /* Finds a file with the given path. Will not find directories.
         * Might return NULL if the path can't be found
         */
        Util::CReferenceCount<Descriptor> lookup(const CAbsolutePath & path);

        /* true if the path (either file or directory) exists */
        bool exists(const CAbsolutePath & path);

    protected:
        void doTraverse(const CAbsolutePath & path, Traverser & traverser);
        void traverse(const CAbsolutePath & path, Traverser & traverser);

        // Util::CReferenceCount<File> doLookup(const Path::AbsolutePath & path);
		
        map<string, Util::CReferenceCount<CDirectory> > directories;
        map<string, Util::CReferenceCount<Descriptor> > files;

        Util::Thread::LockObject lock;
    };




 /**
 * \class CStorage
 *
 * \ingroup SGF_Util
 *
 * \brief Classe BAse para o Gerenciamento do systema de arquivos do computador
 *
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
	class  SGE_API CStorage{
    public:
        CStorage();
        virtual ~CStorage();

        typedef CAbsolutePath AbsolutePath;
        typedef CRelativePath RelativePath;
		typedef CIsolatedPath IsolatedPath;
        virtual AbsolutePath find(const IsolatedPath & path) = 0;
		virtual AbsolutePath find(const RelativePath & path) = 0;
		virtual RelativePath cleanse(const AbsolutePath & path) = 0;
        virtual bool exists(const RelativePath & path) = 0;
        virtual bool exists(const AbsolutePath & path) = 0;
        virtual vector<AbsolutePath> getFilesRecursive(const AbsolutePath & dataPath, const string & find, bool caseInsensitive = false) = 0;

		 /* Finds all supported container files. Currently
         *  .zip
         */
        virtual vector<AbsolutePath> getContainerFilesRecursive(const AbsolutePath & dataPath)=0;
        /* Gets container files only in the specified directory */
        virtual vector<AbsolutePath> getContainerFiles(const AbsolutePath & dataPath)=0;
        
        /* Gets container files in <user>/path ./path and <data>/path */
        virtual vector<AbsolutePath> getContainerFiles(const RelativePath & path)=0;
        
        /* Given a path with no extension, find a container file that is <name>.zip or
         * <name>.7z or whatever exists.
         * So if dataPath is "mugen/foo" this function will look for
         *  mugen/foo.zip
         *  mugen/foo.7z
         *  mugen/foo.rar
         *  ...
         *
         * and return the first one it finds
         */
        virtual AbsolutePath findContainer(const IsolatedPath & dataPath)=0;
        /* Container should be a path to a zip file */
        virtual void addOverlay(const AbsolutePath & container, const AbsolutePath & where)=0;
        virtual void removeOverlay(const AbsolutePath & container, const AbsolutePath & where)=0;
        virtual vector<string> containerFileList(const AbsolutePath & container)=0;



        /* search for a pattern of a single file within a directory */
        virtual vector<AbsolutePath> getFiles(const AbsolutePath & dataPath, const string & find, bool caseInsensitive = false) = 0;

        /* search for some path which may contain wildcards in a directory */
        virtual vector<AbsolutePath> getFiles(const AbsolutePath & dataPath, const RelativePath & find, bool caseInsensitive);
        virtual AbsolutePath configFile() = 0;
        virtual AbsolutePath userDirectory() = 0;
        virtual vector<AbsolutePath> findDirectories(const RelativePath & path) = 0;
        virtual AbsolutePath findInsensitive(const IsolatedPath & path) = 0;
        virtual AbsolutePath findInsensitive(const AbsolutePath & path) = 0;

		virtual AbsolutePath lookupInsensitive(const AbsolutePath & directory, const IsolatedPath & path) = 0;
		virtual AbsolutePath lookup(const CPath *path)=0;
        virtual Util::CReferenceCount<Filesystem::File> open(const AbsolutePath & path, Filesystem::File::Access mode = Filesystem::File::Read)=0;

	
	};
	// Lock para tornar a criação da instância Thread safe

	CStorage & getInstance();
	bool hasInstance();
    CStorage & setInstance(const ::SGF::Util::CReferenceCount<Filesystem::CStorage> & what);

	bool isContainer(const CAbsolutePath & path);

	std::string readFile(const CAbsolutePath & path);

	std::vector<std::string> containerTypes();


}// end namespace Filesystem

/**
 * \class CGameFileSystem
 *
 * \ingroup SGF_Util
 *
 * \brief Gerenciamento do systema de arquivos do computador de uma perspectiva do Jogo
 *
 * Cria um sistema de arquivos para o Jogo, com base no diretório onde o jogo roda
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class  SGE_API CGameFileSystem: public Filesystem::CStorage {

	public:
	CGameFileSystem(const Filesystem::CAbsolutePath & dataPath);

    typedef Filesystem::CAbsolutePath AbsolutePath;
    typedef Filesystem::CRelativePath RelativePath;
	typedef Filesystem::CIsolatedPath IsolatedPath;
    typedef Filesystem::CInsensitivePath InsensitivePath;
    typedef Exception::Filesystem::CException Exception;
    typedef ::SGF::Exception::Filesystem::CNotFound NotFound;

    /* given a relative path like sounds/arrow.png, prepend the proper
     * data path to it to give data/sounds/arrow.png
     */
    AbsolutePath find(const RelativePath & path);
	AbsolutePath find(const IsolatedPath & path);



    /* like `find' but ignores case */
    AbsolutePath findInsensitive(const IsolatedPath & path);
    AbsolutePath findInsensitive(const AbsolutePath & path);

    /* findInsensitive but starts in the given absolute directory path */
    AbsolutePath lookupInsensitive(const AbsolutePath & directory, const IsolatedPath & path);


    // void initialize();

    /* whether the file exists at all */
    bool exists(const RelativePath & path);
    bool exists(const AbsolutePath & path);

    /* remove the data path from a string
     * data/sounds/arrow.png -> sounds/arrow.png
     */
    RelativePath cleanse(const AbsolutePath & path);

    /* returns all the directories starting with the given path.
     * will look in the main data directory, the user directory, and
     * the current working directory.
     */
    vector<AbsolutePath> findDirectories(const RelativePath & path);

    /* user specific directory to hold persistent data */
    AbsolutePath userDirectory();

    /* user specific path to store the configuration file */
    AbsolutePath configFile();


    /* search a directory for some files matching pattern `find' */
    vector<AbsolutePath> getFiles(const AbsolutePath & dataPath, const string & find, bool caseInsensitive = false);

    /* same as getFiles but search directories recursively */
    vector<AbsolutePath> getFilesRecursive(const AbsolutePath & dataPath, const string & find, bool caseInsensitive = false);
        /* Finds all supported container files. Currently
         *  .zip
         */
        virtual vector<AbsolutePath> getContainerFilesRecursive(const AbsolutePath & dataPath);
        /* Gets container files only in the specified directory */
        virtual vector<AbsolutePath> getContainerFiles(const AbsolutePath & dataPath);
        
        /* Gets container files in <user>/path ./path and <data>/path */
        virtual vector<AbsolutePath> getContainerFiles(const RelativePath & path);
        /* Given a path with no extension, find a container file that is <name>.zip or
         * <name>.7z or whatever exists.
         * So if dataPath is "mugen/foo" this function will look for
         *  mugen/foo.zip
         *  mugen/foo.7z
         *  mugen/foo.rar
         *  ...
         *
         * and return the first one it finds
         */
        virtual AbsolutePath findContainer(const IsolatedPath & dataPath);
        /* Container should be a path to a zip file */
        virtual void addOverlay(const AbsolutePath & container, const AbsolutePath & where);
        virtual void removeOverlay(const AbsolutePath & container, const AbsolutePath & where);
        virtual vector<string> containerFileList(const AbsolutePath & container);
        virtual Util::CReferenceCount<Filesystem::File> open(const AbsolutePath & path, Filesystem::File::Access mode = Filesystem::File::Read);

    /* Should be protected but needs to be public so we can use it in template methods
     * in the implementation file.
     */


public:
        virtual void overlayFile(const AbsolutePath & where, Util::CReferenceCount<Filesystem::ZipContainer> zip);
        virtual void overlayFile(const AbsolutePath & where, Util::CReferenceCount<Filesystem::LzmaContainer> container);
protected:
    
        virtual void unoverlayFile(const AbsolutePath & where);

        // map<AbsolutePath, Util::ReferenceCount<ZipContainer> > overlays;
        Filesystem::CDirectory virtualDirectory;

protected:
    AbsolutePath lookup(const Filesystem::CPath *path);
    vector<AbsolutePath> findDirectoriesIn(const AbsolutePath & path);
    vector<AbsolutePath> getAllDirectories(const AbsolutePath & path);

protected:
	Util::Thread::LockObject lock;
    AbsolutePath dataPath;
	};

/**
 * \class ZipFileSystem
 *
 * \ingroup SGF_Util
 *
 * \brief Gerenciamento de sistema de arquivos zipados
 *
 * \note não implementada ainda
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
    class  SGE_API ZipFileSystem: public Filesystem::CStorage {
    };

} //end SGF



#endif
