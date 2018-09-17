/* from http://www.bmarquis.com/wiki/index.php5?title=Elecbyte_Spritesheet_File_Format_Version_2 */
#include <iostream>
#include <cmath>
#include <cstring>
#include <sstream>
#include <map>
#include <string>
#include <vector>
//#include "sff.h"
#include "sprite/defs.h"
#include "util/SGF_FileSystem.h"
//#include "util/graphics/bitmap.h"
#include "util/SGF_Pointer.h"
#include "sprite/SGF_MugenSprite.h"
using std::map;
using std::string;
using std::vector;

#if 0  
unsigned long RLE8_Packet::SetPacket(ifstream &In, uint8_t* Sprite, unsigned long &Ofs)
{
    //bytecount allows the program to count all bytes processed, to be used by SFF2_FileHeader::GetSprite to determine the end of the data
    unsigned long bytecount = 0;
    RunMarker = 0;
    uint8_t Raw = 0;
    In.read((char*)&Raw,sizeof(uint8_t)); //Read raw byte.
    bytecount+=sizeof(uint8_t);           //increment byte counter
    RunMarker = Raw & 0xC0;
    RunLength = Raw & 0x3F;
    if(RunMarker == 0x40)                //If the run marker is set...
    {
        In.read((char*)&Raw,sizeof(uint8_t));//Read another byte for color.
        bytecount+=sizeof(uint8_t);          //and increment.
        for(int a=0; a<RunLength; a++)
        {
            Sprite[Ofs] = Raw;
            Ofs++;
        }
    }
    else                                //Or else this is the color you are searching for
    {
        Sprite[Ofs] = Raw;
        Ofs++;
    }
    return bytecount;
}
 
unsigned long RLE5_Packet::Set3R5V(ifstream &In, uint8_t* Sprite, unsigned long &Ofs)
{
    unsigned long bytecount = 0;
    In.read((char*)&P3R5V,sizeof(uint8_t));  //Read the packet.
    bytecount+=sizeof(uint8_t);
    uint8_t P5V = P3R5V & 0x1F;              //Break it down. P5V is the Packet's 5-bit color value.
    uint8_t P3R = (P3R5V >>5)+1;             //P3R is the packets 3-bit run length plus 1, so increment it, as well.
    for(int a=0; a<P3R; a++)
    {
        Sprite[Ofs] = P5V;
        Ofs++;
    }
    return bytecount;
}
 
unsigned long RLE5_Packet::SetPacket(ifstream &In, uint8_t* Sprite, unsigned long &Ofs)
{
    unsigned long bytecount = 0;
    uint8_t Raw;
    In.read((char*)&RunLength,sizeof(uint8_t));  //Read the run length.
    RunLength++;                                 //Remember to increment it after getting it out of the stream
    bytecount+=sizeof(uint8_t);
    In.read((char*)&Raw,sizeof(uint8_t));        //Read raw byte
    bytecount+=sizeof(uint8_t);
    ColorBit = Raw & 0x80;                       //ColorBit = Raw>>7
    DataLength = Raw & 0x7F;
    if(ColorBit)                                 //If the color bit is set
    {
        In.read((char*)&Raw,sizeof(uint8_t));    //Read the color
        bytecount+=sizeof(uint8_t);
    }
    else
    {
        Raw = 0;                                  //Or else the color is 0.
    }
    for(int a=0; a<RunLength; a++)
    {
        Sprite[Ofs] = Raw;
        Ofs++;
    }
    for(int a=0; a<DataLength; a++)
    {
        bytecount+=Set3R5V(In, Sprite, Ofs);      //Now it will process all the 3R5V packets in the main packet
    }
    return bytecount;
}
 
/*Instead of giving LZ5::SetPacket a return value, I thought it'll be feasible to have a countdown argument.
The purpose of this is because even though the control byte is 8-bits, all 8 bits are not used in the last packet*/
void LZ5_Packet::SetPacket(ifstream &In, uint8_t* Sprite, unsigned long &Ofs, unsigned long &countdown)
{
    In.read((char*)&CtrlByte, sizeof(uint8_t));//Read the control byte
	countdown-=sizeof(uint8_t);                //Decrement everytime you do use In.read
    for(uint8_t a=0; a<8 ; a++)
    {
        uint8_t b = uint8_t(pow(2.0,(int)a )); //This allows me to AND the control byte to determine which packet is next in line
        if(countdown)                          //This allows me to stop when all bytes have been processed
        {
            if(CtrlByte & b)DtrmnLZ(In, Sprite, Ofs, countdown); //If the bit is set, then it's an LZ packet
            else DtrmnRLE(In, Sprite, Ofs, countdown);           //If not, then it's an RLE packet
        }
    }
}
 
void LZ5_Packet::DtrmnLZ(ifstream &In, uint8_t* Sprite, unsigned long &Ofs, unsigned long &countdown)
{
    uint8_t Raw = (uint8_t)In.peek(); //Just need to peak.
    if(Raw &0x3F)                           //If it's still nonzero...
    {
        ProcessSLZ(In, Sprite, Ofs, countdown); //then the next packet is a Short LZ
    }
    else
    {
        ProcessLLZ(In, Sprite, Ofs, countdown); //those 5 bits are nothing, away. let's go long!
    }
}
 
void LZ5_Packet::ProcessSLZ(ifstream &In, uint8_t* Sprite, unsigned long &Ofs, unsigned long &countdown)
{
    uint8_t CopyLength;
    RecyBin++;                                  //The recycle bin, because this packet is eco-friendly.
    In.read((char*)&ShrtLZ[0],sizeof(uint8_t));
	countdown-=sizeof(uint8_t);
    if(RecyBin != 4)                            //we need another byte if the recycle bin isn't full
    {
        In.read((char*)&ShrtLZ[1],sizeof(uint8_t));
		countdown-=sizeof(uint8_t);
    }
    CopyLength = ShrtLZ[0] & 0x3f;
    CopyLength++;
    RecyByte = RecyByte << 2;
    RecyByte = RecyByte | (ShrtLZ[0]>>6) ;
    if(RecyBin == 4)
    {
        uint16_t Off = RecyByte+1;
        LZ_Copy(Sprite+Ofs,&Off,CopyLength);
        Ofs+=CopyLength;
        RecyByte = 0;                             //Clear the recycle byte.
        RecyBin = 0;                              //Empty the recycle bin
    }
    else
    {
        uint16_t Off = ShrtLZ[1]+1;
        LZ_Copy(Sprite+Ofs,&Off,CopyLength);
        Ofs+=CopyLength;
    }
}
 
void LZ5_Packet::ProcessLLZ(ifstream &In, uint8_t* Sprite, unsigned long &Ofs, unsigned long &countdown)
{
    uint32_t Off;                            //Same philosophy goes with offsets.
    In.read((char*)&LongLZ,sizeof(uint8_t)*3);
	countdown-=(sizeof(uint8_t))*3;
    Off =  LongLZ[0]<<2| LongLZ[1];     //ORing is okay, seeing is that almost everything is 0's, anyway.
    Off++;
    uint32_t CopyLength = LongLZ[2]+3;
    LZ_Copy(Sprite+Ofs,&Off,CopyLength);
    Ofs+=CopyLength;
}
 
void LZ5_Packet::LZ_Copy(uint8_t *dst, const uint16_t *ofs, unsigned int num)
{
 
    naivememcpy(dst,dst-*ofs, num);
}
 
void LZ5_Packet::LZ_Copy(uint8_t *dst, const uint32_t *ofs, unsigned int num)
{
 
    naivememcpy(dst, dst-*ofs, num);
}
 
void LZ5_Packet::naivememcpy(uint8_t *dst, const uint8_t *src, unsigned int num)
{
    uint8_t mybyte;
    while(num--)
    {
        mybyte=*src++;
        *dst++=mybyte;
    }
}
 
void LZ5_Packet::DtrmnRLE(ifstream &In, uint8_t* Sprite, unsigned long &Ofs, unsigned long &countdown)
{
    uint8_t Raw = (uint8_t)In.peek();
    if(Raw& 0xE0)                               //If taking out the bits still gives you something...
    {
        ProcessSRLE(In, Sprite, Ofs, countdown);//Then it's a Short RLE
    }
    else
    {
        ProcessLRLE(In, Sprite, Ofs, countdown);
    }
}
 
void LZ5_Packet::ProcessSRLE(ifstream &In, uint8_t* Sprite, unsigned long &Ofs, unsigned long &countdown)
{
    uint8_t Raw, Color, RunLength;
    In.read((char*)&Raw, sizeof(uint8_t));
	countdown-=sizeof(uint8_t);
    Color = Raw & 0x1F;
    RunLength = Raw >> 5;
    for(int a=0; a<RunLength;a++)
    {
        Sprite[Ofs] = Color;
        Ofs++;
    }
}
 
void LZ5_Packet::ProcessLRLE(ifstream &In, uint8_t* Sprite, unsigned long &Ofs, unsigned long &countdown)
{
    uint8_t Raw, Color,RunLength;
    In.read((char*)&Raw, sizeof(uint8_t));
	countdown-=sizeof(uint8_t);
    Color = Raw & 0x1F;
    In.read((char*)&RunLength, sizeof(uint8_t));
	countdown-=sizeof(uint8_t);
    for(int a=0; a<(uint16_t)RunLength+8;a++)
    {
        Sprite[Ofs] = Raw;
        Ofs++;
    }
}
 
