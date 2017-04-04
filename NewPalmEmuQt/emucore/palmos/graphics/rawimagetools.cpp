#include "palmwrapper.h"

#include "rawimagetools.h"
#include "displaydriver.h" //fix this

//new list
#include "m68k.h"
#include "palmmalloc.h"
#include "resourcelocator.h"
#include "palmtypeaccess.h"
#include "stdlib68k.h"
#include "dataexchange.h"
#include "palmdefines.h"

#include "virtuallcd.h"

//HACK remove bitset
#include <bitset>

#include "palmos/graphics/palette.h"

//HACK remove this header
#include "palmos/graphics/bitmapcompression.h"

#include <stdlib.h> //needed for abs()


TEMPHACK
//support bitmaptypev3
//testsize reads a 32bit value as 2 16bit values a multiplys them?
static offset_68k getbestbitmap(offset_68k startbitmap){
	bool hasloresscreen = (LCDW < 320 || LCDH < 320);
	offset_68k currentbestptr = nullptr_68k;
	uint16_t currentbestbpp = 0;
	int32_t currentbestsize = 0;

	offset_68k curbitmap = startbitmap;
	while(true){
		offset_68k nextbmp = get_word(curbitmap + 10) * 4;//offset in longwords

		uint16_t testbpp = getbmpbpp(curbitmap);
		int32_t testsize = ((int16_t)get_word(curbitmap)) * ((int16_t)get_word(curbitmap + 2));//stored as signed but is an error if negative
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
			int8_t updateprams = 0;
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



gchar::gchar(offset_68k fntbmpstart,offset_68k glyphofft,char val, uint16_t oncol, uint16_t offcol, BOUNDRY ar, offset_68k yinc, int lineofft){
	value = val;
	start = fntbmpstart;
	glyphoffset = glyphofft;
	oncolor = oncol;
	offcolor = offcol;
	area = ar;
	yincrement = yinc;
	pxbelowline = lineofft;
}

int gchar::aboveline(){
	return area.h - pxbelowline;
}

int gchar::belowline(){
	return pxbelowline;
}

int16_t gchar::width(){
	return area.w;
}

int16_t gchar::height(){
	return area.h;
}

uint16_t gchar::getpixel(int16_t x,int16_t y){
	uint32_t pxnum = y * yincrement + x + glyphoffset;
	uint8_t pxbyte = get_byte(start + pxnum / 8);
	if(pxbyte & (0x80 >> (pxnum % 8)))return oncolor;
	return offcolor;
}



//RAWfnt parsing
void RAWfnt::setactivefont(offset_68k location){

	dbgprintf("Loading New Font\n");

	//header = 26 bytes
	//height = asecnt + descent
	int16_t fonttype = get_word(location);//0 always 36864/0x9000 for 'NFNT' (unsure about 'nfnt')
	firstch = get_word(location + 2);//2 first ascii value
	lastch = get_word(location + 4);//4 last ascii value
	//6 maxwidth of char (unknown)
	//8 negative of maximum char (unknown)
	//10 negative of descent (unknown)
	charwidth = get_word(location + 12);//12	//hack real width is rowwords * 16 (for 1 bit per pixel)
	height = get_word(location + 14);//14

	//offset to offset/width table (dont know if byte,word or long)
	//int16_t OWToffset = get_word(location + 16);
	charinfotableoffset = get_word(location + 16) * 2;

	ascent = get_word(location + 18);//ascent (pix above line)
	descent = get_word(location + 20);//descent (pix below line)

	int16_t leading = get_word(location + 22);//(unknown)
	rowwords = get_word(location + 24);//row width of fontbitmap
	//fonttype is 26 bytes long
	//then comes bitmap

	//use fontptr from now on!!
	width = rowwords * 16;//HACK!
	fontptr = location;
	size_t_68k fontBMPsize = width * height;
	numch = lastch - firstch;
	charBMP.resize(fontBMPsize);

	//load into memory
	parsefnt();
}

RAWfnt::~RAWfnt(){
	charBMP.clear();
}

void RAWfnt::parsefnt(){
	dbgprintf("Font Size: W:%d,H:%d\n",width,height);

	offset_68k fntbmp = fontptr + 26;
	uint16_t rowbytes = rowwords * 2;
	int finalx,finaly;
	inc_for(finaly,height){
		inc_for(finalx,width){
			offset_68k thisbyte = fntbmp + finaly * rowbytes + finalx / 8;
			uint8_t thisbit = (0x80 >> (finalx % 8));
			uint8_t pig = get_byte(thisbyte) & thisbit;
			charBMP[finaly * width + finalx] = ((pig != 0) ? 0x0000 : 0xFFFF);
		}
	}

#ifdef TESTRENDERFONTS
	//test //hack
	FBWriter display(lcd_start,LCDW,LCDBPP);
	inc_for(finaly,height){
		inc_for(finalx,width){
			int16_t displayx = finalx,displayy = finaly;
			while(displayx > LCDW){
				displayx -= LCDW;
				displayy += height;
			}
			display.setpixel(displayx,displayy + 320,getpixel(finalx,finaly));
		}
	}
#endif
}

uint16_t RAWfnt::getpixel(int16_t x,int16_t y){
	return charBMP[y * width + x];
}

TEMPHACK
//fix above/below line positioning
gchar RAWfnt::getIMG(unsigned char chnum){
	offset_68k glyphoffset = (chnum - firstch) * charwidth;//in pixels
	int16_t chrwidth = get_byte(fontptr + charinfotableoffset + (chnum - firstch) * 2 + 1);
	offset_68k chrimgoffset = get_byte(fontptr + charinfotableoffset + (chnum - firstch) * 2);

	//offset_68k glyphoffset = chnum * charwidth;//in pixels
	//int16_t chrwidth = get_byte(fontptr + charinfotableoffset + chnum * 2 + 1);
	//offset_68k chrimgoffset = get_byte(fontptr + charinfotableoffset + chnum * 2);


	if(chrwidth == fntMissingChar)palmabrt();//hack
	if(chnum < firstch)palmabrt();//hack
	dbgprintf("Char:%c,Value:%d,Offset:%d,Width:%d\n",chnum,chnum,chrimgoffset,chrwidth);


	BOUNDRY gchrarea;
	gchrarea.w = chrwidth;
	gchrarea.h = height;

	gchar temp(fontptr,glyphoffset,chnum,0x0000,0xFFFF,gchrarea,width,descent);//0/*hack should be pixels below line*/);//hack
	return temp;
}



//RAWimg access
RAWimg::RAWimg(offset_68k m68kaddr, uint8_t type){
	from68k(m68kaddr,type,findme,findme,findme,false);
}

RAWimg::RAWimg(offset_68k m68kaddr, uint8_t type, int16_t datawidth,
			   int16_t dataheight, uint8_t bpp, bool leaveinplace){
	from68k(m68kaddr,type,datawidth,dataheight,bpp,leaveinplace);
}

RAWimg::~RAWimg(){
	purifieddata.clear();
}

void RAWimg::from68k(offset_68k m68kaddr, uint8_t type, int16_t datawidth,
					 int16_t dataheight, uint8_t bpp, bool leaveinplace){
	inm68kaddrspace = true;
	datatype = type;
	compression = BitmapCompressionTypeNone;
	switch(datatype){
		case WINDOW:
			m68kaddr = getwinbmp(m68kaddr);
		case ICON:
		case BMP:{
				if(datatype == BMP)m68kaddr = getbestbitmap(m68kaddr);

				typeversion = get_byte(m68kaddr + 9);

				if(typeversion > 2)palmabrt();//version 3 not supported yet

				if(datawidth)width = datawidth;
				else width = get_word(m68kaddr);
				if(dataheight)height = dataheight;
				else height = get_word(m68kaddr + 2);

				rowbytes = get_word(m68kaddr + 4);

				if(bpp)pixelsize = bpp;
				else if(typeversion > 0)pixelsize = get_byte(m68kaddr + 8);
				else pixelsize = 1;

				//dbgprintf("Bmp Rowbytes:%d,PixelSize:%d\n",rowbytes,pixelsize);

				uint16_t flags = get_word(m68kaddr + 6);

				if(flags & bit(15))compression = get_byte(m68kaddr + 13);

				//custom palette
				if(flags & bit(14)){
					custompalette = m68kaddr + 16;
					palmabrt();
				}

				//transparency
				if(flags & bit(13) && typeversion > 1 && pixelsize >= 8){
					//hastransparent = true;//hack
					//transparent = paltopalm(PalmPalette8bpp[get_byte(m68kaddr + 12)]);
					hastransparent = true;//hack
					transparent = paltopalm(PalmPalette8bpp[get_byte(m68kaddr + 12)]);
				}

				//dbgprintf("BMP flags:%04x\n",get_word(m68kaddr + 6));

				m68kptr = getbmpdata(m68kaddr);

				if(m68kptr >= dyn_start && m68kptr < lcd_start)readonly = true;
				break;
		}
		default:
			palmabrt();//hack
			break;
	}
	//only reference m68kptr after this point!

	orgdat = (uint8_t*)get_real_address(m68kptr);

	totalsize = height * rowbytes;

	tobuff();
}

uint16_t RAWimg::mypalettecolor(uint8_t index){
	if(custompalette)return getcolortblindex(custompalette,index);
	else{
		switch(pixelsize){
			case 8:
				return paltopalm(PalmPalette8bpp[index]);
			case 4:
				//4bit can be color or black and white,but this cant currently tell so just stop here
				palmabrt();
				break;
			case 2:
				return paltopalm(PalmPalette2bpp[index]);
			case 1:
				//just black and white
				return (index != 0) ? 0x0000 : 0xFFFF;
			default:
				palmabrt();
				break;
		}
	}
	return 0;
}

uint16_t RAWimg::getpixel(int16_t x, int16_t y){
	return purifieddata[y * width + x];
}

void RAWimg::setpixel(int16_t x, int16_t y, uint16_t color){
	purifieddata[y * width + x] = color;
}

void RAWimg::get1bitpixelarr(){
	int finalx,finaly;
	if(inm68kaddrspace){
		inc_for(finaly,height){
			inc_for(finalx,width){
				offset_68k thisbyte = m68kptr + finaly * rowbytes + finalx / 8;
				uint8_t thisbit = (0x80 >> (finalx % 8));
				uint8_t pig = get_byte(thisbyte) & thisbit;
				purifieddata[finaly * width + finalx] = ((pig != 0) ? 0x0000 : 0xFFFF);
			}
		}
	}
	else{
		inc_for(finaly,height){
			inc_for(finalx,width){
				uint8_t thisbyte = orgdat[finaly * rowbytes + finalx / 8];
				uint8_t thisbit = (0x80 >> (finalx % 8));
				uint8_t pig = thisbyte & thisbit;
				purifieddata[finaly * width + finalx] = ((pig != 0) ? 0x0000 : 0xFFFF);
			}
		}
	}
}

void RAWimg::get2bitpixelarr(){
	palmabrt();//hack
	int finalx,finaly;
	if(inm68kaddrspace){
		for(finaly = 0;finaly < height;finaly++){
			for(finalx = 0;finalx < width;finalx++){
				uint8_t pig = (get_byte(m68kptr + finaly * rowbytes + finalx / 4) >> 2 * (3 - finalx % 4)) & 0x03;
				purifieddata[finaly * width + finalx] = paltopalm(PalmPalette2bpp[pig]);
			}
		}
	}
}

void RAWimg::get4bitpixelarr(){
	palmabrt();//hack
	int finalx,finaly;
	if(inm68kaddrspace){
		for(finaly = 0;finaly < height;finaly++){
			for(finalx = 0;finalx < width;finalx++){
				uint8_t pig = (get_byte(m68kptr + finaly * rowbytes + finalx / 2) << 4 * (1 - finalx % 2)) & 0x0F;
				purifieddata[finaly * width + finalx] = paltopalm(PalmPalette4bpp[pig]);
			}
		}
	}
}

void RAWimg::get8bitpixelarr(){
	int finalx,finaly;
	if(inm68kaddrspace){
		inc_for(finaly,height){
			inc_for(finalx,width){
				uint8_t pig = get_byte(m68kptr + finaly * rowbytes + finalx);
				purifieddata[finaly * width + finalx] = mypalettecolor(pig);
			}
		}
	}else{
		inc_for(finaly,height){
			inc_for(finalx,width){
				uint8_t pig = orgdat[finaly * rowbytes + finalx];
				purifieddata[finaly * width + finalx] = mypalettecolor(pig);
			}
		}
		//palmabrt();//hack
	}
}

void RAWimg::tobuff(){
	if(pixelsize < 16)purifieddata = std::vector<uint16_t>(width * height);//new uint16_t[width * height];

	bool cleanupcompression = false;
	uint8_t* BKorgdat = orgdat;

	if(compression != BitmapCompressionTypeNone){
		switch(compression){
			case BitmapCompressionTypeScanLine:
				orgdat = scanline(m68kptr,width,height,rowbytes);
				break;
			case BitmapCompressionTypeRLE:
				//palmabrt();//hack
				orgdat = RLE(m68kptr,width,height,rowbytes);
				break;
			case BitmapCompressionTypePackBits:
				orgdat = PackBits(m68kptr,width,height,rowbytes);
				break;
			default:
				dbgprintf("err no compression support\n");
				palmabrt();
				break;
		}
		inm68kaddrspace = false;
		cleanupcompression = true;
	}

	switch(pixelsize){
		case 1:
			get1bitpixelarr();
			break;
		case 2:
			get2bitpixelarr();
			break;
		case 4:
			get4bitpixelarr();
			break;
		case 8:
			get8bitpixelarr();
			break;
		case 16:
			//palmabrt();
			//16bit data can just use a pointer since it dosent need to be byteswapped or shifted
			purifieddata = std::vector<uint16_t>((uint16_t*)orgdat,(uint16_t*)orgdat + totalsize);
			break;
		default:
			palmabrt();
			break;
	}

	if(cleanupcompression){
		delete[] orgdat;
		orgdat = BKorgdat;
	}
}







FBWriter::FBWriter(offset_68k addr,uint16_t buffwidth,uint8_t bpp){
	test = get_real_address(addr);
	location = addr;
	width = buffwidth;
	pixelsize = bpp;

	switch(bpp){
		case 16:
			rowbytes = 2 * width;
			return;
		case 8:
			rowbytes = width;
			break;
		case 4:
			rowbytes = width / 2 + (width % 2 != 0 ? 1 : 0);
			break;
		case 2:
			rowbytes = width / 4 + (width % 4 != 0 ? 1 : 0);
			break;
		case 1:
			rowbytes = width / 8 + (width % 8 != 0 ? 1 : 0);
			break;
		default:
			palmabrt();//depth not supported
			break;
	}

	if(rowbytes & 1)rowbytes += 1;//pad to word boundry
}


uint16_t FBWriter::getpixel(int16_t x, int16_t y){
	palmabrt();//hack
	switch(pixelsize){
		case 16:
			return get_word(location + (y * width + x) * 2);
		case 8:
			return get_byte(location + y * rowbytes + x);
		default:
			palmabrt();
			break;
	}
	return 0;
}

void FBWriter::setpixel(int16_t x, int16_t y, uint16_t color){
	if(pixelsize != 16)palmabrt();//hack
	switch(pixelsize){
		case 16:
			put_word(location + (y * width + x) * 2,color);
			return;
		case 8:
			put_byte(location + y * rowbytes + x,color);
			return;
		case 1:
			//hack
			palmabrt();
			return;
		default:
			palmabrt();
			break;
	}
}


void FBWriter::draw(RAWimg& smlimg, int16_t x, int16_t y){
	uint16_t pixstore;
	int cntx,cnty;
	int datawidth = smlimg.width;
	int dataheight = smlimg.height;

	if(smlimg.hastransparent == true){
		inc_for(cnty,dataheight){
			inc_for(cntx,datawidth){
				pixstore = smlimg.getpixel(cntx,cnty);
				if(pixstore != smlimg.transparent)setpixel(cntx + x,cnty + y,pixstore);
			}
		}
	}else {
		inc_for(cnty,dataheight){
			inc_for(cntx,datawidth){
				pixstore = smlimg.getpixel(cntx,cnty);
				setpixel(cntx + x,cnty + y,pixstore);
			}
		}
	}
}

void FBWriter::draw(char letter, RAWfnt& chrimgs, int16_t x, int16_t y){
	gchar IMG = chrimgs.getIMG(letter);
	int width = IMG.width();
	int height = IMG.height();
	int countx,county;
	inc_for(county,height){
		inc_for(countx,width){
			setpixel(x + countx,y + county,IMG.getpixel(countx,county));
		}
	}
}

bool FBWriter::draw5x7(int16_t x,int16_t y,uint16_t color,char letter){
	/*
	if(letter < 0x20 || letter > 0x7f){
		if(letter == 0)return true;//end of string
		dbgprintf("invalid char Value:%d\n",letter);
		return false;
	}
	*/

	int curx,cury;
	inc_for(cury,7){
		inc_for(curx,5){
			unsigned int total = (letter - 0x20) * 5;
			int temp = curx * 5 + cury;//bits
			int thisbyte = curx;//bytes
			int thisbit = cury;//leftover
			//if(Font5x7[total + thisbyte] & bit(thisbit))setpixel(curx + x,cury + y,color);
		}
	}
	return false;
}

void FBWriter::line(int16_t x, int16_t y, int16_t x2, int16_t y2, int prams, uint16_t color){
	//prams dashed,dotted

	//taken from rosetta code
	int dx = abs(x2 - x), sx = x < x2 ? 1 : -1;
	int dy = abs(y2 - y), sy = y < y2 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2, e2;

	for(;;){
	  setpixel(x,y,color);
	  if(x == x2 && y == y2) break;
	  e2 = err;
	  if(e2 > -dx){ err -= dy; x += sx; }
	  if(e2 < dy){ err += dx; y += sy; }
	}
}

void FBWriter::rect(int16_t x, int16_t y,int16_t w, int16_t h,int prams,uint16_t color,uint16_t round){
	int wcnt,hcnt;
	switch(prams){
		case FILL:{
				x += THICKNESS,y += THICKNESS,w -= THICKNESS,h -= THICKNESS;
				inc_for(hcnt,h){
					inc_for(wcnt,w){
						setpixel(x + wcnt,y + hcnt,color);
					}
				}
			}
			break;
		case ERASE:{
				inc_for(hcnt,h){
					inc_for(wcnt,w){
						setpixel(x + wcnt,y + hcnt,color);
					}
				}
			}
			break;
		case OUTLINE:{
				line(x,y,x,y + h,SOLID,color);
				line(x,y,x + w,y,SOLID,color);
				line(x + w,y,x + w,y + h,SOLID,color);
				line(x,y + h,x + w,y + h,SOLID,color);
			}
			break;

		default:
			palmabrt();
			break;
	}

	//HACK add round edges
}

void FBWriter::copyrect(RAWimg& host, int16_t startx, int16_t starty,int16_t rectw, int16_t recth,int16_t outx, int16_t outy){
	int x,y;
	inc_for(y,recth){
		inc_for(x,rectw){
			setpixel(outx + x,outy + y,host.getpixel(startx + x,starty + y));
		}
	}
}



//image type creation
offset_68k newbmp(int16_t width,int16_t height,uint8_t bpp,
			   bool hasclearcol,uint8_t clearcolindex,bool hascoltable,offset_68k coltable){
	uint16_t rowbytes = makerowbytes(width,bpp);
	uint16_t bmpflags = 0;
	size_t_68k bmpcoltablesize;

	//get size
	size_t_68k bmpsize = 16;
	bmpsize += height * rowbytes;

	//make flags
	if(hascoltable){
		if(bpp >= 16)palmabrt();//HACK //you dont need a color table for 16bpp and up,most likely something went wrong
		bmpcoltablesize = bitstocolors(bpp);
		bmpsize += 2 + bmpcoltablesize;
		bmpflags |= bit(14);
	}
	if(hasclearcol)bmpflags |= bit(13);
	else clearcolindex = 0;

	offset_68k thisbmp = getfreeheap(bmpsize);

	//BitmapType
	put_word(thisbmp,width);//size
	put_word(thisbmp + 2,height);
	put_word(thisbmp + 4,rowbytes);//rowbytes
	put_word(thisbmp + 6,bmpflags);//flags
	put_byte(thisbmp + 8,bpp);//bpp
	put_byte(thisbmp + 9,2);//version
	put_word(thisbmp + 10,0);//next BitmapType (there is none)
	put_byte(thisbmp + 12,clearcolindex);//transparency index
	put_byte(thisbmp + 13,0xFF);//compression type (none)
	put_word(thisbmp + 14,0);//reserved

	if(hascoltable){
		put_word(thisbmp + 16,bmpcoltablesize);

		offset_68k inputentryptr = coltable + 2;
		offset_68k bmpentryptr = thisbmp + 16 + 2;

		uint16_t count;
		for(count = 0;count < bmpcoltablesize;count++){
			put_long(bmpentryptr + count * 4,get_long(inputentryptr + count * 4));
		}

		memset68k(thisbmp + 16 + 2 + bmpcoltablesize,0,height * rowbytes);
	}
	else memset68k(thisbmp + 16,0,height * rowbytes);

	return thisbmp;
}

TEMPHACK
//fix scaling values

//only called during bootup to create the main drawstate!
offset_68k newdrawstate(){
	offset_68k thisdrawstate = getfreeheap(44);//20 without HighDensityDisplay Feature Set

	//DrawStateType
	put_byte(thisdrawstate,winPaint);//transfer mode
	put_byte(thisdrawstate + 1,0);//pattern
	put_byte(thisdrawstate + 2,0);//underline mode
	put_byte(thisdrawstate + 3,stdFont);//fontid
	put_long(thisdrawstate + 4,INTERCEPT);//font ptr

	//CustomPatternType ignored CustomPatternType = uint8_t[8]

	put_byte(thisdrawstate + 16,0);//fore color
	put_byte(thisdrawstate + 17,0x22);//back color
	put_byte(thisdrawstate + 18,0xFF);//text color
	put_byte(thisdrawstate + 19,0);//reserved

	//Palm os 5 vars here
	put_long(thisdrawstate + 20,0);//fore rgbcolor (struct{uint8_t r,uint8_t g,uint8_t b,uint8_t index})
	put_long(thisdrawstate + 24,0);//back rgbcolor (struct{uint8_t r,uint8_t g,uint8_t b,uint8_t index})
	put_long(thisdrawstate + 28,0);//text rgbcolor (struct{uint8_t r,uint8_t g,uint8_t b,uint8_t index})
	put_word(thisdrawstate + 32,kCoordinatesStandard);//coord system
	put_word(thisdrawstate + 34,0);//reserved

	//os 5 scale conversion

	TEMPHACK;
	//convert to useable float16 values
	put_word(thisdrawstate + 36,kCoordinatesStandard);//scale
	put_word(thisdrawstate + 38,kCoordinatesStandard);//ntv to active scale
	put_word(thisdrawstate + 40,kCoordinatesStandard);//std to active scale
	put_word(thisdrawstate + 42,kCoordinatesStandard);//active to std scale

	return thisdrawstate;
}

offset_68k newwindow(int16_t width,int16_t height,uint16_t flags,uint16_t frameflags,
				  offset_68k winbmp,offset_68k drawstate,offset_68k nextwindowptr){
	offset_68k thiswindow = getfreeheap(40);
	//WindowType

	//HACK these values should not reflect the framebuffer
	put_word(thiswindow,LCDW);//width of lcd
	put_word(thiswindow + 2,LCDH);//height of lcd
	put_long(thiswindow + 4,lcd_start);//lcd starting addr


	put_word(thiswindow + 8,flags);//flags

	//clipping (unknown format)
	put_word(thiswindow + 10,0);//window bounds
	put_word(thiswindow + 12,0);
	put_word(thiswindow + 14,width);
	put_word(thiswindow + 16,height);
	put_word(thiswindow + 18,0);//clipping bounds
	put_word(thiswindow + 20,0);
	put_word(thiswindow + 22,width);
	put_word(thiswindow + 24,height);

	//pointers and frame attributes
	put_long(thiswindow + 26,winbmp);//bitmap ptr
	put_word(thiswindow + 30,frameflags);//framebitstype //multiple tiny ints < than 8 bits
	put_long(thiswindow + 32,drawstate);//drawstatetype ptr
	put_long(thiswindow + 36,nextwindowptr);//nextwindow ptr

	return thiswindow;
}

void initformwindow(offset_68k thiswindow,int16_t width,int16_t height,uint16_t flags,uint16_t frameflags,
				  offset_68k winbmp,offset_68k drawstate,offset_68k nextwindowptr){
	//WindowType
	put_word(thiswindow,LCDW);//width of lcd
	put_word(thiswindow + 2,LCDH);//height of lcd
	put_long(thiswindow + 4,lcd_start);
	put_word(thiswindow + 8,flags);//flags

	//clipping (unknown format)
	put_word(thiswindow + 10,0);//window bounds
	put_word(thiswindow + 12,0);
	put_word(thiswindow + 14,width);
	put_word(thiswindow + 16,height);
	put_word(thiswindow + 18,0);//clipping bounds
	put_word(thiswindow + 20,0);
	put_word(thiswindow + 22,width);
	put_word(thiswindow + 24,height);

	//pointers and frame attributes
	put_long(thiswindow + 26,winbmp);//bitmap ptr
	put_word(thiswindow + 30,frameflags);//framebitstype //multiple tiny ints < than 8 bits
	put_long(thiswindow + 32,drawstate);//drawstatetype ptr
	put_long(thiswindow + 36,nextwindowptr);//nextwindow ptr
}



//compression

//form
static int sizeof_FRMOBJ(uint8_t type){
	switch(type){
		case frmFieldObj://40
			return 40;
		case frmListObj://32
			return 32;
		case frmTableObj://74
			return 34 + 40/*fieldtype*/;
		case frmBitmapObj://8
			return 8;
		case frmLineObj://10
		case frmRectangleObj://10
			return 10;
		case frmFrameObj://14
		case frmLabelObj://14
			return 14;
		case frmTitleObj://12
			return 12;
		case frmPopupObj://4
		case frmGraffitiStateObj://4
			return 4;
		case frmControlObj://20
		case frmGadgetObj://20
			return 20;
		case frmScrollBarObj://24
			return 24;
		default:
			if(type > frmScrollBarObj)dbgprintf("This is not an object type:%d\n",type);
			palmabrt();//hack
			break;
	}
	return 0;//not valid type
}

offset_68k load_FRMOBJ(uint8_t type,offset_68k unopenedobj,offset_68k dest){
	size_t_68k objsize = sizeof_FRMOBJ(type);
	offset_68k openedobj = dest;

	memcpy68k(openedobj,unopenedobj,objsize);
	switch(type){
		case frmPopupObj://just resource ids
		case frmGraffitiStateObj://only coords of tiny display the os writes things to
		case frmBitmapObj://area and resource id of a bitmap
			//nothing
			break;
		case frmControlObj:
			put_long(openedobj + 10,unopenedobj + 20);//address of string
			break;
		case frmLabelObj:
			put_long(openedobj + 10,unopenedobj + 14);//address of string
			break;
		case frmGadgetObj:
			//may be incorrect
			//put_long(openedobj + 12,unopenedobj + 20);//address of gadget data //hack
			dbgprintf("ID:%04x,Flags:%04x,Handler:%08x,Data:%08x\n",get_word(openedobj),
				   get_word(openedobj + 2),get_long(openedobj + 16),get_long(openedobj + 12));
			//more
			break;
		case frmFieldObj:
			put_long(openedobj + 12,unopenedobj + 40);//text ptr
			dbgprintf("frmFieldObj ID:%04x,CharPtr:%08x,CharHandle:%08x\n",get_word(openedobj),get_long(openedobj + 12),get_long(openedobj + 16));
			dbgprintf("%s\n",readstring(unopenedobj + 40).c_str());
			//more
			break;
		case frmTitleObj:
			//dbgprintf("Char*:%08x\n",get_long(openedobj + 8));
			put_long(openedobj + 8,unopenedobj + 12);//address of string
			//more
			break;
		case frmListObj:{
				offset_68k itemlist = get_long(unopenedobj + 12);//array of char pointers
				offset_68k popupwin = get_long(unopenedobj + 24);
				dbgprintf("frmListObj CharPtrArray:%08x,PopupWin:%08x\n",itemlist,popupwin);
				//load list of strings
				//more
			}
			break;
		default:
			if(type > frmScrollBarObj)dbgprintf("This is not an object type:%d\n",type);
			dbgprintf("frm obj type :%d: not supported\n",type);
			palmabrt();
			break;
	}

	/*
	if(type == frmLabelObj){
		dbgprintf("charptr:%08x",get_long(openedobj + 10));
	}
	*/

	return openedobj + sizeof_FRMOBJ(type);
}

offset_68k load_FRMOBJ(uint8_t type,offset_68k unopenedobj){
	//make decompressed object
	size_t_68k objsize = sizeof_FRMOBJ(type);
	if(objsize == 0)palmabrt();

	offset_68k heapmem = getfreeheap(objsize);

	load_FRMOBJ(type,unopenedobj,heapmem);
	return heapmem;
}

uint16_t frmid;
offset_68k decompressform(uint16_t id){
	offset_68k form = getappresource(id,'tFRM');

	//resource does not exist
	if(!form)return nullptr_68k;


	offset_68k accesspoint = form + 8;
	uint8_t windowflags = get_byte(accesspoint);
	accesspoint = form + 10;//skip pad

	//change to SQUARE
	int16_t x = get_word(accesspoint);
	int16_t y = get_word(accesspoint + 2);
	int16_t w = get_word(accesspoint + 4);
	int16_t h = get_word(accesspoint + 6);

	accesspoint = form + 30;
	uint8_t cornerdiam = get_byte(accesspoint);
	uint8_t frameflags = get_byte(accesspoint + 1);
	uint8_t framewidth = (frameflags & 0x03);
	//3d button and shadow width need to be done later
	accesspoint = form + 40;
	uint16_t formid = get_word(accesspoint);
	if(formid != id)dbgprintf("FormId:%04x,ResourceId:%04x\n",formid,id);
	uint8_t formattr = get_byte(accesspoint + 2);//maybe uint16_t
	//check if useable form and save behind
	uint32_t bitsbehind = get_long(accesspoint + 6);
	uint32_t eventhandler = get_long(accesspoint + 10);
	accesspoint = form + 56;
	uint16_t defaultbtn = get_word(accesspoint);
	uint16_t helpid = get_word(accesspoint + 2);
	uint16_t menuid = get_word(accesspoint + 4);
	uint16_t numobjects = get_word(accesspoint + 6);

	accesspoint = form + 68;//now pointing at first object

	//get total object size
	size_t_68k totalobjsize = 0;
	uint16_t scan;
	inc_for(scan,numobjects){
		uint8_t thisobjtype = get_byte(accesspoint);
		totalobjsize += sizeof_FRMOBJ(thisobjtype);
		accesspoint += 6;
	}

	size_t_68k formsize = 68 + numobjects * 6;
	offset_68k formmemory = getfreeheap(formsize + totalobjsize);

	//make windowdata
	offset_68k formframebuffer = newbmpsimple(w,h,LCDBPP);//change to dynamic bpp

	//universal drawstate pointer
	offset_68k drawstatetype = osdrawstate;

	TEMPHACK;
	//free bitmap with form
	windowflags |= bit(8);

	initformwindow(formmemory,w,h,windowflags,frameflags,formframebuffer,drawstatetype,0);

	//copy old
	memcpy68k(formmemory + 40,form + 40,28);

	//patch form data
	//put_word(formmemory + 54,focus);
	put_word(formmemory + 56,defaultbtn);
	put_word(formmemory + 58,helpid);
	put_word(formmemory + 60,menuid);//MBAR resource to associate with the form (for when the menu bar is touched)
	put_word(formmemory + 62,numobjects);

	//dbgprintf("Objs:%d\n",numobjects);

	//set address of obj list
	put_long(formmemory + 64,formmemory + 68);


	//track current object and load it into ram
	accesspoint = form + 68;//form object list

	uint8_t thisobjtype;
	//offset_68k openedobj;
	offset_68k unopenedobj;

	offset_68k freedataaddr = formmemory + formsize;//put open object data here
	offset_68k heapobjectpointer = formmemory + 68;//put open object indexes here
	uint16_t count;
	inc_for(count,numobjects){
		thisobjtype = get_byte(accesspoint);
		put_byte(heapobjectpointer,thisobjtype);//set this objects type
		put_byte(heapobjectpointer + 1,0);//spacer (NULL/0)
		//place pointer to where decompressed object will be
		put_long(heapobjectpointer + 2,freedataaddr);


		unopenedobj = form + get_long(accesspoint + 2);//size may be different

		//load to cache and set pointer to the next open cache address
		freedataaddr = load_FRMOBJ(thisobjtype,unopenedobj,freedataaddr);

		heapobjectpointer += 6;
		accesspoint += 6;
	}

	frmid = formid;
	return formmemory;
}

void releaseformmemory(offset_68k frmptr){
	//form bitmap
	uint16_t flags = get_word(frmptr + 8);//windowflags
	if(flags & bit(8))abstractfree(getwinbmp(frmptr));

	//form struct
	abstractfree(frmptr);
}


//bitmap

//does not convert to rgb_16
uint8_t* scanline(offset_68k addr,int16_t width,int16_t height,uint16_t rowbytes){
#if 0
	//dbgprintf("height:%d\n",height);
	size_t_68k uncompressedsize = rowbytes * height;
	uint8_t* uncompresseddata = new uint8_t[uncompressedsize];

	size_t_68k datasize = get_word(addr) - 2;//subtract length from its self
	addr += 2;

	size_t_68k meep = height * rowbytes;

	offset_68k endofdata = addr + datasize;
	offset_68k datanum = 0;//byte in uncompressed data
	offset_68k rowptr = addr;//byte in compressed data
	offset_68k rowindex = 0;
	while(rowptr < endofdata){
		bitset<8> reusedflags(get_byte(rowptr));
		rowptr++;

		size_t_68k bytecount;
		inc_for(bytecount,8){
			if(reusedflags.test(7 - bytecount)){
				//plot byte
				uncompresseddata[datanum] = get_byte(rowptr);
				rowptr++;
			}
			else{
				//copy old byte
				uncompresseddata[datanum] = uncompresseddata[datanum - rowbytes];
				//uncompresseddata[datanum] = 0x53;//hack
			}

			if(datanum > meep)dbgprintf("OVERFLOW:");

			datanum++;
			rowindex++;
			if(rowindex >= rowbytes){//was >=
				rowindex = 0;
				break;
			}
		}
	}
	return uncompresseddata;
#else
	size_t_68k datasize = get_word(addr);//compressed data size
	size_t_68k uncompressedsize = rowbytes * height;
	uint8_t* compresseddata = new uint8_t[datasize];
	uint8_t* uncompresseddata = new uint8_t[uncompressedsize];
	readbytearray(addr,compresseddata,datasize);
	BMP_extract(compresseddata,uncompresseddata,BitmapCompressionTypeScanLine,rowbytes);
	delete[] compresseddata;
	return uncompresseddata;
#endif
}

//does not convert to rgb_16
uint8_t* RLE(offset_68k addr, int16_t width, int16_t height, uint16_t rowbytes){
#if 1
	size_t_68k uncompressedsize = rowbytes * height;
	uint8_t* uncompresseddata = new uint8_t[uncompressedsize];
	size_t_68k compressedsize = get_word(addr) - 2;//subtract length from its self
	addr += 2;


	offset_68k loc = 0;
	uint8_t headerbyte,databyte;
	offset_68k bunny = addr;
	offset_68k end = addr + compressedsize;
	while(bunny < end){
		headerbyte = get_byte(bunny);
		databyte = get_byte(bunny + 1);
		bunny += 2;

#define FIXEDRLE
#ifdef FIXEDRLE
		//repeat the byte (headerbyte) times
		while(headerbyte > 0){
			if(loc >= uncompressedsize)palmabrt();//hack //this would be a buffer overflow
			uncompresseddata[loc] = databyte;
			headerbyte--;
			loc++;
		}
#else
		if(headerbyte >= 0){//x bytes of unique data
			for(;headerbyte >= 0;headerbyte--){//maybe > 0 //was >= 0
				uncompresseddata[loc] = get_byte(bunny);
				loc++;
				bunny++;
			}
		}
		else if(headerbyte == -128){//ignore headerbyte
			continue;
		}
		else if(headerbyte < 0){//repeat byte x times
			uint8_t data = 13;//get_byte(bunny);
			for(;headerbyte <= 0;headerbyte++){//maybe <= 0 //was <
				uncompresseddata[loc] = data;
				loc++;
			}
			bunny++;
		}
		else dbgprintf("byte is not a byte.\n");
#endif

	}
	return uncompresseddata;
#else

#endif
}

uint8_t* PackBits(offset_68k addr,int16_t width,int16_t height,uint16_t rowbytes){
#if 1
	size_t_68k uncompressedsize = rowbytes * height;
	uint8_t* uncompresseddata = new uint8_t[uncompressedsize];
	size_t_68k compressedsize = get_word(addr) - 2;//subtract length from its self
	addr += 2;


	offset_68k loc = 0;
	int8_t headerbyte;
	offset_68k bunny = addr;
	offset_68k end = addr + compressedsize;
	while(bunny < end){
		headerbyte = get_byte(bunny);
		bunny++;
		if(headerbyte >= 0){//x bytes of unique data
			for(;headerbyte >= 0;headerbyte--){//maybe > 0 //was >= 0
				uncompresseddata[loc] = get_byte(bunny);
				loc++;
				bunny++;
			}
		}
		else if(headerbyte == -128){//ignore headerbyte
			continue;
		}
		else if(headerbyte < 0){//repeat byte x times
			uint8_t data = get_byte(bunny);
			for(;headerbyte <= 0;headerbyte++){//maybe <= 0 //was <
				uncompresseddata[loc] = data;
				loc++;
			}
			bunny++;
		}
		else dbgprintf("byte is not a byte.\n");
	}
	return uncompresseddata;
#else

#endif
}
