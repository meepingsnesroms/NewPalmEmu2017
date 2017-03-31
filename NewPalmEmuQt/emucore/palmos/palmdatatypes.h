#ifndef DATATYPES
#define DATATYPES

#include "m68k.h"
#include <vector>

typedef union{
	UBYTE typec[4];//type as string
	ULONG typen;//type as number
}TYPE;

typedef struct{
	TYPE type;
	UWORD id;
	ULONG uniqueid;/*this is a 24 bit value*/ //for records only
	CPTR location;
	//attr flags
	UBYTE attr = 0;//pdb specification says UBYTE
	//UWORD attr = 0;
	/*
	bool busyF = false;
	bool secretF = false;
	bool dirtyF = false;
	bool deleteF = false;
	*/
	//my data
	size_t_68k size;
	int lockcount = 0;
}palmresource;

typedef struct{
	//palm data
	char name[32];
	union{
		UWORD flags;
		UWORD fileattr;
	};
	UWORD version = 0;
	ULONG creationtime;
	ULONG modificationtime;
	ULONG backuptime = 0;
	ULONG modnum = 0;
	ULONG appinfo = 0;
	ULONG sortinfo = 0;
	TYPE type;
	TYPE creator;
	ULONG uuidseed = 0;
	ULONG nextrecordlist = 0;
	UWORD numrecords = 0;

	//my data
	std::vector<palmresource> parts;
	bool resdb;
	//runtime data
	bool open = false;
	unsigned int opencount = 0;
	UWORD openmode = 0;
	bool waschanged = false;//changed or created by app
	//execution data
	bool exe = false;
	CPTR intmain;//code1 main function
	CPTR thisglobals;
	CPTR icon = 0;//for app launcher
}palmdb;

typedef struct{
	TYPE creator;
	UWORD id;
	ULONG value;
}feature;

typedef struct{
  UBYTE attributes;
  UBYTE uniqueID[3];
}SortRecordInfoType;



/*
//offsets in palm structs
struct{
	struct{
		enum{
			displayWidthV20 = 0,
			displayHeightV20 = 2,
			displayAddr = 4,
			windowFlags = 8,
			windowBounds = 10,
			clippingBounds = 18,
			bitmapP = 26
		};
	} WindowType;
} Offsets;
*/

/*
struct{
	enum{
		FormType = 68,
		WindowType = 40,
		DrawStateType = 20,
		BitmapType = 16,
		AbsRectType = 8,
		RectangleType = 8
	};
} ObjSize;
*/

#endif // DATATYPES

