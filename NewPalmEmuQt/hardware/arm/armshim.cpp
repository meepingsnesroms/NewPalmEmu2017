#include "types.h"
#include "timing.h"
#include "m68k.h"
#include "CPU.h"
#include "minifunc.h"
#include "dataexchange.h"
#include "armv5te.h"

void palmabrt();//hack


bool inARM = false;
ArmCpu palm2ndcpu;

inline UInt32 get32arm(UInt32 addr){
	UInt32 out;

	//get bytes and make little endian 32bit int
	out = get_byte(addr + 3) << 24;
	out |= get_byte(addr + 2) << 16;
	out |= get_byte(addr + 1) << 8;
	out |= get_byte(addr);

	return out;
}

inline UInt16 get16arm(UInt32 addr){
	UInt16 out;

	//get bytes and make little endian 16bit int
	out = get_byte(addr + 1) << 8;
	out |= get_byte(addr);

	return out;
}

inline UInt8 get8arm(UInt32 addr){
	return get_byte(addr);
}



inline void put32arm(UInt32 addr,UInt32 value){
	//put bytes as little endian 32bit int
	put_byte(addr,value & 0xFF);
	value >>= 8;
	put_byte(addr + 1,value & 0xFF);
	value >>= 8;
	put_byte(addr + 2,value & 0xFF);
	value >>= 8;
	put_byte(addr + 3,value & 0xFF);
}

inline void put16arm(UInt32 addr,UInt16 value){
	//put bytes as little endian 16bit int
	put_byte(addr,value & 0xFF);
	value >>= 8;
	put_byte(addr + 1,value & 0xFF);
}

inline void put8arm(UInt32 addr,UInt8 value){
	put_byte(addr,value);
}



static void emulErrF(ArmCpu* cpu, const char* str){
   /*
   err_str("Emulation error: <<");
   err_str(str);
   err_str(">> halting\r\n");
   while(1);
   */
   palmabrt();//HACK just freakout
}

static Boolean hyperF(ArmCpu* cpu){		//return true if handled
   palmabrt();//HACK just freakout
   return true;
}

static void setFaultAdrF(ArmCpu* cpu, UInt32 adr, UInt8 faultStatus){
   
   //SoC* soc = cpu->userData;
   
   //cp15SetFaultStatus(&soc->cp15, adr, faultStatus);
   //palmabrt();//HACK just freakout
	//HACK ignore for now
}

//Boolean memAccess(ArmMem* mem, UInt32 addr, UInt8 size, Boolean write, void* buf){
Boolean memAccess(ArmCpu* curcpu, void* buf, UInt32 addr, UInt8 size, Boolean write, Boolean priviledged, UInt8* fsr){
	//privliged and fsr are currently ignored (palm os runs everything as root and with kernel memory map)

	//dbgprintf("ARM mem access size:0x%02x,%d\n",size,size);

	UInt8* bytebuf = (UInt8*)buf;

	size /= 8;//size is in bits,convert it to bytes
   
	/*
	switch(size){
		case 32:return get_long(addr);
	}
	*/

   if(write){
      //write
      for(UInt8 fleas = 0;fleas < size;fleas++){
         put_byte(addr + fleas,bytebuf[fleas]);
      }
   }
   else{
      //read
      for(UInt8 fleas = 0;fleas < size;fleas++){
         bytebuf[fleas] = get_byte(addr + fleas);
      }
   }
   return false;
}






void initARM(){
   Err failed = cpuInit(&palm2ndcpu,0/*PC not needed,its set when arm is called*/,memAccess,emulErrF,hyperF,setFaultAdrF);
   if(failed)palmabrt;//HACK
}

void callARM(uint32 function){
	inARM = true;
   
	//use link register instead of stack
   cpuSetReg(&palm2ndcpu,ARMLR,INTERCEPT);

   cpuSetReg(&palm2ndcpu,ARMPC,function);
    while(!ISSPECIAL(cpuGetRegExternal(&palm2ndcpu,ARMPC))){
		if(CPUREQ){
			//just like KILLSWITCH but disables inARM first
			inARM = false;
			throw CPUREQ;
		}

		cpuCycle(&palm2ndcpu);
      
      /*
		//we dont need a palm that runs at 2GHZ
		//its also way slow because then the OS(on the host computer),display refresh,audio and input threads cant run
		cycle();
      */
	}
	inARM = false;
}

void setregARM(uint8 reg,uint32 value){
   cpuSetReg(&palm2ndcpu,reg,value);
}

uint32 getregARM(uint8 reg){
   return cpuGetRegExternal(&palm2ndcpu,reg);
}
