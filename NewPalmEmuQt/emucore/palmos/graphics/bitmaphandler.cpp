#include "minifunc.h"
#include "dataexchange.h"
#include "m68k.h"

#if 0

TEMPHACK
//support bitmaptypev3
//testsize reads a 32bit value as 2 16bit values a multiplys them?
static offset_68k getbestbitmap(offset_68k startbitmap){
	bool hasloresscreen = (LCDW < 320 || LCDH < 320);
	offset_68k currentbestptr = nullptr_68k;
	uint16_t currentbestbpp = 0;
	LONG currentbestsize = 0;

	offset_68k curbitmap = startbitmap;
	while(true){
		offset_68k nextbmp = get_word(curbitmap + 10) * 4;//offset in longwords

		uint16_t testbpp = getbmpbpp(curbitmap);
		LONG testsize = ((WORD)get_word(curbitmap)) * ((WORD)get_word(curbitmap + 2));//stored as signed but is an error if negative
		uint8_t testversion = get_byte(curbitmap + 9);//version 3 has different nextbitmapoffset at a different address

		switch(testversion){
			case 0:
				//version 0 bitmaps dont support dasiy-chaining
				return curbitmap;
			case 1:
			case 2:
				//nothing special to do
				break;
			case 3:
				//version 3 not supported yet
			default:
				palmabrt();//hack
				break;
		}


		//debug tests
		if(testsize < 0)palmabrt();//hack
		//if(testbpp == 0 || testbpp > 32 || testsize < 0)palmabrt();//hack


		if(testsize == 0){//dummy bitmap(used to signal end of lores bitmap section),stop here for lo-res screens

			//first bitmap is dummy therefore there are no lores bitmaps,if screen is lores must abort or ignore this bitmap
			if(hasloresscreen && curbitmap == startbitmap){
				dbgprintf("There are no lores compatible bitmaps!");
				palmabrt();//hack
			}

			if(hasloresscreen)return currentbestptr;//found best bitmap for lores screens
		}else{//valid bitmap proceed with checks
			BYTE updateprams = 0;
			if(testbpp > currentbestbpp)updateprams += 2;//better color palette
			else if(testbpp < currentbestbpp)updateprams -= 2;//worse color palette

			if(testsize > currentbestsize)updateprams += 1;//more pixels
			else if(testsize < currentbestsize)updateprams -= 1;//less pixels

			if(updateprams > 0){
				currentbestptr = curbitmap;
				currentbestbpp = testbpp;
				currentbestsize = testsize;
			}
		}

		if(!nextbmp)break;//no more bitmaps to check
		else curbitmap += nextbmp;
	}

	return currentbestptr;
}

static uint8_t compressedbuffer[65535];//the max size of compressed images is 65535 bytes since the size is stored as a uint16_t
static uint8_t uncompressedbuffer[1048576];//1mb
static uint16_t finishedbuffer[1048576];//2mb
static uint16_t* lastbuffptr;
static uint16_t* nextbuffptr;

void parsebitmapstruct(offset_68k m68kaddr){
	//get the best bitmap from the chain
	m68kaddr = getbestbitmap(m68kaddr);

	//start parsing
	WORD imgwidth = get_word(m68kaddr);
	WORD imgheight = get_word(m68kaddr + 2);
	uint16_t rowbytes = get_word(m68kaddr + 4);
	uint16_t flags = get_word(m68kaddr + 6);
	uint8_t pixelsize = get_byte(m68kaddr + 8);
	uint8_t version = get_byte(m68kaddr + 9);
	//no need to check nextdepthoffset since the best bitmap was already found

	//private values
	int compression = BitmapCompressionTypeNone;
	bool hastransparent = false;
	offset_68k custompalette = nullptr_68k;
	size_t_68k imgbytes;

	//version 3 not supported yet
	if(version > 2)palmabrt();

	//version 0 only supports 1bpp images
	if(version == 0)pixelsize = 1;

	//compression flag
	if(version >= 2 && (flags & bit(15)))compression = get_byte(m68kaddr + 13);

	//transparency flag
	if(version >= 2 && (flags & bit(13))){
		hastransparent = true;
		//transparent = paltopalm(PalmPalette8bpp[get_byte(m68kaddr + 12)]);
	}

	//custom palette flag
	if(version >= 1 && (flags & bit(14))){
		custompalette = m68kaddr + 16;
		palmabrt();
	}

	//get final size of image
	imgbytes = rowbytes * height;

	//start output
	//move out of m68k addr space


	//decompress
	if(compression != BitmapCompressionTypeNone){
		readbytearray(m68kaddr,compressedbuffer,imgbytes);
		BMP_extract(compressedbuffer,uncompressedbuffer);
	}
	else readbytearray(m68kaddr,uncompressedbuffer,imgbytes);

	//convert to 16bit rgb565
	if(pixelsize != 16){
		setimageparams(imgwidth,imgheight,pixelsize);
		upscaleimage(uncompressedbuffer,finishedbuffer);
		imgredirptr = finishedbuffer;
	}
	else imgredirptr = uncompressedbuffer;

	//HACK draw it
}

#endif
