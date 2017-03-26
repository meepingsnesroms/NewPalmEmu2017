#include "palmwrapper.h"
#include "displaydriver.h"
#include "palmapi.h"
#include "rawimagetools.h"
#include "eventqueue.h"
#include "stdlib68k.h"
#include "timing.h"
#include <unordered_map>


//new list
#include "m68k.h"
#include "newcpu.h"
#include "palmmalloc.h"
#include "resourcelocator.h"
#include "palmtypeaccess.h"
#include "palmdefines.h"
#include "dataexchange.h"

#include "palmos/graphics/palette.h"

using namespace std;//hack

//display config //these are hardware abstraction layer values,the actual display size and depth are fixed
UBYTE bpp;
WORD width,height;
UWORD coordsys;
bool color;
bool scalevideo;//should be true if using 160*160 resolution,starts true and apps must enable hires mode
int screenlockcount;
ULONG UIColorTable[31];
CPTR osdrawstate;//theres only one drawstate,every window points to this drawstate
#define XFERTYPE  (osdrawstate)//UBYTE
#define PATTERN	  (osdrawstate + 1)
#define UNDERLINE (osdrawstate + 2)
#define FONTID	  (osdrawstate + 3)//UBYTE
#define FONTPTR	  (osdrawstate + 4)//CPTR
#define FORECOLOR (osdrawstate + 18)//UBYTE
#define BACKCOLOR (osdrawstate + 19)//UBYTE
#define TEXTCOLOR (osdrawstate + 20)//UBYTE
#define COORDSYS  (osdrawstate + 32)//UWORD


#define FORECOLORRGB (osdrawstate + 18)//UBYTE
#define BACKCOLORRGB (osdrawstate + 19)//UBYTE
#define TEXTCOLORRGB (osdrawstate + 20)//UBYTE



//uncompressed version of current font
RAWfnt currentfont;

//status bar on devices with dynamic input area
bool statvisible;
WORD statw,stath;

//touch driver state
bool sendpenevents;
//penUpEvent needs 2 PointType structs in the data vector (start,end)
COORD touchstart;

//for winsetactivewindow
CPTR newwindowptr;
bool changewindow;

//what drawing commands use
CPTR currentdrawwindow;

//what is on the display
CPTR currentactivewindow;

vector<CPTR> windowlist;

vector<CPTR> drawstates;

//form
UWORD activeform;
CPTR activeformptr;
//form objects
vector<UISQUARE> objects;

bool anyformsopen;
bool sendwinenterondraw;

unordered_map<UWORD,CPTR> openforms;
vector<UWORD> openformids;//added to access open forms as a list

void setdisplayaddr(CPTR displayaddr){
	put_long(oslcdwindow + 4,displayaddr);
	CPTR bitmap = getwinbmp(oslcdwindow);
	put_long(bitmap + 16,displayaddr);
}

void freeopenform(UWORD frmid){
	openforms.erase(frmid);
	int32 scan;
	for(scan = openformids.size() - 1;scan >= 0;scan--){
		if(openformids[scan] == frmid){
			openformids.erase(openformids.begin() + scan);
			break;
		}
	}
}

void setopenform(UWORD frmid,CPTR ptr){
	openforms[frmid] = ptr;
	openformids.push_back(frmid);
}

CPTR getopenform(UWORD frmid){
	if(openforms.find(frmid) == openforms.end())return nullptr_68k;
	return openforms[frmid];
}

UWORD getformobjid(CPTR form,UWORD count){
	CPTR objindex = getformobjlist(form) + 6 * count;
	UBYTE objtype = get_byte(objindex);
	CPTR obj = get_long(objindex + 2);

	UWORD finalid;
	switch(objtype){
		//standard id location
		case frmFieldObj:
		case frmGadgetObj:
		case frmLabelObj:
		case frmControlObj:
		case frmListObj:
			finalid = get_word(obj);
			break;

		//special cases
		case frmBitmapObj:
			finalid = get_word(obj + 6);
			break;

		//dont have object ids
		case frmTitleObj:
			finalid = frmInvalidObjectId;
			break;
		case frmPopupObj:
			finalid = frmInvalidObjectId;
			break;

		//invalid type
		default:
			finalid = 0;//compiler was complaining
			dbgprintf("err obj %d not done\n",objtype);
			palmabrt();
			break;
	}
	return finalid;
}



//Virtual GPU
//virtual GPU registers

//allow access to each element seperately
SQUARE srcsquare;
SQUARE dstsquare;

//these used to all be separate values
COORD& srcstart = srcsquare.start;
	WORD& srcx = srcstart.x;
	WORD& srcy = srcstart.y;
COORD& srcend = srcsquare.end;
	WORD& srcendx = srcend.x;
	WORD& srcendy = srcend.y;
BOUNDRY& srcarea = srcsquare.size;
	WORD& srcw = srcarea.w;
	WORD& srch = srcarea.h;

COORD& dststart = dstsquare.start;
	WORD& dstx = dststart.x;
	WORD& dsty = dststart.y;
COORD& dstend = dstsquare.end;
	WORD& dstendx = dstend.x;
	WORD& dstendy = dstend.y;
BOUNDRY& dstarea = dstsquare.size;
	WORD& dstw = dstarea.w;
	WORD& dsth = dstarea.h;


CPTR srcptr,dstptr;
offset_68k srcindex,dstindex;
int srcbpp,dstbpp;
int dstround;
size_t_68k srcsize;
UWORD drwcolor;
UBYTE drwfnt;
int prams;



void copyrectangle(){
	RAWimg hostwindow(srcptr,WINDOW);
	CPTR winbmp = getwinbmp(dstptr);
	//FBWriter window(getbmpdata(winbmp),getbmprowbytes(winbmp),getbmpbpp(winbmp));
	FBWriter window(getbmpdata(winbmp),get_word(winbmp),16);//hack
	window.copyrect(hostwindow,srcx,srcy,srcw,srch,dstx,dsty);

	//read ULONG / write ULONG (cycles = width * height) (copying as ULONG(2 pixels at once) and seperate read/write cancel out)
	simulatecycles(srcw * srch);
}

void rectangle(){
	//dbgprintf("WinBmpPtr:%08x,WinDataPtr:%08x,X:%d,Y:%d,EndX:%d,EndY:%d,Rect:%08x\n",
	//	   getwinbmp(currentdrawwindow),getwindata(currentdrawwindow),x,y,endx,endy,rectptr);

	CPTR winbmp = getwinbmp(dstptr);
	//FBWriter window(getbmpdata(winbmp),getbmprowbytes(winbmp),getbmpbpp(winbmp));
	FBWriter window(getbmpdata(winbmp),get_word(winbmp),16);//hack
	window.rect(srcx,srcy,srcw,srch,prams,drwcolor,dstround);

	//write ULONG
	//simulatecycles(srcw * srch);
}

void dot(){
	//dbgprintf("Draw Pixel:(Dst:%08x,Dst data:%08x,X:%d,Y:%d,Color:%d)\n",dstptr,getwindata(dstptr),dstx,dsty,drwcolor);
	CPTR winbmp = getwinbmp(dstptr);
	//FBWriter window(getbmpdata(winbmp),getbmprowbytes(winbmp),getbmpbpp(winbmp));
	FBWriter window(getbmpdata(winbmp),get_word(winbmp),16);//hack
	window.setpixel(dstx,dsty,drwcolor);

	//write UWORD
	simulatecycles(1);
}

void bitmap(){
	dbgprintf("Draw Bitmap:(Src:%08x,Dst:%08x,X:%d,Y:%d)\n",srcptr,dstptr,dstx,dsty);

	RAWimg palmbmp(srcptr,BMP,findme,findme,findme,false);

	CPTR winbmp = getwinbmp(dstptr);
	dbgprintf("FrameBuffLoc:%08x\n",getbmpdata(winbmp));
	FBWriter window(getbmpdata(winbmp),get_word(winbmp),16);//hack
	//FBWriter window(getbmpdata(winbmp),get_word(winbmp),getbmpbpp(winbmp));
	window.draw(palmbmp,dstx,dsty);

	//read ULONG / write ULONG (cycles = width * height) (copying as ULONG(2 pixels at once) and seperate read/write cancel out)
	simulatecycles(palmbmp.width * palmbmp.height);
}

void text(){
	RAWfnt* activefont;

	dbgprintf("Text At X:%d,Y:%d\n",dstx,dsty);

	if(drwfnt == get_byte(FONTID)){
		activefont = &currentfont;
	}else{
		CPTR tempnewfont = getfontaddr(drwfnt);
		activefont = new RAWfnt;
		activefont->setactivefont(tempnewfont);
	}

	CPTR winbmp = getwinbmp(dstptr);
	FBWriter window(getbmpdata(winbmp),get_word(winbmp),16);//hack
	offset_68k count = 0;
	char curchr;
	if(srcsize == findme){
		while(true){
			curchr = (char)get_byte(srcptr + count);

			if(chraction(curchr) == TERMINATE)break;

			window.draw(curchr,*activefont,dstx,dsty);

			//window.draw5x7(dstx,dsty,drwcolor,curchr);
			dstx += 6;
			count++;
		}
		//dstindex = count + 1;//why does this exist?
	}
	else{
		inc_for(count,srcsize){
			curchr = (char)get_byte(srcptr + count);

			//if(chraction(curchr) == TERMINATE || count >= srcsize)break;
			if(chraction(curchr) == TERMINATE)break;

			if(curchr == (char)254)palmabrt();//HACK

			window.draw(curchr,*activefont,dstx,dsty);

			//window.draw5x7(dstx,dsty,drwcolor,curchr);
			dstx += 6;
		}
	}
	//*/


	/*
	UBYTE fontid = get_byte(FONTID);
	CPTR fontptr = get_long(FONTPTR);

	if(fontid >= fntAppFontCustomBase){
		dbgprintf("Custom font err\n");
		RAWfnt currentfont(fontptr,fontid);
	}
	else{
		dbgprintf("milking cow\n");
		RAWfnt currentfont(fontptr,fontid);
	}
	*/

	/*
	CPTR winbmp = getwinbmp(dstptr);
	//FBWriter window(getbmpdata(winbmp),getbmprowbytes(winbmp),getbmpbpp(winbmp));
	FBWriter window(getbmpdata(winbmp),get_word(winbmp),16);//hack
	offset_68k count = 0;
	if(srcsize == findme){
		while(true){
			bool end = window.draw5x7(dstx,dsty,drwcolor,(char)get_byte(srcptr + count));
			if(end)break;
			dstx += 6;
			count++;
		}
		dstindex = count + 1;
	}
	else{
		inc_for(count,srcsize){
			bool end = window.draw5x7(dstx,dsty,drwcolor,(char)get_byte(srcptr + count));
			if(end && count + 1 == srcsize)break;
			else if(end)palmabrt();
			dstx += 6;
		}
	}
	*/
}

void line(){
	CPTR winbmp = getwinbmp(dstptr);
	//FBWriter window(getbmpdata(winbmp),getbmprowbytes(winbmp),getbmpbpp(winbmp));
	FBWriter window(getbmpdata(winbmp),get_word(winbmp),16);//hack
	window.line(srcx,srcy,srcendx,srcendy,prams,drwcolor);
}

//End of virtual GPU


//helpers
CPTR getuiresource(UWORD id,ULONG type){
	return getappresource(id,type);
}

