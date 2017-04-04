#include "m68k.h"
#include <string>

void readbytearray(offset_68k loc, uint8_t *dest, size_t_68k size){
	offset_68k goo;
	for(goo = 0;goo < size;goo++){
		dest[goo] = get_byte(loc + goo);
	}
}

void writebytearray(offset_68k loc,uint8_t* start,size_t_68k size){
	offset_68k goo;
	for(goo = 0;goo < size;goo++){
		put_byte(loc + goo,start[goo]);
	}
}

std::string readstring(offset_68k loc){
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

void writestring(offset_68k loc,const std::string& str,size_t_68k forcelength = 0){
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
offset_68k emulink;

void pushlonglink(uint32_t val){
	emulink -= 4;
	put_long(emulink,val);
}

uint32_t poplonglink(){
	uint32_t retval;
	retval = get_long(emulink);
	emulink += 4;
	return retval;
}

void pushwordlink(uint16_t val){
	emulink -= 2;
	put_word(emulink,val);
}

uint16_t popwordlink(){
	uint16_t retval;
	retval = get_word(emulink);
	emulink += 2;
	return retval;
}

void pushbytelink(uint8_t val){
	emulink -= 1;
	put_byte(emulink,val);
}

uint8_t popbytelink(){
	uint8_t retval;
	retval = get_byte(emulink);
	emulink += 1;
	return retval;
}