LZ5_Packet::LZ5_Packet()
{
    RecyBin = 0; //You always need to start this off at 0.
    RecyByte = 0;
}
 
SFF2_FileHeader::SFF2_FileHeader()
{
 
}
 
SFF2_FileHeader::SFF2_FileHeader(ifstream &In)
{
    In.read(signature,12);
    In.read((char*)&verlo3,sizeof(uint8_t));
    In.read((char*)&verlo2,sizeof(uint8_t));
    In.read((char*)&verlo1,sizeof(uint8_t));
    In.read((char*)&verhi,sizeof(uint8_t));
    In.read((char*)&reserved0,sizeof(long));
    In.read((char*)&reserved1,sizeof(long));
    In.read((char*)&compatverlo3,sizeof(uint8_t));
    In.read((char*)&compatverlo2,sizeof(uint8_t));
    In.read((char*)&compatverlo1,sizeof(uint8_t));
    In.read((char*)&compatverhi,sizeof(uint8_t));
    In.read((char*)&reserved2,sizeof(long));
    In.read((char*)&reserved3,sizeof(long));
    In.read((char*)&sproff,sizeof(unsigned long));
    In.read((char*)&sprcount,sizeof(unsigned long));
    In.read((char*)&paloff,sizeof(unsigned long));
    In.read((char*)&palcount,sizeof(unsigned long));
    In.read((char*)&ldataoff,sizeof(unsigned long));
    In.read((char*)&ldatalen,sizeof(unsigned long));
    In.read((char*)&tdataoff,sizeof(unsigned long));
    In.read((char*)&tdatalen,sizeof(unsigned long));
    In.read((char*)&reserved4,sizeof(long));
    In.read((char*)&reserved5,sizeof(long));
    In.read(unused,436);
}
 
bool SFF2_FileHeader::isGenuine()
{
    if(!strcmp(signature, "ElecbyteSpr"))
        return true;
    return false;
}
 
unsigned long SFF2_FileHeader::GetlData()
{
    return ldataoff;
}
 
SprNode* SFF2_FileHeader::GetSprNode(ifstream &In, unsigned long index)
{
    if(index>=sprcount)
        return NULL;
    In.seekg(sproff+(28*index),ios::beg);
    SprNode *temp = new SprNode(In);
    return temp;
 
}
 
PalNode* SFF2_FileHeader::GetPalNode(ifstream &In, unsigned long index)
{
    if(index>=palcount)
        return NULL;
    In.seekg(paloff+(16*index),ios::beg);
    PalNode *temp = new PalNode(In);
    return temp;
}
 
unsigned long SFF2_FileHeader::GetNumSpr()
{
    return sprcount;
}
 
unsigned long SFF2_FileHeader::GetNumPal()
{
    return palcount;
}
///////////////////////
SprNode::SprNode()
{
 
}
SprNode::SprNode(ifstream &In)
{
 
    In.read((char*)&groupno,sizeof(unsigned short));
    In.read((char*)&itemno,sizeof(unsigned short));
    In.read((char*)&width,sizeof(unsigned short));
    In.read((char*)&height,sizeof(unsigned short));
    In.read((char*)&axisx,sizeof(short));
    In.read((char*)&axisy,sizeof(short));
    In.read((char*)&linkoff,sizeof(unsigned short));
    In.read((char*)&format,sizeof(uint8_t));
    In.read((char*)&coldepth,sizeof(uint8_t));
    In.read((char*)&dataoff,sizeof(unsigned long));
    In.read((char*)&sprlen,sizeof(unsigned long));
    In.read((char*)&palind,sizeof(unsigned short));
    In.read((char*)&flags,sizeof(unsigned short));
}
 
 
unsigned short SprNode::GetWidth()
{
    return width;
}
 
unsigned short SprNode::GetHeight()
{
    return height;
}
 
unsigned long SprNode::GetData()
{
    return dataoff;
}
 
int SprNode::GetFormat()
{
    return format;
}
 
unsigned long SprNode::GetDataLen()
{
    return sprlen;
}
 
int SprNode::GetDepth()
{
    return coldepth;
}
 
unsigned short SprNode::GetFlags()
{
    return flags;
}
 
unsigned short SprNode::GetPalInd()
{
    return palind;
}
 
bool SprNode::isLinked()
{
    if(!sprlen)
        return true;
    return false;
}
 
unsigned long SprNode::GetOffset()
{
    return linkoff;
}
 
short SprNode::GetAxisX()
{
    return axisx;
}
short SprNode::GetAxisY()
{
    return axisy;
}
 
unsigned short SprNode::GetGroupNo()
{
    return groupno;
}
unsigned short SprNode::GetImageNo()
{
    return itemno;
}
/////////////////////////////
unsigned short PalNode::GetNumColors()
{
    return numcols;
}
unsigned long PalNode::GetData()
{
    return dataoff;
}
unsigned long PalNode::GetDataLen()
{
    return datalen;
}
 
unsigned long PalNode::GetOffset()
{
    return linkoff;
}
 
bool PalNode::isLinked()
{
    if(!datalen)
        return true;
    return false;
}
 
PalNode::PalNode(ifstream &In)
{
     In.read((char*)&groupno,sizeof(unsigned short));
     In.read((char*)&itemno,sizeof(unsigned short));
     In.read((char*)&numcols,sizeof(unsigned short));
     In.read((char*)&linkoff,sizeof(unsigned short));
     In.read((char*)&dataoff,sizeof(unsigned long));
     In.read((char*)&datalen,sizeof(unsigned long));
}
 
colorinfo *SFF2_FileHeader::GetColor (ifstream& In, PalNode *Node, int index)
{
    if(index>=Node->GetNumColors())
        return NULL;
    colorinfo *temp = new colorinfo;
    In.seekg(ldataoff+Node->GetData()+(4*index),ios::beg);
    In.read((char*)&temp->r,sizeof(uint8_t));
    In.read((char*)&temp->g,sizeof(uint8_t));
    In.read((char*)&temp->b,sizeof(uint8_t));
    In.read((char*)&temp->a,sizeof(uint8_t));
    return temp;
}
 
uint8_t *SFF2_FileHeader::GetSprite(ifstream &In,SprNode *Node)
{
    uint8_t *temp = new uint8_t[Node->GetHeight()*Node->GetWidth()];
    unsigned long offset=0, DataLength;
    if(Node->isLinked())
    {
        SprNode *LinkedNode = GetSprNode(In, Node->GetOffset());
        DataLength = LinkedNode->GetDataLen();
        delete LinkedNode;
    }
    else DataLength = Node->GetDataLen();
    if(Node->GetFlags()& 0x1)
        In.seekg((tdataoff+Node->GetData())+4,ios::beg);
    else In.seekg((ldataoff+Node->GetData())+4,ios::beg);
    switch(Node->GetFormat())
    {
        case 0:
        {
            In.read((char*)temp,Node->GetHeight()*Node->GetWidth());
            break;
        }
        case 1:
        {
            cout << "Invalid Packet" << endl;
            break;
        }
        case 2:
        {
            RLE8_Packet Packet;
            for(unsigned long a=0; a<DataLength-4;a=a)
            {
                a+= Packet.SetPacket(In,temp,offset);
            }
            break;
        }
        case 3:
        {
            RLE5_Packet Packet;
            for(unsigned long a=0; a<DataLength-4;a=a)
            {
                a+= Packet.SetPacket(In,temp,offset);
 
            }
            break;
        }
        case 4:
        {
            LZ5_Packet Packet;
            for(unsigned long a=DataLength-4; a>0;a=a)
            {
                Packet.SetPacket(In,temp,offset,a);
            }
            break;
        }
    }
    return temp;
}
 