bool inboundbox(UISQUARE& box,COORD compare){
	if(compare.x >= box.start.x && compare.x <= box.end.x)
		if(compare.y >= box.start.y && compare.y <= box.end.y)return true;

	return false;
}

bool inboundbox(SQUARE& box,COORD compare){
	if(compare.x >= box.start.x && compare.x <= box.end.x)
		if(compare.y >= box.start.y && compare.y <= box.end.y)return true;

	return false;
}

void addobjtocollisionmatrix(SQUARE& area,CPTR object,UBYTE type,UWORD id){
	UISQUARE temp;
	temp.start = area.start;
	temp.end = area.end;
	temp.objtype = type;
	temp.objid = id;
	temp.object = object;
	objects.push_back(temp);
}

void resetcollisionmatrix(){
	objects.clear();
}

void disableobject(CPTR objectptr,UBYTE type){
	UWORD attr;
	switch(type){
		case frmFieldObj:
			attr = get_word(objectptr + 10);
			put_word(objectptr + 10,attr & ~bit(15));
			return;
		//case frmControlObj:
			//break;
		//case frmBitmapObj:
			//break;
		case frmLabelObj:
			attr = get_word(objectptr + 6);
			put_word(objectptr + 6,attr & ~bit(15));
			return;
		//case frmGadgetObj:
			//break;
		default:
			dbgprintf("\nType %d not implimented\n\n",type);
			palmabrt();
			break;
	}
}

COORD waitforpen(){
	while(!PENDOWN){
		KILLSWITCH;
		this_thread::sleep_for(chrono::milliseconds(1));
	}

	COORD loc;
	loc.x = (WORD)PENX;
	loc.y = (WORD)PENY;

	return loc;
}

COORD trackpen(){
	while(PENDOWN){
		KILLSWITCH;
		//stalk the pen!! //later
		//HACK the pen is not being tracked
		this_thread::sleep_for(chrono::milliseconds(1));
	}

	COORD loc;
	loc.x = (WORD)PENX;
	loc.y = (WORD)PENY;

	return loc;
}

void drawborder(SQUARE area){
	srcsquare = area;
	drwcolor = 0xFFFF;//white
	prams = FILL;
	dstptr = oslcdwindow;//hack
	rectangle();
	//palmabrt();//hack
}

void drawbutton(SQUARE area){
	srcsquare = area;
	drwcolor = 0x07E0;//green
	prams = FILL;
	dstptr = oslcdwindow;//hack
	rectangle();
	//palmabrt();//hack
}

//the blue outline around the active control on Palm OS 5
void radioactiveborder(SQUARE area,bool round){
	palmabrt();
}


//used by emulator when writing os data to screen and the onscreen image needs to be preserved(like alerts)
static UWORD spareframe[LCDMAXPIX];

void backupframe(){
	memcpy(spareframe,framebuffer,LCDBYTES);
}

void restoreframe(){
	memcpy(framebuffer,spareframe,LCDBYTES);
}

void restorepartialframe(COORD start,COORD end){
	COORD count;
	for(count.y = start.y;count.y <= end.y;count.y++){
		for(count.x = start.x;count.x <= end.x;count.x++){
			framebuffer[count.y * LCDW + count.x] = spareframe[count.y * LCDW + count.x];
		}
	}
}



bool relaytouchevent(CPTR eventptr){
	COORD touch = get_coord(eventptr + 4);

	size_t_68k totalobjs = objects.size();
	offset_68k curuisquare;
	inc_for(curuisquare,totalobjs){
		if(inboundbox(objects[curuisquare],touch)){
			//send here
			dbgprintf("Object:%d has been pushed\n",curuisquare);
			//no checks are needed because only active objects are in the collision matrix
			switch(objects[curuisquare].objtype){
				case frmControlObj:
					controleventhandler(objects[curuisquare].object,eventptr);
					return true;
				case frmGadgetObj:{
						osevent newevent;
						newevent.type = frmGadgetEnterEvent;
						newevent.data.push_back(objects[curuisquare].objid);
						newevent.data.push_back(objects[curuisquare].object);
						addnewevent(newevent);
					}
					return true;
				case frmFieldObj:
					fieldeventhandler(objects[curuisquare].object,eventptr);
					break;


				default:
					//unknown object
					palmabrt();
					break;
			}
		}
		/*else{
			dbgprintf("Fail object:%d\n",curuisquare);
		}
		*/
	}
	return false;
}

void relaygadgetevent(CPTR eventptr){
	UWORD evttype = get_word(eventptr);
	UWORD targetobj = get_word(eventptr + evtDataOffset);

	if(evttype != frmGadgetEnterEvent && evttype != frmGadgetMiscEvent)palmabrt();

	size_t_68k totalobjs = objects.size();
	offset_68k curuisquare;
	inc_for(curuisquare,totalobjs){
		if(objects[curuisquare].objtype == frmGadgetObj && objects[curuisquare].objid == targetobj){
			//found the target,now will it accept the event
			UWORD attr = get_word(objects[curuisquare].object + 2);
			if(attr & bit(14)){//has a callback //guaranteed to be visible because it is in the collision matrix
				CPTR functionptr = get_long(objects[curuisquare].object + 16);
				CPU_pushlongstack(objects[curuisquare].object);
				CPU_pushwordstack(formGadgetHandleEventCmd);
				CPU_pushlongstack(eventptr);
				CPU_68kfunction(functionptr,notrequired);
				//now remove the arguments of the 68k function call (10 bytes,4+2+4,LONG/WORD/LONG) from stack
				CPU_cleanargsfromstack(10);

				dbgprintf("Sent event to gadget:%04x,Result:%08x\n",objects[curuisquare].objid,D0);
				return;
			}else{
				palmabrt();
			}
		}
	}
	palmabrt();
}

void relaycontrolevent(CPTR eventptr){
	UWORD targetobj = get_word(eventptr + evtDataOffset);
	CPTR targetptr = get_long(eventptr + evtDataOffset + 2);

	UWORD evttype = get_word(eventptr);
	if(evttype != ctlEnterEvent && evttype != ctlExitEvent && evttype != ctlSelectEvent)palmabrt();

	size_t_68k totalobjs = objects.size();
	offset_68k curuisquare;
	inc_for(curuisquare,totalobjs){
		if(objects[curuisquare].objtype == frmControlObj && objects[curuisquare].objid == targetobj){
			controleventhandler(targetptr,eventptr);//controlptr is only used for penDownEvent
			return;
		}
	}
}

void relayfieldevent(CPTR eventptr){
	UWORD targetobj = get_word(eventptr + evtDataOffset);
	CPTR targetptr = get_long(eventptr + evtDataOffset + 2);

	UWORD evttype = get_word(eventptr);
	if(evttype != fldEnterEvent)palmabrt();

	size_t_68k totalobjs = objects.size();
	offset_68k curuisquare;
	inc_for(curuisquare,totalobjs){
		if(objects[curuisquare].objtype == frmFieldObj && objects[curuisquare].objid == targetobj){
			fieldeventhandler(targetptr,eventptr);//controlptr is only used for penDownEvent
			return;
		}
	}
}



//object interaction/drawing

TEMPHACK //all color get functions are unconfirmed and are hacks
UWORD getbackcolor(){
	CPTR activebmp = getwinbmp(activeform);
	UBYTE colortype = getbmpbpp(activebmp);
	switch(colortype){
		case 16:
			return get_word(BACKCOLORRGB);
		case 8:
			{
				CPTR palette = getbmppalette(activebmp);
				if(palette != nullptr_68k)palmabrt();//later
				return paltopalm(PalmPalette8bpp[get_byte(BACKCOLOR)]);
			}
		case 4:
			return paltopalm(PalmPalette4bpp[get_byte(BACKCOLOR)]);
		case 2:
			return paltopalm(PalmPalette2bpp[get_byte(BACKCOLOR)]);
		case 1:
			/*
			if(BACKCOLOR)return 0x0000;//this should be correct (on b/w displays 0 = white,1 = black)
			return 0xFFFF;
			*/
			//HACK find default background color
			return 0xFFFF;//assuming background color is white on b/w palms
		default:
			palmabrt();
	}
	return 0;
}

UWORD getforecolor(){
	CPTR activebmp = getwinbmp(activeform);
	UBYTE colortype = getbmpbpp(activebmp);
	switch(colortype){
		case 16:
			return get_word(FORECOLORRGB);
		case 8:
			{
				CPTR palette = getbmppalette(activebmp);
				if(palette != nullptr_68k)palmabrt();//later
				return paltopalm(PalmPalette8bpp[get_byte(FORECOLOR)]);
			}
		case 4:
			return paltopalm(PalmPalette4bpp[get_byte(FORECOLOR)]);
		case 2:
			return paltopalm(PalmPalette2bpp[get_byte(FORECOLOR)]);
		case 1:
			/*
			if(BACKCOLOR)return 0x0000;//this should be correct (on b/w displays 0 = white,1 = black)
			return 0xFFFF;
			*/
			//HACK find default foreground color
			return 0x0000;//assuming foreground color is black on b/w palms
		default:
			palmabrt();
	}
	return 0;
}

UWORD gettextcolor(){
	CPTR activebmp = getwinbmp(activeform);
	UBYTE colortype = getbmpbpp(activebmp);
	switch(colortype){
		case 16:
			return get_word(TEXTCOLORRGB);
		case 8:
			{
				CPTR palette = getbmppalette(activebmp);
				if(palette != nullptr_68k)palmabrt();//later
				return paltopalm(PalmPalette8bpp[get_byte(TEXTCOLOR)]);
			}
		case 4:
			return paltopalm(PalmPalette4bpp[get_byte(TEXTCOLOR)]);
		case 2:
			return paltopalm(PalmPalette2bpp[get_byte(TEXTCOLOR)]);
		case 1:
			/*
			if(BACKCOLOR)return 0x0000;//this should be correct (on b/w displays 0 = white,1 = black)
			return 0xFFFF;
			*/
			//HACK find default text color
			return 0xFFFF;//assuming text color is black on b/w palms
		default:
			palmabrt();
	}
	return 0;
}



void fielddisassociateaddr(CPTR field){
	//just disasociate pointer and handle
	put_long(field + 12,0);//char ptr
	put_long(field + 16,0);//memhandle

	TEMPHACK;
	//may have to place cursor at end of text and recalculate word wrapping
}

void fieldappointtextaddr(CPTR field,CPTR handle,size_t_68k textsize,offset_68k textoffset){
	if(handle == nullptr_68k){
		fielddisassociateaddr(field);
		return;
	}

	UWORD lengthinchars = strlen68k(handle);

	put_long(field + 12,handle);//char ptr
	put_long(field + 16,handle);//memhandle
	//put_long(field + 20,NULL);//lineinfotype
	put_word(field + 24,lengthinchars);//text length
	put_word(field + 26,textsize);//text block size
	//put_word(field + 28,strlen68k(handle));//max chars
	put_word(field + 30,0);//firstchr
	put_word(field + 32,lengthinchars - 1);//lastchr
	//put_word(field + 34,textsize);//insert X position / char in line
	//put_word(field + 36,textsize);//insert Y position / line number

	TEMPHACK;
	//place cursor at end of text and recalculate word wrapping
}

