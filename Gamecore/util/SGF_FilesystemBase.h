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
#ifndef _SGF_FilesystemBase_h
#define _SGF_FilesystemBase_h

#include <string>
#include <list>
#include <vector>
#include "../SGF_Config.h"
#include "../exceptions/SGF_FileExceptions.h"
#include "../util/SGF_UtilStructs.h"

using namespace std;
namespace SGF {
namespace Filesystem {


//=================FUNCTIONS=======================

	  /* given a relative path like sounds/arrow.png, prepend the proper
     * data path to it to give data/sounds/arrow.png
     */
   //   string find(const string path) throw (CNotFound);


    //string cleanse(const string & path);

    /* returns all the directories starting with the given path.
     * will look in the main data directory, the user directory, and
     * the current working directory.
     */
    //vector<string> findDirectories(const string & path);
	
	

	/* remove extra path separators (/) */
	string sanitize(string path);
    /* basename, just get the filename and remove the directory part */
    string stripDir(const string & str);
	

	/* basename, just get the DIRECTORY and remove the FILENAME part */
    string getDirName(const string path);

    /* remove extension. foo.txt -> foo */
    string removeExtension(const string & str);
    /* return the extension. foo.txt -> txt */
    string checkExtension(const string & str);

		/* strip out the current dir from the string  */
	string stripBaseDir(const string & str);
	bool verifyCompletness(const string & filename);

	/* create a list of all files and subdirectories */
	void TransverseDirectory(string path, list<FILELIST>& theList);

    /* look for specific file tipes into some directory */
	vector< string > getFilesString( const string & dataPath, const string & find );
	 /* search a directory for some files matching pattern `find' */
    //vector<CAbsolutePath> getFiles(const CAbsolutePath & dataPath, const string & find, bool caseInsensitive = false);
	/* same as getFiles but search directories recursively */
    //vector<CAbsolutePath> getFilesRecursive(const CAbsolutePath & dataPath, const string & find, bool caseInsensitive = false);

	const string correctSlashes( const string &str );

    /**
     * @brief getFiles Funtion to get all files inside a folder
     * @param dataPath the path to the container folder
     * @param find the name (pattern) of the files to find
     * @param caseInsensitive Detect Case (windows is always true)
     * @param files the reference to the vectorthat will receive all the found files
     */
    void getFiles(const string & dataPath, const string & find, bool caseInsensitive,vector<string> &files);

    string getBaseDir();
	char * correctSlashes( char *str );
	string removeEndSlashes(string path);

	bool isDirectory(const string & path);
    bool readableFile(const string & path);
    bool readable(const string & path);
	void ExtractPath(char *strPath);
	vector<string> splitPath(string path);
	string stripFirstDir(const string & str);


} //end Filesystem
} //end SGF
#endif
