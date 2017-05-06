#include "palmwrapper.h"
#include "displaydriver.h"
#include "palmapi.h"
#include "rawimagetools.h"
#include "eventqueue.h"
#include "stdlib68k.h"
#include <unordered_map>


//new list
#include "m68k.h"
#include "newcpu.h"
#include "palmmalloc.h"
#include "resourcelocator.h"
#include "palmtypeaccess.h"
#include "palmdefines.h"
#include "dataexchange.h"
#include "virtuallcd.h"

#include "palmos/graphics/palette.h"


#include "ugui.h"

struct {
	uint8_t bpp;//bits per pixel of renderer
	int16_t width;//width of renderer
	int16_t height;//height of renderer
	bool color;//if color should be displayed or not
	bool scale_video;//should be true if using 160*160 resolution, starts true and apps must enable hires mode
	int screen_lock_count;//used to prevent displaying any changes until finished rendering
	offset_68k draw_state;//the current settings of the renderer (stored in palm address space so apps can access it(even though that "forbidden" by the api docs))

	offset_68k lcd_window;//represents the framebuffer as a window
	offset_68k lcd_bitmap;//represents the framebuffer as a palm bitmap struct

	UG_GUI draw_ctx;//gui library rendering context
	offset_68k draw_offset;//the current draw window bitmap data

	offset_68k current_draw_window;//the window to draw to
	offset_68k current_active_window;//the window to render

	uint32_t UIColorTable[31];//may just be used as storage?
	uint16_t color_palette[0xFF];//used for non 16bit color to map to 16bit values

	void set_draw_window(offset_68k new_draw_window) {
		current_draw_window = new_draw_window;
		draw_offset = get_win_data(new_draw_window);//get window pixel data address
	}
	offset_68k get_draw_window() {
		return current_draw_window;
	}
} renderer;

void plotpixel_drawctx(int16_t x, int16_t y, uint16_t pixcolor) {
	put_word(renderer.draw_offset + ((y * renderer.width + x) * 2), pixcolor);
}

#define XFERTYPE  (renderer.draw_state)//uint8_t
#define PATTERN	  (renderer.draw_state + 1)
#define UNDERLINE (renderer.draw_state + 2)
#define FONTID	  (renderer.draw_state + 3)//uint8_t
#define FONTPTR	  (renderer.draw_state + 4)//offset_68k
#define FORECOLOR (renderer.draw_state + 18)//uint8_t
#define BACKCOLOR (renderer.draw_state + 19)//uint8_t
#define TEXTCOLOR (renderer.draw_state + 20)//uint8_t
#define COORDSYS  (renderer.draw_state + 32)//uint16_t

offset_68k get_draw_state() {
	return renderer.draw_state;
}


//uncompressed version of current font
RAWfnt currentfont;

//status bar on devices with dynamic input area
bool statvisible;
int16_t statw, stath;

//touch driver state
bool sendpenevents;
//penUpEvent needs 2 PointType structs in the data vector (start,end)
COORD touchstart;

//for winsetactivewindow
offset_68k newwindowptr;
bool changewindow;

std::vector<offset_68k> windowlist;

std::vector<offset_68k> drawstates;

//form
uint16_t activeform;
offset_68k activeformptr;
//form objects
std::vector<UISQUARE> objects;

bool anyformsopen;
bool sendwinenterondraw;

std::unordered_map<uint16_t, offset_68k> openforms;
std::vector<uint16_t> openformids;//added to access open forms as a list

void setdisplayaddr(offset_68k displayaddr) {
	put_long(renderer.lcd_window + 4, displayaddr);
	offset_68k bitmap = get_win_bmp(renderer.lcd_window);
	put_long(bitmap + 16, displayaddr);
}

void freeopenform(uint16_t frmid) {
	openforms.erase(frmid);

	for(int32_t scan = openformids.size() - 1; scan >= 0; scan--) {
		if(openformids[scan] == frmid) {
			openformids.erase(openformids.begin() + scan);
			break;
		}
	}
}

void setopenform(uint16_t frmid, offset_68k ptr) {
	openforms[frmid] = ptr;
	openformids.push_back(frmid);
}

offset_68k getopenform(uint16_t frmid) {
	if(openforms.find(frmid) == openforms.end()) {
		return nullptr_68k;
	}

	return openforms[frmid];
}

uint16_t getformobjid(offset_68k form, uint16_t count) {
	offset_68k objindex = getformobjlist(form) + 6 * count;
	uint8_t objtype = get_byte(objindex);
	offset_68k obj = get_long(objindex + 2);
	uint16_t finalid;

	switch(objtype) {
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
		dbgprintf("err obj %d not done\n", objtype);
		palmabrt();
		break;
	}

	return finalid;
}


//#if 0
//Virtual GPU
//virtual GPU registers

//allow access to each element seperately
SQUARE srcsquare;
SQUARE dstsquare;

//these used to all be separate values
COORD& srcstart = srcsquare.start;
int16_t& srcx = srcstart.x;
int16_t& srcy = srcstart.y;
COORD& srcend = srcsquare.end;
int16_t& srcendx = srcend.x;
int16_t& srcendy = srcend.y;
BOUNDRY& srcarea = srcsquare.size;
int16_t& srcw = srcarea.w;
int16_t& srch = srcarea.h;

COORD& dststart = dstsquare.start;
int16_t& dstx = dststart.x;
int16_t& dsty = dststart.y;
COORD& dstend = dstsquare.end;
int16_t& dstendx = dstend.x;
int16_t& dstendy = dstend.y;
BOUNDRY& dstarea = dstsquare.size;
int16_t& dstw = dstarea.w;
int16_t& dsth = dstarea.h;


offset_68k srcptr, dstptr;
offset_68k srcindex, dstindex;
int srcbpp, dstbpp;
int dstround;
size_t_68k srcsize;
uint16_t drwcolor;
uint8_t drwfnt;
int prams;



void copyrectangle() {
	RAWimg hostwindow(srcptr, WINDOW);
	offset_68k winbmp = get_win_bmp(dstptr);
	//FBWriter window(getbmpdata(winbmp),getbmprowbytes(winbmp),getbmpbpp(winbmp));
	FBWriter window(get_bmp_data(winbmp), get_word(winbmp), 16); //hack
	window.copyrect(hostwindow, srcx, srcy, srcw, srch, dstx, dsty);
}

void rectangle() {
	//dbgprintf("WinBmpPtr:%08x,WinDataPtr:%08x,X:%d,Y:%d,EndX:%d,EndY:%d,Rect:%08x\n",
	//	   getwinbmp(currentdrawwindow),getwindata(currentdrawwindow),x,y,endx,endy,rectptr);
	offset_68k winbmp = get_win_bmp(dstptr);
	//FBWriter window(getbmpdata(winbmp),getbmprowbytes(winbmp),getbmpbpp(winbmp));
	FBWriter window(get_bmp_data(winbmp), get_word(winbmp), 16); //hack
	window.rect(srcx, srcy, srcw, srch, prams, drwcolor, dstround);
}

void bitmap() {
	dbgprintf("Draw Bitmap:(Src:%08x,Dst:%08x,X:%d,Y:%d)\n", srcptr, dstptr, dstx, dsty);
	RAWimg palmbmp(srcptr, BMP, UNDEFINED, UNDEFINED, UNDEFINED, false);
	offset_68k winbmp = get_win_bmp(dstptr);
	dbgprintf("FrameBuffLoc:%08x\n", get_bmp_data(winbmp));
	FBWriter window(get_bmp_data(winbmp), get_word(winbmp), 16); //hack
	//FBWriter window(getbmpdata(winbmp),get_word(winbmp),getbmpbpp(winbmp));
	window.draw(palmbmp, dstx, dsty);
}