void fieldappointtextptr(CPTR field, CPTR ptr){
	if(ptr == nullptr_68k){
		fielddisassociateaddr(field);
		return;
	}

	/*
	int mallocchk = memisalloc(ptr);
	//validity checks
	if(mallocchk == -1)palmabrt();
	if(ishandle(mallocchk))palmabrt();
	if(islocked(mallocchk))palmabrt();
	*/

	CPTR mallocsize = abstractgetsize(ptr);

	fieldappointtextaddr(field,ptr,mallocsize,0);
}

void fieldappointtexthandle(CPTR field,CPTR handle){
	if(handle == nullptr_68k){
		fielddisassociateaddr(field);
		return;
	}

	int mallocchk = memisalloc(handle);

	//validity checks
	if(mallocchk == -1)palmabrt();
	if(!ishandle(mallocchk))palmabrt();
	if(islocked(mallocchk))palmabrt();

	CPTR mallocsize = abstractgetsize(handle);//malloclist[mallocchk].size;

	fieldappointtextaddr(field,handle,mallocsize,0);
}

//to accomadate different type names ABMP,Tbmp,tAIB,tbmf,taif,PICT
//may or may not count tFBM,Tbsb (boot screen bitmap)
CPTR getbitmap(UWORD bmpid){
	CPTR bitmap = getappresource(bmpid,'Tbmp');
	//if(!bitmap)bitmap = getappresource(bmpid,'PICT');
	if(bitmap)return bitmap;
	else palmabrt();//error
	//add other type names
	return nullptr_68k;
}

CPTR getcontrolobject(int type,UWORD id){
	switch(type){
		//case buttonCtl:
		//	return getuiresource(id,'tBTN');
		default:
			dbgprintf("control object :%d: not done.\n",type);
			palmabrt();
			break;
	}
	return 0;
}

void drawcontrolobject(CPTR window,CPTR controlptr){
	UWORD id = get_word(controlptr);
	SQUARE area = get_square(controlptr + 2);
	CPTR text = get_long(controlptr + 10);
	UWORD attr = get_word(controlptr + 14);
	UBYTE style = get_byte(controlptr + 16);
	UBYTE fontid = get_byte(controlptr + 17);
	UBYTE group = get_byte(controlptr + 18);
	//ignore pad to word (controlptr + 19)

	if(attr & bit(15)){
		if(attr & bit(14)){
			addobjtocollisionmatrix(area,controlptr,frmControlObj,id);
		}else{
			//object grayed out/cant be touched
			palmabrt();//hack
		}

		switch(style){//style/type of control
			case buttonCtl:
				dstptr = window;
				srcsquare = area;
				drwcolor = 0x07E0;//green

				prams = 0;
				dstround = 0;

				rectangle();
				break;
			case repeatingButtonCtl:
				dstptr = window;
				srcsquare = area;
				drwcolor = 0xF800;//red

				prams = 0;
				dstround = 0;

				rectangle();
				break;
			default:
				dbgprintf("control object:%d not done.\n",style);
				palmabrt();
				break;
		}

		TEMPHACK;
		//draw

		//set visible to true
		put_word(controlptr + 14,attr | bit(13));
	}
}

void drawfield(CPTR window,CPTR fieldptr){
	UWORD id = get_word(fieldptr);//dev defined id
	SQUARE area = get_square(fieldptr + 2);
	UWORD attr = get_word(fieldptr + 10);
	CPTR textptr = get_long(fieldptr + 12);
	CPTR texthandle = get_long(fieldptr + 16);
	CPTR lineinfoptr = get_long(fieldptr + 20);
	UWORD textlength = get_word(fieldptr + 24);
	UWORD textblksize = get_word(fieldptr + 26);
	UWORD maxchars = get_word(fieldptr + 28);
	UWORD firstpos = get_word(fieldptr + 30);
	UWORD lastpos = get_word(fieldptr + 32);
	UWORD insptx = get_word(fieldptr + 34);
	UWORD inspty = get_word(fieldptr + 36);
	UBYTE fontid = get_byte(fieldptr + 38);

	if(attr & bit(15)){
		addobjtocollisionmatrix(area,fieldptr,frmFieldObj,id);

		dbgprintf("Field:%04x is useable\n",id);

		//UWORD linestart = get_word(lineinfoptr);
		//UWORD linelength = get_word(lineinfoptr + 2);

		dstptr = window;

		srcptr = textptr;
		if(srcptr == nullptr_68k)srcptr = texthandle;

		dststart = area.start;
		srcsize = textlength;

		text();

		//dsty += textlineheight;
		//dstendy += textlineheight;
		//prams = DOTTED;
		//line();

		//palmabrt();

		//set visible to true
		put_word(fieldptr + 10,attr | bit(14));
	}
}

TEMPHACK
void drawlist(CPTR window,CPTR listptr){
	UWORD id = get_word(listptr);
	SQUARE area = get_square(listptr + 2);
	UWORD attr = get_word(listptr + 10);
	CPTR itemlist = get_long(listptr + 12);//array of char pointers
	WORD numitems = get_word(listptr + 16);
	WORD currentitem = get_word(listptr + 18);
	WORD topitem = get_word(listptr + 20);
	UBYTE fontid = get_byte(listptr + 22);
	//skip pad byte 23
	CPTR popupwin = get_long(listptr + 24);
	CPTR drawfunction = get_long(listptr + 28);//function pointer

	if(attr & bit(15)){
		if(attr & bit(14)){
			addobjtocollisionmatrix(area,listptr,frmListObj,id);
		}else{
			//object grayed out/cant be touched
			palmabrt();//hack
		}


		//add purple bounding box //fix later
		dstptr = window;
		srcsquare = area;
		drwcolor = 0xF81F;//purple
		prams = FILL;
		dstround = 0;
		rectangle();


		TEMPHACK;
		//use callback if it exists


		//set visible to true
		put_word(listptr + 10,attr | bit(13));
	}
}

void drawtable(){
	palmabrt();
}

TEMPHACK
void drawtitle(CPTR window,CPTR titleptr){
	SQUARE area = get_square(titleptr);
	addobjtocollisionmatrix(area,titleptr,frmTitleObj,0);//theres only one title
	//draw title/menu bar popup
}

//only called by frmdrawform (draws bitmap useing special form struct)
void drawbitmap(CPTR window,CPTR bmpptr){
	//draw bitmap
	UWORD attr = get_word(bmpptr);
	if(attr & bit(15)){
		dststart = get_coord(bmpptr + 2);

		UWORD bmpid = get_word(bmpptr + 6);

		dstptr = window;
		srcptr = getbitmap(bmpid);

		bitmap();
	}
}

void drawscrollbar(){
	palmabrt();
}

//only called by frmdrawform //labels dont handle or send events
void drawlabel(CPTR window,CPTR labelptr){
	UWORD id = get_word(labelptr);
	dstx = (WORD)get_word(labelptr + 2);
	dsty = (WORD)get_word(labelptr + 4);
	UWORD attr = get_word(labelptr + 6);
	bool useable = (attr & bit(15));
	prams = get_byte(labelptr + 8);//fontid
	//ignore pad byte
	srcptr = get_long(labelptr + 10);//char ptr
	dstptr = window;
	drwcolor = get_byte(TEXTCOLOR);//hack //must use palette with an index

	dbgprintf("Label %s useable,attr:%04x,charptr:%08x\n",useable ? "IS":"IS NOT",attr,srcptr);
	dbgprintf("X:%d,Y:%d,Text:%s\n",dstx,dsty,m68kstr(srcptr).c_str());

	srcsize = findme;
	if(useable)text();
}

void drawgadget(CPTR window,CPTR gdtptr){
	UWORD id = get_word(gdtptr);//resource not dev defined id
	UWORD attr = get_word(gdtptr + 2);
	SQUARE area = get_square(gdtptr + 4);
	CPTR data = get_long(gdtptr + 12);
	CPTR handler = get_long(gdtptr + 16);
	bool useable = (attr & bit(15));
	bool extended = (attr & bit(14));//has a handler
	//bool visible = (attr & bit(13));

	//CPTR gdtres = getuiresource(id,'tGDT');

	if(useable){
		addobjtocollisionmatrix(area,gdtptr,frmGadgetObj,id);

		//call custom handler
		if(extended && handler != nullptr_68k){//has a callback
			CPU_pushlongstack(gdtptr);
			CPU_pushwordstack(formGadgetDrawCmd);
			CPU_pushlongstack(nullptr_68k);//no prams
			CPU_68kfunction(handler,notrequired);
			//now remove the arguments of the 68k function call (10 bytes,4+2+4,LONG/WORD/LONG) from stack
			CPU_cleanargsfromstack(10);

			dbgprintf("Gadget Function Pointer:%08x,Result:%d\n",handler,D0);
		}
	}
}

void placeformobj(CPTR form,UWORD index){
	CPTR objloc = get_long(form + 64) + index * 6;
	UBYTE type = get_byte(objloc);
	CPTR objdataloc = get_long(objloc + 2);
	switch(type){
		case frmFieldObj:
			drawfield(form,objdataloc);
			break;
		case frmControlObj:
			drawcontrolobject(form,objdataloc);
			break;
		case frmBitmapObj:
			drawbitmap(form,objdataloc);
			break;
		case frmLabelObj:
			drawlabel(form,objdataloc);
			break;
		case frmGadgetObj:
			drawgadget(form,objdataloc);
			break;
		case frmTitleObj:
			drawtitle(form,objdataloc);
			break;
		case frmListObj:
			drawlist(form,objdataloc);
			break;
		case frmGraffitiStateObj:
			TEMPHACK;
			//make state indicator
			SQUARE meeps;
			meeps.start.x = get_word(objdataloc);
			meeps.start.y = get_word(objdataloc + 2);
			meeps.size.w = 8;
			meeps.size.h = 8;
			drwcolor = 0x001F;//blue
			prams = FILL;
			rectangle();
			break;
		default:
			dbgprintf("\nType %d not implimented\n\n",type);
			palmabrt();
			break;
	}
}

void removeformobject(CPTR form,UWORD index){
	CPTR objloc = get_long(form + 64) + index * 6;
	UBYTE type = get_byte(objloc);
	CPTR objdataloc = get_long(objloc + 2);
	disableobject(objdataloc,type);
}

void updateanddrawform(CPTR form){
	UWORD attr = getformattr(form);//the enabled and dirty bits are unused by all os versions

	TEMPHACK;
	//backup pixels behind form if savebehind bit is set

	TEMPHACK;
	//display 'i' icon/button when helpid is set

	TEMPHACK;
	//check if form is modal (draw window border)

	//useable attribute may not be supported for forms
	if(!(attr & bit(15))){//hack
		dbgprintf("Drawing inactive form.\n");
		palmabrt();
	}

	//clean up form framebuffer //may break some apps check os version before deleting
	CPTR formbmp = getwinbmp(form);
	srcx = 0;
	srcy = 0;
	srcw = get_word(formbmp);
	srch = get_word(formbmp + 2);
	//drwcolor = getwinbackcolor(form);
	//drwcolor = paltopalm(BACKCOLOR);
	drwcolor = 0xFFFF;
	//drwcolor = 0x0000;
	dstptr = form;
	rectangle();
	//RAWimg formimg(form,WINDOW,findme,findme,findme,true);
	//formimg.rect(0,0,width,height,0,getwinbackcolor(form),0);
	//memset68k(formdata,0xFF,height * rowbytes);//may be 0x00




	//clear hitboxes
	resetcollisionmatrix();

	//draw the objects
	UWORD numobjects = getformnumobjects(form);

	//dbgprintf("Numobjs:%d,Formptr:%08x\n",numobjects,formptr);

	UWORD count;
	inc_for(count,numobjects){
		placeformobj(form,count);
	}

	srcptr = getwinbmp(form);
	dstptr = oslcdwindow;
	//dstptr = getwindisplaywindow(formptr);//resolution fix
	dstx = 0,dsty = 0;
	bitmap();

	//set visible to true
	setformattr(form,attr | bit(13));


	if(currentactivewindow != form){
		//apparently palm sends winenter every time the form is drawn
		osevent enterevt;
		enterevt.type = winEnterEvent;
		enterevt.data.push_back(form);
		enterevt.data.push_back(currentactivewindow);
		addnewevent(enterevt);

		currentactivewindow = form;
		currentdrawwindow = form;

		//enabled flag in form window is unused in all os versions
	}
}
//end of object interaction/drawing






