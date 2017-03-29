/******************************************************************************
 *
 * Copyright (c) 1995-2002 PalmSource, Inc. All rights reserved.
 *
 * File: ToDoDB.h
 *
 * Release: Palm OS Developer Suite 5 SDK (68K) 4.0
 *
 * Description:
 *		Header for the To Do Manager
 *
 *****************************************************************************/

#ifndef __TDTODOMGR_H__
#define __TDTODOMGR_H__

#include <DateTime.h>

#ifdef __GNUC__
#include "sections.h"
#endif

#ifndef __GNUC__
#define EXTRA_SECTION_ONE
#endif

#define LocalizedAppInfoStr	1000

#define todoLabelLength			12
#define todoNumFields			16

#define toDoMaxPriority			5

// Dirty flags for to do application info
#define toDoSortByPriorityDirty	0x0001

// Sort orders
#define soDueDatePriority		0
#define soPriorityDueDate		1
#define soCategoryPriority		2
#define soCategoryDueDate		3


typedef struct {
    UInt16			renamedCategories;	// bitfield of categories with a different name
	char 				categoryLabels[dmRecNumCategories][dmCategoryLength];
	UInt8 			categoryUniqIDs[dmRecNumCategories];
	UInt8				lastUniqID;	// Uniq IDs generated by the device are between
										// 0 - 127.  Those from the PC are 128 - 255.
	UInt8				reserved1;	// from the compiler word aligning things
	UInt16			reserved2;
	UInt16			dirtyAppInfo;
	UInt8				sortOrder;
	UInt8				reserved3;
} ToDoAppInfoType;

typedef ToDoAppInfoType * ToDoAppInfoPtr;

// ToDoDBRecord.
//
// All strings are null terminated and appear within the record.
//
typedef struct {
	DateType dueDate;
	UInt8 priority;		// high bit is complete flag
	char description;
} ToDoDBRecord;

typedef ToDoDBRecord				ToDoDBRecordType;
typedef ToDoDBRecord*			ToDoDBRecordPtr;

// sizeDBRecord is the minimum size for the ToDoDBRecord structure.
// It assumes empty 'description' and 'note' fields.
// sizeDBRecord allocates an extra byte for the null character
// for the note string.
#define sizeDBRecord (sizeof (ToDoDBRecord) + 1)

// ToDoItemType
//
// This is the format of a to do record used by the application.  All 
// pointers are either NULL or point to data within the PackedDB record.
// All strings are null character terminated.
//
typedef struct {
	DateType 			dueDate;
	UInt8 				priority;		// high bit is complete flag
	UInt8					reserved;
	Char *				description;
	Char *				note;
} ToDoItemType;

typedef ToDoItemType * ToDoItemPtr;


#define completeFlag 	0x80
#define priorityOnly 	~completeFlag
#define toDoNoDueDate	0xffff


// Used for ToDoChangeRecord.
typedef enum  { 
	toDoPriority,
	toDoComplete,
	toDoDueDate,
	toDoDescription,
	toDoNote,
	toDoCategory } ToDoRecordFieldType;



#ifdef __cplusplus
extern "C" {
#endif


//-------------------------------------------------------------------
// Routines
//-------------------------------------------------------------------
Err ToDoNewRecord(DmOpenRef dbP, ToDoItemPtr item, UInt16 category, UInt16 *index)EXTRA_SECTION_ONE;

Err ToDoInsertNewRecord (DmOpenRef dbP, UInt16 * index) EXTRA_SECTION_ONE;

Err ToDoChangeRecord(DmOpenRef dbP, UInt16 * index, 
	ToDoRecordFieldType changedField, const void * data) EXTRA_SECTION_ONE;

Err ToDoChangeSortOrder(DmOpenRef dbP, UInt8 sortOrder) EXTRA_SECTION_ONE;

Err ToDoAppInfoInit(DmOpenRef dbP) EXTRA_SECTION_ONE;

MemHandle ToDoGetAppInfo  (DmOpenRef dbP) EXTRA_SECTION_ONE;

UInt8 ToDoGetSortOrder (DmOpenRef dbP) EXTRA_SECTION_ONE;

void ToDoSort (DmOpenRef dbP) EXTRA_SECTION_ONE;

Err ToDoGetDatabase (DmOpenRef *dbPP, UInt16 mode) EXTRA_SECTION_ONE;

void ToDoSetDBBackupBit (DmOpenRef dbP) EXTRA_SECTION_ONE;


#ifdef __cplusplus
}
#endif


#endif
