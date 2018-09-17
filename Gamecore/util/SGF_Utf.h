#ifndef _SGF___UTF_
#define _SGF___UTF_

#include <string>
#include <stdint.h>
#include "../../ExternalLibs/SDL2/include/SDL.h"

using namespace std;
namespace SGF {

namespace Utf{
    long readUtf8CodePoint(const string & input, unsigned int * position);
    string utf16_to_utf8(const uint16_t * utf16);
	Uint16 *ASCII_to_UNICODE(Uint16 *unicode, const char *text, int len);
	Uint16 * Latin1_Uni(const char *text);
	Uint16 * UTF8_to_UNICODE(Uint16 *unicode, const char *utf8, int len);
	Uint16 * UTF8_Uni(const char *text);
	string encodeUtf8(unsigned long unicode);
}
} //end SGF
#endif
