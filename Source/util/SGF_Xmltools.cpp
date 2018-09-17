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



#include <stdio.h>
#include <malloc.h>
#include <string>
#include "util/SGF_Xmltools.h"
#include "exceptions/all.h"
#include "SGF_Global.h"
namespace SGF {

namespace XmlTools {
void charData (void *userData, const XML_Char *s, int len) {
   int i;
   /* If parent is still empty, close its tag. */

      for (i=0; i < len; i++) {
         putchar (s[i]);
	  }
}


void startElement(void *userData, const char *name, const char **atts)
{
  int i;
  int *depthPtr = (int *) userData;
  for (i = 0; i < *depthPtr; i++)
    putchar('\t');
  puts(name);
  *depthPtr += 1;
}

void endElement(void *userData, const char *name)
{
  int *depthPtr = (int *) userData;
  *depthPtr -= 1;
}

int XmlParseFile(const string & file)
{

  FILE * in;
  char buf[BUFSIZ];
  const char * infile;
  infile= file.c_str();

  XML_Parser parser = XML_ParserCreate(NULL);

  int done;
  int finished;
  int depth = 0;

  if (!infile) {
      in = stdin;
   } else {
      try{
		   if( !(in = fopen (infile, "r")) )
              throw "Unable to open input file!";
		 } catch (char * str){
		 Global::PrintMessage ((char *)"XmlParseFile -> %s\n", str);
         return -1;
	  }
  }



  XML_SetUserData(parser, &depth);
  XML_SetElementHandler(parser, startElement, endElement);
  XML_SetCharacterDataHandler(parser, charData);

  done = 0;
  finished = 0;

   do {
      size_t len = fread(buf, 1, sizeof(buf), in);
      done = len < sizeof(buf);
      if (!XML_Parse(parser, buf, len, done)) {
         fprintf(stderr,
            "%s at line %ld\n",
            XML_ErrorString(XML_GetErrorCode(parser)),
            XML_GetCurrentLineNumber(parser));
         return 1;
      }
   } while (!done && !finished);

  XML_ParserFree(parser);
  return 0;
}
} //end namespace XmlTools
	} //end SGF