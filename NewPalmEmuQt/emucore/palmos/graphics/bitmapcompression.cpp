#include "minifunc.h"
#include "m68k.h"


#include "palmos/graphics/bitmapcompression.h"


static void BMP_ScanLine(UBYTE* compresseddata,UBYTE* uncompresseddata,UWORD rowbytes/*number of bytes per scanline*/){
	uint compressedsize = ((compresseddata[0] << 8) | compresseddata[1]) - 2/*subtract length from its self*/;
	compresseddata += 2;


	uint rowptr = 0;//byte in compressed data
	uint32 datanum = 0;//byte in uncompressed data
	uint rowindex = 0;//byte in current scanline
	UBYTE newdataflags;
	while(rowptr < compressedsize){
		newdataflags = compresseddata[rowptr];
		rowptr++;

		for(uint bytecount = 0;bytecount < 8;bytecount++){
			//plot bytes
			if(newdataflags & bit(7 - bytecount)){
				//this byte is new,get a byte from the stream
				uncompresseddata[datanum] = compresseddata[rowptr];
				rowptr++;
			}
			else{
				//the byte is the same,copy old byte
				uncompresseddata[datanum] = uncompresseddata[datanum - rowbytes];
			}

			datanum++;
			rowindex++;
			if(rowindex >= rowbytes){//should only need "==" but using ">=" just to be safe
				rowindex = 0;
				break;
			}
		}
	}
}

static void BMP_RLE(UBYTE* compresseddata,UBYTE* uncompresseddata){
	uint compressedsize = ((compresseddata[0] << 8) | compresseddata[1]) - 2/*subtract length from its self*/;
	compresseddata += 2;


	uint bunny = 0;//current position in the input
	uint32 loc = 0;//current position in the output
	UBYTE headerbyte,databyte;
	while(bunny < compressedsize){
		headerbyte = compresseddata[bunny];
		databyte = compresseddata[bunny + 1];
		bunny += 2;

		//repeat the byte (headerbyte) times
		while(headerbyte > 0){
			uncompresseddata[loc] = databyte;
			headerbyte--;
			loc++;
		}
	}
}

static void BMP_PackBits(UBYTE* compresseddata,UBYTE* uncompresseddata){
	uint compressedsize = ((compresseddata[0] << 8) | compresseddata[1]) - 2/*subtract length from its self*/;
	compresseddata += 2;


	uint bunny = 0;//current position in the input
	uint32 loc = 0;//current position in the output
	BYTE headerbyte;//the current command (-128 = skip,< 0 repeat,>= 0 unique data)
	while(bunny < compressedsize){
		headerbyte = compresseddata[bunny];
		bunny++;
		if(headerbyte >= 0){//x bytes of unique data
			for(;headerbyte >= 0;headerbyte--){
				uncompresseddata[loc] = compresseddata[bunny];
				loc++;
				bunny++;
			}
		}
		else if(headerbyte == -128){//ignore headerbyte
			continue;
		}
		else if(headerbyte < 0){//repeat byte x times
			UBYTE data = compresseddata[bunny];
			for(;headerbyte <= 0;headerbyte++){
				uncompresseddata[loc] = data;
				loc++;
			}
			bunny++;
		}
		else dbgprintf("byte is not a byte.\n");
	}
}

void BMP_extract(UBYTE* compressed,UBYTE* output,int type,int rowbytes){
	switch(type){
		case BitmapCompressionTypeScanLine:
			BMP_ScanLine(compressed,output,rowbytes);
			break;
		case BitmapCompressionTypeRLE:
			BMP_RLE(compressed,output);
			break;
		case BitmapCompressionTypePackBits:
			BMP_PackBits(compressed,output);
			break;
		default:
			dbgprintf("Unsupported bitmap compression type:%d.\n",type);
			break;
	}
}

/*
exported functions
void BMP_extract(UBYTE* compressed,UBYTE* output,int type,int rowbytes);
*/