//event handlers
void formeventhandler(CPTR formptr,CPTR eventptr){
	UWORD evttype = get_word(eventptr);
	ULONG handled = 0;
	switch(evttype){
		case penUpEvent:
		case penMoveEvent://may or may not handle pen"Move/Up"Event
		case penDownEvent:

			TEMPHACK;
			//check if form is modal (ignores pen events outside its boundrys)
			/*
			bool winmodal = getwinmodal(formptr);
			if(winmodal){
				COORD penloc = get_coord(eventptr + 4);
				SQUARE formarea = get_square(UNKNOWN);//form bounding box
				if(!inboundbox(formarea,penloc))break;//form is modal and touch is outside, ignore it
			}
			*/



			//send to inside object
			if(relaytouchevent(eventptr))return;//D0 == return value of objects event handler
			else{
				/*If the pen is within the bounds of the help icon,
				it is tracked until it is lifted, and if it’s still within the help icon bounds,
				the help dialog is displayed.*/
			}
			handled = 1;
			break;
		case keyDownEvent:
			//send to object with focus
			palmabrt();//HACK
			handled = 1;
			break;
		case frmCloseEvent:{
				//clean up form memory
				UWORD frmid = get_word(eventptr + evtDataOffset);
				releaseformmemory(getopenform(frmid));
				freeopenform(frmid);
				handled = 1;
			}
			break;
		case frmUpdateEvent:
			//redraw me
			updateanddrawform(formptr);
			handled = 1;
			break;
		case frmGadgetEnterEvent:
		case frmGadgetMiscEvent:
			relaygadgetevent(eventptr);
			return;//use D0 from gadgeteventhandler
		case ctlEnterEvent:
		case ctlRepeatEvent:
		case ctlSelectEvent:
			relaycontrolevent(eventptr);
			return;//use D0 from controleventhandler
		case fldEnterEvent:
			relayfieldevent(eventptr);
			return;//use D0 from fieldeventhandler


		//other unimplemented events
		case frmTitleSelectEvent://fix soon
		case frmTitleEnterEvent://fix soon
		case fldHeightChangedEvent:
		case lstEnterEvent:
		case menuCmdBarOpenEvent:
		case menuEvent:
		case popSelectEvent:
		case sclEnterEvent:
		case sclRepeatEvent:
		case tblEnterEvent:
			palmabrt();//hack
			break;

		//remove below
		case nilEvent:
			//nothing
			break;
		case frmLoadEvent:
			//ignore
			break;

		default:
			/*
			//event not implemented or error
			dbgprintf("err frmhandleevent:%d\n",get_word(eventptr));
			palmabrt();//hack
			*/
			break;
	}
	D0 = handled;
}

void menueventhandler(CPTR menubarptr,CPTR eventptr,CPTR errorptr){
	ULONG handled = 0;

	//only handles pen and key down events
	switch(get_word(eventptr)){
		case penDownEvent:
			if(menubarptr == nullptr_68k)break;//tetris calls this function before loading the menubar
			dbgprintf("MBARptr:%08x\n",menubarptr);
			palmabrt();//hack
			break;
		case keyDownEvent:{
				UWORD vchr = get_word(eventptr + evtDataOffset + 2);
				if(vchr == vchrMenu){
					palmabrt();//hack
					handled = 1;
				}else if(vchr == vchrCommand){
					palmabrt();//hack
					handled = 1;
				}
			}
			break;
		default:
			//nothing
			//all events handled by this function are listed above
			break;
	}

	put_word(errorptr,errNone);//never sends an error,even on palm hardware
	D0 = handled;
}

TEMPHACK
void controleventhandler(CPTR controlptr,CPTR eventptr){
	UWORD evttype = get_word(eventptr);
	ULONG handled = 0;
	switch(evttype){
		//controls dont handle or send pen"Move/Up"Events
		case penDownEvent:{
				//check bounds and send ctlEnterEvent
				SQUARE bounds = get_square(controlptr + 2);
				COORD touch = get_coord(eventptr + 4);
				if(inboundbox(bounds,touch)){
					osevent controlenter;
					controlenter.type = ctlEnterEvent;
					controlenter.data.push_back(get_word(controlptr));//control id
					controlenter.data.push_back(controlptr);//control pointer
					addnewevent(controlenter);
					handled = 1;
				}
			}
			break;
		case ctlEnterEvent:{
				UWORD ctlid = get_word(controlptr);
				UWORD ctlidtest = get_word(eventptr + evtDataOffset);//verify that this is the correct control
				if(ctlidtest != ctlid)palmabrt();//hack

				//CPTR curcontrol = get_long(eventptr + evtDataOffset + 2);//the current control as specified by the event

				osevent ctlevent;

				SQUARE box = get_square(controlptr + 2);

				TEMPHACK;
				//change control color if button

				sendpenevents = false;
				COORD releasepoint = trackpen();//waits for pen release
				if(inboundbox(box,releasepoint)){
					ctlevent.type = ctlSelectEvent;
					ctlevent.data.push_back(ctlid);//control id
					ctlevent.data.push_back(controlptr);//control pointer
					ctlevent.data.push_back(true);//on 'pushed'
					ctlevent.data.push_back(0);//reserved field
					if(get_byte(controlptr + 16) == sliderCtl){
						palmabrt();//hack
						//ctlevent.data.push_back(value);//value if slider else 0
					}else{
						ctlevent.data.push_back(0);//value if slider else 0
					}
				}else{
					ctlevent.type = ctlExitEvent;

					//pendown,x and y are set by palm os
					ctlevent.pendown = false;//always false on release
					ctlevent.screenx = releasepoint.x;
					ctlevent.screeny = releasepoint.y;

					ctlevent.data.push_back(ctlid);//control id
					ctlevent.data.push_back(controlptr);//control pointer
				}
				sendpenevents = true;//hack //may remove this
				addnewevent(ctlevent);
			}
			handled = 1;
			break;
		case ctlRepeatEvent:
			palmabrt();//hack
			break;
		case ctlExitEvent:
			palmabrt();//hack
			break;
		default:
			//nothing
			//all events handled by this function are listed above
			break;
	}
	D0 = handled;
}

void fieldeventhandler(CPTR fieldptr,CPTR eventptr){
	UWORD evttype = get_word(eventptr);
	ULONG handled = 0;
	switch(evttype){
		case penDownEvent:{
				UWORD fldid = get_word(fieldptr);
				osevent fieldenter;
				fieldenter.type = fldEnterEvent;
				fieldenter.data.push_back(fldid);
				fieldenter.data.push_back(fieldptr);
				addnewevent(fieldenter);
			}
			handled = 1;
			break;
		case fldEnterEvent:
			palmabrt();//hack
			//set focus to this field
			//check for taps
			//place insertion point
			break;
		default:
			palmabrt();//hack
			break;

	}
	D0 = handled;
}

void listeventhandler(CPTR listptr,CPTR eventptr){
	palmabrt();//hack
}

//no gadgeteventhandler(CPTR eventptr), gadgets are program defined and have a callback for there event handler






//win functions
void wincreateoffscreenwindow(){
	stackword(width);
	stackword(height);
	stackbyte(winformat);//not used yet
	stackptr(errptr);

	TEMPHACK;
	//fix different format types

	UWORD flags = bit(8) | bit(14);//free bitmap on delete & offscreen flags
	//if(winformat != 0)flags |= bit(15);
	CPTR thisbmp = newbmpsimple(width,height,bpp);//global bpp of display
	//CPTR thisbmp = newbmpsimple(width,height,16);//global bpp of display
	//CPTR thisdrawstate = newdrawstate();

	CPTR retval = newwindow(width,height,flags,0,thisbmp,osdrawstate,0);

	//dbgprintf("Win addr:%08x,Real addr:%016lx\n",retval,get_real_address(thisbmp + 16));

	put_word(errptr,errNone);
	A0 = retval;
}

TEMPHACK
void wincreatebitmapwindow(){
	stackptr(bmpptr);
	stackptr(errptr);//UWORD

	TEMPHACK;
	//check for sysErrParamErr
	/*The bitmap must be uncompressed and it must
	 * have a valid pixel size (1, 2, 4, or 8).
	 * It must not be the screen bitmap.*/

	CPTR bmpwindow = newwindow(get_word(bmpptr),get_word(bmpptr + 2),/*flags*/0,
							   /*frameflags*/0,bmpptr,osdrawstate,/*nextwindowptr*/0);

	A0 = bmpwindow;
}

void windeletewindow(){
	stackptr(winhandle);
	stackbool(erase);

	if(erase){
		UWORD flags = get_word(winhandle + 8);
		//free bitmap if flag set
		if(flags & bit(8)){
			abstractfree(getwinbmp(winhandle));
		}
		abstractfree(winhandle);

		//maybe more
	}

	TEMPHACK;
	//remove from window list

	//no return value
}

void wineraserectangle(){
	stackptr(rectptr);
	stackword(cornerrnd);

	srcsquare = get_square(rectptr);
	dstptr = currentdrawwindow;
	drwcolor = paltopalm(PalmPalette8bpp[get_byte(BACKCOLOR)]);
	dstround = cornerrnd;
	prams = ERASE;
	rectangle();
	//no return value
}

void windrawrectangle(){
	stackptr(rectptr);
	stackword(cornerrnd);

	srcsquare = get_square(rectptr);
	dstptr = currentdrawwindow;
	drwcolor = paltopalm(PalmPalette8bpp[get_byte(FORECOLOR)]);
	dstround = cornerrnd;
	prams = OUTLINE;
	rectangle();
	//no return value
}

void windrawrectangleframe(){
	stackword(frametype);
	stackptr(rectptr);

	srcsquare = get_square(rectptr);
	dstptr = currentdrawwindow;
	drwcolor = paltopalm(PalmPalette8bpp[get_byte(FORECOLOR)]);
	dstround = 0;//hack
	prams = OUTLINE;
	rectangle();

	TEMPHACK;
	//draw frame with custom frametype

	//no return value
}

void windrawbitmap(){
	stackptr(bmpptr);
	stackword(x);
	stackword(y);

	if(bmpptr & 1)dbgprintf("Bmp not word aligned!!!\n");
	if(bmpptr == nullptr_68k)dbgprintf("Bmp not at ptr!!!\n");

	dstx = x;
	dsty = y;
	srcptr = bmpptr;
	dstptr = currentdrawwindow;
	bitmap();
	//no return value
}

void windrawpixel(){
	stackword(x);
	stackword(y);
	dstptr = currentdrawwindow;
	drwcolor = paltopalm(PalmPalette8bpp[get_byte(FORECOLOR)]);

	dstx = (WORD)x;
	dsty = (WORD)y;
	dot();
	//no return value
}

