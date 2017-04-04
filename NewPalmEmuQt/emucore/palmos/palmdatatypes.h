#ifndef DATATYPES
#define DATATYPES

#include "m68k.h"
#include <vector>

typedef union{
	uint8_t typec[4];//type as string
	uint32_t typen;//type as number
}TYPE;

typedef struct{
	TYPE type;
	uint16_t id;
	uint32_t uniqueid;/*this is a 24 bit value*/ //for records only
	offset_68k location;
	//attr flags
	uint8_t attr = 0;//pdb specification says uint8_t
	//uint16_t attr = 0;
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
		uint16_t flags;
		uint16_t fileattr;
	};
	uint16_t version = 0;
	uint32_t creationtime;
	uint32_t modificationtime;
	uint32_t backuptime = 0;
	uint32_t modnum = 0;
	uint32_t appinfo = 0;
	uint32_t sortinfo = 0;
	TYPE type;
	TYPE creator;
	uint32_t uuidseed = 0;
	uint32_t nextrecordlist = 0;
	uint16_t numrecords = 0;

	//my data
	std::vector<palmresource> parts;
	bool resdb;
	//runtime data
	bool open = false;
	unsigned int opencount = 0;
	uint16_t openmode = 0;
	bool waschanged = false;//changed or created by app
	//execution data
	bool exe = false;
	offset_68k intmain;//code1 main function
	offset_68k thisglobals;
	offset_68k icon = 0;//for app launcher
}palmdb;

typedef struct{
	//TYPE creator;
	uint32_t creator;
	uint16_t id;
	uint32_t value;
	bool read_only;
}feature;

typedef struct{
  uint8_t attributes;
  uint8_t uniqueID[3];
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