extern "C"
{
    unsigned long RLE8_Packet::SetPacket(FILE* In, uint8_t* Sprite, unsigned long &Ofs)
    {
        //bytecount allows the program to count all bytes processed, to be used by SFF2_FileHeader::GetSprite to determine the end of the data
        unsigned long bytecount = 0;
        RunMarker = 0;
        uint8_t Raw = 0;
        fread(&Raw,1,sizeof(uint8_t),In); //Read raw byte.
        bytecount+=sizeof(uint8_t);           //increment byte counter
        RunMarker = Raw & 0xC0;
        RunLength = Raw & 0x3F;
        if(RunMarker == 0x40)                //If the run marker is set...
        {
            fread(&Raw,1,sizeof(uint8_t),In);//Read another byte for color.
            bytecount+=sizeof(uint8_t);          //and increment.
            for(int a=0; a<RunLength; a++)
            {
                Sprite[Ofs] = Raw;
                Ofs++;
            }
        }
        else                                //Or else this is the color you are searching for
        {
            Sprite[Ofs] = Raw;
            Ofs++;
        }
        return bytecount;
    }
 
    unsigned long RLE5_Packet::Set3R5V(FILE* In, uint8_t* Sprite, unsigned long &Ofs)
    {
        unsigned long bytecount = 0;
        fread(&P3R5V,sizeof(uint8_t),1,In);  //Read the packet.
        bytecount+=sizeof(uint8_t);
        uint8_t P5V = P3R5V & 0x1F;              //Break it down. P5V is the Packet's 5-bit color value.
        uint8_t P3R = (P3R5V >>5)+1;             //P3R is the packets 3-bit run length plus 1, so increment it, as well.
        for(int a=0; a<P3R; a++)
        {
            Sprite[Ofs] = P5V;
            Ofs++;
        }
        return bytecount;
    }
 
    unsigned long RLE5_Packet::SetPacket(FILE* In, uint8_t* Sprite, unsigned long &Ofs)
    {
        unsigned long bytecount = 0;
        uint8_t Raw;
        fread(&RunLength,sizeof(uint8_t),1,In);  //Read the run length.
        RunLength++;                                 //Remember to increment it after getting it out of the stream
        bytecount+=sizeof(uint8_t);
        fread(&Raw,1,sizeof(uint8_t),In);        //Read raw byte
        bytecount+=sizeof(uint8_t);
        ColorBit = Raw & 0x80;                       //ColorBit = Raw>>7
        DataLength = Raw & 0x7F;
        if(ColorBit)                                 //If the color bit is set
        {
            fread(&Raw,1,sizeof(uint8_t),In);    //Read the color
            bytecount+=sizeof(uint8_t);
        }
        else
        {
            Raw = 0;                                  //Or else the color is 0.
        }
        for(int a=0; a<RunLength; a++)
        {
            Sprite[Ofs] = Raw;
            Ofs++;
        }
        for(int a=0; a<DataLength; a++)
        {
            bytecount+=Set3R5V(In, Sprite, Ofs);      //Now it will process all the 3R5V packets in the main packet
        }
        return bytecount;
    }
 
    /*Instead of giving LZ5::SetPacket a return value, I thought it'll be feasible to have a countdown argument.
    The purpose of this is because even though the control byte is 8-bits, all 8 bits are not used in the last packet*/
    void LZ5_Packet::SetPacket(FILE* In, uint8_t* Sprite, unsigned long &Ofs, unsigned long &countdown)
    {
        fread(&CtrlByte,sizeof(uint8_t),1,In);//Read the control byte
        countdown-=sizeof(uint8_t);                //Decrement everytime you do use In.read
        for(uint8_t a=0; a<8 ; a++)
        {
            uint8_t b = uint8_t(pow(2.0,(int)a )); //This allows me to AND the control byte to determine which packet is next in line
            if(countdown)                          //This allows me to stop when all bytes have been processed
            {
                if(CtrlByte & b)DtrmnLZ(In, Sprite, Ofs, countdown); //If the bit is set, then it's an LZ packet
                else DtrmnRLE(In, Sprite, Ofs, countdown);           //If not, then it's an RLE packet
            }
        }
    }
 
    void LZ5_Packet::DtrmnLZ(FILE* In, uint8_t* Sprite, unsigned long &Ofs, unsigned long &countdown)
    {
        uint8_t Raw = (uint8_t)fgetc(In); //Just need to peak.
        ungetc(Raw,In);
        if(Raw &0x3F)                           //If it's still nonzero...
        {
            ProcessSLZ(In, Sprite, Ofs, countdown); //then the next packet is a Short LZ
        }
        else
        {
            ProcessLLZ(In, Sprite, Ofs, countdown); //those 5 bits are nothing, away. let's go long!
        }
    }
 
    void LZ5_Packet::ProcessSLZ(FILE* In, uint8_t* Sprite, unsigned long &Ofs, unsigned long &countdown)
    {
        uint8_t CopyLength;
        RecyBin++;                                  //The recycle bin, because this packet is eco-friendly.
        fread(&ShrtLZ[0],sizeof(uint8_t),1,In);
        countdown-=sizeof(uint8_t);
        if(RecyBin != 4)                            //we need another byte if the recycle bin isn't full
        {
            fread(&ShrtLZ[1],sizeof(uint8_t),1,In);
            countdown-=sizeof(uint8_t);
        }
        CopyLength = ShrtLZ[0] & 0x3f;
        CopyLength++;
        RecyByte = RecyByte << 2;
        RecyByte = RecyByte | (ShrtLZ[0]>>6) ;
        if(RecyBin == 4)
        {
            uint16_t Off = RecyByte+1;
            LZ_Copy(Sprite+Ofs,&Off,CopyLength);
            Ofs+=CopyLength;
            RecyByte = 0;                             //Clear the recycle byte.
            RecyBin = 0;                              //Empty the recycle bin
        }
        else
        {
            uint16_t Off = ShrtLZ[1]+1;
            LZ_Copy(Sprite+Ofs,&Off,CopyLength);
            Ofs+=CopyLength;
        }
    }
 
    void LZ5_Packet::ProcessLLZ(FILE* In, uint8_t* Sprite, unsigned long &Ofs, unsigned long &countdown)
    {
        uint32_t Off;                            //Same philosophy goes with offsets.
        fread(&LongLZ,sizeof(uint8_t),3,In);
        countdown-=(sizeof(uint8_t))*3;
        Off =  LongLZ[0]<<2| LongLZ[1];     //ORing is okay, seeing is that almost everything is 0's, anyway.
        Off++;
        uint32_t CopyLength = LongLZ[2]+3;
        LZ_Copy(Sprite+Ofs,&Off,CopyLength);
        Ofs+=CopyLength;
    }
 
    void LZ5_Packet::DtrmnRLE(FILE* In, uint8_t* Sprite, unsigned long &Ofs, unsigned long &countdown)
    {
        uint8_t Raw = (uint8_t)fgetc(In);
        ungetc(Raw,In);
        if(Raw& 0xE0)                               //If taking out the bits still gives you something...
        {
            ProcessSRLE(In, Sprite, Ofs, countdown);//Then it's a Short RLE
        }
        else
        {
            ProcessLRLE(In, Sprite, Ofs, countdown);
        }
    }
 
    void LZ5_Packet::ProcessSRLE(FILE* In, uint8_t* Sprite, unsigned long &Ofs, unsigned long &countdown)
    {
        uint8_t Raw, Color, RunLength;
        fread(&Raw,sizeof(uint8_t),1,In);
        countdown-=sizeof(uint8_t);
        Color = Raw & 0x1F;
        RunLength = Raw >> 5;
        for(int a=0; a<RunLength;a++)
        {
            Sprite[Ofs] = Color;
            Ofs++;
        }
    }
 
    void LZ5_Packet::ProcessLRLE(FILE* In, uint8_t* Sprite, unsigned long &Ofs, unsigned long &countdown)
    {
        uint8_t Raw, Color,RunLength;
        fread(&Raw,sizeof(uint8_t),1,In);
        countdown-=sizeof(uint8_t);
        Color = Raw & 0x1F;
        fread(&RunLength,sizeof(uint8_t),1,In);
        countdown-=sizeof(uint8_t);
        for(int a=0; a<(uint16_t)RunLength+8;a++)
        {
            Sprite[Ofs] = Raw;
            Ofs++;
        }
    }
 
    SFF2_FileHeader::SFF2_FileHeader(FILE* In)
    {
        fread(signature,sizeof(char),12,In);
        fread(&verlo3,sizeof(uint8_t),1,In);
        fread(&verlo2,sizeof(uint8_t),1,In);
        fread(&verlo1,sizeof(uint8_t),1,In);
        fread(&verhi,sizeof(uint8_t),1,In);
        fread(&reserved0,sizeof(long),1,In);
        fread(&reserved1,sizeof(long),1,In);
        fread(&compatverlo3,sizeof(uint8_t),1,In);
        fread(&compatverlo2,sizeof(uint8_t),1,In);
        fread(&compatverlo1,sizeof(uint8_t),1,In);
        fread(&compatverhi,sizeof(uint8_t),1,In);
        fread(&reserved2,sizeof(long),1,In);
        fread(&reserved3,sizeof(long),1,In);
        fread(&sproff,sizeof(unsigned long),1,In);
        fread(&sprcount,sizeof(unsigned long),1,In);
        fread(&paloff,sizeof(unsigned long),1,In);
        fread(&palcount,sizeof(unsigned long),1,In);
        fread(&ldataoff,sizeof(unsigned long),1,In);
        fread(&ldatalen,sizeof(unsigned long),1,In);
        fread(&tdataoff,sizeof(unsigned long),1,In);
        fread(&tdatalen,sizeof(unsigned long),1,In);
        fread(&reserved4,sizeof(long),1,In);
        fread(&reserved5,sizeof(long),1,In);
        fread(unused,sizeof(char),436,In);
    }
 
    SprNode* SFF2_FileHeader::GetSprNode(FILE* In, unsigned long index)
    {
        if(index>=sprcount)
            return NULL;
        fseek(In,sproff+(28*index),SEEK_SET);
        SprNode *temp = new SprNode(In);
        return temp;
 
    }
 
    PalNode* SFF2_FileHeader::GetPalNode(FILE* In, unsigned long index)
    {
        if(index>=palcount)
            return NULL;
        fseek(In,paloff+(16*index),SEEK_SET);
        PalNode *temp = new PalNode(In);
        return temp;
    }
 
    ///////////////////////
    SprNode::SprNode(FILE* In)
    {
        fread(&groupno,sizeof(unsigned short),12,In);
        fread(&itemno,sizeof(unsigned short),1,In);
        fread(&width,sizeof(unsigned short),1,In);
        fread(&height,sizeof(unsigned short),1,In);
        fread(&axisx,sizeof(short),1,In);
        fread(&axisy,sizeof(short),1,In);
        fread(&linkoff,sizeof(unsigned short),1,In);
        fread(&format,sizeof(uint8_t),1,In);
        fread(&coldepth,sizeof(uint8_t),1,In);
        fread(&dataoff,sizeof(unsigned long),1,In);
        fread(&sprlen,sizeof(unsigned long),1,In);
        fread(&palind,sizeof(unsigned short),1,In);
        fread(&flags,sizeof(unsigned short),1,In);
    }
 
    /////////////////////////////
 
    PalNode::PalNode(FILE* In)
    {
        fread(&groupno,sizeof(unsigned short),12,In);
        fread(&itemno,sizeof(unsigned short),1,In);
        fread(&numcols,sizeof(unsigned short),1,In);
        fread(&linkoff,sizeof(unsigned short),1,In);
        fread(&dataoff,sizeof(unsigned long),1,In);
        fread(&datalen,sizeof(unsigned long),1,In);
    }
 
    colorinfo *SFF2_FileHeader::GetColor (FILE* In, PalNode *Node, int index)
    {
        if(index>=Node->GetNumColors())
            return NULL;
        colorinfo *temp = new colorinfo;
        fseek(In,ldataoff+Node->GetData()+(4*index),SEEK_SET);
        fread(&temp->r,sizeof(unsigned short),12,In);
        fread(&temp->g,sizeof(unsigned short),12,In);
        fread(&temp->b,sizeof(unsigned short),12,In);
        fread(&temp->a,sizeof(unsigned short),12,In);
        return temp;
    }
 
    uint8_t *SFF2_FileHeader::GetSprite(FILE* In,SprNode *Node)
    {
        uint8_t *temp = new uint8_t[Node->GetHeight()*Node->GetWidth()];
        unsigned long offset=0, DataLength;
        if(Node->isLinked())
        {
            SprNode *LinkedNode = GetSprNode(In, Node->GetOffset());
            DataLength = LinkedNode->GetDataLen();
            delete LinkedNode;
        }
        else DataLength = Node->GetDataLen();
        if(Node->GetFlags()& 0x1)
            fseek(In,tdataoff+Node->GetData()+4,SEEK_SET);
        else fseek(In,ldataoff+Node->GetData()+4,SEEK_SET);
        switch(Node->GetFormat())
        {
            case 0:
            {
                fread(temp,sizeof(uint8_t),Node->GetHeight()*Node->GetWidth(),In);
                break;
            }
            case 1:
            {
                cout << "Invalid Packet" << endl;
                break;
            }
            case 2:
            {
                RLE8_Packet Packet;
                for(unsigned long a=0; a<DataLength-4;a=a)
                {
                    a+= Packet.SetPacket(In,temp,offset);
                }
                break;
            }
            case 3:
            {
                RLE5_Packet Packet;
                for(unsigned long a=0; a<DataLength-4;a=a)
                {
                    a+= Packet.SetPacket(In,temp,offset);
 
                }
                break;
            }
            case 4:
            {
                LZ5_Packet Packet;
                for(unsigned long a=DataLength-4; a>0;a=a)
                {
                    Packet.SetPacket(In,temp,offset,a);
                }
                break;
            }
        }
        return temp;
    }
}
#endif


    namespace SGF{

class SffReaderInterface{
public:
    SffReaderInterface(){
    }

    virtual ~SffReaderInterface(){
    }

    virtual bool moreSprites() = 0;
    virtual Util::CReferenceCount<CMugenSprite> readSprite(bool mask) = 0;
    virtual Util::CReferenceCount<CMugenSprite> findSprite(int group, int item, bool mask) = 0;
};

//Le o palette do arquivo passado e coloca no buffer paletteBuffer
static bool readPalette(const Filesystem::CAbsolutePath & filename, unsigned char * paletteBuffer){
    const int PALETTE_SIZE = 768;
    try{
        Util::CReferenceCount<Filesystem::File> file = Filesystem::getInstance().open(filename);
        if (file == NULL){
            return false;
        }

        int size = file->getSize();
        if (size == PALETTE_SIZE){
            int read = file->readLine((char*) paletteBuffer, PALETTE_SIZE);
            if (read != PALETTE_SIZE){
                throw CMugenException("Didn't read 768 bytes", __FILE__, __LINE__);
            }
            unsigned char save[3];
            /* in-memory palette reverse */
            for (int i = 0; i < 256 / 2; i++){
                memcpy(save, paletteBuffer + i * 3, 3);
                memcpy(paletteBuffer + i * 3, paletteBuffer + (256 - 1) * 3 - i * 3, 3);
                memcpy(paletteBuffer + (256 - 1) * 3 - i * 3, save, 3);
            }
        } else if (size < PALETTE_SIZE){
            throw CMugenException("Not an ACT file or PCX file", __FILE__, __LINE__);
        } else {
            PCX_HEADER pcxhead;
            file->readLine((char*) &pcxhead, sizeof(PCX_HEADER));

            bool valid_pcx = pcxhead.manufacturer == 10 && 
                             pcxhead.version >= 5 &&
                             pcxhead.BitsPerPixel == 8 &&
                             pcxhead.NPlanes == 1;

            if (valid_pcx){
                /* Palette is at the end. Check to see if the PCX file uses an 8-bit palette. */
                file->seek(-769, SEEK_END);
                unsigned char save;
                file->readLine((char*) &save, 1);
                if (save == 12){
                    file->readLine((char*) paletteBuffer, PALETTE_SIZE);
                } else {
					Debug::debug(Debug::error,__FUNCTION__) << "File " << filename.path() << " is not a valid palette file. (Must be ACT or 8-bit PCX.)";
                    throw CMugenException("Failed", __FILE__, __LINE__);
                }
            }
        }
    } catch (const Exception::Filesystem::CNotFound & fail){
        return false;
    } catch (const CMugenException & e){
        // file.close();
        return false;
    }

    // file.close();
    return true;
}


class SffReader: public SffReaderInterface {
public:
    SffReader(const Filesystem::CAbsolutePath & filename, const Filesystem::CAbsolutePath & paletteFile):
    filename(filename),
    currentSprite(0){
        /* Must read the palette first because once the sff file is opened
         * we can't open the same zip file twice.
         */
        // Palette related
        useact = false;

        //unsigned char colorsave[3]; // rgb pal save

        memset(palsave1, 0, sizeof(palsave1));

        // Load in first palette
        if (readPalette(paletteFile, palsave1)){
            useact = true;
        }

        /* 16 skips the header stuff */
        sffStream = Filesystem::getInstance().open(filename);
        if (!sffStream){
            throw CMugenException("Could not open SFF file: '" + filename.path() + "'", __FILE__, __LINE__);
        }

        filesize = sffStream->getSize();

        checkVersion(sffStream);

        /* Data starts at the 16th byte.
         */
        location = 16;
        sffStream->seek(location, SEEK_SET);
        /* FIXME: change these to uint32 or whatever */
        uint32_t totalGroups = 0;
        totalImages = 0;
        uint32_t suboffset = 0;
        uint32_t subhead = 0;
        uint32_t sharedPal = 0;

        Filesystem::LittleEndianReader reader(sffStream);

        totalGroups = reader.readByte4();
        totalImages = reader.readByte4();
        suboffset = reader.readByte4();
        subhead = reader.readByte4();
        sharedPal = reader.readByte1();

        if (sharedPal && sharedPal != 1){
            sharedPal = 0;
        }

        location = suboffset;

        if (location < 512 || location > 2147482717 ){
            location = 512;
        }

        Debug::debug(Debug::filesystem,__FUNCTION__) << "Got Total Groups: " << totalGroups << ", Total Images: " << totalImages << ", Next Location in file: " << location << std::endl;
		
        // spriteIndex = new CMugenSprite*[totalImages + 1];
    }

    virtual void checkVersion(const Util::CReferenceCount<Filesystem::File> & stream){
        Filesystem::LittleEndianReader reader(stream);
        string signature = reader.readString2(12);
        if (signature != "ElecbyteSpr"){
            std::ostringstream out;
            out << "Invalid signature. Got '" << signature << "'";
            throw CMugenException(out.str(), __FILE__, __LINE__);
        }

        int versionLo3 = reader.readByte1();
        int versionLo2 = reader.readByte1();
        int versionLo1 = reader.readByte1();
        int versionHi = reader.readByte1();
        if (versionHi != 1){
            std::ostringstream out;
            out << "Invalid version for SFFv1. Got " << versionHi << "." << versionLo1 << "." << versionLo2 << "." << versionLo3;
            throw CMugenException(out.str(), __FILE__, __LINE__);
        }
    }

    virtual ~SffReader(){
        // sffStream.close();
        // delete[] spriteIndex;
    }

    /* gets all the sprite headers without loading the pcx information */
    void quickReadSprites(bool mask){
        for (unsigned int index = 0; index < totalImages; index++){
            //s Util::CReferenceCount<CMugenSpriteV1> sprite = Util::CReferenceCount<CMugenSpriteV1>(new CMugenSpriteV1(mask));
            //s sprite->read(sffStream, location);
            //s spriteIndex[index] = sprite;
            //s location = sprite->getNext();
        }
    }

    /* Actually loads the pcx data */
#if 0
    Util::CReferenceCount<CMugenSpriteV1> loadSprite(Util::CReferenceCount<CMugenSpriteV1> sprite, bool mask){
        if (!sprite->isPCXLoaded()){
            if (sprite->getLength() == 0){
                const Util::CReferenceCount<CMugenSpriteV1> temp = loadSprite(spriteIndex[sprite->getPrevious()], mask);
                if (!temp){
                    std::ostringstream out;
                    out << "Unknown linked sprite " << sprite->getPrevious();
                    throw CMugenException(out.str(), __FILE__, __LINE__);
                }
                sprite->copyImage(temp);
            } else {
                bool islinked = false;
                sprite->loadPCX(sffStream, islinked, useact, palsave1, mask);
            }
        }
        return sprite;
    }

    Util::CReferenceCount<CMugenSprite> findSprite(int group, int item, bool mask){
        if (spriteIndex.size() == 0){
            quickReadSprites(mask);
        }
        for (map<int, Util::CReferenceCount<CMugenSpriteV1> >::iterator it = spriteIndex.begin(); it != spriteIndex.end(); it++){
            Util::CReferenceCount<CMugenSpriteV1> sprite = it->second;
            if (sprite->getGroupNumber() == group &&
                sprite->getImageNumber() == item){
                /* make a deep copy */
                return Util::CReferenceCount<CMugenSpriteV1>(new CMugenSpriteV1(*loadSprite(sprite, mask)));
            }
        }
        return Util::CReferenceCount<CMugenSprite>(NULL);
    }

    Util::CReferenceCount<CMugenSprite> readSprite(bool mask){
        bool islinked = false;
        if (location > filesize){
            std::ostringstream out;
            out << "Error in SFF file: " << filename.path() << ". Offset of image (" << location << ") beyond the end of the file (" << filesize << ").";
            throw CMugenException(out.str(), __FILE__, __LINE__);
        }

        Util::CReferenceCount<CMugenSpriteV1> sprite = Util::CReferenceCount<CMugenSpriteV1>(new CMugenSpriteV1(mask));
        sprite->read(sffStream, location);
        location = sprite->getNext();

        if (sprite->getLength() == 0){
            const Util::CReferenceCount<CMugenSpriteV1> temp = spriteIndex[sprite->getPrevious()];
            if (!temp){
                std::ostringstream out;
                out << "Unknown linked sprite " << sprite->getPrevious();
                throw CMugenException(out.str(), __FILE__, __LINE__);
            }
            sprite->copyImage(temp);
        } else {
            sprite->loadPCX(sffStream, islinked, useact, palsave1, mask);
        }
            
        spriteIndex[currentSprite] = sprite;
        currentSprite += 1;

        return sprite;
    }
#endif
    bool moreSprites(){
        return currentSprite < totalImages;
    }

protected:
    const Filesystem::CAbsolutePath filename;
    Util::CReferenceCount<Filesystem::File> sffStream;
    unsigned long currentSprite;
    int totalSprites;
    map<int, Util::CReferenceCount<CMugenSpriteV1> > spriteIndex;
    bool useact;
    int filesize;
    int location;
    uint32_t totalImages;
    unsigned char palsave1[768]; // First image palette
};

class SffV2Reader: public SffReaderInterface {
public:
    struct SpriteHeader{
        SpriteHeader(uint16_t group, uint16_t item, uint16_t width,
                     uint16_t height, uint16_t axisx, uint16_t axisy,
                     uint16_t linked, uint8_t format, uint8_t colorDepth,
                     uint32_t dataOffset, uint32_t dataLength, uint16_t palette,
                     uint16_t flags, unsigned int index):
        group(group),
        item(item),
        width(width),
        height(height),
        axisx(axisx),
        axisy(axisy),
        linked(linked),
        format(format),
        colorDepth(colorDepth),
        dataOffset(dataOffset),
        dataLength(dataLength),
        palette(palette),
        flags(flags),
        index(index){
        }

        SpriteHeader(const SpriteHeader & copy):
        group(copy.group),
        item(copy.item),
        width(copy.width),
        height(copy.height),
        axisx(copy.axisx),
        axisy(copy.axisy),
        linked(copy.linked),
        format(copy.format),
        colorDepth(copy.colorDepth),
        dataOffset(copy.dataOffset),
        dataLength(copy.dataLength),
        palette(copy.palette),
        flags(copy.flags),
        index(copy.index){
        }

        SpriteHeader(){
        }

        uint16_t group;
        uint16_t item;
        uint16_t width;
        uint16_t height;
        uint16_t axisx;
        uint16_t axisy;
        uint16_t linked;
        uint8_t format;
        uint8_t colorDepth;
        uint32_t dataOffset;
        uint32_t dataLength;
        uint16_t palette;
        uint16_t flags;
        unsigned int index;
    };

    struct PaletteHeader{

        PaletteHeader(uint16_t group, uint16_t item, uint16_t colors,
                      uint16_t linked, uint32_t offset, uint32_t length,
                      unsigned int index):
            group(group),
            item(item),
            colors(colors),
            linked(linked),
            offset(offset),
            length(length),
            index(index){
            }

        PaletteHeader(){
        }

        PaletteHeader(const PaletteHeader & copy):
            group(copy.group),
            item(copy.item),
            colors(copy.colors),
            linked(copy.linked),
            offset(copy.offset),
            length(copy.length),
            index(copy.index){
            }

        uint16_t group;
        uint16_t item;
        uint16_t colors;
        uint16_t linked;
        uint32_t offset;
        uint32_t length;
        unsigned int index;
    };

    SffV2Reader(const Filesystem::CAbsolutePath & filename):
    filename(filename),
    currentSprite(0){
        /* 16 skips the header stuff */
        sffStream = Filesystem::getInstance().open(filename);
        if (!sffStream){
            throw CMugenException("Could not open SFF file: '" + filename.path() + "'", __FILE__, __LINE__);
        }

        filesize = sffStream->getSize();

        totalImages = 0;

        Filesystem::LittleEndianReader reader(sffStream);
        string signature = reader.readString2(12);
        if (signature != "ElecbyteSpr"){
            throw CMugenException(string("Invalid signature for SFFv2 file. Got '") + signature + "'", __FILE__, __LINE__);
        }

        int versionLo3 = reader.readByte1();
        int versionLo2 = reader.readByte1();
        int versionLo1 = reader.readByte1();
        int versionHi = reader.readByte1();
        if (versionHi != 2){
            std::ostringstream out;
            out << "Invalid version for SFFv2. Got " << versionHi << "." << versionLo1 << "." << versionLo2 << "." << versionLo3;
            throw CMugenException(out.str(), __FILE__, __LINE__);
        }

        /* skip reserved */
        reader.readByte4();
        reader.readByte4();

        /* ignore compatability version number */
        reader.readByte4();

        /* skip reserved */
        reader.readByte4();
        reader.readByte4();

        uint32_t suboffset = reader.readByte4();
        totalImages = reader.readByte4();
        uint32_t subpalette = reader.readByte4();
        uint32_t totalPalettes = reader.readByte4();
        
        Debug::debug(Debug::filesystem,__FUNCTION__) << "Image offset " << suboffset << " total images " << totalImages << " palette offset " << subpalette << " total palettes " << totalPalettes << std::endl;

        /* compressed data */
        ldataOffset = reader.readByte4();
        ldataLength = reader.readByte4();

        /* uncompressed data */
        tdataOffset = reader.readByte4();
        tdataLength = reader.readByte4();

        Debug::debug(Debug::filesystem,__FUNCTION__) << "Ldata offset " << ldataOffset << " length " << ldataLength << std::endl;
        Debug::debug(Debug::filesystem,__FUNCTION__) << "Tdata offset " << tdataOffset << " length " << tdataLength << std::endl;

        /* skip reserved */
        reader.readByte4();
        reader.readByte4();
        
        /* seek to first sprite */
        reader.seek(suboffset);

        for (unsigned int index = 0; index < totalImages; index++){
            uint16_t group = reader.readByte2();
            uint16_t item = reader.readByte2();
            uint16_t width = reader.readByte2();
            uint16_t height = reader.readByte2();
            uint16_t axisx = reader.readByte2();
            uint16_t axisy = reader.readByte2();
            uint16_t linked = reader.readByte2();
            uint8_t format = reader.readByte1();
            uint8_t colorDepth = reader.readByte1();
            uint32_t dataOffset = reader.readByte4();
            uint32_t dataLength = reader.readByte4();
            uint16_t palette = reader.readByte2();
            uint16_t flags = reader.readByte2();
            /* if flags == 0 then use ldata, if 1 then tdata */
            Debug::debug(Debug::filesystem,__FUNCTION__) << " " << group << ", " << item << " " << width << "x" << height << " format " << formatName(format) << " color depth " << (int) colorDepth << " data " << dataOffset << " length " << dataLength << (flags == 0 ? " literal" : " translate") << std::endl;
            sprites.push_back(SpriteHeader(group, item, width, height,
                                           axisx, axisy, linked, format,
                                           colorDepth, dataOffset, dataLength,
                                           palette, flags, index));
        }

        reader.seek(subpalette);
        for (unsigned int index = 0; index < totalPalettes; index++){
            uint16_t group = reader.readByte2();
            uint16_t item = reader.readByte2();
            uint16_t colors = reader.readByte2();
            uint16_t linked = reader.readByte2();
            uint32_t offset = reader.readByte4();
            uint32_t length = reader.readByte4();
            palettes.push_back(PaletteHeader(group, item, colors, linked, offset, length, index));
        }
    }

    vector<SpriteHeader> getSprites(){
        return this->sprites;
    }

    const SpriteHeader & findSpriteHeader(unsigned int index){
        for (vector<SpriteHeader>::iterator it = sprites.begin(); it != sprites.end(); it++){
            const SpriteHeader & sprite = *it;
            if (sprite.index == index){
                return sprite;
            }
        }
        std::ostringstream out;
        out << "Could not find a sprite with index " << index;
        throw CMugenException(out.str(), __FILE__, __LINE__);
    }

    const SpriteHeader & findSpriteHeader(int group, int item){
        for (vector<SpriteHeader>::iterator it = sprites.begin(); it != sprites.end(); it++){
            const SpriteHeader & sprite = *it;
            if (sprite.group == group && sprite.item == item){
                return sprite;
            }
        }
        std::ostringstream out;
        out << "No sprite for group " << group << ", " << item;
        throw CMugenException(out.str(), __FILE__, __LINE__);
    }

    Util::CReferenceCount<CMugenSprite> readSprite(const SpriteHeader & sprite, bool mask){
        /* FIXME: do something with mask */
        return Util::CReferenceCount<CMugenSprite>(new CMugenSpriteV2(readBitmap(sprite), sprite.group, sprite.item, sprite.axisx, sprite.axisy));
    }

    Util::CReferenceCount<CMugenSprite> readSprite(bool mask){
        if (currentSprite < totalImages){
            int here = currentSprite;
            currentSprite += 1;
            return readSprite(sprites[here], mask);
        }

        return Util::CReferenceCount<CMugenSprite>(NULL);
    }
    
    virtual Util::CReferenceCount<CMugenSprite> findSprite(int group, int item, bool mask){
        return readSprite(findSpriteHeader(group, item), mask);
    }

    CBitmap readBitmap(const SpriteHeader & sprite){
        Filesystem::LittleEndianReader reader(sffStream);
        if (sprite.dataLength == 0){
            return readBitmap(findSpriteHeader(sprite.linked));
        } else {
            /* Compression formats are consistent across SFF versions. The first
             * 4 bytes of each compressed block comprises an integer representing
             * the length of the data after decompression.
             */
            if (sprite.flags == 0){
                return read(sprite, reader, ldataOffset + sprite.dataOffset + 4, sprite.dataLength - 4);
            } else {
                return read(sprite, reader, tdataOffset + sprite.dataOffset + 4, sprite.dataLength - 4);
            }
        }
        
        /* Pretty sure we can't get here */
        throw CMugenException("Internal error", __FILE__, __LINE__);
    }

    CBitmap read(const SpriteHeader & sprite, Filesystem::LittleEndianReader & reader, uint32_t offset, uint32_t length){
        // Global::debug(0) << "Read sprite " << sprite.group << ", " << sprite.item << " dimensions " << sprite.width << "x" << sprite.height << std::endl;
        char * pixels = new char[sprite.width * sprite.height];
        memset(pixels, 0, sprite.width * sprite.height);
        sffStream->seek(offset, SEEK_SET);
        try{
            switch (sprite.format){
                case 2: readRLE8(reader, length, pixels, sprite.width * sprite.height); break;
                case 3: readRLE5(reader, length, pixels, sprite.width * sprite.height); break;
                case 4: readLZ5(reader, length, pixels, sprite.width * sprite.height); break;
                default: {
                    std::ostringstream out;
                    out << "Don't understand SffV2 format " << sprite.format;
                    throw CMugenException(out.str(), __FILE__, __LINE__);
                }
            }
        } catch (...){
            Debug::debug(Debug::filesystem,__FUNCTION__) << "Ignoring Sffv2 sprite error... " << std::endl;
        }

        map<uint8_t, Colors::PixelColor> palette = readPalette(sprite.palette);
        CBitmap out(sprite.width, sprite.height);
        writePixels(out, pixels, palette);
        delete[] pixels;
        return out;
    }

    map<uint8_t, Colors::PixelColor> readPalette(unsigned int index){
        for (vector<PaletteHeader>::iterator it = palettes.begin(); it != palettes.end(); it++){
            const PaletteHeader & palette = *it;
            if (palette.index == index){
                if (palette.length != 0){
                    return readPalette(palette);
                } else {
                    return readPalette(palette.linked);
                }
            }
        }

        std::ostringstream out;
        out << "Could not find palette with index " << index;
        throw CMugenException(out.str(), __FILE__, __LINE__);
    }

    map<uint8_t, Colors::PixelColor> readPalette(const PaletteHeader & palette){
        if (paletteCache.find(palette.index) != paletteCache.end()){
            return paletteCache[palette.index];
        } else {
            sffStream->seek(palette.offset + ldataOffset, SEEK_SET);
            uint8_t * data = new uint8_t[palette.length];
            sffStream->readLine((char*) data, palette.length);
            map<uint8_t, Colors::PixelColor> out;
            for (int color = 0; color < palette.colors; color++){
                /* Palette data is stored in 4 byte chunks per color.
                 * The first 3 bytes correspond to 8-bit values for RGB color, and
                 * the last byte is unused (set to 0).
                 */
                int red = data[color * 4];
                int green = data[color * 4 + 1];
                int blue = data[color * 4 + 2];
                out[color] =Colors::makeColor(red, green, blue);
            }
            delete[] data;
            paletteCache[palette.index] = out;
            return out;
        }
    }

    /* pixels are an index into a palette */
    void writePixels(CBitmap & out, char * pixels, map<uint8_t, Colors::PixelColor> & palette){
        int height = out.getHeight();
        int width = out.getWidth();
        Colors::PixelColor * lookup = new Colors::PixelColor[palette.size()];
        for (map<uint8_t, Colors::PixelColor>::iterator it = palette.begin(); it != palette.end(); it++){
            lookup[it->first] = it->second;
        }
        for (int y = 0; y < height; y++){
            for (int x = 0; x < width; x++){
                uint8_t pixel = pixels[x + y * width];
				out.putPixelSurface(x, y, lookup[pixel]);
            }
        }
        delete[] lookup;
    }

    void readRLE8(Filesystem::LittleEndianReader & reader, uint32_t length, char * pixels, int pixelLength){
        char * output = pixels;
        while (length > 0){
            uint8_t rle = reader.readByte1();
            length -= 1;
            if ((rle & 0xc0) == 0x40){
                uint8_t color = reader.readByte1();
                length -= 1;
                int runlength = (rle & 0x3f);
                for (int i = 0; i < runlength; i++){
                    *output = color;
                    output += 1;
                }
            } else {
                *output = rle;
                output += 1;
            }
        }
    }

    void readRLE5(Filesystem::LittleEndianReader & reader, uint32_t length, char * pixels, int pixelLength){
            /*
RLE5packet = read(2 bytes)
if RLE5packet.color_bit is 1, then
color = read(1 byte)
else
color = 0
for run_count from 0 to RLE5packet.run_length, do
output(color)
Decode 3RL/5VAL
for bytes_processed from 0 to RLE5packet.data_length - 1, do
one_byte = read(1 byte)
color = one_byte & 0x1F
run_length = one_byte >> 5
for run_count from 0 to run_length, do
output(color)
*/
        char * output = pixels;
        while (length > 0){
            uint16_t packet = reader.readByte2();
            int runlength = packet & 0xff;
            length -= 2;
            int color = 0;
            if ((packet & (1 << 15)) == (1 << 15)){
                color = reader.readByte1();
                length -= 1;
            }
            int data = (packet >> 8) & 0x7f;
            for (int i = 0; i < runlength; i++){
                *output = color;
                output += 1;
            }
            for (int i = 0; i < data; i++){
                uint8_t rle = reader.readByte1();
                length -= 1;
                color = rle & 0x1f;
                runlength = rle >> 5;
                for (int c = 0; c < runlength; c++){
                    *output = color;
                    output += 1;
                }
            }
        }
    }

    enum LZ5PacketType{
        RLEShort,
        RLELong,
        LZ5Short,
        LZ5Long
    };

    struct LZ5Packet{
        LZ5Packet(LZ5PacketType type, int pixel, int length):
        type(type), length(length){
            data.pixel = pixel;
        }

        LZ5Packet(const LZ5Packet & copy):
        type(copy.type), length(copy.length){
            data.pixel = copy.data.pixel;
        }

        LZ5PacketType type;
        union{
            int pixel; /* for rle */
            int offset; /* for lz5 */
        } data;
        int length;
    };

    /* get the stream of packets */
    vector<LZ5Packet> readLZ5Packets(Filesystem::LittleEndianReader & reader, uint32_t length){
        vector<LZ5Packet> packets;
        uint8_t * compressed = new uint8_t[length];
        reader.readBytes(compressed, length);
        uint32_t total = 0;

        uint8_t recycled = 0;
        uint8_t lz5ShortCount = 0;
        while (total < length){
            uint8_t control = compressed[total];
            total += 1;
            /*
            uint8_t data[8];
            int dataRead = 0;
            for (dataRead = 0; dataRead < 8 && total < length; dataRead += 1, total += 1){
                data[dataRead] = compressed[total];
            }
            */

            /* FIXME: remove 'out' because it probably hurts performance */
            std::ostream & out = Debug::debug(Debug::filesystem,__FUNCTION__);
            for (int packet = 0; packet < 8 && total < length; packet++){
                /* I am 99.999% sure that 0 in the control packet means RLE */
                if ((control & (1 << packet)) == 0){
                    /* RLE */
                    if ((compressed[total] >> 5) == 0){
                        out << "Long RLE ";
                        int color = compressed[total] & 31;
                        total += 1;
                        int times = compressed[total] + 8;
                        total += 1;
                        packets.push_back(LZ5Packet(RLELong, color, times));
                    } else {
                        out << "Short RLE ";
                        int color = compressed[total] & 31;
                        int times = compressed[total] >> 5;
                        total += 1;
                        packets.push_back(LZ5Packet(RLEShort, color, times));
                    }
                } else {
                    /* LZ5 */
                    if ((compressed[total] & 63) != 0){
                        int byte1 = compressed[total];
                        int byte2 = 0;
                        /* check if this is the 4th short lz5 packet */
                        // recycled = (compressed[total] & 0xc0) >> (2 * lz5ShortCount);
                        recycled = (recycled << 2) | (compressed[total] >> 6);
                        if (lz5ShortCount == 3){
                            out << "Short LZ5* ";
                            lz5ShortCount = 0;
                            // recycled = (recycled << 2) | (compressed[total] >> 6);
                            byte2 = recycled;
                            recycled = 0;
                            total += 1;
                        } else {
                            out << "Short LZ5 ";
                            // recycled = (recycled << 2) | (compressed[total] >> 6);
                            byte2 = compressed[total + 1];
                            lz5ShortCount += 1;
                            total += 2;
                        }

                        int length = (byte1 & 63) + 1;
                        int offset = byte2 + 1;
                        packets.push_back(LZ5Packet(LZ5Short, offset, length));
                    } else {
                        // int offset = compressed[total] >> 6;
                        int offset = compressed[total] << 2;
                        total += 1;
                        offset |= compressed[total];
                        offset += 1;
                        // offset = (offset << 8) + compressed[total] + 1;
                        // offset = ((offset << 2) | compressed[total]) + 1;
                        total += 1;
                        int length = compressed[total] + 3;
                        packets.push_back(LZ5Packet(LZ5Long, offset, length));
                        total += 1;
                        out << "Long LZ5 ";
                    }
                }
            }
            out << std::endl;
        }

        delete[] compressed;
        
        return packets;
    }

    void readLZ5(Filesystem::LittleEndianReader & reader, uint32_t length, char * pixels, int maxPixelLength){
        vector<LZ5Packet> packets = readLZ5Packets(reader, length);
        char * dest = pixels;
        int maxLength = 0;
        int total = 0;
        Debug::debug(Debug::filesystem,__FUNCTION__) << packets.size() << " packets " << maxPixelLength << " pixels" << std::endl;
        for (vector<LZ5Packet>::iterator it = packets.begin(); it != packets.end(); it++){
            const LZ5Packet & packet = *it;
            int index = (it - packets.begin());
            if (packet.length > maxLength){
                Debug::debug(Debug::filesystem,__FUNCTION__) << "packet " << index << " " << packet.type << " length was " << packet.length << std::endl;
                maxLength = packet.length;
            }
            // Global::debug(0) << "Wrote " << total << " packets. Writing " << packet.length << endl;
            total += packet.length;
            switch (packet.type){
                case RLEShort:
                case RLELong: {
                    for (int i = 0; i < packet.length; i++){
                        if (dest - pixels >= maxPixelLength){
                            std::ostringstream out;
                            out << "packet " << index << " tried to write too many pixels! length " << packet.length << " Packets left " << (packets.end() - it);
                            throw CMugenException(out.str(), __FILE__, __LINE__);
                        }
                        *dest = packet.data.pixel;
                        dest += 1;
                    }
                    break;
                }
                case LZ5Short:
                case LZ5Long: {
                    char * source = dest - packet.data.offset;
                    if (packet.data.offset < 0){
                        std::ostringstream out;
                        out << "LZ5 offset is negative " << packet.data.offset;
                        throw CMugenException(out.str(), __FILE__, __LINE__);
                    }
                    if (source < pixels){
                        std::ostringstream out;
                        out << "Packet " << index << " type (" << packet.type << ") Source is beneath pixels by " << (pixels - source) << ". dest at " << (dest - pixels) << " length " << packet.length << " offset " << packet.data.offset;
                        throw CMugenException(out.str(), __FILE__, __LINE__);
                    }
                    for (int i = 0; i < packet.length; i++){
                        if (dest - pixels >= maxPixelLength){
                            std::ostringstream out;
                            out << "packet " << index << " tried to write too many pixels! length " << packet.length << " Packets left " << (packets.end() - it);
                            throw CMugenException(out.str(), __FILE__, __LINE__);
                        }
                        *dest = *source;
                        dest += 1;
                        source += 1;
                    }
                    break;
                }
            }
        }
    }

    string formatName(int format){
        switch (format){
            case 0: return "raw";
            case 1: return "invalid";
            case 2: return "RLE8";
            case 3: return "RLE5";
            case 4: return "LZ5";
            default: return "unknown";
        }
    }

    virtual ~SffV2Reader(){
    }

    bool moreSprites(){
        return currentSprite < totalImages;
    }

protected:
    const Filesystem::CAbsolutePath filename;
    Util::CReferenceCount<Filesystem::File> sffStream;
    unsigned long currentSprite;
    int totalSprites;
    vector<SpriteHeader> sprites;
    vector<PaletteHeader> palettes;

    int filesize;
    int location;
    uint32_t totalImages;

    uint32_t ldataOffset;
    uint32_t ldataLength;
    uint32_t tdataOffset;
    uint32_t tdataLength;
    
    map< int, map<uint8_t, Colors::PixelColor> > paletteCache;
};

struct Image{
    Image(int group, int item, int axisX, int axisY, string file):
        group(group),
        item(item),
        axisX(axisX),
        axisY(axisY),
        file(file){
        }

    int group;
    int item;
    int axisX;
    int axisY;
    string file;
};

static vector<Image> loadImageDescriptions(const Filesystem::CAbsolutePath & path){
    vector<Image> files;
    Util::CReferenceCount<Filesystem::File> data = Filesystem::getInstance().open(path);
    if (!data->good()){
        throw CMugenException(string("Could not read description file ") + path.path(), __FILE__, __LINE__);
    }
    int size = data->getSize();
    if (size > 0){
        char * raw = new char[size+1];
        /* Just to make sure the string ends properly */
        raw[size] = '\0';
        data->readLine(raw, size);
        std::istringstream input;
        input.str(string(raw));
        // Global::debug(0) << "Raw '" << raw << "'" << std::endl;
        while (!input.eof()){
            int group = -99;
            int item = -99;
            int axisx = 0;
            int axisy = 0;
            string filename;
            input >> group >> item >> axisx >> axisy >> filename;
            if (group == -99){
                break;
            } else {
                files.push_back(Image(group, item, axisx, axisy, filename));
            }
        }
        delete[] raw;
    }
    return files;
}

/* Looks for a txt file in the container that describes the sprites. The format
 * is as follows
 *
 * group# item# axisX# axisY# filename
 * group# item# axisX# axisY# filename
 * ...
 *
 */
class ImageContainerReader: public SffReaderInterface {
public:
    
    ImageContainerReader(const Filesystem::CAbsolutePath & path):
    container(path),
    current(files.begin()){
        vector<string> files = Filesystem::getInstance().containerFileList(path);
        bool ok = false;
        string descriptionFile;
        for (vector<string>::iterator it = files.begin(); it != files.end(); it++){
            if (it->find(".txt") != string::npos){
                ok = true;
                descriptionFile = *it;
                break;
            }
        }

        if (!ok){
            throw CMugenException(string("Could not find a description txt file in the container file ") + path.path(), __FILE__, __LINE__);
        }

        mount = Filesystem::CAbsolutePath(path.path() + "_mount");
        Filesystem::getInstance().addOverlay(path, mount);
        populate(mount, descriptionFile);
    }

    void populate(const Filesystem::CAbsolutePath & folder, const string & descriptionFile){
        files = loadImageDescriptions(folder.join(Filesystem::CIsolatedPath(descriptionFile)));
        current = files.begin();
    }

    virtual ~ImageContainerReader(){
        Filesystem::getInstance().removeOverlay(container, mount);
    }

    virtual bool moreSprites(){
        return current != files.end();
    }

    CBitmap readBitmap(const string & path){
        //Util::CReferenceCount<Filesystem::File> file = Filesystem::getInstance().open(mount.join(Filesystem::CIsolatedPath(path)));
        //return CBitmap(*file);
		Filesystem::CRelativePath file(path);
		if (file.exist()) 
			return CBitmap(path);
		else {
			return CBitmap();
		}
    }

    virtual Util::CReferenceCount<CMugenSprite> readSprite(bool mask){
        if (current == files.end()){
            return Util::CReferenceCount<CMugenSprite>(NULL);
        }
        const Image & image = *current;
        current++;
        /* FIXME: do something with mask */
        return Util::CReferenceCount<CMugenSprite>(new CMugenSpriteV2(readBitmap(image.file), image.group, image.item, image.axisX, image.axisY));
    }

    virtual Util::CReferenceCount<CMugenSprite> findSprite(int group, int item, bool mask){
        for (vector<Image>::iterator it = files.begin(); it != files.end(); it++){
            const Image & image = *it;
            if (image.group == group && image.item == item){
                /* FIXME: do something with mask */
                return Util::CReferenceCount<CMugenSprite>(new CMugenSpriteV2(readBitmap(image.file), image.group, image.item, image.axisX, image.axisY));
            }
        }
        return Util::CReferenceCount<CMugenSprite>(NULL);
    }

protected:
    Filesystem::CAbsolutePath container;
    Filesystem::CAbsolutePath mount;
    std::vector<Image> files;
    std::vector<Image>::iterator current;
};

class DirectoryReader: public SffReaderInterface {
public:
    DirectoryReader(const Filesystem::CAbsolutePath & path):
    root(path),
    current(files.begin()){
        vector<Filesystem::CAbsolutePath> files = Filesystem::getInstance().getFiles(path, "*.txt");
        bool ok = false;
        Filesystem::CAbsolutePath descriptionFile;
        for (vector<Filesystem::CAbsolutePath>::iterator it = files.begin(); it != files.end(); it++){
            if (it->path().find(".txt") != string::npos){
                ok = true;
                descriptionFile = *it;
                break;
            }
        }

        if (!ok){
            throw CMugenException(string("Could not find a description txt file in the container file ") + path.path(), __FILE__, __LINE__);
        }

        populate(descriptionFile);
    }

    void populate(const Filesystem::CAbsolutePath & file){
        files = loadImageDescriptions(file);
        current = files.begin();
    }

    virtual ~DirectoryReader(){
    }

    virtual bool moreSprites(){
        return current != files.end();
    }

    CBitmap readBitmap(const string & path){
        Util::CReferenceCount<Filesystem::File> file = Filesystem::getInstance().open(root.join(Filesystem::CIsolatedPath(path)));
		Filesystem::CRelativePath file2(path);
		if (file2.exist())
			return CBitmap(file2.path());//CBitmap(*file);
		else
			return CBitmap();
    }

    virtual Util::CReferenceCount<CMugenSprite> readSprite(bool mask){
        if (current == files.end()){
            return Util::CReferenceCount<CMugenSprite>(NULL);
        }
        const Image & image = *current;
        current++;
        /* FIXME: do something with mask */
        return Util::CReferenceCount<CMugenSprite>(new CMugenSpriteV2(readBitmap(image.file), image.group, image.item, image.axisX, image.axisY));
    }

    virtual Util::CReferenceCount<CMugenSprite> findSprite(int group, int item, bool mask){
        for (vector<Image>::iterator it = files.begin(); it != files.end(); it++){
            const Image & image = *it;
            if (image.group == group && image.item == item){
                /* FIXME: do something with mask */
                return Util::CReferenceCount<CMugenSprite>(new CMugenSpriteV2(readBitmap(image.file), image.group, image.item, image.axisX, image.axisY));
            }
        }
        return Util::CReferenceCount<CMugenSprite>(NULL);
    }

protected:
    Filesystem::CAbsolutePath root;
    std::vector<Image> files;
    std::vector<Image>::iterator current;
};

static int majorVersion(const Filesystem::CAbsolutePath & filename){
    Util::CReferenceCount<Filesystem::File> stream = Filesystem::getInstance().open(filename);
    if (!stream){
        throw CMugenException("Could not open SFF file: '" + filename.path() + "'", __FILE__, __LINE__);
    }

    Filesystem::LittleEndianReader reader(stream);
    string signature = reader.readString2(12);
    if (signature != "ElecbyteSpr"){
        throw CMugenException(string("Invalid signature for SFF file. Got '") + signature + "'", __FILE__, __LINE__);
    }

    int versionLo3 = reader.readByte1();
    int versionLo2 = reader.readByte1();
    int versionLo1 = reader.readByte1();
    int versionHi = reader.readByte1();

    return versionHi;
}

static bool isSffv1(const Filesystem::CAbsolutePath & filename){
    try{
        return majorVersion(filename) == 1;
    } catch (const CMugenException & fail){
        return false;
    }
}

static bool isSffv2(const Filesystem::CAbsolutePath & filename){
    try{
        return majorVersion(filename) == 2;
    } catch (const CMugenException & fail){
        return false;
    }
}

static Util::CReferenceCount<SffReaderInterface> getSffReader(const Filesystem::CAbsolutePath & filename, const Filesystem::CAbsolutePath & palette){
 //   if (isSffv1(filename)){
 //       return Util::CReferenceCount<SffReaderInterface>(new SffReader(filename, palette));
//    }
    if (isSffv2(filename)){
        /* FIXME: use palette somehow */
        return Util::CReferenceCount<SffReaderInterface>(new SffV2Reader(filename));
    }
    if (Filesystem::isContainer(filename)){
        return Util::CReferenceCount<SffReaderInterface>(new ImageContainerReader(filename));
    }

//s    if (Filesystem::getInstance().isDirectory(filename)){
//s        return Util::CReferenceCount<SffReaderInterface>(new DirectoryReader(filename));
//s    }

    throw CMugenException(filename.path() + " is not an sffv1, sffv2, zip, 7z file or directory", __FILE__, __LINE__);
    return Util::CReferenceCount<SffReaderInterface>(NULL);
}

    }