void winscreenmode(){
	stackbyte(operand);
	stackptr(widthptr);//ptr to ULONG
	stackptr(heightptr);//ptr to ULONG
	stackptr(bppptr);//ptr to ULONG
	stackptr(colenableptr);//ptr to bool

	//only winScreenModeGetSupportedDepths uses bit position(1 << 16) instead of value(0x10 or 16) for bppptr
	//all others use a decimal value

	D0 = errNone;
	switch(operand){
		case winScreenModeGet:
			putlongifvptr(widthptr,width);
			putlongifvptr(heightptr,height);
			putlongifvptr(bppptr,bpp);
			putbyteifvptr(colenableptr,color);
			dbgprintf("getscreenmode\n");
			return;
		case winScreenModeGetDefaults:
			putlongifvptr(widthptr,LCDW);
			putlongifvptr(heightptr,LCDH);
			putlongifvptr(bppptr,LCDBPP);
			putbyteifvptr(colenableptr,LCDHASCOLOR);
			dbgprintf("getdefaultscreenmode\n");
			return;
		case winScreenModeSet:{
				ULONG resultw = width,resulth = height,resultbpp = bpp;
				bool resultcolor = color;

				if(widthptr)resultw = get_long(widthptr);
				if(heightptr)resulth = get_long(heightptr);
				if(bppptr)resultbpp = get_long(bppptr);
				if(colenableptr)resultcolor = get_byte(colenableptr);

				if(resultw == 0 || resultw > LCDW){
					//invalid screen size
					palmabrt();//hack
				}
				if(resulth == 0 || resulth > LCDH){
					//invalid screen size
					palmabrt();//hack
				}
				if(resultbpp == 0 || resultbpp > LCDMAXBPP){
					//invalid screen depth
					palmabrt();//hack
				}
				if(resultcolor && resultbpp < 4){//4bit color works too
					//color needs higher depth
					palmabrt();//hack
				}

				//set screen format
				if(widthptr)width = resultw;
				if(heightptr)height = resulth;
				if(bppptr)bpp = resultbpp;
				if(colenableptr)color = resultcolor;


				dbgprintf("setscreenmode Width:%d,Height:%d,BPP:%d,Color:%d\n",width,height,bpp,color);
			}
			return;
		case winScreenModeSetToDefaults:
			width = LCDW;
			height = LCDH;
			bpp = LCDBPP;
			color = LCDHASCOLOR;
			dbgprintf("setdefaultscreenmode\n");
			return;
		case winScreenModeGetSupportsColor:
			if(colenableptr == nullptr_68k)palmabrt();//hack //this function requires color mode pointer
			if(get_long(bppptr) >= 4)put_byte(colenableptr,true);
			dbgprintf("supportscolor Bpp:%d\n",get_long(bppptr));
			return;
		case winScreenModeGetSupportedDepths:
			if(bppptr){
				TEMPHACK;
				//some apps may try to use 24/32 bit color (This is not supported but may work with dithering!);
				ULONG modes;
				if(colenableptr){
					//hack //4bit mode may or may not support color
					if(get_byte(colenableptr)/*must support color*/){
						//modes = (bit(31) | bit(23)) | (bit(15) | bit(7) | bit(3));
						modes = (bit(15) | bit(7) | bit(3));
					}else{
						//modes = (bit(31) | bit(23)) | (bit(15) | bit(7) | bit(3) | bit(1) | bit(0));
						modes = (bit(15) | bit(7) | bit(3) | bit(1) | bit(0));
					}
				}else{
					//palmabrt();//hack //this function requires color mode pointer
					//just list all supported depths
					//modes = (bit(31) | bit(23)) | (bit(15) | bit(7) | bit(3) | bit(1) | bit(0));
					modes = (bit(15) | bit(7) | bit(3) | bit(1) | bit(0));
				}
				put_long(bppptr,modes);
			}
			else palmabrt();//hack
			dbgprintf("supporteddepths\n");
			return;
		default:
			dbgprintf("Unknown command:%d\n",operand);
			D0 = sysErrParamErr;
			palmabrt();//hack
			return;
	}
}

void winscreenlock(){
	stackbyte(locktype);

	//palmabrt();//hack

	if(screenlockcount == 0){
		//copy screen / erase it with locktype
		switch(locktype){
			case winLockCopy:
				//clone old framebuffer
				memcpy68k(lcd_start + LCDBYTES,lcd_start,LCDBYTES);
				break;
			case winLockErase:
				//white out new framebuffer
				memset68k(lcd_start + LCDBYTES,0xFF,LCDBYTES);
				break;
			case winLockDontCare:
				//do nothing
				break;
			default:
				palmabrt();
				break;
		}

		setdisplayaddr(lcd_start + LCDBYTES);//second display buffer
	}else{
		dbgprintf("err unexpected double display lock.\n");
		palmabrt();
	}
	screenlockcount++;
	D0 = lcd_start + LCDBYTES;
}

void winscreenunlock(){

	//palmabrt();//hack

	//no prams
	if(screenlockcount == 0){
		dbgprintf("err unexpected double display unlock.\n");
		palmabrt();
	}

	if(screenlockcount > 0)screenlockcount--;
	if(screenlockcount == 0){
		//copy over old buffer
		memcpy68k(lcd_start,lcd_start + LCDBYTES,LCDBYTES);
		//set oslcdwindow
		setdisplayaddr(lcd_start);
	}
	//no return value
}

void wingetbitmap(){
	stackptr(window);
	//dbgprintf("Windowptr:%08x\n",window);
	A0 = getwinbmp(window);
}

void winsetforecolor(){
	stackbyte(col);
	D0 = get_byte(FORECOLOR);
	put_byte(FORECOLOR,col);
}

void winsetbackcolor(){
	stackbyte(col);
	D0 = get_byte(BACKCOLOR);
	put_byte(BACKCOLOR,col);
}

void winsettextcolor(){
	stackbyte(col);
	D0 = get_byte(TEXTCOLOR);
	put_byte(TEXTCOLOR,col);
}

void wingetdisplaywindow(){
	A0 = oslcdwindow;
}

void wingetdrawwindow(){
	A0 = currentdrawwindow;
}

void winsetdrawwindow(){
	stackptr(winptr);
	//dbgprintf("Old Addr:%08x,New Addr:%08x\n",currentdrawwindow,winptr);
	A0 = currentdrawwindow;
	if(winptr)currentdrawwindow = winptr;
	else{
		dbgprintf("Cant set drawwindow to nullptr_68k,Setting to oslcdwindow"
			   "(this is not supported above palm os 3.0)\n");//hack
		currentdrawwindow = oslcdwindow;
		palmabrt();//hack
	}
}

void winsetactivewindow(){
	stackptr(dstwindow);

	if(dstwindow)newwindowptr = dstwindow;
	else{
		dbgprintf("Cant set activewindow to nullptr_68k,Setting to oslcdwindow"
			   "(this is not supported above palm os 3.0)\n");//hack
		newwindowptr = oslcdwindow;
		palmabrt();//hack
	}

	changewindow = true;
	//sendwinenterondraw = false;

	//set enable flag in window
	UWORD flags = get_word(dstwindow + 8);
	put_word(dstwindow + 8,flags | bit(10));


	//no return value
}

void winsetclip(){
	stackword(startx);
	stackword(starty);
	stackword(endx);
	stackword(endy);

	CPTR clipptr = getwinclipping(currentdrawwindow);

	put_word(clipptr,startx);
	put_word(clipptr + 2,starty);
	put_word(clipptr + 4,endx);
	put_word(clipptr + 6,endy);
	//no return value
}

void windrawchars(){
	stackptr(chrsptr);
	stackword(length);
	stackword(thisx);
	stackword(thisy);

	TEMPHACK;
	if((WORD)thisx < 0 || (WORD)thisy < 0)return;

	dbgprintf("%d chars to print.\n",length);

	dbgprintf("Chars:%s\n",m68kstr(chrsptr).c_str());//HACK use length if given

	dstptr = currentdrawwindow;
	dstx = thisx;
	dsty = thisy;
	srcsize = (WORD)length;
	srcptr = chrsptr;
	drwcolor = get_byte(TEXTCOLOR);
	text();
	//no return value
}

void winresetclip(){
	UWORD winw = get_word(currentdrawwindow);
	UWORD winh = get_word(currentdrawwindow + 2);
	CPTR clip = getwinclipping(currentdrawwindow);

	put_word(clip,0);
	put_word(clip + 2,0);

	if(winw < LCDW)put_word(clip + 4,winw);
	else put_word(clip + 4,LCDW);

	if(winh < LCDH)put_word(clip + 6,winh);
	else put_word(clip + 6,LCDH);
	//no return value
}

void wincopyrectangle(){
	stackptr(srcwin);
	stackptr(dstwin);
	stackptr(srcrect);
	stackword(x);
	stackword(y);
	stackbyte(mode);

	if(srcwin)srcptr = srcwin;
	else srcptr = currentdrawwindow;

	if(dstwin)dstptr = dstwin;
	else dstptr = currentdrawwindow;

	srcsquare = get_square(srcrect);

	dstx = x;
	dsty = y;

	switch(mode){
		//unknown
		TEMPHACK;
		default:
			break;
	}

	copyrectangle();
	//no return value
}

void winpalette(){
	stackbyte(operation);
	stackword(startindex);
	stackword(paletteentrys);
	stackptr(userpalarray);

	//winErrPalette if no colortable
	if(userpalarray == nullptr_68k && operation != winPaletteSetToDefault){
		dbgprintf("top robin premium dirt noodles.\n");
	}

	CPTR winpal = getwinpalette(currentdrawwindow);
	switch(operation){
		case winPaletteGet:
			memcpy68k(userpalarray,winpal + startindex * 4,(WORD)paletteentrys * 4);
			break;
		case winPaletteSet:
			memcpy68k(winpal + startindex * 4,userpalarray,(WORD)paletteentrys * 4);
			break;
		case winPaletteSetToDefault:
			uint16 rabbid;
			for(rabbid = 0;rabbid < paletteentrys;rabbid++){
				put_long(winpal + (startindex + rabbid) * 4,paltorgbindex8(rabbid));
			}
			break;
	}
	//may need to send an event
	//osevent palettechangeevt;
	//palettechangeevt.type = sysNotifyDisplayChangeEvent

	D0 = errNone;
}

void winrgbtoindex(){
	stackptr(rgbcolor);

	UBYTE red = get_byte(rgbcolor + 1);
	UBYTE green = get_byte(rgbcolor + 2);
	UBYTE blue = get_byte(rgbcolor + 3);

	UBYTE bestindex = 0;
	CPTR clut = getwinpalette(currentdrawwindow);
	UWORD tablesize = getwinpalettenumentrys(currentdrawwindow);

	TEMPHACK;
	//get bpp and compare indicies properly
	offset_68k count;
	if(clut == nullptr_68k || tablesize == 0){
		UBYTE bpp = getbmpbpp(getwinbmp(currentdrawwindow));
		bestindex = getbestdefaultindex(red,green,blue,bpp);
	}
	else{
		UWORD closeness = 0xFFFF;//the bigger the more diffrence
		CPTR curcolor = clut;
		inc_for(count,tablesize){
			UWORD thisdiff = getrgbdiff(red,green,blue,get_byte(curcolor + 1),get_byte(curcolor + 2),get_byte(curcolor + 3));
			if(thisdiff < closeness){
				closeness = thisdiff;
				bestindex = get_byte(curcolor);
			}
			curcolor += 4;
		}
	}
	D0 = bestindex;//IndexedColorType (UBYTE/uint8)
	dbgprintf("TableSize:%d,BestIndex:%d,Red:%d,Green:%d,Blue:%d\n",tablesize,D0,red,green,blue);
}

