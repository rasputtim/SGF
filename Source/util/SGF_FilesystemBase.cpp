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

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <stdio.h>
#include <dirent.h>
#if defined (WINDOWS)
#include <direct.h> // for getcwd
#else
#include <unistd.h>
#endif
#include <stdlib.h>// for MAX_PATH
#include "util/SGF_Path.h"
#include "util/SGF_Debug.h"
#include "util/SGF_FilesystemBase.h"
#include "sfldir.h"

using namespace std;
namespace SGF {
namespace Filesystem{

string getBaseDir(){
	string mypath;
	char _my_dir_prefix[_MAX_DRIVE + _MAX_DIR - 13];
	getcwd(_my_dir_prefix, sizeof(_my_dir_prefix));
/* Append directories separator character, unless it's already there
         (as would be the case if the current directory is root). */
      if( _my_dir_prefix[strlen(_my_dir_prefix)-1] != DIR_SEPARATOR ){
          _my_dir_prefix[strlen(_my_dir_prefix)+1] = '\0';
          _my_dir_prefix[strlen(_my_dir_prefix)] = DIR_SEPARATOR;
      }
mypath.assign(_my_dir_prefix);
return mypath;
}

void getFiles(const string & dataPath, const string & find,vector<string> &files){
//   Util::Thread::ScopedLock scoped(lock);

   DIRST sflEntry;
    bool ok = open_dir(&sflEntry, dataPath.c_str());
    while (ok){
        if (file_matches(sflEntry.file_name, find.c_str())){
            files.push_back(dataPath + DIR_SEPARATOR + string(sflEntry.file_name));
        }
        ok = read_dir(&sflEntry);
    }
    close_dir(&sflEntry);


}

const string correctSlashes( const string &str ){
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

/* remove extra path separators (/) */
string sanitize(string path){
    size_t double_slash = path.find("//");
    while (double_slash != string::npos){
        path.erase(double_slash, 1);
        double_slash = path.find("//");
    }
	double_slash = path.find("\\\\");
    while (double_slash != string::npos){
        path.erase(double_slash, 1);
        double_slash = path.find("\\\\");
    }

    return path;
}



/** @fn  stripDir(const string & filename)
@brief retorna só a parte arquivo contida na string filename
@param const char * filename: nome do arquivo contendo
@return o nome do arquivo ou o diretório completo se é apenas um diretório
@warning nenhum aviso
**/
string stripDir(const string & filename){
	string temp = Filesystem::correctSlashes(filename);
	if (temp.find( DIR_SEPARATOR) != string::npos){
        size_t rem = temp.find_last_of(DIR_SEPARATOR );
        if (rem != string::npos){
            return temp.substr(rem+1,temp.size());
        }

    }
    return temp;
}

/** @fn  getDirName(const string filename)
@brief retorna só a parte diretório contido na string filename
@param const char * filename: nome do arquivo contendo
@return o nome do arquivo ou o diretório completo se é apenas um diretório
@warning nenhum aviso
**/
string getDirName(const string filename){
    if (filename.find(DIR_SEPARATOR) != string::npos){
        size_t rem = filename.find_last_of(DIR_SEPARATOR);  // Searches the string from the end for any of the characters that are part of either str
												  // The position of the last occurrence in the string of any of the characters searched for.
												  // If the content is not found, the member value npos is returned.
        if (rem != string::npos){
            return filename.substr(0, rem+1);  //inicia na posição zero e retorna a string até a posição rem+1
        }


    }
	   return filename;

}

/** @fn  removeExtension(const string & filename)
@brief retira a extensão (parte depois do  ".") do arquivo passado
@param const string & filename: nome do arquivo
@return o nome do arquivo sem a extensão
@warning nenhum aviso
**/
string removeExtension(const string & filename){
    if (filename.find(".") != string::npos){
        return filename.substr(0, filename.find_last_of("."));
    }
    return filename;
}

/** @fn  checkExtension(const string & filename)
@brief retira a extensão (parte depois do  ".") do arquivo passado
@param const string & filename: nome do arquivo
@return a extensão do arquivo
@warning nenhum aviso
**/
string checkExtension(const string & str){
    if (str.find(".") != string::npos){
        return str.substr(str.find_last_of(".")+1,(str.size()-str.find_last_of(".")+1));
    }
    return str;
}


#if !defined (WINDOWS)
#include <iostream>
#include <string>
#include <dirent.h>

static void ProcessEntity(struct dirent* entity, list<FILELIST>& theList);


static void ProcessDirectory(std::string directory, list<FILELIST>& theList)
{
    auto dir = opendir(directory.c_str());

    //set the new path for the content of the directory
    directory = directory + "/";

    //std::cout << "Process directory: " << dirToOpen.c_str() << std::endl;

    if(NULL == dir)
    {
        //std::cout << "could not open directory: " << dirToOpen.c_str() << std::endl;
        return;
    }

    auto entity = readdir(dir);

    while(entity != NULL)
    {
        ProcessEntity(entity, theList);
        entity = readdir(dir);
    }

    //we finished with the directory so remove it from the path
    directory.resize(directory.length() - 1 - directory.length());
    closedir(dir);
}

static void ProcessEntity(struct dirent* entity, list<FILELIST>& theList)
{
    //find entity type
    if(entity->d_type == DT_DIR)
    {//it's an direcotry
        //don't process the  '..' and the '.' directories
        if(entity->d_name[0] == '.')
        {
            return;
        }

        //it's an directory so process it
        ProcessDirectory(std::string(entity->d_name),theList);
        return;
    }

    if(entity->d_type == DT_REG)
    {//regular file
        // this is just a normal filename.  So just add it to our vector
        //sal todo:solve this theList.push_back(std::string(entity->d_name));
        return;
    }

    //there are some other types
    //read here http://linux.die.net/man/3/readdir
    //std::cout << "Not a file or directory: " << entity->d_name << std::endl;
}



#endif


/**
@fn  TransverseDirectory(string path, list<FILELIST>& theList)
@brief  use recursion to get a list of all the directories (folders) and file names within them
@param  string path: caminho inicial
@param  list<FILELIST>& theList: lista que será preenchida com os diretórios e nomes de arquivos
@return
@warning The struct FILELIST hold a directory and all its filenames. ONLY WORKS FOR WINDOWS
**/
void TransverseDirectory(string path, list<FILELIST>& theList)
{
#if defined WINDOWS
    struct _finddatai64_t data;
	string fname = path + "\\"+"*.*";
	long h = _findfirsti64(fname.c_str(),&data);  //! http://msdn.microsoft.com/en-us/library/zyzxfzac(v=vs.71).aspx
	if(h >= 0)
	{
		FILELIST thisList;
		theList.push_back(thisList);
		list<FILELIST>::iterator it = theList.end();
		it--;

		(*it).path = path;
		do {
			if( (data.attrib & _A_SUBDIR) ) {
				// make sure we skip "." and "..".  Have to use strcmp here because
				// some file names can start with a dot, so just testing for the
				// first dot is not suffient.
				if( strcmp(data.name,".") != 0 &&strcmp(data.name,"..") != 0)
				{
					// We found a sub-directory, so get the files in it too
					fname = path + "\\" + data.name;
					// recurrsion here!
					TransverseDirectory(fname,theList);
				}

			}else {
				// this is just a normal filename.  So just add it to our vector
				(*it).theList.push_back(data.name);

			}
		}while( _findnexti64(h,&data) == 0);
		_findclose(h);

	}
#else   //LINUX

    ProcessDirectory(path,theList);

#endif
}



/**
@fn  getFiles( const string & dataPath, const string & find )
@brief cria uma lista (vetor) com todos os arquivos encontrados
@param datapath: caminho no sistema de arquivos
@param find: wildcard que indica o que procurar. Ex *.ttf
@warning ONLY WORKS FOR WINDOWS
**/

vector< string > getFilesString( const string & dataPath, const string & find ){


#ifdef WINDOWS
    struct _finddatai64_t data;
    string fname = dataPath + find;

    //struct al_ffblk info;
    vector< string > files;
    long h = _findfirsti64(fname.c_str(),&data);
    if (h == -1) {
        return files;
    }
    //if ( al_findfirst( (dataPath + find).c_str(), &info, FA_ALL ) != 0 ){ //não encontrou,ou deu erro
    //	return files;
    //}
    files.push_back( dataPath + string( data.name ) );
    while( _findnexti64(h,&data) == 0) {
    //while ( al_findnext( &info ) == 0 ){
        files.push_back( dataPath + string( data.name ) );
    }
    _findclose(h);
    //al_findclose( &info );

    return files;


#if 0
    HANDLE dir;
    WIN32_FIND_DATA file_data;

    if ((dir = FindFirstFile((directory + "/*").c_str(), &file_data)) == INVALID_HANDLE_VALUE)
        return; /* No files found */

    do {
        const string file_name = file_data.cFileName;
        const string full_file_name = directory + "/" + file_name;
        const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

        if (file_name[0] == '.')
            continue;

        if (is_directory)
            continue;

        out.push_back(full_file_name);
    } while (FindNextFile(dir, &file_data));

    FindClose(dir);
#endif
#else
    //struct al_ffblk info;
    vector< string > files;
    DIR *dir;
    class dirent *ent;
    class stat st;
    string fname = dataPath + find;

    dir = opendir(fname.c_str());
    while ((ent = readdir(dir)) != NULL) {
        const string file_name = ent->d_name;
        const string full_file_name = dataPath + "/" + file_name;

        if (file_name[0] == '.')
            continue;

        if (stat(full_file_name.c_str(), &st) == -1)
            continue;

        const bool is_directory = (st.st_mode & S_IFDIR) != 0;

        if (is_directory)
            continue;

        files.push_back(full_file_name);
    }
    closedir(dir);
#endif
    return files;

}


void ExtractPath(char *strPath)
{
    int l;
    l=strlen(strPath);

    for(int i=l;i>0;i--)
    {
        if(strPath[i]=='\\')
        {
               strPath[i+1]=0;
               break;
        }

    }

}

//! PUT THE CORRET SLICES SEPARATOR REGARDING unix OR windows
char *correctSlashes( char *str ){
	unsigned int i;

	if (DIR_SEPARATOR == '\\' ) {
		for (i=0 ; i<strlen(str) ; i++)
        if (str[i] == '/') str[i] = '\\';

	}else if (DIR_SEPARATOR == '/' ) {
		for (i=0 ; i<strlen(str) ; i++)
        if (str[i] == '\\') str[i] = '/';

	}
	//Debug::debug(Debug::filesystem,__FUNCTION__) << "Filesystem::correctSlashes()  "<<str  << endl;

	return str;
}

string removeEndSlashes(string path){
    size_t last = path.rfind(DIR_SEPARATOR);
    while (path.size() > 0 && last == path.size() - 1){
        path.erase(last, 1);
        last = path.rfind(DIR_SEPARATOR);
    }
    return path;
}



vector<string> splitPath(string path){
    vector<string> all;
    if (path.size() > 0 && path[0] == '/'){
        all.push_back("/");
    }
    size_t found = path.find('/');
    while (found != string::npos){
        if (found > 0){
            all.push_back(path.substr(0, found));
        }
        path.erase(0, found + 1);
        found = path.find('/');
    }
    if (path.size() != 0){
        all.push_back(path);
    }
    return all;
}

/* a/b/c/d -> b/c/d */
string stripFirstDir(const string & str){
    if (str.find("/") != string::npos || str.find( "\\") != string::npos){
        string temp = str;
        size_t rem = temp.find("/");
        if (rem != string::npos){
            return str.substr(rem+1,str.size());
        }
        rem = temp.find("\\");
        if( rem != string::npos ){
            return str.substr(rem+1,str.size());
        }
    }
    return str;
}


#ifndef _WIN32
//#ifndef WINDOWS
//#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

static bool isReadable(const string & path){
    if (access(path.c_str(), R_OK) == 0){
        return true;
    } else {
        return false;
    }
}

bool isDirectory(const string & path){
    struct stat info;
    if (stat(path.c_str(), &info) == 0){
        if (S_ISDIR(info.st_mode) == 1){
            return true;
        } else {
            return false;
        }
    }
    return false;
}

bool readableFile(const string & path){
    return isReadable(path) && ! isDirectory(path);
}

bool readable(const string & path){
    return isReadable(path);
}

uint64_t currentMicroseconds(){
    struct timeval hold;
    gettimeofday(&hold, NULL);
    return hold.tv_sec * 1000 * 1000 + hold.tv_usec;
}

#endif

#ifdef _WIN32

#include <windows.h>

#include <fstream>




bool isDirectory(const string & path){
#ifdef WIN32
	unsigned int f = GetFileAttributes(path.c_str());
    if (f == INVALID_FILE_ATTRIBUTES){
        return false;
    }
    return f & FILE_ATTRIBUTE_DIRECTORY;
#else
    struct stat info;
    if (stat(path.c_str(), &info) == 0){
        if (S_ISDIR(info.st_mode) == 1){
            return true;
        } else {
            return false;
        }
    }
    return false;

#endif
}

bool readableFile(const string & path){
    return !isDirectory(path) && readable(path);
}

bool readable(const string & path){
//	Debug::debug(1,__FUNCTION__) << "readable: '" << path.c_str() << "'" << endl;

    if (isDirectory(path)){
//    Debug::debug(1,__FUNCTION__) << "readable: '" << path.c_str() << "' is directory. returning TRUE" << endl;

        return true;
    }
//	Debug::debug(1,__FUNCTION__) << "readable: '" << path.c_str() << "' is not directory. checking if is stream and is good" << endl;

    ::ifstream stream(path.c_str());
    bool ok = stream.good();
    if (stream.is_open()){
        stream.close();
    }
//	Debug::debug(1,__FUNCTION__) << "readable: '" << path.c_str() << "' is not directory. the stream is: "<< ok << endl;

    return ok;

}

#endif
/** @fn  stripBaseDir(const string & str)
@brief retira o diretório atual
@param
@return
@warning
**/
string stripBaseDir(const string & filename){
		string currentDir;
	//! armazena o caminho em *char
	char _my_dir_prefix[_MAX_DRIVE + _MAX_DIR - 13];
	getcwd(_my_dir_prefix, sizeof(_my_dir_prefix));
/* Append directories separator character, unless it's already there
         (as would be the case if the current directory is root). */
      if( _my_dir_prefix[strlen(_my_dir_prefix)-1] != DIR_SEPARATOR ){
          _my_dir_prefix[strlen(_my_dir_prefix)+1] = '\0';
          _my_dir_prefix[strlen(_my_dir_prefix)] = DIR_SEPARATOR;
      }
	currentDir.assign(_my_dir_prefix);
	Debug::debug(Debug::filesystem,__FUNCTION__) << " Current  dir: " << currentDir << endl;
	string temp = correctSlashes(filename);
	Debug::debug(Debug::filesystem,__FUNCTION__) << " Filename dir: " << temp << endl;
	if (!strncmp(filename.c_str(), currentDir.c_str(), strlen(currentDir.c_str()))) { // filename start with current path
		Debug::debug(Debug::filesystem,__FUNCTION__) << " Returning dir: " << temp << endl;
		return temp.substr(currentDir.size()+1,temp.size());
	}else {
		Debug::debug(Debug::filesystem,__FUNCTION__) << " Returning dir: " << filename << endl;
		return filename;
	}


}


/** @fn  verifyCompletness(const string & filename)
@brief verifica se o diretório corrente está no início do caminho
@param
@return true: se sim
@warning
**/
bool verifyCompletness(const string & filename){
	string currentDir;
	//! armazena o caminho em *char
	char _my_dir_prefix[_MAX_DRIVE + _MAX_DIR - 13];
	getcwd(_my_dir_prefix, sizeof(_my_dir_prefix));
/* Append directories separator character, unless it's already there
         (as would be the case if the current directory is root). */
      if( _my_dir_prefix[strlen(_my_dir_prefix)-1] != DIR_SEPARATOR ){
          _my_dir_prefix[strlen(_my_dir_prefix)+1] = '\0';
          _my_dir_prefix[strlen(_my_dir_prefix)] = DIR_SEPARATOR;
      }
	currentDir.assign(_my_dir_prefix);

	Debug::debug(Debug::filesystem,__FUNCTION__) << " Current  dir: " << currentDir << endl;
	string temp = correctSlashes(filename);
	Debug::debug(Debug::filesystem,__FUNCTION__) << " Filename dir: " << temp << endl;
	if (!strncmp(filename.c_str(), currentDir.c_str(), strlen(currentDir.c_str()))) { // filename start with current path
		Debug::debug(Debug::filesystem,__FUNCTION__) << " Returning TRUE dir: " << temp << endl;
		return true;
	}else {
		Debug::debug(Debug::filesystem,__FUNCTION__) << " Returning FALSE dir: " << filename << endl;
		return false;
	}


}





}//end Filesystem

} //end SGF
