#include "SGF_Types.h"

//defined by CMAKE - todo: define it in visual studio
#if defined(THIRDYTWOBITSUPPORT)
//32bit
#define TIFF_SSIZE_T signed long
#elif defined(SIXTYFOUR_BITSUPPORT)
//64 bit
#define TIFF_SSIZE_T signed long long
#endif

// for tiff compilation
#define TIFF_INT8_T int8_t
#define TIFF_UINT8_T uint8_t

#define TIFF_INT16_T int16_t
#define TIFF_UINT16_T uint16_t

#define TIFF_INT32_T int32_t
#define TIFF_UINT32_T uint32_t

#define TIFF_INT64_T int64_t
#define TIFF_UINT64_T uint64_t