void winpushdrawstate(){
	CPTR curdrwstate = getwindrawstate(currentdrawwindow);
	CPTR newdrwptr = getfreeheap(44);

	drawstates.push_back(curdrwstate);
	memcpy68k(newdrwptr,curdrwstate,44);
	setwindrawstate(currentactivewindow,newdrwptr);
	//no return value
}

TEMPHACK
//free now unused drawstate
void winpopdrawstate(){
	setwindrawstate(currentactivewindow,drawstates.back());
	drawstates.pop_back();
	//no return value
}

void wingetdisplayextent(){
	stackptr(returnx);
	stackptr(returny);

	put_word(returnx,LCDW);
	put_word(returny,LCDH);
	//no return value
}

TEMPHACK
void winerasewindow(){
	//just calls wineraserectangle

	CPTR winbmp = getwinbmp(currentdrawwindow);

	srcx = 0;
	srcy = 0;
	srcw = get_word(winbmp);//draw window width
	srch = get_word(winbmp + 2);//draw window height
	drwcolor = paltopalm(PalmPalette8bpp[get_byte(BACKCOLOR)]);//background color
	prams = ERASE;
	dstptr = currentdrawwindow;
	rectangle();

	TEMPHACK;
	//is not suppose to erase the window border

	//no return value
}

TEMPHACK
//unsure if correct
void windrawline(){
	stackword(sx);
	stackword(sy);
	stackword(ex);
	stackword(ey);

	srcx = sx;
	srcy = sy;
	srcendx = ex;
	srcendy = ey;
	dstptr = currentdrawwindow;
	drwcolor = paltopalm(PalmPalette8bpp[get_byte(FORECOLOR)]);
	prams = SOLID;
	line();

	//no return value
}

void winerasepixel(){
	stackword(x);
	stackword(y);
	dstptr = currentdrawwindow;
	drwcolor = paltopalm(PalmPalette8bpp[get_byte(BACKCOLOR)]);

	dstx = (WORD)x;
	dsty = (WORD)y;
	dot();
	//no return value
}

TEMPHACK
void winpaintbitmap(){
	stackptr(bmpptr);
	stackword(x);
	stackword(y);

	if(bmpptr & 1)dbgprintf("Bmp not word aligned!!!\n");
	if(bmpptr == nullptr_68k)dbgprintf("Bmp not at ptr!!!\n");

	switch(get_byte(XFERTYPE)){
		case winPaint:
		case winOverlay:
		case winSwap://(from api docs) winSwap:If the source is a bitmap, then the bitmap is transferred using winPaint mode instead.
			//draw normaly
			dstx = x;
			dsty = y;
			srcptr = bmpptr;
			dstptr = currentdrawwindow;
			bitmap();
			return;
		case winPaintInverse://swap colors
		case winInvert://Bitwise XOR the color-matched source pixel onto the destination
		case winMask://Write backColor if the source pixel is not transparent
		case winErase://Write backColor if the source pixel is transparent
		default://unknown mode
			palmabrt();//hack
			break;
	}

	//no return value
}

//not in trap table (HighDensityDispatch)
void winscreengetattribute(){
	stackbyte(attr);
	stackptr(resultptr);

	D0 = errNone;
	switch(attr){
		case winScreenWidth:
			put_long(resultptr,LCDW);
			return;
		case winScreenHeight:
			put_long(resultptr,LCDH);
			return;
		case winScreenDepth:
			put_long(resultptr,LCDBPP);
			return;
		case winScreenDensity:
			TEMPHACK;
			//set on emu bootup
			//put_long(resultptr,kDensityQuadruple);
			put_long(resultptr,kDensityDouble);
			//palmabrt();//hack
			return;

			TEMPHACK;
			//more conditions to implement

		default:
			dbgprintf("Attr:%d failed\n",attr);
			palmabrt();//hack
			D0 = sysErrParamErr;
			return;
	}
}

//not in trap table (HighDensityDispatch)
void wingetcoordinatesystem(){
	D0 = get_word(COORDSYS);
}

//not in trap table (HighDensityDispatch)
void winsetcoordinatesystem(){
	stackword(newcoordsys);
	D0 = get_word(COORDSYS);//old coord sys
	put_word(COORDSYS,newcoordsys);
}



//bmp functions
void bmpgetbits(){
	stackptr(bmpptr);
	A0 = getbmpdata(bmpptr);
}

void bmpbitssize(){
	stackptr(bmpptr);
	UWORD flags = get_word(bmpptr + 6);

	//compressed
	if(flags & bit(15)){
		UBYTE version = get_byte(bmpptr + 9);
		CPTR cmpdata = getbmpdata(bmpptr);
		switch(version){
			case 0://version 0 has no compression
				D0 = (get_word(bmpptr + 2)/*height*/ * get_word(bmpptr + 4)/*rowbytes*/);
				return;
			case 1:
			case 2:
				D0 = get_word(cmpdata) + 2;//bytes + 2 for the size variable
				return;
			case 3:
				palmabrt();//hack //not done
				return;
			default:
				palmabrt();//hack //not done
				return;
		}
	}

	D0 = (get_word(bmpptr + 2)/*height*/ * get_word(bmpptr + 4)/*rowbytes*/);
}

//not in trap table (HighDensityDispatch)
void bmpgetdensity(){
	stackptr(bmpptr);

	UBYTE version = get_byte(bmpptr + 9);
	if(version < 3)D0 = kDensityLow;
	else D0 = get_word(bmpptr + 14);//density
}

void bmpcreate(){
	stackword(uw);
	stackword(uh);
	stackbyte(bpp);//hack //normal is byte
	stackptr(colortable);
	stackptr(err);//return UWORD
	WORD w = (WORD)uw,h = (WORD)uh;//sign change

	dbgprintf("W:%d,H:%d,Bpp:%d\n",w,h,bpp);

	if(w == 0 || h == 0){
		put_word(err,sysErrParamErr);
		A0 = nullptr_68k;
		return;
	}

	switch(bpp){
		case 16:
		case 8:
		case 4:
		case 2:
		case 1:
			break;
		default:
			put_word(err,sysErrParamErr);
			A0 = nullptr_68k;
			return;
	}

	bool hastable = (colortable != nullptr_68k);
	CPTR newbitmap = newbmp(w,h,bpp,false,0,hastable,colortable);

	//palm sets all pixels to white
	//get clear params
	uint rowbytes = (w * bpp) / 8;//full bytes in row
	bool leftoverbyte = (((w * bpp) % 8) != 0);//has byte with unused data on end(since all rows are byte aligned)
	if(leftoverbyte)rowbytes += 1;
	//clear bitmap to white
	if(bpp == 1)memset68k(getbmpdata(newbitmap),0x00,rowbytes * h);//black and white are swapped in 1bpp mode
	else memset68k(getbmpdata(newbitmap),0xFF,rowbytes * h);

	put_word(err,errNone);
	A0 = newbitmap;
}

TEMPHACK
//may not be fully working
//not in trap table (HighDensityDispatch)
void bmpcreatebitmapv3(){
	stackptr(bmpv2ptr);
	stackword(density);
	stackptr(dataptr);//data to copy to the finished bitmap
	stackptr(coltblptr);//color table to use if bpp <= 8


	UWORD v2flags = get_word(bmpv2ptr + 6);


	//palm os cant handle compressed bitmaps with this function
	if(v2flags & bit(15))palmabrt();//hack


	CPTR bmpv3out = getfreeheap(100);//hack //dont know correct size

	/*
	put_word(bmpv3out,get_word(bmpv2ptr));//width
	put_word(bmpv3out + 2,get_word(bmpv2ptr + 2));//height
	put_word(bmpv3out + 4,get_word(bmpv2ptr + 4));//rowbytes
	put_word(bmpv3out + 6,get_word(bmpv2ptr + 6));//flags
	put_byte(bmpv3out + 8,get_byte(bmpv2ptr + 8));//pixelsize
	*/

	UBYTE v2bpp = get_byte(bmpv2ptr + 8);
	UBYTE v2clearindex = get_byte(bmpv2ptr + 12);

	memcpy68k(bmpv3out,bmpv2ptr,9);
	put_byte(bmpv3out + 9,3);//version

	//size of bitmapv3type in bytes (may or may not contain implimentation defined data pointer)
	put_byte(bmpv3out + 10,24);

	if(v2bpp == 16)put_byte(bmpv3out + 11,pixelFormat565);//pixel format
	else if(v2bpp < 16)put_byte(bmpv3out + 11,pixelFormatIndexed);
	else palmabrt();//hack

	put_byte(bmpv3out + 12,0);//unused
	put_byte(bmpv3out + 13,0);//compression type (this == 0 when compressed not set)

	if(density != 0){
		put_word(bmpv3out + 14,density);//density
		dbgprintf("Density:%d\n",density);//hack
	}
	else put_word(bmpv3out + 14,kDensityLow);

	put_long(bmpv3out + 16,v2clearindex);//transparent index
	put_long(bmpv3out + 20,0);//nextbitmapoffset //0 since it cant be part of a family


	/*
	//copy dataptr data into new bitmap
	WORD width = get_word(bmpv2ptr);
	WORD height = get_word(bmpv2ptr + 2);
	UWORD rowbytes = get_word(bmpv2ptr + 4);

	size_t_68k datasize = rowbytes * height;

	memcpy
	*/

	/*bitmapv3type structures dont store any data they just have pointers
	 * to it, this is given away by the bmpcreatbitmapv3() api definition
	 * stating that if the data pointer passed to it is to storage ram that
	 * the bitmap must be read only because blitting to it would cause an
	 * error.*/

	const UWORD flgmask = bit(13)/*hasclear*/ | bit(10)/*directcolor*/ | bit(8)/*nodither*/;
	UWORD v3flags = (v2flags & flgmask) | bit(12)/*indirectdata*/;

	if(coltblptr){
		v3flags |= bit(14)/*hascoltbl*/ | bit(9)/*indirectcoltbl*/;

		put_long(bmpv3out + 24,coltblptr);
		put_long(bmpv3out + 28,dataptr);
	}else{
		put_long(bmpv3out + 24,dataptr);
	}

	put_word(bmpv3out + 6,v3flags);

	A0 = bmpv3out;
}

void bmpgetdimensions(){
	stackptr(bitmap);
	stackptr(width);
	stackptr(height);
	stackptr(rowbytes);

	if(bitmap == nullptr_68k)palmabrt();//hack

	putwordifvptr(width,get_word(bitmap));
	putwordifvptr(height,get_word(bitmap + 2));
	putwordifvptr(rowbytes,get_word(bitmap + 4));
	//no return value
}



//fonts
void fntsetfont(){
	stackbyte(newfont);

	/*
	CPTR drwstate = getwindrawstate(currentactivewindow);
	D0 = get_byte(drwstate + 3);
	put_byte(drwstate + 3,newfont);
	*/

	D0 = get_byte(FONTID);
	put_byte(FONTID,newfont);

	dbgprintf("font id:%d\n",newfont);

	CPTR newfntptr = getfontaddr(newfont);
	currentfont.setactivefont(newfntptr);
	put_long(FONTPTR,newfntptr);

	//TEMPHACK;
	//set pointer

	/*
	if(newfont >= fntAppFontCustomBase){

	}
	*/
}

