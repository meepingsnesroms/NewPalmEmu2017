#include "palmwrapper.h"
#include "displaydriver.h"
#include "eventqueue.h"
#include "palmapi.h"

//new list
#include "m68k.h"
#include "armv5te.h"
#include "newcpu.h"
#include "prcfile.h"
#include "virtuallcd.h"
#include "dataexchange.h"
#include "palmmalloc.h"
#include "minifunc.h"
#include "stdlib68k.h"
#include "resourcelocator.h"
#include "datamanager.h"
#include "palmdefines.h"

#include "romutils.h"
#include "palmosv4.1-en-m515.h"

static CPTR outa5,outgblstart,outgblend;

//for non aligned ULONG size offsets in compressed globals
static ULONG nonalignedlong(CPTR addr){
	return get_byte(addr) << 24 | get_byte(addr + 1) << 16 | get_byte(addr + 2) << 8 | get_byte(addr + 3);
}

static CPTR RLEglobals(CPTR output,CPTR compresseddata){
	dbgprintf("OutputDataStart:%08x\n",output);//hack

	bool moredata = true;
	while(moredata){
		UBYTE controlbyte = get_byte(compresseddata);
		compresseddata++;
		if(controlbyte >= 0x80){//1 + (value - 0x80) bytes of literal data
			size_t_68k bytes = (controlbyte - 0x80) + 1;
			memcpy68k(output,compresseddata,bytes);
			output += bytes;
			compresseddata += bytes;
		}else if(controlbyte >= 0x40){//1 + (value - 0x40) bytes of 0x00
			size_t_68k bytes = (controlbyte - 0x40) + 1;
			memset68k(output,0x00,bytes);
			output += bytes;
		}else if(controlbyte >= 0x20){//next byte repeated 2 + (value - 0x20) times
			size_t_68k bytes = (controlbyte - 0x20) + 2;
			UBYTE value = get_byte(compresseddata);
			compresseddata++;
			memset68k(output,value,bytes);
			output += bytes;
		}else if(controlbyte >= 0x10){//1 + (value - 0x10) bytes of 0xFF
			size_t_68k bytes = (controlbyte - 0x10) + 1;
			memset68k(output,0xFF,bytes);
			output += bytes;
		}else{
			switch(controlbyte){
				//patterns
				case 0x04:
					put_byte(output,0xA9);
					put_byte(output + 1,0xF0);
					put_byte(output + 2,0x00);
					put_byte(output + 3,get_byte(compresseddata));
					put_byte(output + 4,get_byte(compresseddata + 1));
					put_byte(output + 5,get_byte(compresseddata) + 2);
					put_byte(output + 6,0x00);
					put_byte(output + 7,get_byte(compresseddata) + 3);
					compresseddata += 4;
					output += 8;
					break;
				case 0x03:
					put_byte(output,0xA9);
					put_byte(output + 1,0xF0);
					put_byte(output + 2,0x00);
					put_byte(output + 3,0x00);
					put_byte(output + 4,get_byte(compresseddata));
					put_byte(output + 5,get_byte(compresseddata + 1));
					put_byte(output + 6,0x00);
					put_byte(output + 7,get_byte(compresseddata + 2));
					compresseddata += 3;
					output += 8;
					break;
				case 0x02:
					memset68k(output,0x00,4);
					put_byte(output + 4,0xFF);
					memcpy68k(output + 5,compresseddata,3);
					compresseddata += 3;
					output += 8;
					break;
				case 0x01:
					memset68k(output,0x00,4);
					memset68k(output + 4,0xFF,2);
					put_byte(output + 6,get_byte(compresseddata));
					put_byte(output + 7,get_byte(compresseddata + 1));
					compresseddata += 2;
					output += 8;
					break;

				//end of data
				case 0x00:
					moredata = false;
					break;
				default:
					palmabrt();
					break;
			}
		}
	}
	dbgprintf("CompressdDataEnd:%08x\n",compresseddata);
	return compresseddata;
}

static void installglobals(int app){
	CPTR globalsinfo = getresource(app,0,'code');
	CPTR globalsdata = getresource(app,0,'data');
	if(globalsdata == nullptr_68k || globalsinfo == nullptr_68k){
		dbgprintf("Flying cow?\n");
		palmabrt();
	}

	offset_68k abovea5 = get_long(globalsinfo);
	size_t_68k globalssize = abovea5 + get_long(globalsinfo + 4);
	size_t_68k jmptblsize = get_long(globalsinfo + 8);
	offset_68k jmptbla5offset = get_long(globalsinfo + 12);
	CPTR gbldataarr = getfreeheap(globalssize);

	//set ptr to globals
	CPTR a5ptr = gbldataarr + globalssize - get_long(globalsinfo);//offset in globals A5 should be at


	dbgprintf("JmptblOffset:%08x,Jmptblsize:%08x,AboveA5:%08x,A5:%08x,Gblsize:%08x\n",
		   jmptbla5offset,jmptblsize,abovea5,a5ptr,globalssize);


	CPTR start = globalsdata + 4;
	offset_68k offsetofa5;
	CPTR dest;

	offsetofa5 = (LONG)nonalignedlong(start);
	//dbgprintf("OffestOfA5:%08x\n",offsetofa5);
	dest = a5ptr + offsetofa5;
	start += 4;
	start = RLEglobals(dest,start);

	offsetofa5 = (LONG)nonalignedlong(start);
	dest = a5ptr + offsetofa5;
	start += 4;
	start = RLEglobals(dest,start);

	offsetofa5 = (LONG)nonalignedlong(start);
	dest = a5ptr + offsetofa5;
	start += 4;
	start = RLEglobals(dest,start);

	apps[app].thisglobals = gbldataarr;//was a5ptr

	//dbgprintf("A5 ptr:%08x,int main:0x%08x\n",a5ptr,apps[app].intmain);

	outa5 = a5ptr;
	outgblstart = gbldataarr;
	outgblend = gbldataarr + globalssize;
}

