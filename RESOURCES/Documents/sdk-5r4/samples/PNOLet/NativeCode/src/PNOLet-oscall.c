/******************************************************************************
 *
 * Copyright (c) 1995-2004 PalmSource, Inc. All rights reserved.
 *
 * File: pnolet-oscall.c
 *
 * Release: Palm OS Developer Suite 5 SDK (68K) 4.0
 *
 *****************************************************************************/


#include "PceNativeCall.h"
#include "utils68K.h"

// from CoreTraps.h
#define sysTrapMemPtrNew	0xA013 // we need this in order to call into MemPtrNew

/*

This pnolet makes a call (through PACE) to MemPtrNew to allocate a buffer.  The
arguments to the OS function (here just size) must be on the stack, and must be
in big-endian format.

*/

unsigned long MyNativeOSCall(const void *emulStateP, void *userData68KP, Call68KFuncType *call68KFuncP)
{
	unsigned long  size;     // UInt32, must be stack based
	unsigned char* bufferP;  // array of Byte
	unsigned char  i;        // Byte

	// set the size to 10 bytes, byte swapped so it's in big-endian format
	// This will be the argument to MemPtrNew().
	size = EndianSwap32(0x0000000AL);   // == 10 in big endian

	// a more clever but less-readable equivalent is:
//	size = 0x0A000000L;

	// call MemPtrNew, using the 4 bytes of size directly from the stack
	// The 4 specifies the size of the arguments, and we need to OR the size
	// with kPceNativeWantA0 because the return value is a pointer type.
	bufferP = (unsigned char *)(
				(call68KFuncP)(emulStateP, PceNativeTrapNo(sysTrapMemPtrNew), &size, 4 | kPceNativeWantA0));

	// just for fun, lets do something with the bytes in the buffer
	for (i = 0; i < 9; i++) bufferP[i] = i+'A';  // write in "ABCDEFGHI"
	bufferP[9] = 0;                              // force in the null string terminator

	return (unsigned long)bufferP;  // return a pointer to the buffer
}
