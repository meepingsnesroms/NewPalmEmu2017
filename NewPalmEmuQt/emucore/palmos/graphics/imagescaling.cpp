#include "minifunc.h"
#include "m68k.h"
#include "dataexchange.h"
#include "palette.h"

#include "palmwrapper.h"//HACK remove this and all palmabrt() functions from this file


//this files varibles should be private to this file to prevent conflicts

//image width and height
static int width,height,rowbytes,imagebpp;

//original and converted buffers
static uint8_t* imagedata;
static uint16_t* converteddata;

//handlers for custom palette
uint16_t activepalette[256];
//#define getcolor8bbp(eek) (palette8bpp[eek])



void upscale1bppimage(uint8_t* inputbuffer,uint16_t* outputbuffer){
	int finalx,finaly;
	uint8_t thisbyte;
	uint8_t thisbit;
	uint8_t pig;
	inc_for(finaly,height){
		inc_for(finalx,width){
			thisbyte = inputbuffer[finaly * rowbytes + finalx / 8];
			thisbit = (0x80 >> (finalx % 8));
			pig = thisbyte & thisbit;
			outputbuffer[finaly * width + finalx] = ((pig != 0) ? 0x0000 : 0xFFFF);
		}
	}
}

void upscale2bppimage(uint8_t* inputbuffer,uint16_t* outputbuffer){
	int finalx,finaly;
	palmabrt();//HACK
}

void upscale4bppimage(uint8_t* inputbuffer,uint16_t* outputbuffer){
	int finalx,finaly;
	palmabrt();//HACK
}

void upscale8bppimage(uint8_t* inputbuffer,uint16_t* outputbuffer){
	int finalx,finaly;
	uint8_t activebyte;
	inc_for(finaly,height){
		inc_for(finalx,width){
			activebyte = inputbuffer[finaly * rowbytes + finalx];
			//outputbuffer[finaly * width + finalx] = mypalettecolor(activebyte);
			outputbuffer[finaly * width + finalx] = activepalette[activebyte];
		}
	}
}

void setimageparams(int width_L,int height_L,int imagebpp_L){
	width = width_L;
	height = height_L;
	imagebpp = imagebpp_L;
}

void setpalette(uint8_t** newpalette){
	uint32_t indexes = bitstocolors(imagebpp);
	for(uint32_t index = 0;index < indexes;index++){
		activepalette[index] = paltopalm(newpalette[index]);
	}
}

void setpalette68k(offset_68k newpalette){
	//uint32_t indexes = bitstocolors(imagebpp);
	uint32_t indexes = get_word(newpalette);//read it from the palette
	for(uint32_t index = 0;index < indexes;index++){
		activepalette[index] = getcolortblindex(newpalette,index);
	}
}

void resetpalette(){
	switch(imagebpp){
		case 8:
			//setpalette(PalmPalette8bpp);
			break;
		case 4:
			palmabrt();//HACK dont know how to handle 4bbp color
			break;
		case 2:
			//setpalette(PalmPalette2bpp);
			break;
			//1bpp has no palette because it is just on and off
		default:
			palmabrt();//HACK unsupported format
			break;
	}
}

void upscaleimage(uint8_t* inptr,uint16_t* outptr){
	imagedata = inptr;
	converteddata = outptr;
	rowbytes = width * imagebpp / 8;
	if(width * imagebpp % 8)rowbytes += 1;
	switch(imagebpp){
		case 1:
			upscale1bppimage(imagedata,converteddata);
			break;
		case 2:
			upscale2bppimage(imagedata,converteddata);
			break;
		case 4:
			upscale4bppimage(imagedata,converteddata);
			break;
		case 8:
			upscale8bppimage(imagedata,converteddata);
			break;
		case 16:
			//no formatting necssary,already 16bit
			memcpy(converteddata,imagedata,width * height * 2);
			break;
		default:
			palmabrt();//HACK
			break;
	}
}

//all other parameters remain unchanged,only new pointers are needed
void upscaleimagein68k(offset_68k m68kin,offset_68k m68kout){
	//every line is byte aligned,so part of one byte at the end of every line may be unused
	size_t_68k totalbytes = width * imagebpp / 8;
	if(width * imagebpp % 8)totalbytes += height;//add one extra byte on each row

	//read out image data,convert,than put converted data back
	uint8_t* tempbufferinput = new uint8_t[totalbytes];
	uint16_t* tempbufferoutput = new uint16_t[width * height];
	readbytearray(m68kin,tempbufferinput,totalbytes);
	upscaleimage(tempbufferinput,tempbufferoutput);
	writebytearray(m68kout,(uint8_t*)tempbufferoutput,totalbytes);
	delete[] tempbufferinput;
	delete[] tempbufferoutput;
}

//converts one pixel into 2 in each direction(4 total)
void expand2x(uint16_t* input,uint16_t* output,int orgwidth,int orgheight){
	uint16_t store;
	for(int hcnt = 0;hcnt < orgheight;hcnt++){
		for(int wcnt = 0;wcnt < orgwidth;wcnt++){
			//doubles all pixels on a line(increases horizontal size)
			store = input[hcnt * orgwidth + wcnt];
			output[0] = store;
			output[1] = store;
			output += 2;
		}
		//doubles the line(increases vertical size)
		memcpy(output,output - orgwidth * 2,orgwidth * 2 * sizeof(uint16_t));
		output += orgwidth * 2;
	}
}

/*
exported functions
setimageparams(int,int,int);
setpalette(uint8_t**);
setpalette68k(offset_68k);
upscaleimage(uint8_t*,uint16_t*);
upscaleimagein68k(offset_68k,offset_68k);
expand2x(uint16_t*,uint16_t*,int);
*/

//palette is currently only suported for 8bpp
