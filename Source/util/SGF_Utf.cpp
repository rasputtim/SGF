#include "util/SGF_Utf.h"
#include <string>
#include <sstream>
#include <cstring>
using ::std::string;
using ::std::ostringstream;
namespace SGF {

namespace Utf{

    /* utf8 decoding. reads a utf8 string and returns a unicode code point.
     * position should be a pointer to an integer that stores the current
     *  place in the input string where the next character is to be read.
     * FIXME: handle the case when `position' runs out of bytes
     */
    long readUtf8CodePoint(const string & input, unsigned int * position){
        unsigned char byte1 = (unsigned char) input[*position];
        /* one byte - ascii */
        if (byte1 >> 7 == 0){
            return byte1;
        }

        if (byte1 >> 5 == 6){
            *position += 1;
            if (*position >= input.size()){
                return 0;
            }
            unsigned char byte2 = (unsigned char) input[*position];
            int top = byte1 & 31;
            int bottom = byte2 & 63;
            return (top << 6) + bottom;
        }

        if (byte1 >> 4 == 14){
            *position += 1;
            if (*position >= input.size()){
                return 0;
            }
            unsigned char byte2 = (unsigned char) input[*position];
            *position += 1;
            if (*position >= input.size()){
                return 0;
            }
            unsigned char byte3 = (unsigned char) input[*position];
            int top4 = byte1 & 15;
            int middle6 = byte2 & 63;
            int bottom6 = byte3 & 63;
            return (top4 << (6+6)) + (middle6 << 6) + bottom6;
        }

        if (byte1 >> 3 == 30){
            *position += 1;
            if (*position >= input.size()){
                return 0;
            }
            unsigned char byte2 = (unsigned char) input[*position];
            *position += 1;
            if (*position >= input.size()){
                return 0;
            }
            unsigned char byte3 = (unsigned char) input[*position];
            *position += 1;
            if (*position >= input.size()){
                return 0;
            }
            unsigned char byte4 = (unsigned char) input[*position];
            int unit1 = byte1 & 7;
            int unit2 = byte2 & 63;
            int unit3 = byte3 & 63;
            int unit4 = byte4 & 63;
            return (unit1 << 18) + (unit2 << 12) + (unit3 << 6) + unit4;
        }

        return 0;
    }

    string codePointToUtf8(long unicode){
        ostringstream out;
        if (unicode <= 0x7f){
            out << (char) unicode;
        } else if (unicode <= 0x7ff){
            /* 110xxxxx 10xxxxxx */
            unsigned char byte1 = ((unicode >> 6) & 0x1f) | (6 << 5);
            unsigned char byte2 = (unicode & 0x3f) | (2 << 6);
            out << byte1 << byte2;
        } else if (unicode <= 0xffff){
            /* 1110xxxx 10xxxxxx 10xxxxxx */
            unsigned char byte1 = ((unicode >> 12) & 0xf) | (0xe << 4);
            unsigned char byte2 = ((unicode >> 6) & 0x3f) | (2 << 6);
            unsigned char byte3 = (unicode & 0x3f) | (2 << 6);
            out << byte1 << byte2 << byte3;
        } else if (unicode <= 0x10ffff){
            /* 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx */
            unsigned char byte1 = ((unicode >> 18) & 0x7) | (0x1e << 3);
            unsigned char byte2 = ((unicode >> 12) & 0x3f) | (2 << 6);
            unsigned char byte3 = ((unicode >> 6) & 0x3f) | (2 << 6);
            unsigned char byte4 = (unicode & 0x3f) | (2 << 6);
            out << byte1 << byte2 << byte3 << byte4;
        }

        return out.str();
    }

    /* Reads a code point from a utf16 string made up of uint16_t integers */
    /* FIXME: add length for input */

    long readUtf16CodePoint(const uint16_t * input, unsigned int * position){
        uint16_t word1 = input[*position];
        *position += 1;

        /*  1) If W1 < 0xD800 or W1 > 0xDFFF, the character value U is the value
         *     of W1. Terminate.
         */
        if (word1 < 0xd800 || word1 > 0xdfff){
            return word1;
        }

        /* 2) Determine if W1 is between 0xD800 and 0xDBFF. If not, the sequence
         *    is in error and no valid character can be obtained using W1.
         *    Terminate.
         */
        if (word1 >= 0xd800 && word1 <= 0xdbff){

            /* 3) If there is no W2 (that is, the sequence ends with W1), or if W2
             *    is not between 0xDC00 and 0xDFFF, the sequence is in error.
             *    Terminate.
             */
            uint16_t word2 = input[*position];
            if (word2 >= 0xdc00 && word2 <= 0xdfff){
                /* 4) Construct a 20-bit unsigned integer U', taking the 10 low-order
                 *    bits of W1 as its 10 high-order bits and the 10 low-order bits of
                 *    W2 as its 10 low-order bits.
                 */
                /* 5) Add 0x10000 to U' to obtain the character value U. Terminate. */
                return (((word1 & 0x3ff) << 10) |
                         (word2 & 0x3ff)) + 0x10000;
            }
        }

        return 0;
    }

