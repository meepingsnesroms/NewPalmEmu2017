/******************************************************************************
 *
 * Copyright (c) 1995-2002 PalmSource, Inc. All rights reserved.
 *
 * File: pnolet-endianness_and_alignment.c
 *
 * Release: Palm OS Developer Suite 5 SDK (68K) 4.0
 *
 *****************************************************************************/


#include "PceNativeCall.h"
#include "utils68K.h"
#include "example_data_type.h"


unsigned long NativeFunction(const void *emulStateP, void *userData68KP, Call68KFuncType *call68KFuncP)
{
	ExampleStructType* exampleData68KP = (ExampleStructType*)userData68KP;
	unsigned long number1;
	unsigned long number2;

	// make a local copies that are guaranteed to be 4-byte-aligned
	number1 = Read68KUnaligned32(&(exampleData68KP->number1));
	number2 = Read68KUnaligned32(&(exampleData68KP->number2));

	// add the two together and return the result
	return (unsigned long)(number1 + number2);
}