void text() {
	RAWfnt* activefont;
	dbgprintf("Text At X:%d,Y:%d\n", dstx, dsty);

	if(drwfnt == get_byte(FONTID)) {
		activefont = &currentfont;
	}
	else {
		offset_68k tempnewfont = getfontaddr(drwfnt);
		activefont = new RAWfnt;
		activefont->setactivefont(tempnewfont);
	}

	offset_68k winbmp = get_win_bmp(dstptr);
	FBWriter window(get_bmp_data(winbmp), get_word(winbmp), 16); //hack
	offset_68k count = 0;
	char curchr;

	if(srcsize == UNDEFINED) {
		while(true) {
			curchr = (char)get_byte(srcptr + count);

			if(chraction(curchr) == TERMINATE) {
				break;
			}

			window.draw(curchr, *activefont, dstx, dsty);
			//window.draw5x7(dstx,dsty,drwcolor,curchr);
			dstx += 6;
			count++;
		}

		//dstindex = count + 1;//why does this exist?
	}
	else {
		for(count = 0; count < srcsize; count++) {
			curchr = (char)get_byte(srcptr + count);

			//if(chraction(curchr) == TERMINATE || count >= srcsize)break;
			if(chraction(curchr) == TERMINATE) {
				break;
			}

			if(curchr == (char)254) {
				palmabrt();    //HACK
			}

			window.draw(curchr, *activefont, dstx, dsty);
			//window.draw5x7(dstx,dsty,drwcolor,curchr);
			dstx += 6;
		}
	}

	//*/
	/*
		uint8_t fontid = get_byte(FONTID);
		offset_68k fontptr = get_long(FONTPTR);

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
		offset_68k winbmp = getwinbmp(dstptr);
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

//End of virtual GPU
//#endif


//helpers
offset_68k get_ui_resource(uint16_t id, uint32_t type) {
	return get_app_resource(id, type);
}

bool in_bound_box(UISQUARE& box, COORD compare) {
	if(compare.x >= box.start.x && compare.x <= box.end.x)
		if(compare.y >= box.start.y && compare.y <= box.end.y) {
			return true;
		}

	return false;
}

bool in_bound_box(SQUARE& box, COORD compare) {
	if(compare.x >= box.start.x && compare.x <= box.end.x)
		if(compare.y >= box.start.y && compare.y <= box.end.y) {
			return true;
		}

	return false;
}

void addobjtocollisionmatrix(SQUARE& area, offset_68k object, uint8_t type, uint16_t id) {
	UISQUARE temp;
	temp.start = area.start;
	temp.end = area.end;
	temp.objtype = type;
	temp.objid = id;
	temp.object = object;
	objects.push_back(temp);
}

void resetcollisionmatrix() {
	objects.clear();
}

void disableobject(offset_68k objectptr, uint8_t type) {
	uint16_t attr;

	switch(type) {
	case frmFieldObj:
		attr = get_word(objectptr + 10);
		put_word(objectptr + 10, attr & ~bit(15));
		return;

	//case frmControlObj:
	//break;
	//case frmBitmapObj:
	//break;
	case frmLabelObj:
		attr = get_word(objectptr + 6);
		put_word(objectptr + 6, attr & ~bit(15));
		return;

	//case frmGadgetObj:
	//break;
	default:
		dbgprintf("\nType %d not implimented\n\n", type);
		palmabrt();
		break;
	}
}

COORD waitforpen() {
	while(!PENDOWN) {
		m68k_handle_changes();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	COORD loc;
	loc.x = (int16_t)PENX;
	loc.y = (int16_t)PENY;
	return loc;
}

COORD trackpen() {
	while(PENDOWN) {
		m68k_handle_changes();
		//stalk the pen!! //later
		//HACK the pen is not being tracked
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	COORD loc;
	loc.x = (int16_t)PENX;
	loc.y = (int16_t)PENY;
	return loc;
}

//#if 0
void drawborder(SQUARE area) {
	srcsquare = area;
	drwcolor = 0xFFFF;//white
	prams = FILL;
	dstptr = renderer.lcd_window;//hack
	rectangle();
	//palmabrt();//hack
}

void drawbutton(SQUARE area) {
	UG_FillFrame(area.start.x, area.start.y, area.end.x, area.end.y, C_GREEN);
}

//the blue outline around the active control on Palm OS 5
void radioactiveborder(SQUARE area, bool round) {
	palmabrt();
}
//#endif

//used by emulator when writing os data to screen and the onscreen image needs to be preserved(like alerts)
static uint16_t spareframe[LCDMAXPIX];

void backupframe() {
	memcpy(spareframe, framebuffer, LCDBYTES);
}

void restoreframe() {
	memcpy(framebuffer, spareframe, LCDBYTES);
}

void restorepartialframe(COORD start, COORD end) {
	COORD count;

	for(count.y = start.y; count.y <= end.y; count.y++) {
		for(count.x = start.x; count.x <= end.x; count.x++) {
			framebuffer[count.y * LCDW + count.x] = spareframe[count.y * LCDW + count.x];
		}
	}
}



bool relaytouchevent(offset_68k eventptr) {
	COORD touch = get_coord(eventptr + 4);
	size_t_68k totalobjs = objects.size();
	offset_68k curuisquare;

	for(curuisquare = 0; curuisquare < totalobjs; curuisquare++) {
		if(in_bound_box(objects[curuisquare], touch)) {
			//send here
			dbgprintf("Object:%d has been pushed\n", curuisquare);

			//no checks are needed because only active objects are in the collision matrix
			switch(objects[curuisquare].objtype) {
			case frmControlObj:
				controleventhandler(objects[curuisquare].object, eventptr);
				return true;

			case frmGadgetObj: {
				osevent newevent;
				newevent.type = frmGadgetEnterEvent;
				newevent.data.push_back(objects[curuisquare].objid);
				newevent.data.push_back(objects[curuisquare].object);
				addnewevent(newevent);
			}

			return true;

			case frmFieldObj:
				fieldeventhandler(objects[curuisquare].object, eventptr);
				break;

			default:
				//unknown object
				palmabrt();
				break;
			}
		}

		/*  else{
			dbgprintf("Fail object:%d\n",curuisquare);
			}
		*/
	}

	return false;
}

void relaygadgetevent(offset_68k eventptr) {
	uint16_t evttype = get_word(eventptr);
	uint16_t targetobj = get_word(eventptr + evtDataOffset);

	if(evttype != frmGadgetEnterEvent && evttype != frmGadgetMiscEvent) {
		palmabrt();
	}

	size_t_68k totalobjs = objects.size();
	offset_68k curuisquare;

	for(curuisquare = 0; curuisquare < totalobjs; curuisquare++) {
		if(objects[curuisquare].objtype == frmGadgetObj && objects[curuisquare].objid == targetobj) {
			//found the target,now will it accept the event
			uint16_t attr = get_word(objects[curuisquare].object + 2);

			if(attr & bit(14)) { //has a callback //guaranteed to be visible because it is in the collision matrix
				offset_68k functionptr = get_long(objects[curuisquare].object + 16);
				CPU_pushlongstack(objects[curuisquare].object);
				CPU_pushwordstack(formGadgetHandleEventCmd);
				CPU_pushlongstack(eventptr);
				CPU_68kfunction(functionptr);
				//now remove the arguments of the 68k function call (10 bytes,4+2+4,int32_t/int16_t/int32_t) from stack
				CPU_cleanargsfromstack(10);
				dbgprintf("Sent event to gadget:%04x,Result:%08x\n", objects[curuisquare].objid, D0);
				return;
			}
			else {
				palmabrt();
			}
		}
	}

	palmabrt();
}

void relaycontrolevent(offset_68k eventptr) {
	uint16_t targetobj = get_word(eventptr + evtDataOffset);
	offset_68k targetptr = get_long(eventptr + evtDataOffset + 2);
	uint16_t evttype = get_word(eventptr);

	if(evttype != ctlEnterEvent && evttype != ctlExitEvent && evttype != ctlSelectEvent) {
		palmabrt();
	}

	size_t_68k totalobjs = objects.size();
	offset_68k curuisquare;

	for(curuisquare = 0; curuisquare < totalobjs; curuisquare++) {
		if(objects[curuisquare].objtype == frmControlObj && objects[curuisquare].objid == targetobj) {
			controleventhandler(targetptr, eventptr); //controlptr is only used for penDownEvent
			return;
		}
	}
}

void relayfieldevent(offset_68k eventptr) {
	uint16_t targetobj = get_word(eventptr + evtDataOffset);
	offset_68k targetptr = get_long(eventptr + evtDataOffset + 2);
	uint16_t evttype = get_word(eventptr);

	if(evttype != fldEnterEvent) {
		palmabrt();
	}

	size_t_68k totalobjs = objects.size();
	offset_68k curuisquare;

	for(curuisquare = 0; curuisquare < totalobjs; curuisquare++) {
		if(objects[curuisquare].objtype == frmFieldObj && objects[curuisquare].objid == targetobj) {
			fieldeventhandler(targetptr, eventptr); //controlptr is only used for penDownEvent
			return;
		}
	}
}



//object interaction/drawing

void fielddisassociateaddr(offset_68k field) {
	//just disasociate pointer and handle
	put_long(field + 12, 0); //char ptr
	put_long(field + 16, 0); //memhandle
	TEMPHACK;
	//may have to place cursor at end of text and recalculate word wrapping
}

void fieldappointtextaddr(offset_68k field, offset_68k handle, size_t_68k textsize, offset_68k textoffset) {
	if(handle == nullptr_68k) {
		fielddisassociateaddr(field);
		return;
	}

	uint16_t lengthinchars = strlen68k(handle);
	put_long(field + 12, handle); //char ptr
	put_long(field + 16, handle); //memhandle
	//put_long(field + 20,NULL);//lineinfotype
	put_word(field + 24, lengthinchars); //text length
	put_word(field + 26, textsize); //text block size
	//put_word(field + 28,strlen68k(handle));//max chars
	put_word(field + 30, 0); //firstchr
	put_word(field + 32, lengthinchars - 1); //lastchr
	//put_word(field + 34,textsize);//insert X position / char in line
	//put_word(field + 36,textsize);//insert Y position / line number
	TEMPHACK;
	//place cursor at end of text and recalculate word wrapping
}

