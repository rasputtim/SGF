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

#include "ai/SGF_PathFinder.h"

namespace SGF {

CPathFinder::CPathFinder(CMap &ourMap):
pathLength(-1),    //stores length of the found path for critter
pathPosition(-1),   //stores current position along the chosen path for critter
pathBank(NULL),
pathStatus(notStarted),
ourMap(ourMap),
heap(NULL)
{
	heap = new CAstarHeap(ourMap.getWidth(),ourMap.getHeight());
	pathBank = (int*) malloc(4);
}

CPathFinder::~CPathFinder(){
	free (pathBank);
	if (heap) delete heap;
}

//==========================================================
//READ PATH DATA: These functions read the path aStarData and convert
//it to screen pixel coordinates.
/*
;	Note on PixelsPerFrame: The need for this parameter probably isn't
;	that obvious, so a little explanation is in order. This
;	parameter is used to determine if the pathfinder has gotten close
;	enough to the center of a given path square to warrant looking up
;	the next step on the path.
;
;	This is needed because the speed of certain sprites can
;	make reaching the exact center of a path square impossible.
;	In Demo #2, the chaser has a velocity of 3 pixels per frame. Our
;	tile size is 50 pixels, so the center of a tile will be at location
;	25, 75, 125, etc. Some of these are not evenly divisible by 3, so
;	our pathfinder has to know how close is close enough to the center.
;	It calculates this by seeing if the pathfinder is less than
;	pixelsPerFrame # of pixels from the center of the square.

;	This could conceivably cause problems if you have a *really* fast
;	sprite and/or really small tiles, in which case you may need to
;	adjust the formula a bit. But this should almost never be a problem
;	for games with standard sized tiles and normal speeds. Our smiley
;	in Demo #4 moves at a pretty fast clip and it isn't even close
;	to being a problem.
*/
void CPathFinder::readPath(Gui::CAbsolutePoint currentPosition, int pixelsPerFrame){
	int currentX = currentPosition.getX();
	int currentY = currentPosition.getY();

	//If a path has been found for the pathfinder	...
	if (pathStatus == found)
	{

		//If path finder is just starting a new path or has reached the
		//center of the current path square (and the end of the path
		//hasn't been reached), look up the next path square.
		if (pathPosition < pathLength)
		{
			//if just starting or if close enough to center of square
			if (pathPosition == 0 ||
				(abs(currentX - locationPath.getX()) < pixelsPerFrame && abs(currentY - locationPath.getY()) < pixelsPerFrame))
					pathPosition = pathPosition + 1;
		}

		//Read the path aStarData.
		locationPath.setXY((readPathX(pathPosition)),(readPathY(pathPosition)));


		//If the center of the last path square on the path has been
		//reached then reset.
		if (pathPosition == pathLength)
		{
			if (abs(currentX - locationPath.getX()) < pixelsPerFrame
				&& abs(currentY - locationPath.getY()) < pixelsPerFrame) //if close enough to center of square
					pathStatus = notStarted;
		}
	}

	//If there is no path for this pathfinder, simply stay in the current
 	//location.
	else
	{
		locationPath.setXY(currentX,currentY);

	}

}
// Desc: Reads the x coordinate of the next path step
int CPathFinder::readPathX(int pathPosition){
	int x;
	if (pathPosition <= pathLength)
	{

	//Read coordinate from bank
	x = pathBank [pathPosition*2-2];

	//Adjust the coordinates so they align with the center
	//of the path square (optional). This assumes that you are using
	//sprites that are centered -- i.e., with the midHandle command.
	//Otherwise you will want to adjust this.
	x = ourMap.getTyleSize()*x + .5*ourMap.getTyleSize();

	}
	return x;
}

// Desc: Reads the y coordinate of the next path step
int CPathFinder::readPathY(int pathPosition){
	int y;
	if (pathPosition <= pathLength)
	{

	//Read coordinate from bank
	y = pathBank [pathPosition*2-1];

	//Adjust the coordinates so they align with the center
	//of the path square (optional). This assumes that you are using
	//sprites that are centered -- i.e., with the midHandle command.
	//Otherwise you will want to adjust this.
	y = ourMap.getTyleSize()*y + .5*ourMap.getTyleSize();

	}
	return y;
}
int CPathFinder::findPath (Gui::CAbsolutePoint startlocation, Gui::CAbsolutePoint targetLocation){

	int startingX = startlocation.getX();
	int	startingY = startlocation.getY();
	int targetX= targetLocation.getX();
	int targetY= targetLocation.getY();
	int parentXval=0, parentYval=0,
	a=0, b=0, corner=0;//, numberOfOpenListItems=0,
	int addedGCost=0, tempGcost = 0, path = 0,
	tempx, pathX, pathY, cellPosition;
	//,
	//newOpenListItemID=0;

//1. Convert location aStarData (in pixels) to coordinates in the walkability array.
	int startX = startingX/ourMap.getTyleSize();
	int startY = startingY/ourMap.getTyleSize();
	targetX = targetX/ourMap.getTyleSize();
	targetY = targetY/ourMap.getTyleSize();

//2.Quick Path Checks: Under the some circumstances no path needs to
//	be generated ...

//	If starting location and target are in the same location...
	if (startX == targetX && startY == targetY && pathPosition > 0)
		return found;
	if (startX == targetX && startY == targetY && pathPosition == 0)
		return nonExistent;

//	If target square is unwalkable, return that it's a nonexistent path.
	if (ourMap.isUnwalkable(targetX,targetY))
		goto noPath;

//3.Reset some variables that need to be cleared
	// reset heap

    heap->reset();
	ourMap.reset();
	ourMap.clear(); //clear Gcost array
	ourMap.addToOpenedList(-1); //changing the values of onOpenList and onClosed list is faster than redimming whichList() array
	ourMap.addToClosedList(2);
	pathLength  = notStarted;//i.e, = 0
	pathPosition = notStarted;//i.e, = 0

	ourMap.setGcost(startX,startY,0); //reset starting square's G value to 0

//4.Add the starting location to the open list of squares to be checked.
	heap->add(startX,startY,1); //assign it as the top (and currently only) item in the open list, which is maintained as a binary heap (explained below)
//5.Do the following until a path is found or deemed nonexistent.
while (true ) //Do until path is found or deemed nonexistent
	{

//6.If the open list is not empty, take the first cell off of the list.
//	This is the lowest F cost cell on the open list.
	if (!heap->isEmpty())
	{

//7. Pop the first item off the open list.
        //record cell coordinates of the item
		parentXval = heap->getX();
		parentYval = heap->getY();
		ourMap.onClosedList(parentXval,parentYval); //add the item to the closed list

//	Open List = Binary Heap: Delete this item from the open list, which
//  is maintained as a binary heap. For more information on binary heaps, see:
//	http://www.policyalmanac.org/games/binaryHeaps.htm
	heap->remove();

//7.Check the adjacent squares. (Its "children" -- these path children
//	are similar, conceptually, to the binary heap children mentioned
//	above, but don't confuse them. They are different. Path children
//	are portrayed in Demo 1 with grey pointers pointing toward
//	their parents.) Add these adjacent child squares to the open list
//	for later consideration if appropriate (see various if statements
//	below).
	for (b = parentYval-1; b <= parentYval+1; b++){
	for (a = parentXval-1; a <= parentXval+1; a++){

//	If not off the map (do this first to avoid array out-of-bounds errors)
		if (a != -1 && b != -1 && a != ourMap.getWidth() && b != ourMap.getHeight()){

//	If not already on the closed list (items on the closed list have
//	already been considered and can now be ignored).
	if (!ourMap.isOnClosedList(a,b)/*whichList[a][b] != onClosedList*/) {

//	If not a wall/obstacle square.
		if (ourMap.isWalkable(a,b)) {

//	Don't cut across corners
	corner = walkable;
	if (a == parentXval-1)
	{
		if (b == parentYval-1)
		{
			if (ourMap.isUnwalkable(parentXval-1,parentYval)
				|| ourMap.isUnwalkable(parentXval,parentYval-1)) \
				corner = unwalkable;
		}
		else if (b == parentYval+1)
		{
			if (ourMap.isUnwalkable(parentXval,parentYval+1)
				|| ourMap.isUnwalkable(parentXval-1,parentYval))
				corner = unwalkable;
		}
	}
	else if (a == parentXval+1)
	{
		if (b == parentYval-1)
		{
			if (ourMap.isUnwalkable(parentXval,parentYval-1)
				|| ourMap.isUnwalkable(parentXval+1,parentYval))
				corner = unwalkable;
		}
		else if (b == parentYval+1)
		{
			if (ourMap.isUnwalkable(parentXval+1,parentYval)
				|| ourMap.isUnwalkable(parentXval,parentYval+1))
				corner = unwalkable;
		}
	}
	if (corner == walkable) {

//	If not already on the open list, add it to the open list.
	if (!ourMap.isOnOpenedList(a,b) /*whichList[a][b] != onOpenList*/)
	{

		//Figure out its G cost
		if (abs(a-parentXval) == 1 && abs(b-parentYval) == 1)
			addedGCost = 14;//cost of going to diagonal squares
		else
			addedGCost = 10;//cost of going to non-diagonal squares

		ourMap.setGcost(a,b,(ourMap.getGcost(parentXval,parentYval) + addedGCost));
		//Figure out its H and F costs and parent
		int Hval= 10*(abs(a - targetX) + abs(b - targetY)); //heuristic val
		ourMap.getparentLocation(a,b).setXY(parentXval,parentYval);
		ourMap.setHcost(a,b,Hval);
		int Fval= ourMap.getGcost(a,b) +  ourMap.getHcost(a,b);
		//Create a new open list item in the binary heap.
		heap->add(a,b,Fval);
     	//Change whichList to show that the new item is on the open list.
		ourMap.onOpenList(a,b);

	}

//8.If adjacent cell is already on the open list, check to see if this
//	path to that cell from the starting location is a better one.
//	If so, change the parent of the cell and its G and F costs.
	else //If whichList(a,b) = onOpenList
	{

		//Figure out the G cost of this possible new path
		if (abs(a-parentXval) == 1 && abs(b-parentYval) == 1)
			addedGCost = 14;//cost of going to diagonal tiles
		else
			addedGCost = 10;//cost of going to non-diagonal tiles
		tempGcost = ourMap.getGcost(parentXval,parentYval) + addedGCost;

		//If this path is shorter (G cost is lower) then change
		//the parent cell, G cost and F cost.
		if (tempGcost < ourMap.getGcost(a,b)) //if G cost is less,
		{
			ourMap.getparentLocation(a,b).setXY(parentXval,parentYval); //change the square's parent
			ourMap.setGcost(a,b,tempGcost);//change the G cost

			//Because changing the G cost also changes the F cost, if
			//the item is on the open list we need to change the item's
			//recorded F cost and its position on the open list to make
			//sure that we maintain a properly ordered open list.
			//look for the item in the heap and chanf Fcost
			heap->changeF(heap->find(a,b),ourMap.getGcost(a,b) +  ourMap.getHcost(a,b));

		}//If tempGcost < Gcost(a,b)

	}//else If whichList(a,b) = onOpenList
	}//If not cutting a corner
	}//If not a wall/obstacle square.
	}//If not already on the closed list
	}//If not off the map
	}//for (a = parentXval-1; a <= parentXval+1; a++){
	}//for (b = parentYval-1; b <= parentYval+1; b++){

	}//if (numberOfOpenListItems != 0)

//9.If open list is empty then there is no path.
	else
	{
		path = nonExistent; break;
	}

	//If target is added to open list then path has been found.
	if (ourMap.isOnOpenedList(targetX,targetY))
	{
		path = found; break;
	}

	}

//10.Save the path if it exists.
	if (path == found)
	{

//a.Working backwards from the target to the starting location by checking
//	each cell's parent, figure out the length of the path.
	pathX = targetX; pathY = targetY;
	do
	{
		//Look up the parent of the current cell.
		tempx = ourMap.getparentLocation(pathX,pathY).getX();
		pathY = ourMap.getparentLocation(pathX,pathY).getY();
		pathX = tempx;

		//Figure out the path length
		pathLength = pathLength + 1;
	}
	while (pathX != startX || pathY != startY);

//b.Resize the aStarData bank to the right size in bytes
	pathBank = (int*) realloc (pathBank,pathLength*8);

//c. Now copy the path information over to the databank. Since we are
//	working backwards from the target to the start location, we copy
//	the information to the aStarData bank in reverse order. The result is
//	a properly ordered set of path aStarData, from the first step to the
//	last.
	pathX = targetX ; pathY = targetY;
	cellPosition = pathLength*2;//start at the end
	do
	{
	cellPosition = cellPosition - 2;//work backwards 2 integers
	pathBank [cellPosition] = pathX;
	pathBank [cellPosition+1] = pathY;

//d.Look up the parent of the current cell.
	tempx = ourMap.getparentLocation(pathX,pathY).getX();
	pathY = ourMap.getparentLocation(pathX,pathY).getY();
	pathX = tempx;

//e.If we have reached the starting square, exit the loop.
	}
	while (pathX != startX || pathY != startY);

//11.Read the first path step into xPath/yPath arrays
	Gui::CAbsolutePoint startPosition(startingX,startingY);
	readPath(startPosition,1);

	}
	return path;


//13.If there is no path to the selected target, set the pathfinder's
//	xPath and yPath equal to its current location and return that the
//	path is nonexistent.
noPath:
	locationPath.setXY(startingX,startingY);
	return nonExistent;


}
} //end SGF