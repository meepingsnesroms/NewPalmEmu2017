#include "m68k.h"
#include <string>

void membyteswap(UBYTE *start, size_t_68k size){
	UBYTE temp;
	offset_68k bunny;
	for(bunny = 0;bunny < size;bunny += 2){
		temp = start[bunny];
		start[bunny] = start[bunny + 1];
		start[bunny + 1] = temp;
	}
}

void readbytearray(CPTR loc, UBYTE *dest, size_t_68k size){
	offset_68k goo;
	for(goo = 0;goo < size;goo++){
		dest[goo] = get_byte(loc + goo);
	}
}

void writebytearray(CPTR loc,UBYTE* start,size_t_68k size){
	offset_68k goo;
	for(goo = 0;goo < size;goo++){
		put_byte(loc + goo,start[goo]);
	}
}

std::string readstring(CPTR loc){
	std::string tempstr;
	char chr;//is needed to check if the last char was a null terminator before appending it
	while(true){
		chr = (char)get_byte(loc);
		if(chr == '\0')break;//HACK
		tempstr += chr;
		loc++;
	}
	return tempstr;
}

void writestring(CPTR loc,const std::string& str,size_t_68k forcelength = 0){
	const char* strptr = str.c_str();
	offset_68k goo = 0;
	while(true){
		put_byte(loc + goo,strptr[goo]);
		if(strptr[goo] == '\0')break;
		else goo++;
	}

	//the last iteration dosent increment,this fixes that
	goo++;

	//sets remaining chars to null if size is forced
	if(forcelength > goo){//continue writing with just nulls
		while(goo < forcelength){
			put_byte(loc + goo,'\0');
			goo++;
		}
	}
}



//fake stack push and pop,used to push and pop without changing 68k memory or registers
CPTR emulink;

void pushlonglink(ULONG val){
	emulink -= 4;
	put_long(emulink,val);
}

ULONG poplonglink(){
	ULONG retval;
	retval = get_long(emulink);
	emulink += 4;
	return retval;
}

void pushwordlink(UWORD val){
	emulink -= 2;
	put_word(emulink,val);
}

UWORD popwordlink(){
	UWORD retval;
	retval = get_word(emulink);
	emulink += 2;
	return retval;
}

void pushbytelink(UBYTE val){
	emulink -= 1;
	put_byte(emulink,val);
}

UBYTE popbytelink(){
	UBYTE retval;
	retval = get_byte(emulink);
	emulink += 1;
	return retval;
}
