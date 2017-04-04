#ifndef TYPES
#define TYPES

#include <stdint.h>

typedef float  float32_t;
typedef double double64_t;

//there is currently no FPU emulator avalible to use
static_assert(sizeof(float) == sizeof(uint8_t) * 4,"Incompatible FPU using emulator.");
static_assert(sizeof(double) == sizeof(uint8_t) * 8,"Incompatible FPU using emulator.");

//Used in arm emulator
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

#endif // TYPES