#if 0
	void Mugen::Util::readSprites(const Filesystem::CAbsolutePath & filename, const Filesystem::CAbsolutePath & palette, Mugen::SpriteMap & sprites, bool mask){
    Util::CReferenceCount<SffReaderInterface> reader = getSffReader(filename, palette);
    /* where replaced sprites go */
    vector<Util::CReferenceCount<CMugenSprite> > unused;
    while (reader->moreSprites()){
        // try{
            Util::CReferenceCount<CMugenSprite> sprite = reader->readSprite(mask);

            Mugen::SpriteMap::iterator first_it = sprites.find(sprite->getGroupNumber());
            if (first_it != sprites.end()){
                std::map< unsigned int, Util::CReferenceCount<CMugenSprite> >::iterator it = first_it->second.find(sprite->getImageNumber());
                if (it != first_it->second.end()){
                    Global::debug(0) << "Warning: replacing sprite in " << Filesystem::getInstance().cleanse(filename).path() << " group " << sprite->getGroupNumber() << " item " << sprite->getImageNumber() << std::endl;
                    unused.push_back(it->second);
                }
            }
            sprites[sprite->getGroupNumber()][sprite->getImageNumber()] = sprite;
        /* 5/5/2012: if a sprite can't be read then throw an error */
        /*
        } catch (const CMugenException & e){
            Global::debug(0) << e.getReason() << endl;
        }
        */
    }

    /* delete all replaced sprites */
    /*for (vector< Util::CReferenceCount<CMugenSprite> >::iterator it = unused.begin(); it != unused.end(); it++){
        delete (*it);
    }*/
}

