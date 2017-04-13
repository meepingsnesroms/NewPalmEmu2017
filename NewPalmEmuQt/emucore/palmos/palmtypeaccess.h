#ifndef PALMTYPEACCESS
#define PALMTYPEACCESS

#include "m68k.h"
#include "rawimagetools.h"
#include "minifunc.h"

#include "palmos/graphics/palette.h"

//new format palm struct field accessors
#define WINFLAGS(winptr) ((winptr) + 8)
//#define WINFLAGMODAL(flags) ((flags) & bit(13))

inline uint16_t getwinflags(offset_68k winptr){
	return get_word(winptr + 8);
}

inline bool getwinmodal(offset_68k winptr){
	return getwinflags(winptr) & bit(13);
}

inline uint16_t getwinbackcolor(offset_68k winptr){
	return get_word(winptr + 8);
}


//bitmap
inline offset_68k getbmppalette(offset_68k bmpptr){
	uint16_t bmpflags = get_word(bmpptr + 6);

	//color table check
	if((bmpflags & bit(14)) == 0)return nullptr_68k;

	offset_68k data;
	if(bmpflags & bit(12))data = get_long(bmpptr + 16) + 2;
	else data = bmpptr + 16 + 2;
	return data;
}

inline uint16_t getbmppalettenumentrys(offset_68k bmpptr){
	if((get_word(bmpptr + 6) & bit(14)) != 0){
		return bitstocolors(get_byte(bmpptr + 8));
	}
	return 0;
}

inline offset_68k getbmpdata(offset_68k bmpptr){
	offset_68k data;
	uint16_t bmpflags = get_word(bmpptr + 6);
	if(bmpflags & bit(12))data = get_long(bmpptr + 16);
	else data = bmpptr + 16;

	//dbgprintf("BitmapFlags:%04x,Bitmap:%08x\n",bmpflags,bmpptr);

	//color table check
	if(bmpflags & bit(14))data += bitstocolors(get_byte(bmpptr + 8)) * 4 + 2;

	return data;
}

inline uint8_t getbmpbpp(offset_68k bmpptr){
	if(get_byte(bmpptr + 9) > 0)return get_byte(bmpptr + 8);
	return 1;
}

inline uint16_t getbmprowbytes(offset_68k bmpptr){
	return get_word(bmpptr + 4);
}

//window
inline offset_68k get_win_bmp(offset_68k winptr){
	return get_long(winptr + 26);
}

inline offset_68k getwindata(offset_68k winptr){
	return getbmpdata(get_win_bmp(winptr));
}

inline offset_68k getwinbounds(offset_68k winptr){
	return winptr + 10;
}

inline offset_68k get_win_clipping(offset_68k winptr){
	return winptr + 18;
}

inline offset_68k getwinpalette(offset_68k winptr){
	return getbmppalette(get_win_bmp(winptr));
}

inline uint16_t getwinpalettenumentrys(offset_68k winptr){
	return getbmppalettenumentrys(get_win_bmp(winptr));
}

inline void setwinbmp(offset_68k winptr,offset_68k bitmap){
	put_long(winptr + 26,bitmap);
}

//win drawstate
inline void setwindrawstate(offset_68k winptr,offset_68k drawstate){
	put_long(winptr + 32,drawstate);
}
inline offset_68k getwindrawstate(offset_68k winptr){
	return get_long(winptr + 32);
}



//form
inline offset_68k getformobjlist(offset_68k formptr){
	return get_long(formptr + 64);
}
inline offset_68k getformobjloc(offset_68k form,uint16_t count){
	offset_68k objindex = getformobjlist(form) + 6 * count;
	return get_long(objindex + 2);
}


inline void setformeventhandler(offset_68k formptr,offset_68k functionptr){
	put_long(formptr + 50,functionptr);
}
inline offset_68k getformeventhandler(offset_68k formptr){
	return get_long(formptr + 50);
}


inline void setformnumobjects(offset_68k formptr,uint16_t numobjects){
	put_word(formptr + 62,numobjects);
}
inline uint16_t getformnumobjects(offset_68k formptr){
	return get_word(formptr + 62);
}

inline void setformfocus(offset_68k formptr,uint16_t numobjects){
	put_word(formptr + 54,numobjects);
}
inline uint16_t getformfocus(offset_68k formptr){
	return get_word(formptr + 54);
}

inline uint16_t getformid(offset_68k formptr){
	return get_word(formptr + 40);
}

inline void setformattr(offset_68k formptr,uint16_t newval){
	put_word(formptr + 42,newval);
}
inline uint16_t getformattr(offset_68k formptr){
	return get_word(formptr + 42);
}


//form gadget object
inline void setgadgethandler(offset_68k gadget,offset_68k handler){
	put_long(gadget + 16,handler);
}
inline offset_68k getgadgethandler(offset_68k gadget){
	return get_long(gadget + 16);
}

#endif // PALMTYPEACCESS