TEMPHACK
void fntcharswidth(){
	stackptr(chrarray);
	stackword(length);
	D0 = (length * 1/*fix this*/) + ((length - 1) * 1/*fix this*/);//hack
	/*
	stackptr(chrarray);
	stackword(ulength);
	WORD length = (WORD)ulength;
	WORD pixellength = 0;
	WORD cnt;
	inc_for(cnt,length){
		pixellength += getcharwidth(get_byte(chrarray + cnt));
		//hack ,add spacing inbetween letters if not multi byte character
	}
	D0 = pixellength;
	*/
}

void fntgetfontptr(){
	A0 = get_long(FONTPTR);
}



//forms
void frmgotoform(){
	stackword(frmid);

	if(anyformsopen){
		osevent closeold;
		closeold.type = frmCloseEvent;
		closeold.data.push_back(activeform);
		addnewevent(closeold);
	}

	osevent loadnew;
	osevent opennew;

	loadnew.type = frmLoadEvent;
	loadnew.data.push_back(frmid);

	opennew.type = frmOpenEvent;
	opennew.data.push_back(frmid);

	addnewevent(loadnew);
	addnewevent(opennew);

	anyformsopen = true;//hack
	//no return value
}

void frmgetformptr(){
	stackword(frmid);
	A0 = getopenform(frmid);
}

void frmgetwindowhandle(){
	stackptr(handle);
	A0 = handle;
}

void frmdispatchevent(){
	stackptr(eventptr);
	UWORD event = get_word(eventptr);

	CPTR frmptr;
	switch(event){
		case frmOpenEvent:
		case frmGotoEvent:
		case frmLoadEvent:
		case frmCloseEvent:
		case frmTitleEnterEvent:
		case frmTitleSelectEvent:
			frmptr = getopenform(get_word(eventptr + evtDataOffset));//developer defined id NOT resource id
			break;
		default:
			frmptr = activeformptr;
			break;
	}

	if(event != 0)dbgprintf("Evtnum:%d,Frmid:%04x,FrmPtr:%08x\n",event,get_word(eventptr + evtDataOffset),frmptr);

	//custom event handler
	CPTR functionptr = getformeventhandler(frmptr);
	if(functionptr != nullptr_68k){
		CPU_pushlongstack(eventptr);
		CPU_68kfunction(functionptr,notrequired);
		//now remove eventptr(the argument of the 68k function call) from stack
		CPU_cleanargsfromstack(4);

		//dbgprintf("Result:%08x\n",D0);//HACK

		if(D0 != 0)return;
	}
	else palmabrt();//hack //fatal error

	dbgprintf("Not handled by custom event handler.\n");

	formeventhandler(frmptr,eventptr);
}

void frmhandleevent(){
	stackptr(formptr);
	stackptr(eventptr);
	formeventhandler(formptr,eventptr);
}

void frminitform(){
	stackword(resid);
	dbgprintf("ResID:%04x\n",resid);

	A0 = decompressform(resid);

	if(A0 == nullptr_68k)palmabrt();

	//TEMPHACK;
	//form id not resource id
	setopenform(frmid,A0);
}

void frmdeleteform(){
	stackptr(formptr);

	releaseformmemory(formptr);

	//no return value
}

void frmcloseallforms(){
	//no params

	int32 scan;
	for(scan = openformids.size() - 1;scan >= 0;scan--){
		osevent closeevt;
		closeevt.type = frmCloseEvent;
		closeevt.data.push_back(openformids[scan]);
		addnewevent(closeevt);
		freeopenform(openformids[scan]);
	}

	//no return value
}

void frmsetactiveform(){
	stackptr(formptr);

	dbgprintf("FormPtr:%08x\n",formptr);

	/*
	osevent exit;
	exit.type = winExitEvent;
	exit.data.push_back(formptr);
	exit.data.push_back(currentactivewindow);
	addnewevent(exit);

	activeformptr = formptr;
	activeform = getformid(formptr);

	TEMPHACK;
	//most likely sets these to the form
	currentactivewindow = formptr;
	currentdrawwindow = formptr;
	//currentactivewindow = newwindowptr;
	//currentdrawwindow = newwindowptr;

	anyformsopen = true;//hack
	*/
	newwindowptr = formptr;
	changewindow = true;
	activeformptr = formptr;
	activeform = getformid(formptr);

	anyformsopen = true;//hack

	//no return value
}

void frmgetactiveform(){
	A0 = activeformptr;
}

void frmgetactiveformid(){
	D0 = activeform;
}

void frmseteventhandler(){
	stackptr(formptr);
	stackptr(functionptr);
	setformeventhandler(formptr,functionptr);
	dbgprintf("Evt handler:%08x,FormPtr:%08x\n",functionptr,formptr);
	//no return value
}

void frmsettitle(){
	stackptr(formptr);
	stackptr(chrptr);

	UWORD frmid = getformid(formptr);
	UWORD attr = getformattr(formptr);

	dbgprintf("Formptr:%08x,New Title:%08x\n",formptr,chrptr);

	CPTR formobjlist = getformobjlist(formptr);
	CPTR titleobj = nullptr_68k;
	UWORD thisnumobjects = getformnumobjects(formptr);
	UWORD count;
	inc_for(count,thisnumobjects){
		if(get_byte(formobjlist + count * 6) == frmTitleObj){
			titleobj = get_long(formobjlist + count * 6 + 2);
			break;
		}
	}

	if(titleobj)put_long(titleobj + 8,chrptr);
	else{
		dbgprintf("bunny phlem\n");
		palmabrt();
	}

	//TEMPHACK;
	//if visible needs to redraw title
	if((attr & 0xA000) == 0xA000){//0xA000 == (useable | visible)
		osevent newtitle;
		newtitle.type = frmUpdateEvent;
		newtitle.data.push_back(frmid);
		newtitle.data.push_back(frmRedrawUpdateCode);
		addnewevent(newtitle);
	}

	//no return value
}

void frmdrawform(){
	stackptr(formptr);

	updateanddrawform(formptr);

	dbgprintf("ACTwin:%08x,DRAWwin:%08x,Thisform:%08x\n",currentactivewindow,currentdrawwindow,formptr);

	//no return value
}

TEMPHACK
//draw every thing and do it correctly
void frmcustomalert(){
	stackword(resourcenum);
	stackptr(str1);
	stackptr(str2);
	stackptr(str3);
	dbgprintf("Custom alert!\n");
	if(str1)dbgprintf("S1:%s\n",m68kstr(str1).c_str());
	if(str2)dbgprintf("S2:%s\n",m68kstr(str2).c_str());
	if(str3)dbgprintf("S3:%s\n",m68kstr(str3).c_str());

	sendpenevents = false;

	CPTR alert = getuiresource(resourcenum,'Talt');

	UWORD alertype = get_word(alert);
	UWORD helprscid = get_word(alert + 2);
	UWORD numbuttons = get_word(alert + 4);
	UWORD defaultbutton = get_word(alert + 6);

	CPTR accessptr = alert + 8;

	vector<string> alerttext(2);
	//string* alerttext = new string[2];
	alerttext[0] = m68kstr(accessptr);
	accessptr += alerttext[0].size() + 1;
	alerttext[1] = m68kstr(accessptr);
	accessptr += alerttext[1].size() + 1;

	vector<string> buttontext(numbuttons);
	//string* buttontext = new string[numbuttons];
	for(UWORD count = 0;count < numbuttons;count++){
		buttontext[count] =  m68kstr(accessptr);
		accessptr += buttontext[count].size() + 1;
	}

	dbgprintf("%s\n,%s\n,%s\n,%s\n",alerttext[0].c_str(),alerttext[1].c_str(),buttontext[0].c_str(),buttontext[1].c_str());


	UWORD result;
	SQUARE buttonbounds[numbuttons];

	backupframe();

	SQUARE window;
	window.start.x = 0;
	window.start.y = LCDH / 2;
	window.size.w = LCDW;
	window.size.h = LCDH;
	window.end.x = LCDW - 1;
	window.end.y = LCDH - 1;

	drawborder(window);

	//draw text

	//draw icon

	WORD btngap = 5 * LCDDENSITY;//hack //find real gap

	SQUARE btnloc;

	btnloc.size.w = 20 * LCDDENSITY;//hack //find real width
	btnloc.size.h = 10 * LCDDENSITY;//hack //find real height

	//just guesses vvv

	btnloc.start.x = 4 * LCDDENSITY;
	btnloc.start.y = LCDH - 6 * LCDDENSITY - btnloc.size.h;//6 is offset of button from bottom of screen
	//and 10 is height of button

	//just guesses ^^^

	btnloc.end.y = LCDH - 6 * LCDDENSITY;
	btnloc.end.x = btnloc.start.x + btnloc.size.w;

	for(UWORD count = 0;count < numbuttons;count++){
		buttonbounds[count] = btnloc;
		drawbutton(btnloc);
		btnloc.start.x += btnloc.size.w + btngap;
		btnloc.end.x += btnloc.size.w + btngap;
	}

	//finished drawing



	//wait
	bool done = false;
	UWORD button;
	COORD pressloc;
	COORD releaseloc;
	while(true){
		KILLSWITCH;
		pressloc = waitforpen();
		for(button = 0;button < numbuttons;button++){
			if(inboundbox(buttonbounds[button],pressloc)){

				//change button color

				releaseloc = trackpen();
				if(inboundbox(buttonbounds[button],releaseloc)){

					//change button color

					done = true;
					result = button;
				}
			}
			if(done)break;
		}
		if(done)break;
	}

	sendpenevents = true;

	restoreframe();
	D0 = result;
}

void frmalert(){
	stackword(id);
	UWORD button = 0;
	CPTR alert = getuiresource(id,'Talt');

	UWORD alerttype = get_word(alert);
	UWORD helprsc = get_word(alert + 2);
	UWORD numbuttons = get_word(alert + 4);
	UWORD defaultbutton = get_word(alert + 6);

	CPTR string1 = alert + 8;
	CPTR string2 = string1 + strlen68k(string1) + 1;
	CPTR string3 = string2 + strlen68k(string2) + 1;

	dbgprintf("AlertName:%s,AlertText:%s,String3:%s\n",m68kstr(string1).c_str(),
		   m68kstr(string2).c_str(),m68kstr(string3).c_str());

	//draw alert


	D0 = button;
}

void frmgetobjectindex(){
	stackptr(form);
	stackword(objid);//not resource id

	uint16 formobjnum = getformnumobjects(form);
	uint16 count;
	inc_for(count,formobjnum){
		if(getformobjid(form,count) == objid){
			D0 = count;
			return;
		}
	}

	D0 = frmInvalidObjectId;
}

void frmsetgadgethandler(){
	stackptr(form);
	stackword(gadgetindex);
	stackptr(handler);

	CPTR gadget = getformobjloc(form,gadgetindex);
	setgadgethandler(gadget,handler);
	//no return value
}

void frmgetobjectptr(){
	stackptr(form);
	stackword(index);
	A0 = getformobjloc(form,index);
}

void frmhideobject(){
	stackptr(formptr);
	stackword(index);
	removeformobject(formptr,index);
	//no return value
}

