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


//#include "compiler/AirCompilerOld/driver.h"
#include "resource/all.h"
#include "mugen/ast/all.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include "util/AirManager.h"
#include "util/SGF_Debug.h"

namespace SGF {

CAirManager::CAirManager()
{
    pTempList=NULL;
    nCurrentElement=0;
    nCurrentClsn=0;
    bClsnDefault=false;

}

CAirManager::~CAirManager()
{
}

void CAirManager::Reset()
{
    pTempList=NULL;
    nCurrentElement=0;
    nCurrentClsn=0;
    bClsnDefault=false;

}

void CAirManager::AddAction(int nActionNumber)
{
    nHowManyBlocks++;
    // Isto realoca todo o bloco de memória do bloco de ação anterior
	// mas o último bloco é ignorado

    RealocateActionBlock();
	//Reseta variáveis para um novo elemento

    nCurrentElement=0;
    nCurrentClsn=0;
    nCurrentClsn2=0;
    pTempList=NULL;
    pTempClsn=NULL;
    bClsnDefault=false;

    Debug::debug(Debug::resources,__FUNCTION__) << "CAirManager::AddAction" << " - " << "Action" << " = " << nActionNumber << endl;

    pTempList=new AirLinkedList;

    //Set all to Zero
    memset(pTempList,0,sizeof(AirLinkedList));
    pTempList->ElementData.loopStart=-1;
    pTempList->ElementData.nActionNumber=nActionNumber;

    //Allocate 100 Elemant and then realc it
    pTempList->ElementData.AnimationElement= (Element*) malloc(sizeof(Element)* 100);

    if(pTempList->ElementData.AnimationElement==NULL)

		Debug::debug(Debug::resources,__FUNCTION__) << "CAirManager::AddAction" << " - " << "Cannot allocate Memory for: " << "Airmanager" << endl;

   //Allocate 100 Clsn boxes for evry Element
    for(int i=0;i<100;i++)
        pTempList->ElementData.AnimationElement[i].pClnsData=(Clsn*) malloc(sizeof(Clsn)*100);


    m_AirList.Adicionar(pTempList);
}
//Reallocates unessery memory
void CAirManager::RealocateActionBlock()
{
    Clsn *pTemp;

     Debug::debug(Debug::resources,__FUNCTION__) << "CAirManager::RealocateActionBlock"<< " "<< "Running"<< endl;


    if(pTempList!=NULL && nCurrentElement!=0 )
    {
        for(int i=nCurrentElement;i<100;i++)
         {
          pTemp=pTempList->ElementData.AnimationElement[i].pClnsData;
          Debug::debug(Debug::font,__FUNCTION__) << "Freeing "<<endl;

		  free(pTemp);
          pTemp=NULL;

         }
         pTempList->ElementData.AnimationElement= (Element*) realloc(pTempList->ElementData.AnimationElement,sizeof(Element)*(nCurrentElement));

    }

}

void CAirManager::AddElement(int nGroupNumber,int nImageNumber,int x,int y,
                             int nDuringTime,Uint16 nFlip,Uint16 nColorFlag)
{

     Debug::debug(Debug::resources,__FUNCTION__) << "CAirManager::AddElement" << " "<<"Running" << endl;
    //if we have more then 100 elements reallocate 100 elements to it
    if(nCurrentElement==100)
    {
       pTempList->ElementData.AnimationElement=(Element*) realloc(pTempList->ElementData.AnimationElement,sizeof(Element)*200);
        for(int i=100;i<200;i++)
        pTempList->ElementData.AnimationElement[i].pClnsData=(Clsn*) malloc(sizeof(Clsn)*100);

       Debug::debug(Debug::resources,__FUNCTION__) << "CAirManager::AddElement"<<" - " << "Temp= " <<pTempList << endl ;
    }

    Debug::debug(Debug::resources,__FUNCTION__) << "CAirManager::AddElement" << " - " <<"Group= " << nGroupNumber << "Image= " << nImageNumber << " x= " << x << " y= " << y << " " <<"DuringTime= "<< nDuringTime  << endl;

    //Fill the element with the Values
    pTempList->ElementData.AnimationElement[nCurrentElement].nGroupNumber=nGroupNumber;
    pTempList->ElementData.AnimationElement[nCurrentElement].nImageNumber=nImageNumber;
    pTempList->ElementData.AnimationElement[nCurrentElement].x=x;
    pTempList->ElementData.AnimationElement[nCurrentElement].y=y;
    pTempList->ElementData.AnimationElement[nCurrentElement].nNumberOfClsn=nCurrentClsn;
    pTempList->ElementData.AnimationElement[nCurrentElement].nDuringTime=nDuringTime;
    pTempList->ElementData.AnimationElement[nCurrentElement].ColorFlags=nColorFlag;
    pTempList->ElementData.AnimationElement[nCurrentElement].FlipFlags=nFlip;
    pTempList->ElementData.nNumberOfElements=nCurrentElement;
    //calculate the time
    pTempList->ElementData.dwCompletAnimTime+=nDuringTime;

    if(bClsnDefault)
    {
          memcpy(pTempList->ElementData.AnimationElement[nCurrentElement].pClnsData,pTempClsn,sizeof(Clsn)*nCurrentClsn2);
          pTempList->ElementData.AnimationElement[nCurrentElement].nNumberOfClsn=nCurrentClsn2;

          //Debug::debug(Debug::resources,__FUNCTION__) << "CAirManager::AddElement - In Action " << pTempList->ElementData.nActionNumber << endl;
    }


    //Now realloc the 100 Clsn element to to the right amount of it
    if(nCurrentClsn!=0 && !bClsnDefault )
    {
        pTempList->ElementData.AnimationElement[nCurrentElement].pClnsData=(Clsn*)realloc(pTempList->ElementData.AnimationElement[nCurrentElement].pClnsData,sizeof(Clsn)*(nCurrentClsn));
    }

    if(nCurrentClsn!=0 && bClsnDefault )
    {
        pTempList->ElementData.AnimationElement[nCurrentElement].pClnsData=(Clsn*)realloc(pTempList->ElementData.AnimationElement[nCurrentElement].pClnsData,sizeof(Clsn)*(nCurrentClsn2));
    }

    if(nCurrentClsn==0 && !bClsnDefault)
    {
       Debug::debug(Debug::font,__FUNCTION__) << "Freeing "<<endl;

		free(pTempList->ElementData.AnimationElement[nCurrentElement].pClnsData);
       pTempList->ElementData.AnimationElement[nCurrentElement].pClnsData=NULL;
    }

    //End of realocation stuff

    //reset Clsn counter
    nCurrentClsn=0;
    nCurrentElement++;

}

void CAirManager::SetLoop()
{
    pTempList->ElementData.loopStart=nCurrentElement;

}
//to add a Clsn box
void CAirManager::AddClsnBox(short x,short y,short w,short h,int nNumberOfClsn)
{
    //Error handling
    if(nNumberOfClsn!=nCurrentClsn2)
    {

        Debug::debug(Debug::resources,__FUNCTION__) << "CAirManager::AddClsnBox" << " " << "Error Index of clsn is not equal to current index"<<" ("<< nNumberOfClsn << " != " << nCurrentClsn << ")" << endl;
        Debug::debug(Debug::resources,__FUNCTION__) << "Number of total Clsn boxes"<< " " << nHowManyClsn << endl;;

    }

    pTempList->ElementData.AnimationElement[nCurrentElement].pClnsData[nCurrentClsn].bClsn1=bClsn1or2;
    pTempList->ElementData.AnimationElement[nCurrentElement].pClnsData[nCurrentClsn].ClsnRect.x=x;
    pTempList->ElementData.AnimationElement[nCurrentElement].pClnsData[nCurrentClsn].ClsnRect.y=y;
    pTempList->ElementData.AnimationElement[nCurrentElement].pClnsData[nCurrentClsn].ClsnRect.w=w;
    pTempList->ElementData.AnimationElement[nCurrentElement].pClnsData[nCurrentClsn].ClsnRect.h=h;

    if(bClsnDefault)
    {
           pTempClsn=pTempList->ElementData.AnimationElement[nCurrentElement].pClnsData;
//           Debug::debug(Debug::resources,__FUNCTION__) << "In Action "<< pTempList->ElementData.nActionNumber << endl;

    }


    nCurrentClsn2++;
    nCurrentClsn++;

}

void CAirManager::CreateClsnBox(int nNumberOfClsn,bool bClsn1,bool bDefault)
{
   // nCurrentClsn=0;
    nCurrentClsn2=0;
    nHowManyClsn=nNumberOfClsn;
    bClsnDefault=bDefault;
    bClsn1or2=bClsn1;
   Debug::debug(Debug::resources,__FUNCTION__) << "CAirManager::CreateClnsBox" << " "<<"Number of Clns=" <<nNumberOfClsn << "bClsn1 =" << bClsn1 << "bDefault=" << bDefault << endl;

}

ActionElement* CAirManager::GetAction(int nActionNumber)
{
	m_AirList.SetStart();
	//char str[255];

	while(m_AirList.GetAirData())
	{

		if(m_AirList.GetAirData()->ElementData.nActionNumber==nActionNumber)
			return &m_AirList.GetAirData()->ElementData;

		m_AirList.Next();

	}

	Debug::debug(Debug::resources,__FUNCTION__) << "CAirManager::GetAction" << " - " << nActionNumber << " " << "Action number not found" << endl;

    return NULL;


}

void CAirManager::OpenAir(const char *strFileName)
{

    //AirCompilerOld::Driver driver(this);
	//Todo Make a parser to fullfill AirManager
	SGF::Util::CReferenceCount<SGF::Ast::CAstManager> parsed = CResource::getAIRParsedFile(Filesystem::CAbsolutePath(strFileName));
	nHowManyBlocks=0;

    Debug::debug(Debug::resources,__FUNCTION__) << "CAirManager::OpenAir Loading" <<" " << strFileName << endl;
     //now reallocate the last Actionblock
	//driver.parse_file(strFileName);
	RealocateActionBlock();

    Debug::debug(Debug::resources,__FUNCTION__) << "CAirManager::OpenAir"<< " " << strFileName <<"has " << nHowManyBlocks << "action ellements" << endl;

}

void CAirManager::CleanUp()
{

    Debug::debug(Debug::resources,__FUNCTION__) << "CAirManager::CleanUP" <<" "<< "Cleaning air list" << endl;
	m_AirList.SetStart();

	if(m_AirList.Corrente!=NULL)
	{
		while(m_AirList.Corrente)
		{

    	if(m_AirList.GetAirData()->ElementData.AnimationElement!=NULL)
		{
	   	    if(m_AirList.GetAirData()->ElementData.AnimationElement->pClnsData!=NULL)
               delete m_AirList.GetAirData()->ElementData.AnimationElement->pClnsData;

        	delete m_AirList.GetAirData()->ElementData.AnimationElement;

		}

			m_AirList.Next();

		}

	}
	Reset();
	m_AirList.CleanUpTheList();

}
} //end SGF