#if 0
#include "palmtypeaccess.h"
#include "displaydriver.h"

static UG_WINDOW			form_window;
std::vector<UG_BUTTON>		form_buttons;
std::vector<UG_CHECKBOX>	form_checkboxes;
std::vector<UG_TEXTBOX>		form_textboxes;


static void drawcontrolobject(offset_68k window, offset_68k controlptr) {
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

static void drawfield(offset_68k window, offset_68k fieldptr) {
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
		//UG_PutString();
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
static void drawlist(offset_68k window, offset_68k listptr) {
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

static void drawtable() {
	palmabrt();
}

TEMPHACK
static void drawtitle(offset_68k window, offset_68k titleptr) {
	SQUARE area = get_square(titleptr);
	addobjtocollisionmatrix(area, titleptr, frmTitleObj, 0); //theres only one title
	//draw title/menu bar popup
}

//only called by frmdrawform (draws bitmap using special form struct)
static void drawbitmap(offset_68k window, offset_68k bmpptr) {
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

static void drawscrollbar() {
	palmabrt();
}

//only called by frmdrawform //labels dont handle or send events
static void drawlabel(offset_68k window, offset_68k labelptr) {
	uint16_t id = get_word(labelptr);
	uint16_t x = (int16_t)get_word(labelptr + 2);
	uint16_t y = (int16_t)get_word(labelptr + 4);
	uint16_t attr = get_word(labelptr + 6);
	bool useable = (attr & bit(15));
	TEMPHACK;//use custom fonts
	//prams = get_byte(labelptr + 8);//fontid
	//ignore pad byte
	offset_68k src = get_long(labelptr + 10);//char ptr
	//dstptr = window;
	//drwcolor = get_byte(TEXTCOLOR);//hack //must use palette with an index
	//dbgprintf("Label %s useable,attr:%04x,charptr:%08x\n", useable ? "IS" : "IS NOT", attr, srcptr);
	//dbgprintf("X:%d,Y:%d,Text:%s\n", dstx, dsty, readstring(srcptr).c_str());
	//srcsize = UNDEFINED;

	if(useable) {
		//text();
		std::string str = readstring(src);
		UG_SetForecolor(renderer.color_palette[get_byte(TEXTCOLOR)]);
		UG_PutString((char*)str.c_str());
		UG_SetForecolor(renderer.color_palette[get_byte(FORECOLOR)]);
	}
}

static void drawgadget(offset_68k window, offset_68k gdtptr) {
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


static void placeformobj(offset_68k form, uint16_t index) {
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

void render_form(offset_68k form) {
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
	//resetcollisionmatrix();
	//draw the objects
	uint16_t numobjects = get_form_num_objects(form);

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
#endif
