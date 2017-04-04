#include "m68k.h"
#include "memmap.h"
#include "minifunc.h"
#include "dataexchange.h"
#include "stdlib68k.h"
#include "palmdefines.h"

#include <string>

void memmoveAPI(){
	stackptr(dest);
	stackptr(source);
	stacklong(size);

	if(size == 0){
		D0 = errNone;//always returns 0/errNone
		return;
	}

	uint8_t* backup = new uint8_t[size];
	readbytearray(source,backup,size);
	writebytearray(dest,backup,size);
	delete[] backup;

	D0 = errNone;//always returns 0/errNone
}

void memsetAPI(){
	stackptr(dest);
	stacklong(size);
	stackbyte(val);

	memset68k(dest,val,size);
	D0 = errNone;//always returns 0/errNone
}

void strcopyAPI(){
	stackptr(dest);
	stackptr(src);
	if(src && dest){
		offset_68k offset = 0;
		while(true){
			uint8_t next = get_byte(src + offset);
			put_byte(dest + offset,next);
			if(next == '\0' || buserr)break;
			offset++;
		}
	}
	A0 = dest;
}

TEMPHACK //palm os api reference does not state if the null terminator counts as a char
//C stdlib does not count the null terminator
void strlenAPI(){
	stackptr(strptr);
	D0 = (uint16_t)strlen68k(strptr);//returns unsigned value in palm os 5 and any less than 3.5
}

TEMPHACK //check and fix sign extend
void strncompare(){
	stackptr(str1);
	stackptr(str2);
	stacklong(length);

	offset_68k end;
	uint8_t byte1,byte2;
	for(end = 0;end < length;end++){
		byte1 = get_byte(str1 + end);
		byte2 = get_byte(str2 + end);
		if(byte1 != byte2){
			D0 = (BYTE)(byte1 - byte2);//HACK check and fix sign extend
			return;
		}
		//both chars are the same,now check if there 0,if yes the strings are the same
		//this prevents equal strings smaller than the max size from read overflowing
		if(byte1 == '\0'){
			D0 = 0;
			return;
		}
	}

	D0 = 0;
}

TEMPHACK //only exit on multibyte char if it overflows the length to copy
void strncopy(){
	stackptr(dest);
	stackptr(src);
	stackword(num);

	offset_68k offset;
	uint8_t next;
	if(src && dest){
		for(offset = 0;offset < num;offset++){
			next = get_byte(src + offset);
			put_byte(dest + offset,next);
			if(next == '\0' || next > 127/*is multibyte*/ || buserr)break;
		}

		//the last byte written above is rewritten with '\0' below regardless so a multibyte char wont slip through
		put_byte(dest + offset,'\0');
	}

	TEMPHACK;
	//may or may not be padding string properly

	A0 = dest;
}

TEMPHACK //sign extend
void strcompare(){
	stackptr(str1);
	stackptr(str2);

	offset_68k offs = 0;
	uint8_t byte1,byte2;
	while(true){
		byte1 = get_byte(str1 + offs);
		byte2 = get_byte(str2 + offs);
		if(byte1 != byte2){
			D0 = (BYTE)(byte1 - byte2);//HACK check and fix sign extend
			return;
		}
		//both chars are the same,now check if there 0,if yes the strings are the same
		if(byte1 == '\0'){
			D0 = 0;
			return;
		}
		offs++;
	}

	D0 = 0;
}

void strchr(){
	stackptr(chrptr);
	stackword(wchartype);

	//16bit char support is beta

	offset_68k stop = chrptr;

	if(wchartype > 0xFF){
		//this is a 16bit char
		uint8_t wcharhighbyte = wchartype >> 8;
		uint8_t wcharlowbyte = wchartype & 0xFF;
        failed:
		while(get_byte(stop) != wcharhighbyte && get_byte(stop) != 0)stop++;
		if(get_byte(stop) == 0){
			A0 = nullptr_68k;
			return;
		}
		if(get_byte(stop + 1) != wcharlowbyte){
			//continue searching
			stop++;
			goto failed;
		}
	}
	else{
		//this is an 8bit char
		while(get_byte(stop) != wchartype && get_byte(stop) != 0)stop++;
		if(get_byte(stop) == 0){
			A0 = nullptr_68k;
			return;
		}
	}

	A0 = stop;
}

void stritoa(){
	stackptr(dst);
	stacklong(value);

	char convert[20];//64bit maxes out at 20 digits,this is only 32
	sprintf(convert,"%d",(LONG)value);
	writestring(dst,convert);

	A0 = dst;
}
