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
#ifndef _SGF_ANDROID_DEBUG_H_
#define _SGF_ANDROID_DEBUG_H_


#include <string>
#include <map>
#include <vector>
#include <string>
#include <ostream>
#include "../SGF_Config.h"
#if defined (ANDROID)
#include <sstream>
#include <iostream>
#endif
#include "../SGF_DebugDefs.h"


using namespace std;
namespace SGF {
namespace Debug
{
#ifdef ANDROID


typedef android_ostream stream_type;
android_ostream & operator<<(android_ostream & stream, const string & input);
android_ostream & operator<<(android_ostream & stream, const char * input);
android_ostream & operator<<(android_ostream & stream, const char);
android_ostream & operator<<(android_ostream & stream, const double);
android_ostream & operator<<(android_ostream & stream, const int);
android_ostream & operator<<(android_ostream & stream, const short int);
android_ostream & operator<<(android_ostream & stream, const short unsigned int);
android_ostream & operator<<(android_ostream & stream, const unsigned int);
android_ostream & operator<<(android_ostream & stream, const bool);
android_ostream & operator<<(android_ostream & stream, const long int);
android_ostream & operator<<(android_ostream & stream, const unsigned long int);
android_ostream & operator<<(android_ostream & stream, const void *);
android_ostream & operator<<(android_ostream & stream, std::ostream & (*f)(std::ostream &));
#elif defined(WII) && defined(DEBUG)
class wii_ostream: public std::ostream {
public:
    wii_ostream(bool enabled = true);
    static wii_ostream stream;
    /* make these private at some point */
public:
    bool enabled;
    ::std::ostringstream buffer;
};

typedef wii_ostream stream_type;
wii_ostream & operator<<(wii_ostream & stream, const string & input);
wii_ostream & operator<<(wii_ostream & stream, const char * input);
wii_ostream & operator<<(wii_ostream & stream, const char);
wii_ostream & operator<<(wii_ostream & stream, const double);
wii_ostream & operator<<(wii_ostream & stream, const int);
wii_ostream & operator<<(wii_ostream & stream, const short int);
wii_ostream & operator<<(wii_ostream & stream, const short unsigned int);
wii_ostream & operator<<(wii_ostream & stream, const unsigned int);
wii_ostream & operator<<(wii_ostream & stream, const bool);
wii_ostream & operator<<(wii_ostream & stream, const long int);
wii_ostream & operator<<(wii_ostream & stream, const unsigned long int);
wii_ostream & operator<<(wii_ostream & stream, const void *);
wii_ostream & operator<<(wii_ostream & stream, uint64_t);
wii_ostream & operator<<(wii_ostream & stream, std::ostream & (*f)(std::ostream &));
#elif defined(NETWORK_DEBUG)
class network_ostream: public std::ostream {
public:
    network_ostream(const string & host, int port, bool enabled = true);
    static network_ostream stream;
    /* make these private at some point */
public:
    string host;
    int port;
    bool enabled;
    ::std::ostringstream buffer;
};

typedef network_ostream stream_type;
stream_type & operator<<(stream_type & stream, const string & input);
stream_type & operator<<(stream_type & stream, const char * input);
stream_type & operator<<(stream_type & stream, const char);
stream_type & operator<<(stream_type & stream, const double);
stream_type & operator<<(stream_type & stream, const int);
stream_type & operator<<(stream_type & stream, const short int);
stream_type & operator<<(stream_type & stream, const short unsigned int);
stream_type & operator<<(stream_type & stream, const unsigned int);
stream_type & operator<<(stream_type & stream, const bool);
stream_type & operator<<(stream_type & stream, const long int);
#ifndef PS3
stream_type & operator<<(stream_type & stream, const unsigned long int);
#endif
stream_type & operator<<(stream_type & stream, const void *);
stream_type & operator<<(stream_type & stream, uint64_t);
stream_type & operator<<(stream_type & stream, std::ostream & (*f)(std::ostream &));


#endif



}
} //end SGF
#endif
