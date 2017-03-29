/*
	File:			utils.h

	Description:	Utility Functions

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

extern Err
AppReadBMP(TwGfxType* aGfx,
    TwGfxSurfaceType** aResult,
    const void * dataP,
    Int32 dataSize);

extern Err
FontInit(TwGfxType* aGfx);

extern Int16
FontGetLineHeight(void);

extern Int16
FontGetCharWidth(char c);

extern void
FontGetCharsInWidth(const char * s, 
    Int32 * lengthP, //! pass in the length, the length that fits is returned
    Int32 * widthP,  //! pass in the width, the width used is returned.
    char * truncationCharP //! pass in the truncation char, the char (if any) used
    );


extern Int32
FontDrawChars(const char * s, Int32 length, 
    TwGfxSurfaceType * destSurface, Int32 x, Int32 y);
    
extern const char* pack(const char* format, char* buf, const void* source);
