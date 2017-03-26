#ifndef BITMAPCOMPRESSION_H
#define BITMAPCOMPRESSION_H

#include "m68k.h"

//Compression Types for BitMap (for BitmapVersionTwo and >)
enum{
	BitmapCompressionTypeScanLine = 0,
	BitmapCompressionTypeRLE,
	BitmapCompressionTypePackBits,
	BitmapCompressionTypeNone = 0xFF
};

void BMP_extract(UBYTE* compressed,UBYTE* output,int type,int rowbytes);

#endif // BITMAPCOMPRESSION_H