static void trickROMtest(){
	put_long(0x8,0xFEEDBEEF);//all pre os 5 roms have this at 0x8 (os 5 most likely does too but with ram in memory bank 0)
}

bool launchapp(int num){
	if(!apps[num].exe)return false;//check validity

	trickROMtest();//in case the app trys arbitrary memory reads as a form of drm

	installglobals(num);

	MC68000_setpc(apps[num].intmain);
	SP = STACKEND;
	A5 = outa5;
	CPU_pushlongstack(INTERCEPT);//if app trys to execute above the stack

	CPTR newexlist = getnewlinearchunks(1) << 16;

	CPTR sysappinfoptr = getfreeheap(60);
	CPTR sysappinfoptrstart = sysappinfoptr;

	put_word(sysappinfoptr,sysAppLaunchCmdNormalLaunch);//command
	sysappinfoptr += 2;
	put_long(sysappinfoptr,nullptr_68k);//param block //normallaunch has no params
	sysappinfoptr += 4;
	put_word(sysappinfoptr,sysAppLaunchFlagUIApp | sysAppLaunchFlagNewGlobals);//flags
	sysappinfoptr += 2;

	put_long(sysappinfoptr,'init');//taskid
	sysappinfoptr += 4;
	put_long(sysappinfoptr,apps[num].intmain);//memhandle to main
	sysappinfoptr += 4;
	put_long(sysappinfoptr,num + dmOpenRefOffset);//dmopenref to this app
	sysappinfoptr += 4;
	put_long(sysappinfoptr,STACKEND - STACKSIZE / 2);//app stackptr
	sysappinfoptr += 4;
	put_long(sysappinfoptr,outgblstart);//globals ptr//gbldataarr
	sysappinfoptr += 4;

	put_word(sysappinfoptr,0x1245);//memownerid
	sysappinfoptr += 2;
	put_long(sysappinfoptr,0xBADC0DE);//open dbs
	sysappinfoptr += 4;
	put_word(sysappinfoptr,0x1245);//dmlasterr
	sysappinfoptr += 2;
	put_long(sysappinfoptr,newexlist);//exception list
	sysappinfoptr += 4;

	put_long(sysappinfoptr,A5);//a5 memptr
	sysappinfoptr += 4;
	put_long(sysappinfoptr,STACK);//stackend //was STACK
	sysappinfoptr += 4;
	put_long(sysappinfoptr,outgblend);//globals end
	sysappinfoptr += 4;
	put_long(sysappinfoptr,sysappinfoptrstart);//first appinfo on this thread
	//put_long(sysappinfoptr,0);//hack //first appinfo on this thread
	sysappinfoptr += 4;
	put_long(sysappinfoptr,nullptr_68k);//unused pointer


	curapp = num;
	apps[num].open = true;
	apps[num].openmode = dmModeReadWrite;
	appcall = sysappinfoptrstart;
	appexceptionlist = newexlist;

	//create all record ids
	forgeuniqueids();

	//start lcd driver
	if(!initdisplaydriver())return false;

	//overlay (for os >= 3.5)
	CPTR overlaysettings = getresource(num,0,'xprf');
	if(!overlaysettings || !(get_long(overlaysettings + 2) & bit(0))){//disable overlays if app asks
		curoverlay = numfromtypecreator(0,'ovly',belong(apps[num].creator.typen));
		if(curoverlay > -1){
			apps[curoverlay].open = true;
			apps[curoverlay].openmode = dmModeReadWrite;
		}
	}else{
		dbgprintf("App %d has banned overlays.\n",num);
		curoverlay = -1;
	}

	return true;
}

bool full_init(std::string& palmname, int w, int h){
	//create lcd framebuffer
	lcd_init(w,h);

	//cpu / memory
	initARM();//set up arm cpu,for palm os 5 native arm apps
	if(CPU_init(&palm))return false;
	resetmallocstate();//palm os memory state

	//Sets default database and sdcard filesystem values
	init_filesystem_driver();

	//Used by FtrGet and FtrSet
	reset_and_load_default_features();

	//Using 68k code as apis whenever possible
	//install_rom_to_memory(palmosv41_en_m515_rom, palmosv41_en_m515_rom_len);
	//make_api_list_from_rom(palmosv41_en_m515_rom_SysGetTrapAddress);

	//set all start values
	username = palmname;

	keymask = 0;
	BTNTBL = 0;
	PENX = 0;
	PENY = 0;
	PENDOWN = false;

	fullticks = 0;
	partialticks = 0.0;
	starttime = std::chrono::high_resolution_clock::now();

	textclipbank = getnewlinearchunks(1) << 16;
	emulstate = getnewlinearchunks(1) << 16;

	TEMPHACK;
	palm.regs.intmask = 0;//allow interupts

	return true;
}

void full_deinit(){
	wipeeventqueue();
	releasefilemem();
	deinitdisplaydriver();
	memory_deinit();
	clear_rommemory();
}
