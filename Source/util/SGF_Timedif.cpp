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

#include "util/SGF_Timedif.h"
#include <sstream>
#include <iostream>
#include <string>
#include <math.h>
#include "sys/SGF_System.h"

using namespace std;
namespace SGF {

TimeDifference::TimeDifference():
start(0),
end(0){
}

void TimeDifference::startTime(){
    start = System::currentMicroseconds();
}

void TimeDifference::endTime(){
    end = System::currentMicroseconds();
}

const string TimeDifference::printTime(){
    return this->printTime("Function took");
}

unsigned long long int TimeDifference::getTime(){
    unsigned long long int g = end - start;
    return g;
}

static double roundit(double number, int digits){
    return (long long) (number * pow((double) 10.0, digits)) / pow((double) 10.0, digits);
}

const string TimeDifference::printTime(const string & s){

    double total = getTime();
    string units = "microseconds";

    int unit_times[] = {1000, 1000, 60};
    string unit_descriptions[] = {"milliseconds", "seconds", "minutes"};

    for (unsigned int index = 0; index < sizeof(unit_times) / sizeof(int); index++){
        if (total > unit_times[index]){
            total /= unit_times[index];
            units = unit_descriptions[index];
        } else {
            break;
        }
    }

    ostringstream o;
    o << s << " " << roundit(total, 3) << " " << units;
    return o.str();

    /*

	unsigned long long int micro = (end.tv_sec*1000000+end.tv_usec) - (start.tv_sec*1000000 + start.tv_usec );
	unsigned long long int milli = micro / 1000;
	unsigned long long int sec = milli / 1000;

	//cout<<s<<" took "<<micro<<" microseconds / "<< milli << " milliseconds / " <<sec<< " seconds "<< endl;
	ostringstream o;
	o << s <<" took "<<micro<<" microseconds / "<< milli << " milliseconds / " <<sec<< " seconds";
	return o.str();
        */
}

TimeDifference::~TimeDifference(){
}
} //end SGF