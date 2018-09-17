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
#include <stdio.h>
#include <dirent.h>
#ifdef _WIN32
#include <direct.h> // for getcwd
#else
#include <unistd.h>
#endif
#include <stdlib.h>// for MAX_PATH
#include <algorithm> // for transform

#include "util/SGF_Path.h"
#include "exceptions/SGF_Exception.h"
#include "util/SGF_Debug.h"
#include "util/SGF_FilesystemBase.h"
#include "util/SGF_FileSystem.h"




using namespace std;
namespace SGF {
namespace Filesystem{

static int upperCase(int c){
    return toupper(c);
}

static string upperCaseAll(string str){
    ::std::transform(str.begin(), str.end(), str.begin(), upperCase);
    return str;
}

/////////  ILEGAL PATH///////////
CIllegalPath::CIllegalPath(const string & where, int line, const string & file):
CException(where, line, file){
}

CIllegalPath::CIllegalPath(const string & where, int line, const Exception::CBase & nested, const string & file):
CException(where, line, nested, file){
}

CIllegalPath::CIllegalPath(const CIllegalPath & copy):
CException(copy){
}

CIllegalPath::~CIllegalPath() throw(){
}
//=========END ILEGAL

//===============PATH====================



CPath::~CPath(){
}

CPath::CPath(){
}

/*CPath::CPath(const string & path):
mypath(sanitize(correctSlashes(path))),
exists(false){
}*/

CPath::CPath(const CPath & path)
{

}

CInsensitivePath::CInsensitivePath(const CPath & what):
CPath(what){
	mypath= what.path();
}

bool CInsensitivePath::operator==(const CPath & path) const {
	Debug::debug(Debug::gameConfiguration,__FUNCTION__) << "Comparing: " <<this->path() <<" with: "<<path.path()<< endl;

    return upperCaseAll(this->path()) == upperCaseAll(path.path());
}

bool CInsensitivePath::isFile() const {
	return readableFile(this->path().c_str());
 }

//  -----------------  CIsolatedPath ----------------------------

CIsolatedPath::CIsolatedPath():
mypath("")
{
}

CIsolatedPath::CIsolatedPath(const string & path):
mypath(sanitize(correctSlashes(path)))
{
   Debug::debug(Debug::filesystem,__FUNCTION__) <<" - Constructor: mypath: " << mypath <<endl;

	if (! path.empty() && path[0] == DIR_SEPARATOR){
        ostringstream out;
        out << "CIsolatedPath path '" << path << "' cannot start with a /. Only absolute paths can start with /";
       throw CIllegalPath(__FILE__, __LINE__, out.str());
    }
		Debug::debug(Debug::filesystem,__FUNCTION__) <<" END - Path initialized " << this->path() <<endl;


}

CIsolatedPath::CIsolatedPath(const CMyString & path):
	mypath(sanitize(correctSlashes(path.c_str())))
{
   Debug::debug(Debug::filesystem,__FUNCTION__) <<" - Constructor: mypath: " << mypath <<endl;

	if (! path.isEmpty() && path[0] == DIR_SEPARATOR){
        ostringstream out;
        out << "CIsolatedPath path '" << path << "' cannot start with a /. Only absolute paths can start with /";
       throw CIllegalPath(__FILE__, __LINE__, out.str());
    }
		Debug::debug(Debug::filesystem,__FUNCTION__) <<" END - Path initialized " << this->path() <<endl;


}

bool CIsolatedPath::isEmpty() const {
    return mypath.empty() ||  mypath=="";
}

CIsolatedPath::CIsolatedPath(const CIsolatedPath & copy):
mypath(copy.mypath){
Debug::debug(Debug::filesystem,__FUNCTION__) << " // Copying CIsolatedPath" << endl;
}
const string & CIsolatedPath::path() const {
    return mypath;
}
CIsolatedPath CIsolatedPath::getDirectory() const {
	return CIsolatedPath(getDirName(path()));
}

CIsolatedPath CIsolatedPath::getFilename() const {
    return CIsolatedPath(stripDir(path()));
}
bool CIsolatedPath::isFile() const {
    vector<string> paths = splitPath(path());
    return paths.size() == 1;
}
bool CIsolatedPath::operator<(const CIsolatedPath & path) const {
    return this->path() < path.path();
}

bool CIsolatedPath::operator==(const CIsolatedPath & path) const {
    return this->path() == path.path();
}

CIsolatedPath CIsolatedPath::join(const string & him) const {
		CIsolatedPath temp(*this);
		temp.setPath(correctSlashes(sanitize(path() + DIR_SEPARATOR + him)));


	return temp;

}

CIsolatedPath CIsolatedPath::join(const CIsolatedPath & him) const {
    CIsolatedPath temp(correctSlashes(sanitize(path() + DIR_SEPARATOR + him.path())));


	return temp;

}

CIsolatedPath & CIsolatedPath::operator=(const CIsolatedPath & copy){
    // Check for self assignment!
    if (this == &copy)      // Same object?
      return *this;
	this->mypath = copy.path();

    return *this;
}

CIsolatedPath CIsolatedPath::firstDirectory() const {
    vector<string> paths = splitPath(path());
    if (paths.size() > 1){
        return CIsolatedPath(paths[0]);
    }
    return CIsolatedPath();
}

CIsolatedPath CIsolatedPath::removeFirstDirectory() const {
    return CIsolatedPath(stripFirstDir(path()));
}




//  -----------------  CRelativePath ----------------------------

CRelativePath::CRelativePath():
isComplete(false),
mypath(""),
exists(false),
myCompletePath(""){
}

CRelativePath::CRelativePath(const string & path, bool findit):
isComplete(false),
mypath(sanitize(correctSlashes(path))),
exists(false)
{
   Debug::debug(Debug::filesystem,__FUNCTION__) <<" - Constructor: mypath: " << mypath <<endl;

	if (! path.empty() && path[0] == DIR_SEPARATOR){
        ostringstream out;
        out << "Relative path '" << path << "' cannot start with a /. Only absolute paths can start with /";
       throw CIllegalPath(__FILE__, __LINE__, out.str());
    }else {
		if (findit) {
		try {
			Debug::debug(Debug::filesystem,__FUNCTION__) <<" - BEGIN CREATING LOCAL PATH " << endl;
			CAbsolutePath temp=getInstance().find(*this);

			Debug::debug(Debug::filesystem,__FUNCTION__) <<" - END CREATING LOCAL PATH " << temp.path() <<endl;
			if(temp.exist())
			{
				Debug::debug(Debug::filesystem,__FUNCTION__) <<" - setting path to: " << temp.path() <<endl;
				this->setCompletedPath(temp.path());
				this->exists=true;
				this->isComplete=verifyCompletness(temp.path());
			}else {
				Debug::debug(Debug::filesystem,__FUNCTION__) <<" continue with same Path: " << mypath <<endl;
				this->exists= false;
				this->isComplete=verifyCompletness(this->path());
			}
		}catch(...) {
		Debug::debug(Debug::error,__FUNCTION__) << " not found and not exists " << this->path() <<endl;
		Debug::debug(Debug::error,__FUNCTION__) << "original path: " << path <<endl;

		}
		} //end findit
		else{
			this->exists= Filesystem::readable(this->path());
			this->setCompletedPath(path);
			this->isComplete=verifyCompletness(this->path());
		}
		}
		if (this->exist()) Debug::debug(Debug::filesystem,__FUNCTION__) <<" END - Path initialized and exists " << this->path() <<endl;
		else Debug::debug(Debug::filesystem,__FUNCTION__) <<" END Path initialized and NOT exists " << this->path() <<endl;


}

bool CRelativePath::isEmpty() const {
    return mypath.empty() ||  mypath=="";
}

CRelativePath::CRelativePath(const CRelativePath & copy):
isComplete(copy.isComplete),
mypath(copy.mypath),
exists(copy.exists),
myCompletePath(copy.myCompletePath){
Debug::debug(Debug::filesystem,__FUNCTION__) << " // Copying CRelativePath" << endl;
}
const string & CRelativePath::path() const {
    return mypath;
}
CRelativePath CRelativePath::getDirectory() const {
	return CRelativePath(getDirName(path()));
}

CRelativePath CRelativePath::getFilename() const {
    return CRelativePath(stripDir(path()));
}
bool CRelativePath::isFile() const {
    vector<string> paths = splitPath(path());
    return paths.size() == 1;
}
bool CRelativePath::operator<(const CRelativePath & path) const {
    return this->path() < path.path();
}

bool CRelativePath::operator==(const CRelativePath & path) const {
    return this->path() == path.path();
}

CRelativePath CRelativePath::join(const string & him) const {
		CRelativePath temp(*this);
		temp.setPath(correctSlashes(sanitize(path() + DIR_SEPARATOR + him)));
		temp.setCompletedPath(correctSlashes(sanitize(completePath() + DIR_SEPARATOR + him)));
		temp.exists= readable(temp.completePath());

	if (exists) Debug::debug(Debug::filesystem,__FUNCTION__) << " - Path Joined and exists " << path() <<endl;
	else        Debug::debug(Debug::filesystem,__FUNCTION__) <<  __FUNCTION__ << " -Path Joined and not exists " << path() <<endl;

	return temp;

}


CRelativePath CRelativePath::join(const CIsolatedPath & him) const {
	if(this->isComplete) {
		CRelativePath temp(correctSlashes(sanitize(this->completePath() + DIR_SEPARATOR + him.path())));
		temp.exists= readable(temp.path());
		if (temp.exists) Debug::debug(Debug::filesystem,__FUNCTION__) << " - Path Joined and exists " << temp.path() <<endl;
		else        Debug::debug(Debug::filesystem,__FUNCTION__) <<  __FUNCTION__ << " -Path Joined and not exists " << temp.path() <<endl;

	return temp;
	}else {
	CRelativePath temp(correctSlashes(sanitize(path() + DIR_SEPARATOR + him.path())));
		temp.exists= readable(temp.path());
		if (temp.exists) Debug::debug(Debug::filesystem,__FUNCTION__) << " - Path Joined and exists " << temp.path() <<endl;
		else        Debug::debug(Debug::filesystem,__FUNCTION__) <<  __FUNCTION__ << " -Path Joined and not exists " << temp.path() <<endl;

	return temp;

	}

}


CRelativePath CRelativePath::join(const CRelativePath & him) const {
    CRelativePath temp(correctSlashes(sanitize(path() + DIR_SEPARATOR + him.path())));

		temp.exists= readable(temp.path());
		if (exists) Debug::debug(Debug::filesystem,__FUNCTION__) << " - Path Joined and exists " << temp.path() <<endl;
		else        Debug::debug(Debug::filesystem,__FUNCTION__) <<  __FUNCTION__ << " -Path Joined and not exists " << temp.path() <<endl;

	return temp;

}

CRelativePath & CRelativePath::operator=(const CRelativePath & copy){
    // Check for self assignment!
    if (this == &copy)      // Same object?
      return *this;
	this->mypath = copy.path();
	this->exists = copy.exists;
	this->isComplete =copy.isComplete;
	this->myCompletePath = copy.myCompletePath;

    return *this;
}

CRelativePath CRelativePath::firstDirectory() const {
    vector<string> paths = splitPath(path());
    if (paths.size() > 1){
        return CRelativePath(paths[0]);
    }
    return CRelativePath();
}

CRelativePath CRelativePath::removeFirstDirectory() const {
    return CRelativePath(stripFirstDir(path()));
}


//  -----------------  CAbsolutePath ----------------------------

CAbsolutePath::CAbsolutePath():
mypath(""),
tamanho_maximo(_MAX_DRIVE + _MAX_DIR - 13),
exists(false)
{
memset( _my_dir_prefix, 0, sizeof(_my_dir_prefix) );	// init _my_dir_prefix
getcwd(_my_dir_prefix, sizeof(_my_dir_prefix));
/* Append directories separator character, unless it's already there
         (as would be the case if the current directory is root). */
      if( _my_dir_prefix[strlen(_my_dir_prefix)-1] != DIR_SEPARATOR ){
          _my_dir_prefix[strlen(_my_dir_prefix)+1] = '\0';
          _my_dir_prefix[strlen(_my_dir_prefix)] = DIR_SEPARATOR;
      }
mypath.assign(_my_dir_prefix);
//this->setPath(_my_string_dir_prefix);
}
void CAbsolutePath::GetBasePath(char *path) {
		memcpy(path,&_my_dir_prefix,tamanho_maximo);
}
const string & CAbsolutePath::path() const {
    return mypath;
}
bool CAbsolutePath::isEmpty() const {
	//Convert char to string
	stringstream ss;
	string temp;
	ss << _my_dir_prefix;
	ss >> temp;
	return (mypath == temp || mypath.empty());
}



CAbsolutePath::CAbsolutePath(const string & path):
mypath(sanitize(correctSlashes(path))),
tamanho_maximo(_MAX_DRIVE + _MAX_DIR - 13),
exists(false)
{
	getcwd(_my_dir_prefix, sizeof(_my_dir_prefix));
/* Append directories separator character, unless it's already there
         (as would be the case if the current directory is root). */
      if( _my_dir_prefix[strlen(_my_dir_prefix)-1] != DIR_SEPARATOR ){
          _my_dir_prefix[strlen(_my_dir_prefix)+1] = '\0';
          _my_dir_prefix[strlen(_my_dir_prefix)] = DIR_SEPARATOR;
      }
//mypath.assign(_my_dir_prefix);
		try {
			this->exists= Filesystem::readable(this->path());
		}catch(...) {
		//Debug::debug(Debug::filesystem,__FUNCTION__) << "From String: Path not found and not exists " << this->path() <<endl;
		}

if (this->exist()) {
	//Debug::debug(Debug::filesystem,__FUNCTION__) << "From String: Path found and exists " << this->path() <<endl;
}

}
CAbsolutePath::CAbsolutePath(const CRelativePath & other):
mypath(""),
tamanho_maximo(_MAX_DRIVE + _MAX_DIR - 13),
exists(false)
{
	getcwd(_my_dir_prefix, sizeof(_my_dir_prefix));
/* Append directories separator character, unless it's already there
         (as would be the case if the current directory is root). */
      if( _my_dir_prefix[strlen(_my_dir_prefix)-1] != DIR_SEPARATOR ){
          _my_dir_prefix[strlen(_my_dir_prefix)+1] = '\0';
          _my_dir_prefix[strlen(_my_dir_prefix)] = DIR_SEPARATOR;
      }
mypath.assign(_my_dir_prefix);
try{
	if(other.exist() && other.isComplete) {
		mypath=other.completePath();
		this->exists=true;
	}else if (other.exist() && !other.isComplete) {
			mypath=mypath+other.path();
			this->exists=readable(path()); //Todo if no exists throw CNOTFOUND
	}else if (!other.exist()){
	    this->setPath(sanitize(correctSlashes(getInstance().lookup(&other).path())));
        this->exists=readable(path());
		Debug::debug(Debug::error,__FUNCTION__) << "CAbsolutePath::CAbsolutePath(const CRelativePath & path) found and exists " << this->path() <<endl;
		}
} catch (const Exception::Filesystem::CNotFound & found){
        this->exists=false;
		Debug::debug(Debug::error,__FUNCTION__) << "Path initialized from a CRelativePath Not found and not exists " << this->path() <<endl;
		Debug::debug(Debug::error,__FUNCTION__) << "original path: " << other.path() <<endl;

	}

}

CAbsolutePath::CAbsolutePath(const CAbsolutePath & copy):
mypath(copy.path()),
tamanho_maximo(copy.tamanho_maximo),
exists(copy.exists)
{
	memcpy(_my_dir_prefix,copy._my_dir_prefix,sizeof(_my_dir_prefix));
}


bool CAbsolutePath::isFile() const {
	return readableFile(this->path().c_str());
 }

CAbsolutePath & CAbsolutePath::operator=(const CAbsolutePath & copy){
	Debug::debug(Debug::filesystem,__FUNCTION__) <<  __FUNCTION__ << "Coping Path Object: "<< copy.path() << endl;
	if (copy.getType() !="absolute") {
		Debug::debug(Debug::filesystem,__FUNCTION__) << "trying to copy wrog Path type" << endl;
		throw Filesystem::CIllegalPath(__FUNCTION__,__LINE__,"ilegal type of copy");
	}
	// Check for self assignment!
    if (this == &copy)    // Same object?
      return *this;
	this->mypath =copy.mypath;
	this->exists = copy.exists;
	tamanho_maximo= copy.tamanho_maximo;
	memcpy(_my_dir_prefix,copy._my_dir_prefix,sizeof(_my_dir_prefix));
	    Debug::debug(Debug::filesystem,__FUNCTION__) <<  __FUNCTION__ << "Object copied: " << this->path() << endl;
		Debug::debug(Debug::filesystem,__FUNCTION__) << "-----------------------------------------------------" << endl;
	return *this;
}

CAbsolutePath & CAbsolutePath::operator=(const CRelativePath & copy){
     // Check for self assignment!

	this->mypath =copy.completePath();
	this->exists = copy.exist();
	//tamanho_maximo= copy.tamanho_maximo;
	//memcpy(_my_dir_prefix,copy._my_dir_prefix,sizeof(_my_dir_prefix));
	return *this;
}

CAbsolutePath & CAbsolutePath::copy(){
	Filesystem::CAbsolutePath *temp = new CAbsolutePath();
	temp->mypath = mypath;
	temp->exists = exists;
	temp->tamanho_maximo= this->tamanho_maximo;
	memcpy(temp->_my_dir_prefix,_my_dir_prefix,sizeof(_my_dir_prefix));
	return *temp;
}
bool CAbsolutePath::operator==(const CAbsolutePath & other) const {
    return this->path() == other.path();
}

bool CAbsolutePath::operator<(const CAbsolutePath & other) const {
    return this->path() < other.path();
}

CAbsolutePath CAbsolutePath::getDirectory() const {
    CAbsolutePath caminho;
	string meiocaminho=getDirName(this->mypath);
	caminho=CAbsolutePath(meiocaminho);
	return caminho;
}

CAbsolutePath CAbsolutePath::getFilename() const {
    return CAbsolutePath(stripDir(path()));
}

CAbsolutePath CAbsolutePath::join(const CRelativePath & path) const {
    Debug::debug(Debug::filesystem,__FUNCTION__) << "-----------------------------------------------------" << endl;
	Debug::debug(Debug::filesystem,__FUNCTION__) << " to join: " << path.path() <<endl;
	Debug::debug(Debug::filesystem,__FUNCTION__) << " to join complete path: " << path.completePath() <<endl;
	Debug::debug(Debug::filesystem,__FUNCTION__) << " to join isComplete: " << path.isComplete <<endl;
	Debug::debug(Debug::filesystem,__FUNCTION__) << " to join existes: " << path.exist() <<endl;
	if(!path.isComplete){
		Debug::debug(Debug::filesystem,__FUNCTION__) << " will try is not complete join: " <<endl;
		Debug::debug(Debug::filesystem,__FUNCTION__) << " to join this path: " << this->path() <<endl;
		string tempString= correctSlashes(sanitize(this->path() + DIR_SEPARATOR + path.path()));
		Debug::debug(Debug::filesystem,__FUNCTION__) << " complete made string: "<< tempString <<endl;
		CAbsolutePath temp(tempString);
		exists= Filesystem::readable(this->path());
		if( exists) Debug::debug(Debug::filesystem,__FUNCTION__) << "joined and exists: " << this->path() << endl;
		if( !exists) Debug::debug(Debug::filesystem,__FUNCTION__) << "joined and not exists: " <<this->path() << endl;
		Debug::debug(Debug::filesystem,__FUNCTION__) << "-----------------------------------------------------" << endl;
		return temp;
	}
	else {
		CAbsolutePath temp(path.completePath());
		exists= Filesystem::readable(this->path());
		if( exists) Debug::debug(Debug::filesystem,__FUNCTION__) << "joined and exists: " << this->path() << endl;
		if( !exists) Debug::debug(Debug::filesystem,__FUNCTION__) << "joined and not exists: " <<this->path() << endl;
		Debug::debug(Debug::filesystem,__FUNCTION__) << "-----------------------------------------------------" << endl;
		return temp;
	}



}

CAbsolutePath CAbsolutePath::join(const CIsolatedPath & path) const{

return this->joinToCurrent(path);
}

void CAbsolutePath::localJoin(const CRelativePath & other) {
    Debug::debug(Debug::filesystem,__FUNCTION__) << "-----------------------------------------------------" << endl;
	Debug::debug(Debug::filesystem,__FUNCTION__) << " to join: " << other.path() <<endl;
	if(!other.isComplete)this->setPath(correctSlashes(sanitize(this->path() + other.path())));
	else {
		if(!other.exist()) {
		string to_join=correctSlashes(sanitize(stripBaseDir(other.path())));
		this->setPath(mypath+to_join);
		}
	}
	Debug::debug(Debug::filesystem,__FUNCTION__) << " joined: " << this->path() << endl;

		exists= readable(path());
		if(exists) Debug::debug(Debug::filesystem,__FUNCTION__) <<"Path Joined and exists " << this->path() <<endl;
		else Debug::debug(Debug::filesystem,__FUNCTION__) <<"Path Joined and not exists " << this->path() <<endl;
		Debug::debug(Debug::filesystem,__FUNCTION__) << "-----------------------------------------------------" << endl;

}
CAbsolutePath CAbsolutePath::joinToCurrent(const CRelativePath & path) const {
	Debug::debug(Debug::filesystem,__FUNCTION__) << "-----------------------------------------------------" << endl;
	Debug::debug(Debug::filesystem,__FUNCTION__) << " to join: " << path.path() <<endl;
    CAbsolutePath temp(correctSlashes(sanitize(this->getCurrentDir() + "/" + path.path())));
	Debug::debug(Debug::filesystem,__FUNCTION__) << "joined: " << path.path() << endl;
	if (temp.exists)
		Debug::debug(Debug::filesystem,__FUNCTION__) << "Found and Exists " << temp.path() <<endl;
	else
		Debug::debug(Debug::error,__FUNCTION__) << "not found and not exists: " << temp.path() <<endl;
	    Debug::debug(Debug::error,__FUNCTION__) << "original path: " << path.path() <<endl;
		Debug::debug(Debug::error,__FUNCTION__) << "-----------------------------------------------------" << endl;
	return temp;
}

CAbsolutePath CAbsolutePath::joinToCurrent(const CIsolatedPath & path) const {
	Debug::debug(Debug::filesystem,__FUNCTION__) << "-----------------------------------------------------" << endl;
	Debug::debug(Debug::filesystem,__FUNCTION__) << " to join: " << path.path() <<endl;
    CAbsolutePath temp(correctSlashes(sanitize(this->getCurrentDir() + "/" + path.path())));
	Debug::debug(Debug::filesystem,__FUNCTION__) << "joined: " << temp.path() << endl;
		if (temp.exist())
			Debug::debug(Debug::filesystem,__FUNCTION__) << "CAbsolutePath CAbsolutePath Found and exists " << temp.path() <<endl;
		else
		Debug::debug(Debug::filesystem,__FUNCTION__) << "not found and not exists " << temp.path() <<endl;
		Debug::debug(Debug::error,__FUNCTION__) << "original path: " << path.path() <<endl;
		Debug::debug(Debug::filesystem,__FUNCTION__) << "-----------------------------------------------------" << endl;
	return temp;
}


CIsolatedPath CAbsolutePath::remove(const CAbsolutePath & what) const {
    string real = path();
    real.erase(0, what.path().size());
    while (real.find("/") == 0){
        real.erase(0, 1);
    }
    return CIsolatedPath(real);
}
string CAbsolutePath::firstDirectory() const {
    vector<string> paths = splitPath(path());
    if (paths.size() > 1){
        return paths[0];
    }
    return removeEndSlashes(path());
}
CAbsolutePath CAbsolutePath::removeFirstDirectory() const {
    return CAbsolutePath(stripFirstDir(path()));
}


} //end Filesystem
} //end Path
