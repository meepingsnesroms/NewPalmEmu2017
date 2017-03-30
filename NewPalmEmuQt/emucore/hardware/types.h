#ifndef TYPES
#define TYPES

#include <stdint.h>

//the real definitions (all others are just different names for these,required by 3rd party libraries)
typedef uint8_t uint8;
typedef int8_t int8;
typedef uint16_t uint16;
typedef int16_t int16;
typedef uint32_t uint32;
typedef int32_t int32;
typedef uint64_t uint64;
typedef int64_t int64;
typedef float float32;
typedef double float64;
typedef float double32;
typedef double double64;

static_assert(sizeof(float) == sizeof(uint8_t) * 4,"Incompatible FPU using emulator.");
static_assert(sizeof(double) == sizeof(uint8_t) * 8,"Incompatible FPU using emulator.");


//Used in arm emulator
typedef uint8 u8;
typedef uint16 u16;
typedef uint32 u32;
typedef uint64 u64;

typedef int8 s8;
typedef int16 s16;
typedef int32 s32;
typedef int64 s64;

//for ease of use
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

#endif // TYPES

