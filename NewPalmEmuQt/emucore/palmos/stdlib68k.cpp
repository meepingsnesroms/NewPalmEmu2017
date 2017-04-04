#include "m68k.h"
#include "minifunc.h"

void memcpy68k(offset_68k dest, offset_68k src, size_t_68k size){
	for(offset_68k bytes = 0;bytes < size;bytes++){
		put_byte(dest + bytes,get_byte(src + bytes));
	}
}

void memset68k(offset_68k dest,uint8_t value,size_t_68k size){
	for(offset_68k count = 0;count < size;count++){
		put_byte(dest + count,value);
	}
}

int16_t memcmp68k(offset_68k ptr1, offset_68k ptr2, size_t_68k size){
	uint8_t byte1,byte2;
	for(offset_68k end = 0;end < size;end++){
		byte1 = get_byte(ptr1 + end);
		byte2 = get_byte(ptr2 + end);
		if(byte1 != byte2)return (int8_t)(byte1 - byte2);
	}
	return 0;
}

/*
int16_t strcmp68k(offset_68k ptr1, offset_68k ptr2, size_t_68k size){
	//may multithread this by NUMBER_OF_PROCESSORS & switch to UWORDs instead of UBYTEs
	offset_68k end;
	uint8_t byte1,byte2;
	inc_for(end,size){
		byte1 = get_byte(ptr1 + end);
		byte2 = get_byte(ptr2 + end);
		if(byte1 != byte2)return (int8_t)(byte1 - byte2);
		//both chars are the same now check if there 0,if yes the strings are the same
		//this prevents equal strings smaller than the max size from overflowing
		if(byte1 == '\0')return 0;
	}
	return 0;
}
*/

//C standard strlen does not count the null terminator
uint16_t strlen68k(offset_68k strptr){
	size_t_68k bytes = 0;
	while(true){
		if(get_byte(strptr + bytes) == '\0')break;
		else bytes++;
	}
	//dont include null terminator,if needed just add +1 to the return value
	return bytes;
}
