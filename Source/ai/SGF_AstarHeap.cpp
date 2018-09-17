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

#include "ai/SGF_AstarHeap.h"

#include <iostream>


//===========================
namespace SGF {
void CAstarHeap::reset() {
    while ( numberOfOpenListItems != 0) remove();
    newOpenListItemID=0;
    numberOfOpenListItems=0;
}


int CAstarHeap::find(int x, int y) {
    int i;
    for (i=1;i<=numberOfOpenListItems;i++) {
        if (aStarData[i]!=0 ) {
			if (  aStarData[i].getX() ==x && aStarData[i].getY() == y ) return i;
        }
    }
    return 0;
}

bool CAstarHeap::changeF(int pos, unsigned int newF) {	//position in openlist and new value of F
    int i;
	CAStarData tmp;
	if (newF < aStarData[pos].getF() && pos > 0) {
        aStarData[pos].setF(newF);
        i=pos;
        if (i > 1) {
			while ( aStarData[i].getF()  < aStarData[i/2].getF() && i > 1 )  {
                tmp=aStarData[i];
                aStarData[i]=aStarData[i/2];
                aStarData[i/2]=tmp;
                i=i/2;
            }
        }
        return 0;
    }
    return 1;
}

void CAstarHeap::remove() {
    int i, j;
	CAStarData tmp;

    aStarData[1]=aStarData[numberOfOpenListItems];
	aStarData[numberOfOpenListItems].remove();
    --numberOfOpenListItems;

    if (numberOfOpenListItems) {	//not empty?
        i=1;

        while (1) {
            j=i;

            if (2*j+1 <= numberOfOpenListItems && (aStarData[2*j]!=0) && (aStarData[2*j+1]!=0)) {	//both children

                if ( aStarData[j].getF() >= aStarData[j*2].getF() ) i=2*j;
                if ( aStarData[i].getF() >= aStarData[j*2+1].getF() ) i=2*j+1;
            }
            else if (2*j+1 <= numberOfOpenListItems && (aStarData[2*j+1]!=0)) {			//only right child
                if ( aStarData[i].getF() >= aStarData[i*2+1].getF() ) i=2*j+1;
            }
            else if (2*j <=numberOfOpenListItems && (aStarData[2*j]!=0)) {	//only left child
                if ( aStarData[i].getF() >= aStarData[i*2].getF() ) i=2*j;
            }
            if (j!=i) {
                tmp=aStarData[i];		//problem here
                aStarData[i]=aStarData[j];
                aStarData[j]=tmp;
            }
            else break;
        }
    }
}

void CAstarHeap::add(int x, int y, int f) {
    int i;

    ++newOpenListItemID;
    ++numberOfOpenListItems;

	aStarData[newOpenListItemID].setF(f);
	aStarData[newOpenListItemID].setX(x);
	aStarData[newOpenListItemID].setY(y);
	//Coloca o elemento no último item da lista
    aStarData[numberOfOpenListItems]=aStarData[newOpenListItemID];  //?
	//! coloca o elemento em ordemno Heap
    //Move the new open list item to the proper place in the binary heap.
	//Starting at the bottom, successively compare to parent items,
	//swapping as needed until the item finds its place in the heap
	//or bubbles all the way to the top (if it has the lowest F cost).

	i=numberOfOpenListItems;
    if (i>1) {
        while (  aStarData[newOpenListItemID].getF() < aStarData[i/2].getF() && i > 1 )  {
            aStarData[i]=aStarData[i/2];
            aStarData[i/2]=aStarData[newOpenListItemID];  //parent = newOpenListItemID
            i=i/2;
        }
    }
}

bool CAstarHeap::isEmpty() {
    if ( numberOfOpenListItems == 0) return true;
    else return false;
}

CAstarHeap::CAstarHeap(int width, int height): newOpenListItemID(0), numberOfOpenListItems(0)
{
    //int i;
	size = width*height;
    aStarData= new CAStarData[size];

}

CAstarHeap::~CAstarHeap(void)
{

    delete[] aStarData;

}

} //end SGF