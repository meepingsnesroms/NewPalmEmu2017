//Tapwave zodiac firmware emulation
#include "m68k.h"
#include "minifunc.h"
#include "palmapi.h"
#include "astrology.h"
#include "dataexchange.h"
#include "palmdefines.h"

void palmabrt();//hack



void twloadmodule(){
	stacklong(dbtype);
	stacklong(dbcreator);
	stacklong(dbresourcetype);
	stacklong(resourceid);
	stacklong(flags);
	stackptr(nativefunction);//(pointer to pointer)

	palmabrt();//hack

	D0 = errNone;
}

void tapwavedispatch(){
	//This trap is just a switch statement!

	SELECTOR{
		SELAPI(trapTwLoadModule,twloadmodule());


		default:
			dbgprintf("Selector Function:%d\n",D2);
			palmabrt();//hack
			break;
	}
}