Util::CReferenceCount<CMugenSprite> Mugen::Util::probeSff(const Filesystem::CAbsolutePath &file, int groupNumber, int spriteNumber, bool mask, const Filesystem::CAbsolutePath & actFile){
    Util::CReferenceCount<SffReaderInterface> reader = getSffReader(file, actFile);
    Util::CReferenceCount<CMugenSprite> found = reader->findSprite(groupNumber, spriteNumber, mask);
    if (found != NULL){
        return found;
    }
    std::ostringstream out;
    out << "Could not find sprite " << groupNumber << ", " << spriteNumber << " in " << file.path();
    throw CMugenException(out.str(), __FILE__, __LINE__);
}
 
void Mugen::Util::getIconAndPortrait(const Filesystem::CAbsolutePath & sffPath, const Filesystem::CAbsolutePath & actPath, Util::CReferenceCount<CMugenSprite> * icon, Util::CReferenceCount<CMugenSprite> * portrait){
    Util::CReferenceCount<SffReaderInterface> reader = getSffReader(sffPath, actPath);
    *icon = reader->findSprite(9000, 0, true);
    *portrait = reader->findSprite(9000, 1, true);
    if (*icon == NULL || *portrait == NULL){
        bool failed_icon = *icon == NULL;
        bool failed_portrait = *portrait == NULL;
        //delete *icon;
        *icon = NULL;
        //delete *portrait;
        *portrait = NULL;
        std::ostringstream out;
        if (failed_icon){
            out << "Could not find sprite " << 9000 << ", " << 0 << " in " << sffPath.path();
        } else {
            out << "Could not find sprite " << 9000 << ", " << 1 << " in " << sffPath.path();
        }
        throw CMugenException(out.str(), __FILE__, __LINE__);
    }
}

#endif