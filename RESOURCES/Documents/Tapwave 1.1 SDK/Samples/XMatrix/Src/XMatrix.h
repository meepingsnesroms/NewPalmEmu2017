/*
	File:			XMatrix.h

	Description:	Matrix header file.

	Author:		

	Copyright:		Copyright © 2003 by Tapwave, Inc.

	Disclaimer:		IMPORTANT:  This Tapwave software is provided by Tapwave, Inc. ("Tapwave").  Your 
					use is subject to and governed by terms and conditions of the Software Development 
					Kit Agreement ("SDK Agreement") between you and Tapwave.  If you have not entered 
					into Tapwave’s standard SDK Agreement with Tapwave, you have no right or license 
					to use, reproduce, modify, distribute or otherwise exploit this Tapwave software.  
					You may obtain a copy of Tapwave’s standard SDK Agreement by calling 650-960-1817
					or visiting Tapwave at http://www.tapwave.com/developers/. 

	Change History (most recent first):
				
*/

#ifndef XMatrix_h___
#define XMatrix_h___

#include <TapWave.h>

#define PLAIN_MAP 1
#define GLOW_MAP  2

#define BITMAP_WIDTH    160
#define BITMAP_HEIGHT   182

#define MODE_TRACE      0
#define MODE_MATRIX     1
#define MODE_DNA        2
#define MODE_BINARY     3
#define MODE_HEX        4

#define INSERT_TOP      0
#define INSERT_BOTTOM   1
#define INSERT_BOTH     2

typedef void (*FillRectProc)(int dstX, int dstY, int dstW, int dstH);
typedef void (*DrawGlyphProc)(int dstX, int dstY, int srcX, int srcY, int srcW, int srcH,
                              int map, bool doFlip);

inline void* MyCalloc(Int32 aSize, Int32 aCount) {
  aSize *= aCount;
  void* p = MemPtrNew(aSize);
  MemSet(p, aSize, 0);
  return p;
}

inline void* MyMalloc(Int32 aSize) {
  void* p = MemPtrNew(aSize);
  return p;
}

inline void MyFree(void* aPtr) {
  if (aPtr) MemPtrFree(aPtr);
}

#endif /* XMatrix_h___ */