void fieldappointtextptr(offset_68k field, offset_68k ptr) {
	if(ptr == nullptr_68k) {
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
	offset_68k mallocsize = getsizememaddr(ptr);
	fieldappointtextaddr(field, ptr, mallocsize, 0);
}

void fieldappointtexthandle(offset_68k field, offset_68k handle) {
	if(handle == nullptr_68k) {
		fielddisassociateaddr(field);
		return;
	}

	int mallocchk = memisalloc(handle);

	//validity checks
	if(mallocchk == -1) {
		palmabrt();
	}

	offset_68k mallocsize = getsizememaddr(handle);//malloclist[mallocchk].size;
	fieldappointtextaddr(field, handle, mallocsize, 0);
}

//to accomadate different type names ABMP,Tbmp,tAIB,tbmf,taif,PICT
//may or may not count tFBM,Tbsb (boot screen bitmap)
offset_68k getbitmap(uint16_t bmpid) {
	offset_68k bitmap = get_app_resource(bmpid, 'Tbmp');

	//if(!bitmap)bitmap = getappresource(bmpid,'PICT');
	if(bitmap) {
		return bitmap;
	}
	else {
		palmabrt();    //error
	}

	//add other type names
	return nullptr_68k;
}

offset_68k getcontrolobject(int type, uint16_t id) {
	switch(type) {
	//case buttonCtl:
	//	return getuiresource(id,'tBTN');
	default:
		dbgprintf("control object :%d: not done.\n", type);
		palmabrt();
		break;
	}

	return 0;
}

void drawcontrolobject(offset_68k window, offset_68k controlptr) {
	uint16_t id = get_word(controlptr);
	SQUARE area = get_square(controlptr + 2);
	offset_68k text = get_long(controlptr + 10);
	uint16_t attr = get_word(controlptr + 14);
	uint8_t style = get_byte(controlptr + 16);
	uint8_t fontid = get_byte(controlptr + 17);
	uint8_t group = get_byte(controlptr + 18);
	//ignore pad to word (controlptr + 19)

	if(attr & bit(15)) {
		if(attr & bit(14)) {
			addobjtocollisionmatrix(area, controlptr, frmControlObj, id);
		}
		else {
			//object grayed out/cant be touched
			palmabrt();//hack
		}

		switch(style) { //style/type of control
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
			dbgprintf("control object:%d not done.\n", style);
			palmabrt();
			break;
		}

		TEMPHACK;
		//draw
		//set visible to true
		put_word(controlptr + 14, attr | bit(13));
	}
}

void drawfield(offset_68k window, offset_68k fieldptr) {
	uint16_t id = get_word(fieldptr);//dev defined id
	SQUARE area = get_square(fieldptr + 2);
	uint16_t attr = get_word(fieldptr + 10);
	offset_68k textptr = get_long(fieldptr + 12);
	offset_68k texthandle = get_long(fieldptr + 16);
	offset_68k lineinfoptr = get_long(fieldptr + 20);
	uint16_t textlength = get_word(fieldptr + 24);
	uint16_t textblksize = get_word(fieldptr + 26);
	uint16_t maxchars = get_word(fieldptr + 28);
	uint16_t firstpos = get_word(fieldptr + 30);
	uint16_t lastpos = get_word(fieldptr + 32);
	uint16_t insptx = get_word(fieldptr + 34);
	uint16_t inspty = get_word(fieldptr + 36);
	uint8_t fontid = get_byte(fieldptr + 38);

	if(attr & bit(15)) {
		addobjtocollisionmatrix(area, fieldptr, frmFieldObj, id);
		dbgprintf("Field:%04x is useable\n", id);
		//uint16_t linestart = get_word(lineinfoptr);
		//uint16_t linelength = get_word(lineinfoptr + 2);
		dstptr = window;
		srcptr = textptr;

		if(srcptr == nullptr_68k) {
			srcptr = texthandle;
		}

		dststart = area.start;
		srcsize = textlength;
		text();
		//dsty += textlineheight;
		//dstendy += textlineheight;
		//prams = DOTTED;
		//line();
		//palmabrt();
		//set visible to true
		put_word(fieldptr + 10, attr | bit(14));
	}
}

TEMPHACK
void drawlist(offset_68k window, offset_68k listptr) {
	uint16_t id = get_word(listptr);
	SQUARE area = get_square(listptr + 2);
	uint16_t attr = get_word(listptr + 10);
	offset_68k itemlist = get_long(listptr + 12);//array of char pointers
	int16_t numitems = get_word(listptr + 16);
	int16_t currentitem = get_word(listptr + 18);
	int16_t topitem = get_word(listptr + 20);
	uint8_t fontid = get_byte(listptr + 22);
	//skip pad byte 23
	offset_68k popupwin = get_long(listptr + 24);
	offset_68k drawfunction = get_long(listptr + 28);//function pointer

	if(attr & bit(15)) {
		if(attr & bit(14)) {
			addobjtocollisionmatrix(area, listptr, frmListObj, id);
		}
		else {
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
		put_word(listptr + 10, attr | bit(13));
	}
}

void drawtable() {
	palmabrt();
}

TEMPHACK
void drawtitle(offset_68k window, offset_68k titleptr) {
	SQUARE area = get_square(titleptr);
	addobjtocollisionmatrix(area, titleptr, frmTitleObj, 0); //theres only one title
	//draw title/menu bar popup
}

//only called by frmdrawform (draws bitmap useing special form struct)
void drawbitmap(offset_68k window, offset_68k bmpptr) {
	//draw bitmap
	uint16_t attr = get_word(bmpptr);

	if(attr & bit(15)) {
		dststart = get_coord(bmpptr + 2);
		uint16_t bmpid = get_word(bmpptr + 6);
		dstptr = window;
		srcptr = getbitmap(bmpid);
		bitmap();
	}
}

void drawscrollbar() {
	palmabrt();
}

//only called by frmdrawform //labels dont handle or send events
void drawlabel(offset_68k window, offset_68k labelptr) {
	uint16_t id = get_word(labelptr);
	dstx = (int16_t)get_word(labelptr + 2);
	dsty = (int16_t)get_word(labelptr + 4);
	uint16_t attr = get_word(labelptr + 6);
	bool useable = (attr & bit(15));
	prams = get_byte(labelptr + 8);//fontid
	//ignore pad byte
	srcptr = get_long(labelptr + 10);//char ptr
	dstptr = window;
	drwcolor = get_byte(TEXTCOLOR);//hack //must use palette with an index
	dbgprintf("Label %s useable,attr:%04x,charptr:%08x\n", useable ? "IS" : "IS NOT", attr, srcptr);
	dbgprintf("X:%d,Y:%d,Text:%s\n", dstx, dsty, readstring(srcptr).c_str());
	srcsize = UNDEFINED;

	if(useable) {
		text();
	}
}

void drawgadget(offset_68k window, offset_68k gdtptr) {
	uint16_t id = get_word(gdtptr);//resource not dev defined id
	uint16_t attr = get_word(gdtptr + 2);
	SQUARE area = get_square(gdtptr + 4);
	offset_68k data = get_long(gdtptr + 12);
	offset_68k handler = get_long(gdtptr + 16);
	bool useable = (attr & bit(15));
	bool extended = (attr & bit(14));//has a handler
	//bool visible = (attr & bit(13));

	//offset_68k gdtres = getuiresource(id,'tGDT');

	if(useable) {
		addobjtocollisionmatrix(area, gdtptr, frmGadgetObj, id);

		//call custom handler
		if(extended && handler != nullptr_68k) { //has a callback
			CPU_pushlongstack(gdtptr);
			CPU_pushwordstack(formGadgetDrawCmd);
			CPU_pushlongstack(nullptr_68k);//no prams
			CPU_68kfunction(handler);
			//now remove the arguments of the 68k function call (10 bytes,4+2+4,int32_t/int16_t/int32_t) from stack
			CPU_cleanargsfromstack(10);
			dbgprintf("Gadget Function Pointer:%08x,Result:%d\n", handler, D0);
		}
	}
}

void placeformobj(offset_68k form, uint16_t index) {
	offset_68k objloc = get_long(form + 64) + index * 6;
	uint8_t type = get_byte(objloc);
	offset_68k objdataloc = get_long(objloc + 2);

	switch(type) {
	case frmFieldObj:
		drawfield(form, objdataloc);
		break;

	case frmControlObj:
		drawcontrolobject(form, objdataloc);
		break;

	case frmBitmapObj:
		drawbitmap(form, objdataloc);
		break;

	case frmLabelObj:
		drawlabel(form, objdataloc);
		break;

	case frmGadgetObj:
		drawgadget(form, objdataloc);
		break;

	case frmTitleObj:
		drawtitle(form, objdataloc);
		break;

	case frmListObj:
		drawlist(form, objdataloc);
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
		dbgprintf("\nType %d not implimented\n\n", type);
		palmabrt();
		break;
	}
}

void removeformobject(offset_68k form, uint16_t index) {
	offset_68k objloc = get_long(form + 64) + index * 6;
	uint8_t type = get_byte(objloc);
	offset_68k objdataloc = get_long(objloc + 2);
	disableobject(objdataloc, type);
}

void updateanddrawform(offset_68k form) {
	uint16_t attr = getformattr(form);//the enabled and dirty bits are unused by all os versions
	TEMPHACK;
	//backup pixels behind form if savebehind bit is set
	TEMPHACK;
	//display 'i' icon/button when helpid is set
	TEMPHACK;
	//check if form is modal (draw window border)

	//useable attribute may not be supported for forms
	if(!(attr & bit(15))) { //hack
		dbgprintf("Drawing inactive form.\n");
		palmabrt();
	}

	//clean up form framebuffer //may break some apps check os version before deleting
	offset_68k formbmp = get_win_bmp(form);
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
	uint16_t numobjects = getformnumobjects(form);

	//dbgprintf("Numobjs:%d,Formptr:%08x\n",numobjects,formptr);

	for(uint16_t count = 0; count < numobjects; count++) {
		placeformobj(form, count);
	}

	srcptr = get_win_bmp(form);
	dstptr = renderer.lcd_window;
	//dstptr = getwindisplaywindow(formptr);//resolution fix
	dstx = 0, dsty = 0;
	bitmap();
	//set visible to true
	setformattr(form, attr | bit(13));

	if(renderer.current_active_window != form) {
		//apparently palm sends winenter every time the form is drawn
		osevent enterevt;
		enterevt.type = winEnterEvent;
		enterevt.data.push_back(form);
		enterevt.data.push_back(renderer.current_active_window);
		addnewevent(enterevt);
		renderer.current_active_window = form;
		//current_draw_window = form;
		renderer.set_draw_window(form);
		//enabled flag in form window is unused in all os versions
	}
}
//end of object interaction/drawing






//event handlers
void formeventhandler(offset_68k formptr, offset_68k eventptr) {
	uint16_t evttype = get_word(eventptr);
	uint32_t handled = 0;

	switch(evttype) {
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
		if(relaytouchevent(eventptr)) {
			return;    //D0 == return value of objects event handler
		}
		else {
			/*  If the pen is within the bounds of the help icon,
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

	case frmCloseEvent: {
		//clean up form memory
		uint16_t frmid = get_word(eventptr + evtDataOffset);
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

void menueventhandler(offset_68k menubarptr, offset_68k eventptr, offset_68k errorptr) {
	uint32_t handled = 0;

	//only handles pen and key down events
	switch(get_word(eventptr)) {
	case penDownEvent:
		if(menubarptr == nullptr_68k) {
			break;    //tetris calls this function before loading the menubar
		}

		dbgprintf("MBARptr:%08x\n", menubarptr);
		palmabrt();//hack
		break;

	case keyDownEvent: {
		uint16_t vchr = get_word(eventptr + evtDataOffset + 2);

		if(vchr == vchrMenu) {
			palmabrt();//hack
			handled = 1;
		}
		else
			if(vchr == vchrCommand) {
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

	put_word(errorptr, errNone); //never sends an error,even on palm hardware
	D0 = handled;
}

TEMPHACK
void controleventhandler(offset_68k controlptr, offset_68k eventptr) {
	uint16_t evttype = get_word(eventptr);
	uint32_t handled = 0;

	switch(evttype) {
	//controls dont handle or send pen"Move/Up"Events
	case penDownEvent: {
		//check bounds and send ctlEnterEvent
		SQUARE bounds = get_square(controlptr + 2);
		COORD touch = get_coord(eventptr + 4);

		if(in_bound_box(bounds, touch)) {
			osevent controlenter;
			controlenter.type = ctlEnterEvent;
			controlenter.data.push_back(get_word(controlptr));//control id
			controlenter.data.push_back(controlptr);//control pointer
			addnewevent(controlenter);
			handled = 1;
		}
	}
	break;

	case ctlEnterEvent: {
		uint16_t ctlid = get_word(controlptr);
		uint16_t ctlidtest = get_word(eventptr + evtDataOffset);//verify that this is the correct control

		if(ctlidtest != ctlid) {
			palmabrt();    //hack
		}

		//offset_68k curcontrol = get_long(eventptr + evtDataOffset + 2);//the current control as specified by the event
		osevent ctlevent;
		SQUARE box = get_square(controlptr + 2);
		TEMPHACK;
		//change control color if button
		sendpenevents = false;
		COORD releasepoint = trackpen();//waits for pen release

		if(in_bound_box(box, releasepoint)) {
			ctlevent.type = ctlSelectEvent;
			ctlevent.data.push_back(ctlid);//control id
			ctlevent.data.push_back(controlptr);//control pointer
			ctlevent.data.push_back(true);//on 'pushed'
			ctlevent.data.push_back(0);//reserved field

			if(get_byte(controlptr + 16) == sliderCtl) {
				palmabrt();//hack
				//ctlevent.data.push_back(value);//value if slider else 0
			}
			else {
				ctlevent.data.push_back(0);//value if slider else 0
			}
		}
		else {
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

void fieldeventhandler(offset_68k fieldptr, offset_68k eventptr) {
	uint16_t evttype = get_word(eventptr);
	uint32_t handled = 0;

	switch(evttype) {
	case penDownEvent: {
		uint16_t fldid = get_word(fieldptr);
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

void listeventhandler(offset_68k listptr, offset_68k eventptr) {
	palmabrt();//hack
}

//no gadgeteventhandler(offset_68k eventptr), gadgets are program defined and have a callback for there event handler






//win functions
void wincreateoffscreenwindow() {
	stackword(width);
	stackword(height);
	stackbyte(winformat);//not used yet
	stackptr(errptr);
	TEMPHACK;
	//fix different format types
	uint16_t flags = bit(8) | bit(14);//free bitmap on delete & offscreen flags
	//if(winformat != 0)flags |= bit(15);
	offset_68k thisbmp = newbmpsimple(width, height, renderer.bpp);//global bpp of display
	//offset_68k thisbmp = newbmpsimple(width,height,16);//global bpp of display
	//offset_68k thisdrawstate = newdrawstate();
	offset_68k retval = newwindow(width, height, flags, 0, thisbmp, renderer.draw_state, 0);
	//dbgprintf("Win addr:%08x,Real addr:%016lx\n",retval,get_real_address(thisbmp + 16));
	put_word(errptr, errNone);
	A0 = retval;
}

TEMPHACK
void wincreatebitmapwindow() {
	stackptr(bmpptr);
	stackptr(errptr);//uint16_t
	TEMPHACK;
	//check for sysErrParamErr
	/*  The bitmap must be uncompressed and it must
		have a valid pixel size (1, 2, 4, or 8).
		It must not be the screen bitmap.*/
	offset_68k bmpwindow = newwindow(get_word(bmpptr), get_word(bmpptr + 2),/*flags*/0,
	                                 /*frameflags*/0, bmpptr, renderer.draw_state,/*nextwindowptr*/0);
	A0 = bmpwindow;
}

void windeletewindow() {
	stackptr(winhandle);
	stackbool(erase);

	if(erase) {
		uint16_t flags = get_word(winhandle + 8);

		//free bitmap if flag set
		if(flags & bit(8)) {
			freememaddr(get_win_bmp(winhandle));
		}

		freememaddr(winhandle);
		//maybe more
	}

	TEMPHACK;
	//remove from window list
	//no return value
}

void wineraserectangle() {
	stackptr(rectptr);
	stackword(cornerrnd);
	SQUARE square = get_square(rectptr);

	if(cornerrnd == 0) {
		UG_FillFrame(square.start.x, square.start.y, square.end.x, square.end.y, renderer.color_palette[get_byte(BACKCOLOR)]);
	}
	else {
		UG_FillRoundFrame(square.start.x, square.start.y, square.end.x, square.end.y, cornerrnd, renderer.color_palette[get_byte(BACKCOLOR)]);
	}

	//no return value
}

void windrawrectangle() {
	stackptr(rectptr);
	stackword(cornerrnd);
	SQUARE square = get_square(rectptr);

	if(cornerrnd == 0) {
		UG_FillFrame(square.start.x, square.start.y, square.end.x, square.end.y, renderer.color_palette[get_byte(FORECOLOR)]);
	}
	else {
		UG_FillRoundFrame(square.start.x, square.start.y, square.end.x, square.end.y, cornerrnd, renderer.color_palette[get_byte(FORECOLOR)]);
	}

	//no return value
}

void windrawrectangleframe() {
	stackword(frametype);
	stackptr(rectptr);
	SQUARE square = get_square(rectptr);
	UG_DrawFrame(square.start.x, square.start.y, square.end.x, square.end.y, renderer.color_palette[get_byte(FORECOLOR)]);
	TEMPHACK;
	//draw frame with custom frametype
	//no return value
}

void windrawbitmap() {
	stackptr(bmpptr);
	stackword(x);
	stackword(y);

	if(bmpptr & 1) {
		dbgprintf("Bmp not word aligned!!!\n");
	}

	if(bmpptr == nullptr_68k) {
		dbgprintf("Bmp not at ptr!!!\n");
	}

	dstx = x;
	dsty = y;
	srcptr = bmpptr;
	dstptr = renderer.get_draw_window();
	bitmap();
	//no return value
}

void windrawpixel() {
	stackword(x);
	stackword(y);
	UG_DrawPixel(x, y, renderer.color_palette[get_byte(FORECOLOR)]);
	//no return value
}

void winscreenmode() {
	stackbyte(operand);
	stackptr(widthptr);//ptr to uint32_t
	stackptr(heightptr);//ptr to uint32_t
	stackptr(bppptr);//ptr to uint32_t
	stackptr(colenableptr);//ptr to bool
	//only winScreenModeGetSupportedDepths uses bit position(1 << 16) instead of value(0x10 or 16) for bppptr
	//all others use a decimal value
	D0 = errNone;

	switch(operand) {
	case winScreenModeGet:
		putlongifvptr(widthptr, renderer.width);
		putlongifvptr(heightptr, renderer.height);
		putlongifvptr(bppptr, renderer.bpp);
		putbyteifvptr(colenableptr, renderer.color);
		dbgprintf("getscreenmode\n");
		return;

	case winScreenModeGetDefaults:
		putlongifvptr(widthptr, LCDW);
		putlongifvptr(heightptr, LCDH);
		putlongifvptr(bppptr, LCDBPP);
		putbyteifvptr(colenableptr, LCDHASCOLOR);
		dbgprintf("getdefaultscreenmode\n");
		return;

	case winScreenModeSet: {
		uint32_t resultw = renderer.width;
		uint32_t resulth = renderer.height;
		uint32_t resultbpp = renderer.bpp;
		bool resultcolor = renderer.color;

		if(widthptr) {
			resultw = get_long(widthptr);
		}

		if(heightptr) {
			resulth = get_long(heightptr);
		}

		if(bppptr) {
			resultbpp = get_long(bppptr);
		}

		if(colenableptr) {
			resultcolor = get_byte(colenableptr);
		}

		if(resultw == 0 || resultw > LCDW) {
			//invalid screen size
			palmabrt();//hack
		}

		if(resulth == 0 || resulth > LCDH) {
			//invalid screen size
			palmabrt();//hack
		}

		if(resultbpp == 0 || resultbpp > LCDMAXBPP) {
			//invalid screen depth
			palmabrt();//hack
		}

		if(resultcolor && resultbpp < 4) { //4bit color works too
			//color needs higher depth
			palmabrt();//hack
		}

		//set screen format
		if(widthptr) {
			renderer.width = resultw;
		}

		if(heightptr) {
			renderer.height = resulth;
		}

		if(bppptr) {
			renderer.bpp = resultbpp;
		}

		if(colenableptr) {
			renderer.color = resultcolor;
		}

		dbgprintf("setscreenmode Width:%d,Height:%d,BPP:%d,Color:%d\n", renderer.width, renderer.height, renderer.bpp, renderer.color);
	}

	return;

	case winScreenModeSetToDefaults:
		renderer.width = LCDW;
		renderer.height = LCDH;
		renderer.bpp = LCDBPP;
		renderer.color = LCDHASCOLOR;
		dbgprintf("setdefaultscreenmode\n");
		return;

	case winScreenModeGetSupportsColor:
		if(colenableptr == nullptr_68k) {
			palmabrt();    //hack //this function requires color mode pointer
		}

		if(get_long(bppptr) >= 4) {
			put_byte(colenableptr, true);
		}

		dbgprintf("supportscolor Bpp:%d\n", get_long(bppptr));
		return;

	case winScreenModeGetSupportedDepths:
		if(bppptr) {
			TEMPHACK;
			//some apps may try to use 24/32 bit color (This is not supported but may work with dithering!);
			uint32_t modes;

			if(colenableptr) {
				//hack //4bit mode may or may not support color
				if(get_byte(colenableptr)/*must support color*/) {
					//modes = (bit(31) | bit(23)) | (bit(15) | bit(7) | bit(3));
					modes = (bit(15) | bit(7) | bit(3));
				}
				else {
					//modes = (bit(31) | bit(23)) | (bit(15) | bit(7) | bit(3) | bit(1) | bit(0));
					modes = (bit(15) | bit(7) | bit(3) | bit(1) | bit(0));
				}
			}
			else {
				//palmabrt();//hack //this function requires color mode pointer
				//just list all supported depths
				//modes = (bit(31) | bit(23)) | (bit(15) | bit(7) | bit(3) | bit(1) | bit(0));
				modes = (bit(15) | bit(7) | bit(3) | bit(1) | bit(0));
			}

			put_long(bppptr, modes);
		}
		else {
			palmabrt();    //hack
		}

		dbgprintf("supporteddepths\n");
		return;

	default:
		dbgprintf("Unknown command:%d\n", operand);
		D0 = sysErrParamErr;
		palmabrt();//hack
		return;
	}
}

void winscreenlock() {
	stackbyte(locktype);

	//palmabrt();//hack

	if(renderer.screen_lock_count == 0) {
		//copy screen / erase it with locktype
		switch(locktype) {
		case winLockCopy:
			//clone old framebuffer
			memcpy68k(lcd_start + LCDBYTES, lcd_start, LCDBYTES);
			break;

		case winLockErase:
			//white out new framebuffer
			memset68k(lcd_start + LCDBYTES, 0xFF, LCDBYTES);
			break;

		case winLockDontCare:
			//do nothing
			break;

		default:
			palmabrt();
			break;
		}

		setdisplayaddr(lcd_start + LCDBYTES);//second display buffer
	}
	else {
		dbgprintf("err unexpected double display lock.\n");
		palmabrt();
	}

	renderer.screen_lock_count++;
	D0 = lcd_start + LCDBYTES;
}

void winscreenunlock() {
	//no params
	if(renderer.screen_lock_count == 0) {
		dbgprintf("err unexpected double display unlock.\n");
		palmabrt();
	}

	if(renderer.screen_lock_count > 0) {
		renderer.screen_lock_count--;
	}

	if(renderer.screen_lock_count == 0) {
		//copy over old buffer
		memcpy68k(lcd_start, lcd_start + LCDBYTES, LCDBYTES);
		//set oslcdwindow
		setdisplayaddr(lcd_start);
	}

	//no return value
}

void wingetbitmap() {
	stackptr(window);
	A0 = get_win_bmp(window);
}

void winsetforecolor() {
	stackbyte(col);
	D0 = get_byte(FORECOLOR);
	put_byte(FORECOLOR, col);
}

void winsetbackcolor() {
	stackbyte(col);
	D0 = get_byte(BACKCOLOR);
	put_byte(BACKCOLOR, col);
}

void winsettextcolor() {
	stackbyte(col);
	D0 = get_byte(TEXTCOLOR);
	put_byte(TEXTCOLOR, col);
}

void wingetdisplaywindow() {
	A0 = renderer.lcd_window;
}

void wingetdrawwindow() {
	A0 = renderer.get_draw_window();
}

void winsetdrawwindow() {
	stackptr(winptr);
	//dbgprintf("Old Addr:%08x,New Addr:%08x\n",currentdrawwindow,winptr);
	A0 = renderer.get_draw_window();

	if(winptr) {
		renderer.set_draw_window(winptr);    //current_draw_window = winptr;
	}
	else {
		dbgprintf("Cant set drawwindow to nullptr_68k,Setting to oslcdwindow"
		          "(this is not supported above palm os 3.0)\n");//hack
		//current_draw_window = os_lcd_window;
		renderer.set_draw_window(renderer.lcd_window);
		//palmabrt();//hack
	}
}

void winsetactivewindow() {
	stackptr(dstwindow);

	if(dstwindow) {
		newwindowptr = dstwindow;
	}
	else {
		dbgprintf("Cant set activewindow to nullptr_68k,Setting to oslcdwindow"
		          "(this is not supported above palm os 3.0)\n");//hack
		newwindowptr = renderer.lcd_window;
		palmabrt();//hack
	}

	changewindow = true;
	//sendwinenterondraw = false;
	//set enable flag in window
	uint16_t flags = get_word(dstwindow + 8);
	put_word(dstwindow + 8, flags | bit(10));
	//no return value
}

void winsetclip() {
	stackword(startx);
	stackword(starty);
	stackword(endx);
	stackword(endy);
	offset_68k clipptr = get_win_clipping(renderer.get_draw_window());
	put_word(clipptr, startx);
	put_word(clipptr + 2, starty);
	put_word(clipptr + 4, endx);
	put_word(clipptr + 6, endy);
	//no return value
}

void windrawchars() {
	stackptr(chrsptr);
	stackword(length);
	stackword(thisx);
	stackword(thisy);
#if 0
	TEMPHACK;

	if((int16_t)thisx < 0 || (int16_t)thisy < 0) {
		return;
	}

	dbgprintf("%d chars to print.\n", length);
	dbgprintf("Chars:%s\n", readstring(chrsptr).c_str()); //HACK use length if given
	dstptr = renderer.get_draw_window();
	dstx = thisx;
	dsty = thisy;
	srcsize = (int16_t)length;
	srcptr = chrsptr;
	drwcolor = get_byte(TEXTCOLOR);
	text();
#endif
	TEMPHACK;
	//no return value
}

void winresetclip() {
	uint16_t winw = get_word(renderer.get_draw_window());
	uint16_t winh = get_word(renderer.get_draw_window() + 2);
	offset_68k clip = get_win_clipping(renderer.get_draw_window());
	put_word(clip, 0);
	put_word(clip + 2, 0);

	if(winw < LCDW) {
		put_word(clip + 4, winw);
	}
	else {
		put_word(clip + 4, LCDW);
	}

	if(winh < LCDH) {
		put_word(clip + 6, winh);
	}
	else {
		put_word(clip + 6, LCDH);
	}

	//no return value
}

void wincopyrectangle() {
	stackptr(src_win);
	stackptr(dst_win);
	stackptr(src_rect);
	stackword(x);
	stackword(y);
	stackbyte(mode);

	/*
		offset_68k src_data;
		offset_68k dst_data;
		SQUARE area = get_square(src_rect);

		//get_bmp_row_bytes(get_win_bmp(offset_68k winptr));

		if(src_win)src_data = get_win_data(src_win);
		else src_data = get_win_data(renderer.get_draw_window());

		if(dst_win)dstdata = get_win_data(dst_win);
		else dst_data = get_win_data(renderer.get_draw_window());

		for(uint32_t y = area.start.y;y < area.end.y;y++){
		for(uint32_t x = area.start.x;x < area.end.x;x++){

		}
		}
	*/

	if(src_win) {
		srcptr = src_win;
	}
	else {
		srcptr = renderer.get_draw_window();
	}

	if(dst_win) {
		dstptr = dst_win;
	}
	else {
		dstptr = renderer.get_draw_window();
	}

	srcsquare = get_square(src_rect);
	dstx = x;
	dsty = y;

	switch(mode) {
		//unknown
		TEMPHACK;

	default:
		break;
	}

	copyrectangle();
	//no return value
}

void winpalette() {
	stackbyte(operation);
	stackword(startindex);
	stackword(paletteentrys);
	stackptr(userpalarray);

	//winErrPalette if no colortable
	if(userpalarray == nullptr_68k && operation != winPaletteSetToDefault) {
		dbgprintf("top robin premium dirt noodles.\n");
	}

	offset_68k winpal = getwinpalette(renderer.get_draw_window());

	switch(operation) {
	case winPaletteGet:
		memcpy68k(userpalarray, winpal + startindex * 4, (int16_t)paletteentrys * 4);
		break;

	case winPaletteSet:
		memcpy68k(winpal + startindex * 4, userpalarray, (int16_t)paletteentrys * 4);
		break;

	case winPaletteSetToDefault:
		uint16_t rabbid;

		for(rabbid = 0; rabbid < paletteentrys; rabbid++) {
			put_long(winpal + (startindex + rabbid) * 4, paltorgbindex8(rabbid));
		}

		break;
	}

	//may need to send an event
	//osevent palettechangeevt;
	//palettechangeevt.type = sysNotifyDisplayChangeEvent
	D0 = errNone;
}

void winrgbtoindex() {
	stackptr(rgbcolor);
	uint8_t red = get_byte(rgbcolor + 1);
	uint8_t green = get_byte(rgbcolor + 2);
	uint8_t blue = get_byte(rgbcolor + 3);
	uint8_t bestindex = 0;
	offset_68k clut = getwinpalette(renderer.get_draw_window());
	uint16_t tablesize = getwinpalettenumentrys(renderer.get_draw_window());
	TEMPHACK;
	//get bpp and compare indicies properly
	offset_68k count;

	if(clut == nullptr_68k || tablesize == 0) {
		uint8_t bpp = get_bmp_bpp(get_win_bmp(renderer.get_draw_window()));
		bestindex = getbestdefaultindex(red, green, blue, bpp);
	}
	else {
		uint16_t closeness = 0xFFFF;//the bigger the more diffrence
		offset_68k curcolor = clut;

		for(count = 0; count < tablesize; count++) {
			uint16_t thisdiff = get_rgb_diff(red, green, blue, get_byte(curcolor + 1), get_byte(curcolor + 2), get_byte(curcolor + 3));

			if(thisdiff < closeness) {
				closeness = thisdiff;
				bestindex = get_byte(curcolor);
			}

			curcolor += 4;
		}
	}

	D0 = bestindex;//IndexedColorType (uint8_t/uint8)
	dbgprintf("TableSize:%d,BestIndex:%d,Red:%d,Green:%d,Blue:%d\n", tablesize, D0, red, green, blue);
}

void winpushdrawstate() {
	offset_68k curdrwstate = getwindrawstate(renderer.get_draw_window());
	offset_68k newdrwptr = getfreeheap(44);
	drawstates.push_back(curdrwstate);
	memcpy68k(newdrwptr, curdrwstate, 44);
	setwindrawstate(renderer.get_draw_window(), newdrwptr);
	//no return value
}

TEMPHACK
//free now unused drawstate
void winpopdrawstate() {
	setwindrawstate(renderer.get_draw_window(), drawstates.back());
	drawstates.pop_back();
	//no return value
}

void wingetdisplayextent() {
	stackptr(returnx);
	stackptr(returny);
	put_word(returnx, LCDW);
	put_word(returny, LCDH);
	//no return value
}

TEMPHACK
void winerasewindow() {
	//this function does not erase the border
	//UG_FillScreen(active_color_palette[get_byte(BACKCOLOR)]);
	//no return value
}

void windrawline() {
	stackword(start_x);
	stackword(start_y);
	stackword(end_x);
	stackword(end_y);
	UG_DrawLine(start_x, start_y, end_x, end_y, renderer.color_palette[get_byte(FORECOLOR)]);
	//no return value
}

void winerasepixel() {
	stackword(x);
	stackword(y);
	UG_DrawPixel(x, y, renderer.color_palette[get_byte(BACKCOLOR)]);
	//no return value
}

TEMPHACK
void winpaintbitmap() {
	stackptr(bmpptr);
	stackword(x);
	stackword(y);

	if(bmpptr & 1) {
		dbgprintf("Bmp not word aligned!!!\n");
	}

	if(bmpptr == nullptr_68k) {
		dbgprintf("Bmp not at ptr!!!\n");
	}

	switch(get_byte(XFERTYPE)) {
	case winPaint:
	case winOverlay:
	case winSwap://(from api docs) winSwap:If the source is a bitmap, then the bitmap is transferred using winPaint mode instead.
		//draw normaly
		dstx = x;
		dsty = y;
		srcptr = bmpptr;
		dstptr = renderer.get_draw_window();
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
void winscreengetattribute() {
	stackbyte(attr);
	stackptr(resultptr);
	D0 = errNone;

	switch(attr) {
	case winScreenWidth:
		put_long(resultptr, LCDW);
		return;

	case winScreenHeight:
		put_long(resultptr, LCDH);
		return;

	case winScreenDepth:
		put_long(resultptr, LCDBPP);
		return;

	case winScreenDensity:
		TEMPHACK;
		//set on emu bootup
		//put_long(resultptr,kDensityQuadruple);
		put_long(resultptr, kDensityDouble);
		//palmabrt();//hack
		return;
		TEMPHACK;

	//more conditions to implement

	default:
		dbgprintf("Attr:%d failed\n", attr);
		palmabrt();//hack
		D0 = sysErrParamErr;
		return;
	}
}

//not in trap table (HighDensityDispatch)
void wingetcoordinatesystem() {
	D0 = get_word(COORDSYS);
}

//not in trap table (HighDensityDispatch)
void winsetcoordinatesystem() {
	stackword(newcoordsys);
	D0 = get_word(COORDSYS);//old coord sys
	put_word(COORDSYS, newcoordsys);
}



//bmp functions
void bmpgetbits() {
	stackptr(bmpptr);
	A0 = get_bmp_data(bmpptr);
}

void bmpbitssize() {
	stackptr(bmpptr);
	uint16_t flags = get_word(bmpptr + 6);

	//compressed
	if(flags & bit(15)) {
		uint8_t version = get_byte(bmpptr + 9);
		offset_68k cmpdata = get_bmp_data(bmpptr);

		switch(version) {
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
void bmpgetdensity() {
	stackptr(bmpptr);
	uint8_t version = get_byte(bmpptr + 9);

	if(version < 3) {
		D0 = kDensityLow;
	}
	else {
		D0 = get_word(bmpptr + 14);    //density
	}
}

void bmpcreate() {
	stackword(uw);
	stackword(uh);
	stackbyte(bpp);//hack //normal is byte
	stackptr(colortable);
	stackptr(err);//return uint16_t
	int16_t w = (int16_t)uw, h = (int16_t)uh; //sign change
	dbgprintf("W:%d,H:%d,Bpp:%d\n", w, h, bpp);

	if(w == 0 || h == 0) {
		put_word(err, sysErrParamErr);
		A0 = nullptr_68k;
		return;
	}

	switch(bpp) {
	case 16:
	case 8:
	case 4:
	case 2:
	case 1:
		break;

	default:
		put_word(err, sysErrParamErr);
		A0 = nullptr_68k;
		return;
	}

	bool hastable = (colortable != nullptr_68k);
	offset_68k newbitmap = newbmp(w, h, bpp, false, 0, hastable, colortable);
	//palm sets all pixels to white
	//get clear params
	uint32_t rowbytes = (w * bpp) / 8;//full bytes in row
	bool leftoverbyte = (((w * bpp) % 8) != 0);//has byte with unused data on end(since all rows are byte aligned)

	if(leftoverbyte) {
		rowbytes += 1;
	}

	//clear bitmap to white
	if(bpp == 1) {
		memset68k(get_bmp_data(newbitmap), 0x00, rowbytes * h);    //black and white are swapped in 1bpp mode
	}
	else {
		memset68k(get_bmp_data(newbitmap), 0xFF, rowbytes * h);
	}

	put_word(err, errNone);
	A0 = newbitmap;
}

TEMPHACK
//may not be fully working
//not in trap table (HighDensityDispatch)
void bmpcreatebitmapv3() {
	stackptr(bmpv2ptr);
	stackword(density);
	stackptr(dataptr);//data to copy to the finished bitmap
	stackptr(coltblptr);//color table to use if bpp <= 8
	uint16_t v2flags = get_word(bmpv2ptr + 6);

	//palm os cant handle compressed bitmaps with this function
	if(v2flags & bit(15)) {
		palmabrt();    //hack
	}

	offset_68k bmpv3out = getfreeheap(100);//hack //dont know correct size
	/*
		put_word(bmpv3out,get_word(bmpv2ptr));//width
		put_word(bmpv3out + 2,get_word(bmpv2ptr + 2));//height
		put_word(bmpv3out + 4,get_word(bmpv2ptr + 4));//rowbytes
		put_word(bmpv3out + 6,get_word(bmpv2ptr + 6));//flags
		put_byte(bmpv3out + 8,get_byte(bmpv2ptr + 8));//pixelsize
	*/
	uint8_t v2bpp = get_byte(bmpv2ptr + 8);
	uint8_t v2clearindex = get_byte(bmpv2ptr + 12);
	memcpy68k(bmpv3out, bmpv2ptr, 9);
	put_byte(bmpv3out + 9, 3); //version
	//size of bitmapv3type in bytes (may or may not contain implimentation defined data pointer)
	put_byte(bmpv3out + 10, 24);

	if(v2bpp == 16) {
		put_byte(bmpv3out + 11, pixelFormat565);    //pixel format
	}
	else
		if(v2bpp < 16) {
			put_byte(bmpv3out + 11, pixelFormatIndexed);
		}
		else {
			palmabrt();    //hack
		}

	put_byte(bmpv3out + 12, 0); //unused
	put_byte(bmpv3out + 13, 0); //compression type (this == 0 when compressed not set)

	if(density != 0) {
		put_word(bmpv3out + 14, density); //density
		dbgprintf("Density:%d\n", density); //hack
	}
	else {
		put_word(bmpv3out + 14, kDensityLow);
	}

	put_long(bmpv3out + 16, v2clearindex); //transparent index
	put_long(bmpv3out + 20, 0); //nextbitmapoffset //0 since it cant be part of a family
	/*
		//copy dataptr data into new bitmap
		int16_t width = get_word(bmpv2ptr);
		int16_t height = get_word(bmpv2ptr + 2);
		uint16_t rowbytes = get_word(bmpv2ptr + 4);

		size_t_68k datasize = rowbytes * height;

		memcpy
	*/
	/*  bitmapv3type structures dont store any data they just have pointers
		to it, this is given away by the bmpcreatbitmapv3() api definition
		stating that if the data pointer passed to it is to storage ram that
		the bitmap must be read only because blitting to it would cause an
		error.*/
	const uint16_t flgmask = bit(13)/*hasclear*/ | bit(10)/*directcolor*/ | bit(8)/*nodither*/;
	uint16_t v3flags = (v2flags & flgmask) | bit(12)/*indirectdata*/;

	if(coltblptr) {
		v3flags |= bit(14)/*hascoltbl*/ | bit(9)/*indirectcoltbl*/;
		put_long(bmpv3out + 24, coltblptr);
		put_long(bmpv3out + 28, dataptr);
	}
	else {
		put_long(bmpv3out + 24, dataptr);
	}

	put_word(bmpv3out + 6, v3flags);
	A0 = bmpv3out;
}

void bmpgetdimensions() {
	stackptr(bitmap);
	stackptr(width);
	stackptr(height);
	stackptr(rowbytes);

	if(bitmap == nullptr_68k) {
		palmabrt();    //hack
	}

	putwordifvptr(width, get_word(bitmap));
	putwordifvptr(height, get_word(bitmap + 2));
	putwordifvptr(rowbytes, get_word(bitmap + 4));
	//no return value
}



//fonts
void fntsetfont() {
	stackbyte(newfont);
	/*
		offset_68k drwstate = getwindrawstate(currentactivewindow);
		D0 = get_byte(drwstate + 3);
		put_byte(drwstate + 3,newfont);
	*/
	D0 = get_byte(FONTID);
	put_byte(FONTID, newfont);
	dbgprintf("font id:%d\n", newfont);
	offset_68k newfntptr = getfontaddr(newfont);
	currentfont.setactivefont(newfntptr);
	put_long(FONTPTR, newfntptr);
	//TEMPHACK;
	//set pointer
	/*
		if(newfont >= fntAppFontCustomBase){

		}
	*/
}

TEMPHACK
void fntcharswidth() {
	stackptr(chrarray);
	stackword(length);
	D0 = (length * 1/*fix this*/) + ((length - 1) * 1/*fix this*/);//hack
	/*
		stackptr(chrarray);
		stackword(ulength);
		int16_t length = (int16_t)ulength;
		int16_t pixellength = 0;
		int16_t cnt;
		inc_for(cnt,length){
		pixellength += getcharwidth(get_byte(chrarray + cnt));
		//hack ,add spacing inbetween letters if not multi byte character
		}
		D0 = pixellength;
	*/
}

void fntgetfontptr() {
	A0 = get_long(FONTPTR);
}



//forms
void frmgotoform() {
	stackword(frmid);

	if(anyformsopen) {
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

void frmgetformptr() {
	stackword(frmid);
	A0 = getopenform(frmid);
}

void frmgetwindowhandle() {
	stackptr(handle);
	A0 = handle;
}

void frmdispatchevent() {
	stackptr(eventptr);
	uint16_t event = get_word(eventptr);
	offset_68k frmptr;

	switch(event) {
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

	if(event != 0) {
		dbgprintf("Evtnum:%d,Frmid:%04x,FrmPtr:%08x\n", event, get_word(eventptr + evtDataOffset), frmptr);
	}

	//custom event handler
	offset_68k functionptr = getformeventhandler(frmptr);

	if(functionptr != nullptr_68k) {
		CPU_pushlongstack(eventptr);
		CPU_68kfunction(functionptr);
		//now remove eventptr(the argument of the 68k function call) from stack
		CPU_cleanargsfromstack(4);

		//dbgprintf("Result:%08x\n",D0);//HACK

		if(D0 != 0) {
			return;
		}
	}
	else {
		palmabrt();    //hack //fatal error
	}

	dbgprintf("Not handled by custom event handler.\n");
	formeventhandler(frmptr, eventptr);
}

void frmhandleevent() {
	stackptr(formptr);
	stackptr(eventptr);
	formeventhandler(formptr, eventptr);
}

void frminitform() {
	stackword(resid);
	dbgprintf("ResID:%04x\n", resid);
	A0 = decompressform(resid);

	if(A0 == nullptr_68k) {
		palmabrt();
	}

	//TEMPHACK;
	//form id not resource id
	setopenform(frmid, A0);
}

void frmdeleteform() {
	stackptr(formptr);
	releaseformmemory(formptr);
	//no return value
}

void frmcloseallforms() {
	//no params
	for(int32_t scan = openformids.size() - 1; scan >= 0; scan--) {
		osevent closeevt;
		closeevt.type = frmCloseEvent;
		closeevt.data.push_back(openformids[scan]);
		addnewevent(closeevt);
		freeopenform(openformids[scan]);
	}

	//no return value
}

void frmsetactiveform() {
	stackptr(formptr);
	dbgprintf("FormPtr:%08x\n", formptr);
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

void frmgetactiveform() {
	A0 = activeformptr;
}

void frmgetactiveformid() {
	D0 = activeform;
}

void frmseteventhandler() {
	stackptr(formptr);
	stackptr(functionptr);
	setformeventhandler(formptr, functionptr);
	dbgprintf("Evt handler:%08x,FormPtr:%08x\n", functionptr, formptr);
	//no return value
}

void frmsettitle() {
	stackptr(formptr);
	stackptr(chrptr);
	uint16_t frmid = getformid(formptr);
	uint16_t attr = getformattr(formptr);
	dbgprintf("Formptr:%08x,New Title:%08x\n", formptr, chrptr);
	offset_68k formobjlist = getformobjlist(formptr);
	offset_68k titleobj = nullptr_68k;
	uint16_t thisnumobjects = getformnumobjects(formptr);

	for(uint16_t count = 0; count < thisnumobjects; count++) {
		if(get_byte(formobjlist + count * 6) == frmTitleObj) {
			titleobj = get_long(formobjlist + count * 6 + 2);
			break;
		}
	}

	if(titleobj) {
		put_long(titleobj + 8, chrptr);
	}
	else {
		dbgprintf("bunny phlem\n");
		palmabrt();
	}

	//TEMPHACK;
	//if visible needs to redraw title
	if((attr & 0xA000) == 0xA000) { //0xA000 == (useable | visible)
		osevent newtitle;
		newtitle.type = frmUpdateEvent;
		newtitle.data.push_back(frmid);
		newtitle.data.push_back(frmRedrawUpdateCode);
		addnewevent(newtitle);
	}

	//no return value
}

void frmdrawform() {
	stackptr(formptr);
	updateanddrawform(formptr);
	dbgprintf("ACTwin:%08x,DRAWwin:%08x,Thisform:%08x\n", renderer.current_active_window, renderer.get_draw_window(), formptr);
	//no return value
}

TEMPHACK
//draw every thing and do it correctly
void frmcustomalert() {
	stackword(resourcenum);
	stackptr(str1);
	stackptr(str2);
	stackptr(str3);
	dbgprintf("Custom alert!\n");

	if(str1) {
		dbgprintf("S1:%s\n", readstring(str1).c_str());
	}

	if(str2) {
		dbgprintf("S2:%s\n", readstring(str2).c_str());
	}

	if(str3) {
		dbgprintf("S3:%s\n", readstring(str3).c_str());
	}

	sendpenevents = false;
	offset_68k alert = get_ui_resource(resourcenum, 'Talt');
	uint16_t alertype = get_word(alert);
	uint16_t helprscid = get_word(alert + 2);
	uint16_t numbuttons = get_word(alert + 4);
	uint16_t defaultbutton = get_word(alert + 6);
	offset_68k accessptr = alert + 8;
	std::vector<std::string> alerttext(2);
	//string* alerttext = new string[2];
	alerttext[0] = readstring(accessptr);
	accessptr += alerttext[0].size() + 1;
	alerttext[1] = readstring(accessptr);
	accessptr += alerttext[1].size() + 1;
	std::vector<std::string> buttontext(numbuttons);

	//string* buttontext = new string[numbuttons];
	for(uint16_t count = 0; count < numbuttons; count++) {
		buttontext[count] = readstring(accessptr);
		accessptr += buttontext[count].size() + 1;
	}

	dbgprintf("%s\n,%s\n,%s\n,%s\n", alerttext[0].c_str(), alerttext[1].c_str(), buttontext[0].c_str(), buttontext[1].c_str());
	uint16_t result;
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
	int16_t btngap = 5 * LCDDENSITY;//hack //find real gap
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

	for(uint16_t count = 0; count < numbuttons; count++) {
		buttonbounds[count] = btnloc;
		drawbutton(btnloc);
		btnloc.start.x += btnloc.size.w + btngap;
		btnloc.end.x += btnloc.size.w + btngap;
	}

	//finished drawing
	//wait
	bool done = false;
	uint16_t button;
	COORD pressloc;
	COORD releaseloc;

	while(true) {
		m68k_handle_changes();
		pressloc = waitforpen();

		for(button = 0; button < numbuttons; button++) {
			if(in_bound_box(buttonbounds[button], pressloc)) {
				//change button color
				releaseloc = trackpen();

				if(in_bound_box(buttonbounds[button], releaseloc)) {
					//change button color
					done = true;
					result = button;
				}
			}

			if(done) {
				break;
			}
		}

		if(done) {
			break;
		}
	}

	sendpenevents = true;
	restoreframe();
	D0 = result;
}

void frmalert() {
	stackword(id);
	uint16_t button = 0;
	offset_68k alert = get_ui_resource(id, 'Talt');
	uint16_t alerttype = get_word(alert);
	uint16_t helprsc = get_word(alert + 2);
	uint16_t numbuttons = get_word(alert + 4);
	uint16_t defaultbutton = get_word(alert + 6);
	offset_68k string1 = alert + 8;
	offset_68k string2 = string1 + strlen68k(string1) + 1;
	offset_68k string3 = string2 + strlen68k(string2) + 1;
	dbgprintf("AlertName:%s,AlertText:%s,String3:%s\n", readstring(string1).c_str(),
	          readstring(string2).c_str(), readstring(string3).c_str());
	//draw alert
	D0 = button;
}

void frmgetobjectindex() {
	stackptr(form);
	stackword(objid);//not resource id
	uint16_t formobjnum = getformnumobjects(form);

	for(uint16_t count = 0; count < formobjnum; count++) {
		if(getformobjid(form, count) == objid) {
			D0 = count;
			return;
		}
	}

	D0 = frmInvalidObjectId;
}

void frmsetgadgethandler() {
	stackptr(form);
	stackword(gadgetindex);
	stackptr(handler);
	offset_68k gadget = getformobjloc(form, gadgetindex);
	setgadgethandler(gadget, handler);
	//no return value
}

void frmgetobjectptr() {
	stackptr(form);
	stackword(index);
	A0 = getformobjloc(form, index);
}

void frmhideobject() {
	stackptr(formptr);
	stackword(index);
	removeformobject(formptr, index);
	//no return value
}

void frmsetfocus() {
	stackptr(formptr);
	stackword(objindex);
	setformfocus(formptr, objindex);
}

TEMPHACK
void frmsetcontrolvalue() {
	stackptr(formptr);
	stackword(index);
	stackword(newvalue);
	offset_68k objptr = getformobjloc(formptr, index);
	uint16_t attr = get_word(objptr + 14);
	uint8_t type = get_byte(objptr + 16);

	if(type == sliderCtl) {
		palmabrt();//hack
	}
	else {
		//just turn on or off
		if(newvalue != 0) {
			attr |= bit(12);
		}
		else {
			attr &= ~bit(12);
		}

		put_word(objptr + 14, attr);
	}

	//no return value
}



//menus
void menuhandleevent() {
	stackptr(menubarptr);
	stackptr(eventptr);
	stackptr(errorptr);
	menueventhandler(menubarptr, eventptr, errorptr);
}



//uicolor
void uicolorgettableentryrgb() {
	stackbyte(index);
	stackptr(rgbcolor);
	put_long(rgbcolor, renderer.UIColorTable[index]);
	//no return value
}

void uicolortablesettableentry() {
	stackbyte(index);
	stackptr(rgbcolor);
	renderer.UIColorTable[index] = get_long(rgbcolor);
	D0 = errNone;
}

void uicolorgettableentryindex() {
	stackbyte(colortableindex);
	D0 = renderer.UIColorTable[colortableindex] >> 24;
}



//field
void fldsetuseable() {
	stackptr(field);
	stackbool(enabled);
	uint16_t curflags = get_word(field + 10);

	if(enabled) {
		put_word(field + 10, curflags | bit(15));
	}
	else {
		put_word(field + 10, curflags & ~bit(15));
	}

	//no return value
}

void flderasefield() {
	stackptr(field);
	//disable visible bit
	put_word(field + 10, get_word(field + 10) & ~bit(14));
	TEMPHACK;
	//may redraw the display
	//no return value
}

void fldsettextptr() {
	stackptr(field);
	stackptr(textptr);
	fieldappointtextptr(field, textptr);
	//no return value
}

void fldsettexthandle() {
	stackptr(field);
	stackptr(texthandle);
	fieldappointtexthandle(field, texthandle);
	//no return value
}

void flddrawfield() {
	stackptr(field);
	TEMPHACK;
	drawfield(renderer.lcd_window, field);//to screen or activeform unsure? //hack
	//palmabrt();
	//no return value
}

void fldgettextptr() {
	stackptr(fldptr);
	A0 = get_long(fldptr + 12);
}

void fldgettexthandle() {
	stackptr(fldptr);
	A0 = get_long(fldptr + 16);
}



//controls
void ctlsetusable() {
	stackptr(ctlptr);
	stackbool(value);
	uint16_t newattr = get_word(ctlptr + 14);//get old attr

	if(value) {
		newattr |= bit(15);
	}
	else {
		newattr &= ~bit(15);
	}

	put_word(ctlptr + 14, newattr);
	//no return value
}



//pen input manager //none of these are in the dispatch table

uint16_t lcddirection = 0;//dummy value

TEMPHACK
void syssetorientationtriggerstate() {
	stackword(state);
	//unknown
	D0 = errNone;
}

TEMPHACK
void syssetorientation() {
	stackword(orientation);
	lcddirection = orientation;
	//rotate images if needed
	D0 = errNone;
}

void sysgetorientation() {
	D0 = lcddirection;
}

TEMPHACK
void frmsetdiapolicyattr() {
	stackptr(frmptr);
	stackword(newpol);
	//unknown
	D0 = errNone;
}

TEMPHACK
//only returns fixed value
void pingetinputareastate() {
	D0 = pinInputAreaNone;//pretends there is no graffiti area
}

void statgetattribute() {
	stackword(selector);
	stackptr(dataptr);

	switch(selector) {
	case statAttrBarVisible:
		put_long(dataptr, statvisible);
		break;

	case statAttrDimension:
		put_long(dataptr, ((uint32_t)statw << 16 | stath));
		break;

	default:
		D0 = sysErrParamErr;
		return;
	}

	D0 = errNone;
}



//other
void evtgetpen() {
}

void rctsetrectangle() {
	stackptr(rectptr);
	stackword(left);
	stackword(top);
	stackword(width);
	stackword(height);
	put_word(rectptr, left);
	put_word(rectptr + 2, top);
	put_word(rectptr + 4, width);
	put_word(rectptr + 6, height);
	//no return value
}

void rctptinrectangle() {
	stackword(x);
	stackword(y);
	stackptr(rectptr);
	SQUARE rect = get_square(rectptr);
	COORD testpt = {(int16_t)x, (int16_t)y};
	D0 = in_bound_box(rect, testpt);
}

TEMPHACK
//hardcoded to tx fullscreen mode (no pen/silkscreen buttons)
void evtgetpenbuttonlist() {
	stackptr(countptr);//uint16_t
	put_word(countptr, 0);
	A0 = nullptr_68k;
}

void highdensitydispatch() {
	//This trap is just a switch statement!
	SELECTOR{
		SELAPI(HDSelectorWinScreenGetAttribute, winscreengetattribute()); //check for highdensity,get display size,etc
		SELAPI(HDSelectorBmpCreateBitmapV3, bmpcreatebitmapv3());
		SELAPI(HDSelectorBmpGetDensity, bmpgetdensity());
		SELAPI(HDSelectorWinGetCoordinateSystem, wingetcoordinatesystem());
		SELAPI(HDSelectorWinSetCoordinateSystem, winsetcoordinatesystem());

	default:
		//invalid command
		dbgprintf("INV_CMD:%d\n", D2);
		palmabrt();//hack
		break;
	}
}

void pinsdispatch() {
	//This trap is just a switch statement!
	SELECTOR{
		SELAPI(pinSysSetOrientationTriggerState, syssetorientationtriggerstate());
		SELAPI(pinSysSetOrientation, syssetorientation());
		SELAPI(pinSysGetOrientation, sysgetorientation());
		SELAPI(pinFrmSetDIAPolicyAttr, frmsetdiapolicyattr());
		SELAPI(pinPINGetInputAreaState, pingetinputareastate());
		SELAPI(pinStatGetAttribute, statgetattribute());

	default:
		//invalid command
		dbgprintf("INV_CMD:%d\n", D2);
		palmabrt();//hack
		break;
	}
}



//part of evtgetevent
void evtgeteventWIN() {
	if(changewindow) {
		osevent closeold;
		osevent opennew;
		closeold.type = winExitEvent;
		closeold.data.push_back(newwindowptr);
		closeold.data.push_back(renderer.current_active_window);
		addnewevent(closeold);
		opennew.type = winEnterEvent;
		opennew.data.push_back(newwindowptr);
		opennew.data.push_back(renderer.current_active_window);
		addnewevent(opennew);
		renderer.current_active_window = newwindowptr;
		renderer.set_draw_window(newwindowptr);
		changewindow = false;
	}
}




//sets up memory and varibles
bool init_display_driver() {
	//Make color palette
	for(uint16_t cnt = 0; cnt < 0xFF; cnt++) {
		renderer.color_palette[cnt] = paltopalm(PalmPalette8bpp[cnt]);
	}

	//Init gui library
	UG_Init(&renderer.draw_ctx, plotpixel_drawctx, LCDW, LCDH);
	UG_SelectGUI(&renderer.draw_ctx);

	//Clear hardware screen to white
	for(uint32_t pixels = 0; pixels < LCDW * LCDH; pixels++) {
		put_word(lcd_start + (pixels * 2), 0xFFFF /*white*/);
	}

	//spareframe does not need to be cleared since it is not accessible from inside the emulator
	//(it is only drawn after being filled with valid screen data)
	renderer.scale_video = true;
	renderer.width  = LCDW;
	renderer.height = LCDH;
	renderer.bpp	= LCDBPP;
	renderer.color  = LCDHASCOLOR;
	TEMPHACK;
	//status bar on devices with dynamic input area
	statvisible = false;
	statw = 0;
	stath = 0;
	//touch driver
	sendpenevents = true;
	renderer.draw_state = newdrawstate();
	renderer.lcd_bitmap = getfreeheap(20);
	renderer.lcd_window = getfreeheap(68);
	initformwindow(renderer.lcd_window, 160, 160, bit(11) | bit(10) | bit(8),
	               0, renderer.lcd_bitmap, renderer.draw_state, 0);

	if(renderer.lcd_window == nullptr_68k || renderer.lcd_bitmap == nullptr_68k || renderer.draw_state == nullptr_68k) {
		palmabrt();//hack
		return false;
	}

	//setup lcdbitmaptype
	put_word(renderer.lcd_bitmap, LCDW);
	put_word(renderer.lcd_bitmap + 2, LCDH);
	put_word(renderer.lcd_bitmap + 4, LCDW * 2);
	put_word(renderer.lcd_bitmap + 6, bit(11) | bit(12));
	put_byte(renderer.lcd_bitmap + 8, LCDBPP); //bits per pixel
	put_byte(renderer.lcd_bitmap + 9, 2);
	put_word(renderer.lcd_bitmap + 10, 0); //next bitmaptype
	put_byte(renderer.lcd_bitmap + 12, 0); //transparent color (none)
	put_byte(renderer.lcd_bitmap + 13, 0xFF); //compression type (none)
	put_word(renderer.lcd_bitmap + 14, 0); //reserved
	put_long(renderer.lcd_bitmap + 16, lcd_start); //indirect flag ptr (to lcd)
	TEMPHACK;
	//most likely *double or *single not *native
	put_word(COORDSYS, kCoordinatesNative);
	renderer.set_draw_window(renderer.lcd_window);
	renderer.current_active_window	= renderer.lcd_window;
	//fonts
	offset_68k stdfntaddr = getfontaddr(stdFont);
	currentfont.setactivefont(stdfntaddr);
	put_byte(FONTID, stdFont);
	put_long(FONTPTR, stdfntaddr);
	//may load specific tFRM for display on start
	anyformsopen = false;
	TEMPHACK;
	activeform = 0x0;
	activeformptr = renderer.current_active_window;
	renderer.screen_lock_count = 0;
	changewindow = false;
	sendwinenterondraw = false;
	return true;
}

void deinit_display_driver() {
	//nothing right now
}



void appTouchDriver(int x, int y, bool pressed) {
	if(x > 320 || y > 480 || x < 0 || y < 0) {
		dbgprintf("TouchX:%d,TouchY:%d\n", x, y);
		palmabrt();//hack
	}

	PENX = x;
	PENY = y;
	osevent touch;
	touch.screenx = x;
	touch.screeny = y;

	if(pressed) {
		touch.pendown = true;
	}

	//move event
	if(PENDOWN && pressed) {
		//some objects track automaticly,palm does not send this event for those objects
		//(make this disabled for those objects)
		touch.type = penMoveEvent;
		touch.pendown = true;
	}
	else
		if(pressed) {
			PENDOWN = true;
			touch.type = penDownEvent;
			touch.pendown = true;
			touch.tapcount = 1;//hack
			//tracking for penUpEvent
			touchstart.x = x;
			touchstart.y = y;
		}
		else
			if(!pressed && PENDOWN) {
				PENDOWN = false;
				touch.type = penUpEvent;
				touch.pendown = false;
				touch.data.push_back(touchstart.x);
				touch.data.push_back(touchstart.y);
				touch.data.push_back(x);
				touch.data.push_back(y);
			}
			else {
				palmabrt();    //hack
			}

	if(sendpenevents) {
		addnewevent(touch);
	}
}

void appKeyDriver(char thiskey, bool pressed) {
	if(pressed) {
		osevent keypress;
		keypress.type = keyDownEvent;
		keypress.data.push_back((uint8_t)thiskey);//chr
		keypress.data.push_back(0);//virtual key num
		keypress.data.push_back(0);//modifiers
		addnewevent(keypress);
	}
	else {
		osevent keypress;
		keypress.type = keyUpEvent;
		keypress.data.push_back((uint8_t)thiskey);//chr
		keypress.data.push_back(0);//virtual key num
		keypress.data.push_back(0);//modifiers
		addnewevent(keypress);
	}
}