void frmsetfocus(){
	stackptr(formptr);
	stackword(objindex);
	setformfocus(formptr,objindex);
}

TEMPHACK
void frmsetcontrolvalue(){
	stackptr(formptr);
	stackword(index);
	stackword(newvalue);

	CPTR objptr = getformobjloc(formptr,index);

	UWORD attr = get_word(objptr + 14);
	UBYTE type = get_byte(objptr + 16);

	if(type == sliderCtl){
		palmabrt();//hack
	}else{
		//just turn on or off
		if(newvalue != 0)attr |= bit(12);
		else attr &= ~bit(12);
		put_word(objptr + 14,attr);
	}
	//no return value
}



//menus
void menuhandleevent(){
	stackptr(menubarptr);
	stackptr(eventptr);
	stackptr(errorptr);
	menueventhandler(menubarptr,eventptr,errorptr);
}



//uicolor
void uicolorgettableentryrgb(){
	stackbyte(index);
	stackptr(rgbcolor);
	put_long(rgbcolor,UIColorTable[index]);
	//no return value
}

void uicolortablesettableentry(){
	stackbyte(index);
	stackptr(rgbcolor);
	UIColorTable[index] = get_long(rgbcolor);
	D0 = errNone;
}

void uicolorgettableentryindex(){
	stackbyte(colortableindex);
	D0 = UIColorTable[colortableindex] >> 24;
}



//field
void fldsetuseable(){
	stackptr(field);
	stackbool(enabled);

	UWORD curflags = get_word(field + 10);

	if(enabled){
		put_word(field + 10,curflags | bit(15));
	}else{
		put_word(field + 10,curflags & ~bit(15));
	}

	//no return value
}

void flderasefield(){
	stackptr(field);

	//disable visible bit
	put_word(field + 10,get_word(field + 10) & ~bit(14));

	TEMPHACK;
	//may redraw the display

	//no return value
}

void fldsettextptr(){
	stackptr(field);
	stackptr(textptr);

	fieldappointtextptr(field,textptr);
	//no return value
}

void fldsettexthandle(){
	stackptr(field);
	stackptr(texthandle);

	fieldappointtexthandle(field,texthandle);
	//no return value
}

void flddrawfield(){
	stackptr(field);
	drawfield(oslcdwindow,field);//to screen or activeform unsure? //hack
	//palmabrt();
	//no return value
}

void fldgettextptr(){
	stackptr(fldptr);
	A0 = get_long(fldptr + 12);
}

void fldgettexthandle(){
	stackptr(fldptr);
	A0 = get_long(fldptr + 16);
}



//controls
void ctlsetusable(){
	stackptr(ctlptr);
	stackbool(value);

	UWORD newattr = get_word(ctlptr + 14);//get old attr
	if(value)newattr |= bit(15);
	else newattr &= ~bit(15);
	put_word(ctlptr + 14,newattr);
	//no return value
}



//pen input manager //none of these are in the dispatch table

UWORD lcddirection = 0;//dummy value

TEMPHACK
void syssetorientationtriggerstate(){
	stackword(state);

	//unknown

	D0 = errNone;
}

TEMPHACK
void syssetorientation(){
	stackword(orientation);
	lcddirection = orientation;
	//rotate images if needed
	D0 = errNone;
}

void sysgetorientation(){
	D0 = lcddirection;
}

TEMPHACK
void frmsetdiapolicyattr(){
	stackptr(frmptr);
	stackword(newpol);

	//unknown

	D0 = errNone;
}

TEMPHACK
//only returns fixed value
void pingetinputareastate(){
	D0 = pinInputAreaNone;//pretends there is no graffiti area
}

void statgetattribute(){
	stackword(selector);
	stackptr(dataptr);

	switch(selector){
		case statAttrBarVisible:
			put_long(dataptr,statvisible);
			break;
		case statAttrDimension:
			put_long(dataptr,((ULONG)statw << 16 | stath));
			break;
		default:
			D0 = sysErrParamErr;
			return;
	}
	D0 = errNone;
}



//other
void evtgetpen(){

}

void rctsetrectangle(){
	stackptr(rectptr);
	stackword(left);
	stackword(top);
	stackword(width);
	stackword(height);

	put_word(rectptr,left);
	put_word(rectptr + 2,top);
	put_word(rectptr + 4,width);
	put_word(rectptr + 6,height);
	//no return value
}

void rctptinrectangle(){
	stackword(x);
	stackword(y);
	stackptr(rectptr);

	SQUARE rect = get_square(rectptr);
	COORD testpt = {(WORD)x,(WORD)y};

	D0 = inboundbox(rect,testpt);
}

TEMPHACK
//hardcoded to tx fullscreen mode (no pen/silkscreen buttons)
void evtgetpenbuttonlist(){
	stackptr(countptr);//UWORD

	put_word(countptr,0);

	A0 = nullptr_68k;
}

void highdensitydispatch(){
	//This trap is just a switch statement!

	SELECTOR{
		SELAPI(HDSelectorWinScreenGetAttribute,winscreengetattribute());//check for highdensity,get display size,etc
		SELAPI(HDSelectorBmpCreateBitmapV3,bmpcreatebitmapv3());
		SELAPI(HDSelectorBmpGetDensity,bmpgetdensity());
		SELAPI(HDSelectorWinGetCoordinateSystem,wingetcoordinatesystem());
		SELAPI(HDSelectorWinSetCoordinateSystem,winsetcoordinatesystem());

		default:
			//invalid command
			dbgprintf("INV_CMD:%d\n",D2);
			palmabrt();//hack
			break;
	}
}

void pinsdispatch(){
	//This trap is just a switch statement!

	SELECTOR{
		SELAPI(pinSysSetOrientationTriggerState,syssetorientationtriggerstate());
		SELAPI(pinSysSetOrientation,syssetorientation());
		SELAPI(pinSysGetOrientation,sysgetorientation());
		SELAPI(pinFrmSetDIAPolicyAttr,frmsetdiapolicyattr());
		SELAPI(pinPINGetInputAreaState,pingetinputareastate());
		SELAPI(pinStatGetAttribute,statgetattribute());

		default:
			//invalid command
			dbgprintf("INV_CMD:%d\n",D2);
			palmabrt();//hack
			break;
	}
}



//part of evtgetevent
void evtgeteventWIN(){
	if(changewindow){
		osevent closeold;
		osevent opennew;

		closeold.type = winExitEvent;
		closeold.data.push_back(newwindowptr);
		closeold.data.push_back(currentactivewindow);
		addnewevent(closeold);

		opennew.type = winEnterEvent;
		opennew.data.push_back(newwindowptr);
		opennew.data.push_back(currentactivewindow);
		addnewevent(opennew);

		currentactivewindow = newwindowptr;
		currentdrawwindow = newwindowptr;

		changewindow = false;
	}
}




//sets up memory and varibles
bool initdisplaydriver(){
	//spareframe does not need to be cleared since it is not accessible from inside the emulator
	//(it is only drawn after being filled with valid screen data)

	scalevideo = true;

	width = 160;
	height = 160;
	bpp = LCDBPP;
	color = LCDHASCOLOR;

	/*
	width = LCDW;
	height = LCDH;
	bpp = LCDBPP;
	color = LCDHASCOLOR;
	*/

	TEMPHACK;
	//status bar on devices with dynamic input area
	statvisible = false;
	statw = 0;
	stath = 0;

	//touch driver
	sendpenevents = true;

	osdrawstate = newdrawstate();
	lcdbitmaptype = getfreeheap(20);
	oslcdwindow = getfreeheap(68);
	/*
	initformwindow(oslcdwindow,LCDW,LCDH,bit(11) | bit(10) | bit(8),
			  0,lcdbitmaptype,osdrawstate,0);
	*/
	initformwindow(oslcdwindow,160,160,bit(11) | bit(10) | bit(8),
	          0,lcdbitmaptype,osdrawstate,0);

	if(oslcdwindow == nullptr_68k || lcdbitmaptype == nullptr_68k || osdrawstate == nullptr_68k){
		palmabrt();//hack
		return false;
	}

	//setup lcdbitmaptype
	put_word(lcdbitmaptype,LCDW);
	put_word(lcdbitmaptype + 2,LCDH);
	put_word(lcdbitmaptype + 4,LCDW * 2);
	put_word(lcdbitmaptype + 6,bit(11) | bit(12));
	put_byte(lcdbitmaptype + 8,LCDBPP);//bits per pixel
	put_byte(lcdbitmaptype + 9,2);
	put_word(lcdbitmaptype + 10,0);//next bitmaptype
	put_byte(lcdbitmaptype + 12,0);//transparent color (none)
	put_byte(lcdbitmaptype + 13,0xFF);//compression type (none)
	put_word(lcdbitmaptype + 14,0);//reserved
	put_long(lcdbitmaptype + 16,lcd_start);//indirect flag ptr (to lcd)

	TEMPHACK;
	//most likely *double or *single not *native
	put_word(COORDSYS,kCoordinatesNative);

	currentdrawwindow = oslcdwindow;
	currentactivewindow = oslcdwindow;

	//fonts
	CPTR stdfntaddr = getfontaddr(stdFont);
	currentfont.setactivefont(stdfntaddr);
	put_byte(FONTID,stdFont);
	put_long(FONTPTR,stdfntaddr);

	//may load specific tFRM for display on start
	anyformsopen = false;

	TEMPHACK;
	activeform = 0x0;
	activeformptr = currentactivewindow;

	screenlockcount = 0;

	changewindow = false;
	sendwinenterondraw = false;

	return true;
}

void deinitdisplaydriver(){
}



void appTouchDriver(int x,int y,bool pressed){
	if(!running)return;

	if(x > 320 || y > 480 || x < 0 || y < 0){
		dbgprintf("TouchX:%d,TouchY:%d\n",x,y);
		palmabrt();//hack
	}

	PENX = x;
	PENY = y;

	osevent touch;
	touch.screenx = x;
	touch.screeny = y;
	if(pressed)touch.pendown = true;

	//move event
	if(PENDOWN && pressed){
		//some objects track automaticly,palm does not send this event for those objects
		//(make this disabled for those objects)
		touch.type = penMoveEvent;
		touch.pendown = true;
	}else if(pressed){
		PENDOWN = true;

		touch.type = penDownEvent;
		touch.pendown = true;
		touch.tapcount = 1;//hack

		//tracking for penUpEvent
		touchstart.x = x;
		touchstart.y = y;
	}else if(!pressed && PENDOWN){
		PENDOWN = false;

		touch.type = penUpEvent;
		touch.pendown = false;
		touch.data.push_back(touchstart.x);
		touch.data.push_back(touchstart.y);
		touch.data.push_back(x);
		touch.data.push_back(y);
	}
	else palmabrt();//hack

	if(sendpenevents)addnewevent(touch);
}

void appKeyDriver(char thiskey,bool pressed){
	if(!running)return;

	if(pressed){
		osevent keypress;
		keypress.type = keyDownEvent;
		keypress.data.push_back((UBYTE)thiskey);//chr
		keypress.data.push_back(0);//virtual key num
		keypress.data.push_back(0);//modifiers
		addnewevent(keypress);
	}else{
		osevent keypress;
		keypress.type = keyUpEvent;
		keypress.data.push_back((UBYTE)thiskey);//chr
		keypress.data.push_back(0);//virtual key num
		keypress.data.push_back(0);//modifiers
		addnewevent(keypress);
	}
}
