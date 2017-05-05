#include "minifunc.h"
#include "m68k.h"


#include "palmos/graphics/bitmapcompression.h"


static void BMP_ScanLine(uint8_t* compresseddata, uint8_t* uncompresseddata, uint16_t rowbytes/*number of bytes per scanline*/){
	uint32_t compressedsize = ((compresseddata[0] << 8) | compresseddata[1]) - 2/*subtract length from its self*/;
	compresseddata += 2;


	uint32_t rowptr = 0;//byte in compressed data
	uint32_t datanum = 0;//byte in uncompressed data
	uint32_t rowindex = 0;//byte in current scanline
	uint8_t newdataflags;
	while(rowptr < compressedsize){
		newdataflags = compresseddata[rowptr];
		rowptr++;

		for(uint32_t bytecount = 0;bytecount < 8;bytecount++){
			//plot bytes
			if(newdataflags & bit(7 - bytecount)){
				//this byte is new, get a byte from the stream
				uncompresseddata[datanum] = compresseddata[rowptr];
				rowptr++;
			}
			else{
				//the byte is the same, copy old byte
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

static void BMP_RLE(uint8_t* compresseddata, uint8_t* uncompresseddata){
	uint32_t compressedsize = ((compresseddata[0] << 8) | compresseddata[1]) - 2/*subtract length from its self*/;
	compresseddata += 2;


	uint32_t bunny = 0;//current position in the input
	uint32_t loc = 0;//current position in the output
	uint8_t headerbyte,databyte;
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

static void BMP_PackBits(uint8_t* compresseddata, uint8_t* uncompresseddata){
	uint32_t compressedsize = ((compresseddata[0] << 8) | compresseddata[1]) - 2/*subtract length from its self*/;
	compresseddata += 2;


	uint32_t bunny = 0;//current position in the input
	uint32_t loc = 0;//current position in the output
	int8_t headerbyte;//the current command (-128 = skip,< 0 repeat,>= 0 unique data)
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
			uint8_t data = compresseddata[bunny];
			for(;headerbyte <= 0;headerbyte++){
				uncompresseddata[loc] = data;
				loc++;
			}
			bunny++;
		}
	}
}

void BMP_extract(uint8_t* compressed, uint8_t* output, int type, int rowbytes){
	switch(type){
		case BitmapCompressionTypeScanLine:
			BMP_ScanLine(compressed, output, rowbytes);
			break;
		case BitmapCompressionTypeRLE:
			BMP_RLE(compressed, output);
			break;
		case BitmapCompressionTypePackBits:
			BMP_PackBits(compressed, output);
			break;
		default:
			dbgprintf("Unsupported bitmap compression type:%d.\n", type);
			break;
	}
}

/*
exported functions
void BMP_extract(uint8_t* compressed, uint8_t* output, int type, int rowbytes);
*/
