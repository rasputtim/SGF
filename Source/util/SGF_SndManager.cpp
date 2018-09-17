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


#include "util/SGF_SndManager.h"
#include "util/SGF_Timedif.h"
namespace SGF {

// Todo: utilizar apenas um construtor => unificar os dois em apenas um
CSndSoundManager::CSndSoundManager(const string strFileName)
{
	FILE *SndFile;
    //Local Variables
	SNDHEADER SndHeader;
	//char strErrorMsg[255];
	short SingCheck=0;

	nCurrentChunk=0;
	TimeDifference diff;
    diff.startTime();
	
	Debug::debug(Debug::resources,__FUNCTION__) << "CSndSoundManager Loading "<<strFileName<<endl;

	memset(&SndHeader,0,sizeof(SndHeader));

	
	//Open the Snd file
	SndFile=fopen(strFileName.c_str(),"rb");

	//if cant open the file then say it
	if(SndFile==NULL)
	{
	  Debug::debug(Debug::resources,__FUNCTION__) << "CSndSoundManager %s File not found "<<strFileName<<endl;

	  return;

	}

	//read the header of the file
	fread(&SndHeader,sizeof(SndHeader),1,SndFile);

	//now check the File Signatur (i know there are better ways to do that)
	for(int i=0;i<11;i++)
		SingCheck+=SndHeader.signature[i];
    Debug::debug(Debug::resources,__FUNCTION__) << "CSndSoundManager::InitSoundManager File signature :" <<SingCheck <<endl;
	//if it is not an SND file then say it and quit
	if(SingCheck!=1106)
	{
		Debug::debug(Debug::resources,__FUNCTION__) << "CSndSoundManager::InitSoundManager Snd file Signature of "<<strFileName<<" is Invalid"<<endl;
		return;

	}
	//now move the filepointer to 1st Sub header
	fseek(SndFile,SndHeader.SubHeaderFileOffset,SEEK_SET);
	//this procedure reads all the subheaders and decodes the images
	DecodeWavFromSnd(SndFile,SndHeader.nNumberOfSounds);
	//Strore the current time and caluate now how much time this has take
	diff.endTime();
	Debug::debug(Debug::gameConfiguration,__FUNCTION__) << "Snd Chunks loaded in "  << diff.printTime("") << endl;


	fclose(SndFile);
}
/*
CSndSoundManager::CSndSoundManager(string& strFileName)
{

    //Local Variables
	SNDHEADER SndHeader;
	char strErrorMsg[255];
	short SingCheck=0;

	nCurrentChunk=0;
	Uint32 startTime,endTime;

	//Store the current time to calulate how much time the procedure takes
	startTime=SDL_GetTicks();
	Debug::debug(Debug::resources,__FUNCTION__) << "CSndSoundManager Loading "<<strFileName<<endl;

	memset(&SndHeader,0,sizeof(SndHeader));

	SndFile=NULL;
	//Open the Snd file
	SndFile=fopen(strFileName.c_str(),"rb");

	//if cant open the file then say it
	if(SndFile==NULL)
	{
	  Debug::debug(Debug::resources,__FUNCTION__) << "CSndSoundManager %s File not found "<<strFileName<<endl;

	  return;

	}

	//read the header of the file
	fread(&SndHeader,sizeof(SndHeader),1,SndFile);

	//now check the File Signatur (i know there are better ways to do that)
	for(int i=0;i<11;i++)
		SingCheck+=SndHeader.signature[i];
#ifdef DEBUG
    Debug::debug(Debug::resources,__FUNCTION__) << "CSndSoundManager::InitSoundManager File signature (%i)",SingCheck);
#endif
	//if it is not an SND file then say it and quit
	if(SingCheck!=1106)
	{
		Debug::debug(Debug::resources,__FUNCTION__) << "CSndSoundManager::InitSoundManager Snd file Signature of "<<strFileName<<" is Invalid"<<endl;
		return;

	}
	//now move the filepointer to 1st Sub header
	fseek(SndFile,SndHeader.SubHeaderFileOffset,SEEK_SET);
	//this procedure reads all the subheaders and decodes the images
	DecodeWavFromSnd(SndFile,SndHeader.nNumberOfSounds);
	//Strore the current time and caluate now how much time this has take
	endTime=SDL_GetTicks();
	Debug::debug(Debug::resources,__FUNCTION__) << "CSndSoundManager::InitSoundManager Snd Chunks loaded in "<<endTime-startTime<<" milliseconds!"<<endl;

	fclose(SndFile);
}
*/
CSndSoundManager::~CSndSoundManager()
{
    this->ClearUpSoundManager();

}
/*
//Loads the give Snd file and decode the sounds
void CSndSoundManager::InitSoundManager(char* strFileName)
{

	//Local Variables
	SNDHEADER SndHeader;
	char strErrorMsg[255];
	short SingCheck=0;

	nCurrentChunk=0;
	Uint32 startTime,endTime;

	//Store the current time to calulate how much time the procedure takes
	startTime=SDL_GetTicks();
	Debug::debug(Debug::resources,__FUNCTION__) << "CSndSoundManager Loading %s",strFileName);

	memset(&SndHeader,0,sizeof(SndHeader));

	SndFile=NULL;
	//Open the Snd file
	SndFile=fopen(strFileName,"rb");

	//if cant open the file then say it
	if(SndFile==NULL)
	{
	  Debug::debug(Debug::resources,__FUNCTION__) << "CSndSoundManager %s File not found",strFileName);

	  return;

	}

	//read the header of the file
	fread(&SndHeader,sizeof(SndHeader),1,SndFile);

	//now check the File Signatur (i know there are better ways to do that)
	for(int i=0;i<11;i++)
		SingCheck+=SndHeader.signature[i];
#ifdef DEBUG
    Debug::debug(Debug::resources,__FUNCTION__) << "CSndSoundManager::InitSoundManager File signature (%i)",SingCheck);
#endif
	//if it is not an SND file then say it and quit
	if(SingCheck!=1106)
	{
		Debug::debug(Debug::resources,__FUNCTION__) << "CSndSoundManager::InitSoundManager Snd file Signature of %s is Invalid",strFileName);
		return;

	}
	//now move the filepointer to 1st Sub header
	fseek(SndFile,SndHeader.SubHeaderFileOffset,SEEK_SET);
	//this procedure reads all the subheaders and decodes the images
	DecodeWavFromSnd(SndFile,SndHeader.nNumberOfSounds);
	//Strore the current time and caluate now how much time this has take
	endTime=SDL_GetTicks();
	Debug::debug(Debug::resources,__FUNCTION__) << "CSndSoundManager::InitSoundManager Snd Chunks loaded in %i milliseconds!",endTime-startTime);

	fclose(SndFile);
} */

//The main Image decode function
void CSndSoundManager::DecodeWavFromSnd(FILE *SndFile,short nSounds)
{
	//Snd file Subheader struct
	SNDSUBHEADER SndSubHeader;
	BYTE *		 tempByte;
//	FILE *		pWavFile=NULL;

	//WAVHEADER WavHeader;
	//SNDDATA tempSndSound;
	SoundLinkedList* tempSndList;
	SGF_Dword dwUseOfRam=0;
	nTotalChunks=0;
	

	memset(&SndSubHeader,0,sizeof(SndSubHeader));
	//memset(&tempSndSound,0,sizeof(tempSndSound));

	fread(&SndSubHeader,sizeof(SndSubHeader),1,SndFile);

	//File offset of the Next SubHeader is Null if it is the last?Is this right????
	int group,sample;
	//Loop till the file reaches the end
	while(!feof(SndFile))
	{
		group= SndSubHeader.nGroupNumber;
		sample = SndSubHeader.SampleNumber;
		
		//Create a new Linked list enterny
	/*	tempSndList=new SoundLinkedList;
		tempSndSound.nGroupNumber=group;
		tempSndSound.nSampleNumber=sample;
		*/
		//Read the wav header
		//fread(&WavHeader,sizeof(WavHeader),1,SndFile);

		//Copy the WAV header
		//tempSndSound. WavHeader=WavHeader;

		//A littel trick to be sure that the data is an WAV
		//if(WavHeader.RIFFType==10 && SndSubHeader.LenghtOfSubheader!=0)
        if(SndSubHeader.SubFileLenght!=0)
		{
			//the wav header is valid so it is not an linked image
			//tempSndSound. .bIsLinked=false;
			//Allocate memory to save the chunk in to the memory
			//tempbyte é deletado qdo CSound for deletado
			tempByte = new BYTE[SndSubHeader.SubFileLenght];
			//now read and copy the chunk in to the allocated memory
			fread(tempByte,SndSubHeader.SubFileLenght,1,SndFile);
			//move the file pointer to Color pallet of the PCX file
			//fseek(SndFile,-768L,SEEK_CUR);

			//Eat an Empty 8bit block
			//fgetc(SndFile);

			//now check if it is nesecery to read the color table
		/*	tempSndSound.nLenght=SndSubHeader.SubFileLenght;
			tempSndSound.bySndData=tempByte;
			tempSndSound.pCSound=new CSound(tempByte);
			//tempSndSound.bPalletSame=SndSubHeader.PalletSame;
			tempSndList->SoundData=tempSndSound;
			SndSoundList.Adicionar(tempSndList); */
			Debug::debug(Debug::sound,__FUNCTION__) << "WILL Load (Group,item): ( "<< group <<" , "<< sample<<" ) " << endl;
			Util::CReferenceCount<CMugenSound> tempsound=Util::CReferenceCount<CMugenSound>(new CMugenSound(new CSound(tempByte)));
			tempsound->groupNumber=group;
			tempsound->sampleNumber=sample;
			tempsound->length=SndSubHeader.SubFileLenght;
			tempsound->sample=tempByte;
			sounds[group][sample]= tempsound;

		}
		/* else
		{
			//if is a Previous copy it
			if(SndSubHeader.IndexOfPrevious>0 && SndSubHeader.LenghtOfSubheader==0)
			{
				SndSoundList.SetStart();

				//goto the previeus
				for(int j=0;j<=SndSubHeader .IndexOfPrevious-1;j++)
					SndSoundList.Next();

				tempSndSound.byPcxFile=SndSoundList.GetSoundData()->SoundData.byPcxFile;
				tempSndSound.bIsLinked=true;
				tempSndSound.WavHeader=SndSoundList.GetSoundData()->SoundData.WavHeader;
				memcpy(&tempSndSound.ColorPallet,&SndSoundList.GetSoundData()->SoundData.ColorPallet,sizeof(ColorPallet));
				SndSoundList.SetEnd();

				tempSndList->SoundData=tempSndSound;

				SndSoundList.Hinzufuegen(tempSndList);
			}

		}*/
		dwUseOfRam+=SndSubHeader.SubFileLenght;

		nTotalChunks++;

		//Seek to the next Subheader
		fseek(SndFile,SndSubHeader.NextSubHeaderFileOffset,SEEK_SET);

		//read the next Subheader
		fread(&SndSubHeader,sizeof(SndSubHeader),1,SndFile);

	}
		Debug::debug(Debug::resources,__FUNCTION__) << "CSndSoundManager "<< nTotalChunks <<" Chunks are Decoded from the total of "<<nSounds <<endl;

		Debug::debug(Debug::resources,__FUNCTION__) << "CSndSoundManager Snd File has used "<< dwUseOfRam/1024 <<" KBytes of ram"<<endl;


}

void CSndSoundManager::TestSoundManager()
{
/*	SndSoundList.SetStart();
	while(SndSoundList.GetSoundData())
	{
		PlayChunk(LoadChunkMem((Uint8 *)SndSoundList.Corrente->SoundData.bySndData));
		WaitAnyAvailableChannel();
		SndSoundList.Next();
	}
	*/
}

void CSndSoundManager::ClearUpSoundManager()
{
	/* the reference cuntwill delete it
	MugenSoundMap::iterator first_it = sounds.begin();
	for(first_it;first_it!=sounds.end();first_it++) {
		for(MugenSoundGroup::iterator it = first_it->second.begin();it != first_it->second.end();it++){
                if ((*it).second!=NULL) delete (*it).second;
       }

	} */
}


#if 0
SNDDATA CSndSoundManager::GetSndSound(short nGroupNumber,short nSoundNumber)
{


	//SndSoundList.SetStart();
	SNDDATA NoChunk;
	//memset(&NoChunk,0,sizeof(NoChunk));
//	char str[255];
			SndSoundMap::iterator first_it = sounds.find(nGroupNumber);
            if (first_it != sounds.end()){
				map<unsigned int, Util::CReferenceCount<CSound>>::iterator it = first_it->second.find(nSoundNumber);
                if (it != first_it->second.end()){
					
					Util::CReferenceCount<CSound> sound = sounds[nGroupNumber][nSoundNumber];
					NoChunk.pCSound= sound.data;
					NoChunk.nGroupNumber= nGroupNumber;
					NoChunk.nSampleNumber=nSoundNumber;
                }	
				
			}

/*	while(SndSoundList.GetSoundData())
	{
		if(SndSoundList.GetSoundData()->SoundData.nSampleNumber==nSoundNumber
		&& SndSoundList.GetSoundData()->SoundData.nGroupNumber==nGroupNumber)
		{



			return SndSoundList.GetSoundData()->SoundData;


		}
		SndSoundList.Next();


	}*/

	Debug::debug(Debug::resources,__FUNCTION__) << "CSndSoundManager Sound with groubnumber "<<nGroupNumber<<" and soundnumber "<<nSoundNumber <<" not found"<<endl;

	return NoChunk;

}
#endif
Util::CReferenceCount<CMugenSound > CSndSoundManager::getSNDSound (short nGroupNumber,short nSoundNumber){
	MugenSoundMap::iterator first_it = sounds.find(nGroupNumber);
            if (first_it != sounds.end()){
				MugenSoundGroup::iterator it = first_it->second.find(nSoundNumber);
                if (it != first_it->second.end()){
					
				return	 sounds[nGroupNumber][nSoundNumber];
					
                }	
				
			}
		return 	NULL;

}

void CSndSoundManager::Play(short nGroupNumber,short nSoundNumber) {
	Util::CReferenceCount<CMugenSound> sound=getSNDSound(nGroupNumber,nSoundNumber);
	if (sound !=NULL) sound->play();
}

void CSndSoundManager::PlayLoop(short nGroupNumber,short nSoundNumber) {

	Util::CReferenceCount<CMugenSound> sound=getSNDSound(nGroupNumber,nSoundNumber);
	if (sound !=NULL) sound->sound->playLoop();
	}

void CSndSoundManager::PlaySomeTimes(short nGroupNumber,short nSoundNumber, int times) {

	Util::CReferenceCount<CMugenSound > sound=getSNDSound(nGroupNumber,nSoundNumber);
   if (sound !=NULL) sound->sound->playSomeTimes(times);
	}

void CSndSoundManager::readSounds(const string & filename, MugenSoundMap & m_sounds){
    
    int group,sample;
	MugenSoundMap::iterator first_it;
	MugenSoundGroup::iterator it;
	for (first_it=sounds.begin();first_it!=sounds.end();first_it++) {
		group = first_it->first;
			for(it = first_it->second.begin();it != first_it->second.end();it++){
				m_sounds[group][it->first]= (it->second);  //verificar se não é necessário criar um novo objeto ao invés de usar o já existente
				
                }


		

	}
	

}

} //end SGF