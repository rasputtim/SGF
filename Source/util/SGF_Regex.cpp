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
/* gnu/posix's regex header */
//#include <regex.h>
#include <map>
#include "pcre.h"
/* our regex header */
#include "util/SGF_Regex.h"

using namespace std;

namespace SGF {
namespace Util {
static map<string, pcre*> cachedPatterns;

CRegex::CRegex(const string & data):
data(data){
}
        
const string & CRegex::get() const {
    return data;
}
//NEW with pre

bool matchRegex(const string & str, const CRegex & pattern){
    pcre * regex;
    const char * error;
    int errorOffset;
    int count;
    regex = cachedPatterns[pattern.get()];
    if (regex == NULL){
        regex = pcre_compile(pattern.get().c_str(), 0, &error, &errorOffset, NULL);
        if (regex == NULL){
            return false;
        }
        cachedPatterns[pattern.get()] = regex;
    }

    count = pcre_exec(regex, NULL, str.c_str(), str.size(), 0, 0, NULL, 0);
    // pcre_free(regex);
    return count >= 0;
}
    
string captureRegex(const string & str, const CRegex & pattern, int capture){
    pcre * regex;
    const char * error;
    int errorOffset;
    int count;
    const int captureMax = 100;
    int captures[captureMax];
    regex = cachedPatterns[pattern.get()];
    if (regex == NULL){
        regex = pcre_compile(pattern.get().c_str(), 0, &error, &errorOffset, NULL);
        if (regex == NULL){
            return "";
        }
        cachedPatterns[pattern.get()] = regex;
    }

    count = pcre_exec(regex, NULL, str.c_str(), str.size(), 0, 0, captures, captureMax);
    // pcre_free(regex);
    if (count >= 0 && capture < count){
        int start = captures[(capture + 1) * 2];
        int end = captures[(capture + 1) * 2 + 1];
        return str.substr(start, end - start);
    }
    
    return "";
}



//OLD
/* http://www.gnu.org/s/libc/manual/html_node/Regular-Expressions.html */
bool matchRegex(const string & str, const string & pattern){
   /* regex_t regex;
    if (regcomp(&regex, pattern.c_str(), REG_EXTENDED) != 0){
        return false;
    }
    bool matched = regexec(&regex, str.c_str(), 0, NULL, 0) == 0;
    regfree(&regex);
    return matched;*/
	return matchRegex(str,Util::CRegex(pattern));
}
    
string captureRegex(const string & str, const string & pattern, int capture){
  /*  regex_t regex;
    regmatch_t matches[20];
    if (regcomp(&regex, pattern.c_str(), REG_EXTENDED) != 0){
        return "";
    }
    bool matched = regexec(&regex, str.c_str(), 20, matches, 0) == 0;
    regfree(&regex);
    if (matched){
        if (matches[capture+1].rm_so != -1){
            int start = matches[capture+1].rm_so;
            int end = matches[capture+1].rm_eo;
            return str.substr(start, end - start);
        }
    }
    return "";*/
	return Util::captureRegex(str,Util::CRegex(pattern),capture);
} 
} //end util

} //end SGF