    string utf16_to_utf8(const uint16_t * utf16){
        ostringstream out;
        unsigned int position = 0;
        while (utf16[position] != 0){
            out << codePointToUtf8(readUtf16CodePoint(utf16, &position));
        }
        return out.str();
    }

//used on textinput clas CTextInput
string encodeUtf8(unsigned long unicode){
    ostringstream out;
    if (unicode < 128){
        out << (unsigned char) unicode;
    } else if (unicode < 2047){
        unsigned char byte1 = 192 + unicode / 64;
        unsigned char byte2 = 128 + unicode % 64;
        out << byte1 << byte2;
    } else if (unicode <= 65535){
        unsigned char byte1 = 224 + unicode / 4096;
        unsigned char byte2 = 128 + (unicode / 64) % 64;
        unsigned char byte3 = 128 + unicode % 64;

        out << byte1 << byte2 << byte3;
    } else if (unicode <= 2097151){
        unsigned char byte1 = 240 + unicode / 262144;
        unsigned char byte2 = 128 + (unicode / 4096) % 64;
        unsigned char byte3 = 128 + (unicode / 64) % 64;
        unsigned char byte4 = 128 + (unicode % 64);

        out << byte1 << byte2 << byte3 << byte4;
    } else if (unicode <= 67108863){
        unsigned char byte1 = 248 + (unicode / 16777216);
        unsigned char byte2 = 128 + ((unicode / 262144) % 64);
        unsigned char byte3 = 128 + ((unicode / 4096) % 64);
        unsigned char byte4 = 128 + ((unicode / 64) % 64);
        unsigned char byte5 = 128 + (unicode % 64);

        out << byte1 << byte2 << byte3 << byte4 << byte5;
    } else if (unicode <= 2147483647){
        unsigned char byte1 = 252 + (unicode / 1073741824);
        unsigned char byte2 = 128 + ((unicode / 16777216) % 64);
        unsigned char byte3 = 128 + ((unicode / 262144) % 64);
        unsigned char byte4 = 128 + ((unicode / 4096) % 64);
        unsigned char byte5 = 128 + ((unicode / 64) % 64);
        unsigned char byte6 = 128 + (unicode % 64);
    }
    return out.str();
}

//==================================================================================
// Convert the Latin-1 text to UNICODE
//==================================================================================
Uint16 *ASCII_to_UNICODE(Uint16 *unicode, const char *text, int len)
{
	int i;

	for ( i=0; i < len; ++i ) {
		unicode[i] = ((const unsigned char *)text)[i];
	}
	unicode[i] = 0;

	return unicode;
}

Uint16 * Latin1_Uni(const char *text)
{
	Uint16 *unicode_text;
	int i, unicode_len;

	/* Copy the Latin-1 text to a UNICODE text buffer */
	unicode_len = strlen(text);
	unicode_text = (Uint16 *)malloc((unicode_len+1)*(sizeof *unicode_text));
	if ( unicode_text == NULL ) {
		SDL_SetError("SGE - Out of memory");
		return(NULL);
	}
	for ( i=0; i < unicode_len; ++i ) {
		unicode_text[i] = ((const unsigned char *)text)[i];
	}
	unicode_text[i] = 0;

	return(unicode_text);
}

//==================================================================================
// Convert the UTF-8 text to UNICODE
//==================================================================================
Uint16 * UTF8_to_UNICODE(Uint16 *unicode, const char *utf8, int len)
{
	int i, j;
	Uint16 ch;

	for ( i=0, j=0; i < len; ++i, ++j ) {
		ch = ((const unsigned char *)utf8)[i];
		if ( ch >= 0xF0 ) {
			ch  =  (Uint16)(utf8[i]&0x07) << 18;
			ch |=  (Uint16)(utf8[++i]&0x3F) << 12;
			ch |=  (Uint16)(utf8[++i]&0x3F) << 6;
			ch |=  (Uint16)(utf8[++i]&0x3F);
		} else
		if ( ch >= 0xE0 ) {
			ch  =  (Uint16)(utf8[i]&0x3F) << 12;
			ch |=  (Uint16)(utf8[++i]&0x3F) << 6;
			ch |=  (Uint16)(utf8[++i]&0x3F);
		} else
		if ( ch >= 0xC0 ) {
			ch  =  (Uint16)(utf8[i]&0x3F) << 6;
			ch |=  (Uint16)(utf8[++i]&0x3F);
		}
		unicode[j] = ch;
	}
	unicode[j] = 0;

	return unicode;
}

Uint16 * UTF8_Uni(const char *text)
{
	Uint16 *unicode_text;
	int unicode_len;

	/* Copy the UTF-8 text to a UNICODE text buffer */
	unicode_len = strlen(text);
	unicode_text = (Uint16 *)malloc((unicode_len+1)*(sizeof *unicode_text));
	if ( unicode_text == NULL ) {
		SDL_SetError("SGE - Out of memory");
		return(NULL);
	}

	return UTF8_to_UNICODE(unicode_text, text, unicode_len);
}


}
} //end SGF
