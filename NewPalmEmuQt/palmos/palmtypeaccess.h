#ifndef PALMTYPEACCESS
#define PALMTYPEACCESS

#include "m68k.h"
#include "rawimagetools.h"
#include "minifunc.h"

#include "palmos/graphics/palette.h"

//new format palm struct field accessors
#define WINFLAGS(winptr) ((winptr) + 8)
//#define WINFLAGMODAL(flags) ((flags) & bit(13))

inline UWORD getwinflags(CPTR winptr){
	return get_word(winptr + 8);
}

inline bool getwinmodal(CPTR winptr){
	return getwinflags(winptr) & bit(13);
}

inline UWORD getwinbackcolor(CPTR winptr){
	return get_word(winptr + 8);
}


//bitmap
inline CPTR getbmppalette(CPTR bmpptr){
	UWORD bmpflags = get_word(bmpptr + 6);

	//color table check
	if((bmpflags & bit(14)) == 0)return nullptr_68k;

	CPTR data;
	if(bmpflags & bit(12))data = get_long(bmpptr + 16) + 2;
	else data = bmpptr + 16 + 2;
	return data;
}

inline UWORD getbmppalettenumentrys(CPTR bmpptr){
	if((get_word(bmpptr + 6) & bit(14)) != 0){
		return bitstocolors(get_byte(bmpptr + 8));
	}
	return 0;
}

inline CPTR getbmpdata(CPTR bmpptr){
	CPTR data;
	UWORD bmpflags = get_word(bmpptr + 6);
	if(bmpflags & bit(12))data = get_long(bmpptr + 16);
	else data = bmpptr + 16;

	//dbgprintf("BitmapFlags:%04x,Bitmap:%08x\n",bmpflags,bmpptr);

	//color table check
	if(bmpflags & bit(14))data += bitstocolors(get_byte(bmpptr + 8)) * 4 + 2;

	return data;
}

inline UBYTE getbmpbpp(CPTR bmpptr){
	if(get_byte(bmpptr + 9) > 0)return get_byte(bmpptr + 8);
	return 1;
}

inline UWORD getbmprowbytes(CPTR bmpptr){
	return get_word(bmpptr + 4);
}

//window
inline CPTR getwinbmp(CPTR winptr){
	return get_long(winptr + 26);
}

inline CPTR getwindata(CPTR winptr){
	return getbmpdata(getwinbmp(winptr));
}

inline CPTR getwinbounds(CPTR winptr){
	return winptr + 10;
}

inline CPTR getwinclipping(CPTR winptr){
	return winptr + 18;
}

inline CPTR getwinpalette(CPTR winptr){
	return getbmppalette(getwinbmp(winptr));
}

inline UWORD getwinpalettenumentrys(CPTR winptr){
	return getbmppalettenumentrys(getwinbmp(winptr));
}

inline void setwinbmp(CPTR winptr,CPTR bitmap){
	put_long(winptr + 26,bitmap);
}

//win drawstate
inline void setwindrawstate(CPTR winptr,CPTR drawstate){
	put_long(winptr + 32,drawstate);
}
inline CPTR getwindrawstate(CPTR winptr){
	return get_long(winptr + 32);
}



//form
inline CPTR getformobjlist(CPTR formptr){
	return get_long(formptr + 64);
}
inline CPTR getformobjloc(CPTR form,UWORD count){
	CPTR objindex = getformobjlist(form) + 6 * count;
	return get_long(objindex + 2);
}


inline void setformeventhandler(CPTR formptr,CPTR functionptr){
	put_long(formptr + 50,functionptr);
}
inline CPTR getformeventhandler(CPTR formptr){
	return get_long(formptr + 50);
}


inline void setformnumobjects(CPTR formptr,UWORD numobjects){
	put_word(formptr + 62,numobjects);
}
inline UWORD getformnumobjects(CPTR formptr){
	return get_word(formptr + 62);
}

inline void setformfocus(CPTR formptr,UWORD numobjects){
	put_word(formptr + 54,numobjects);
}
inline UWORD getformfocus(CPTR formptr){
	return get_word(formptr + 54);
}

inline UWORD getformid(CPTR formptr){
	return get_word(formptr + 40);
}

inline void setformattr(CPTR formptr,UWORD newval){
	put_word(formptr + 42,newval);
}
inline UWORD getformattr(CPTR formptr){
	return get_word(formptr + 42);
}


//form gadget object
inline void setgadgethandler(CPTR gadget,CPTR handler){
	put_long(gadget + 16,handler);
}
inline CPTR getgadgethandler(CPTR gadget){
	return get_long(gadget + 16);
}

#endif // PALMTYPEACCESS

