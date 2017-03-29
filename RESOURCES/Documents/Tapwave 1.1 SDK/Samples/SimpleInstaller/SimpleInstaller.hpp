/*
	File:			SimpleInstaller.hpp

	Description:	Installer header file.

	Author:			

	Copyright:		Copyright © 2003 by Tapwave, Inc.

	Disclaimer:		IMPORTANT:  This Tapwave software is provided by Tapwave, Inc. ("Tapwave").  Your 
					use is subject to and governed by terms and conditions of the Software Development 
					Kit Agreement ("SDK Agreement") between you and Tapwave.  If you have not entered 
					into Tapwave’s standard SDK Agreement with Tapwave, you have no right or license 
					to use, reproduce, modify, distribute or otherwise exploit this Tapwave software.  
					You may obtain a copy of Tapwave’s standard SDK Agreement by calling 650-960-1817
					or visiting Tapwave at http://www.tapwave.com/developers/. 

	Change History (most recent first):
				
*/

#pragma once
#pragma pack(1)
#pragma warning(disable:4097)               // typedef-name used as synonym for class-name 
#pragma warning(disable:4127)               // conditional expression is constant
#pragma warning(disable:4166)               // illegal calling convention for constructor/destructor
#pragma warning(disable:4201)               // nonstandard extension used : nameless struct/union
#pragma warning(disable:4284)               // operator -> will produce errors if applied using infix notation
#pragma warning(disable:4355)               // this used in base member initializer list
#pragma warning(disable:4511)               // copy constructor could not be generated
#pragma warning(disable:4512)               // assignment operator could not be generated
#pragma warning(disable:4514)               // unreferenced inline function has been removed
#pragma warning(disable:4710)               // function not inlined
#pragma warning(disable:4711)               // function selected for automatic inline expansion
#pragma warning(disable:4786)               // identifier was truncated to '255' characters in the browser information
#if !defined(DEBUG) && !defined(_DEBUG)
# pragma warning(disable:4100)              // unreferenced formal paramter
# pragma warning(disable:4101)              // unreferenced local variable
# pragma warning(disable:4102)              // unreferenced label
# pragma warning(disable:4189)              // local variable is initialized but not referenced
# pragma warning(disable:4505)              // unreferenced local function has been removed
# pragma warning(disable:4508)              // function should return a value; 'void' return type assumed 
#endif

#include <ole2.h>
#include <tchar.h>
#include <shlwapi.h>
#include <commctrl.h>
#include "../../Desktop/InstAide.h"
#include "../../Desktop/UserData.h"

#pragma comment(lib,"USER32")
#pragma comment(lib,"KERNEL32")
#pragma comment(lib,"ADVAPI32")
#pragma comment(lib,"COMCTL32")
#pragma comment(lib,"SHLWAPI")
#pragma comment(lib,"DELAYIMP")


#define STATIC                              static
#define COMMON                              _declspec(selectany)
#define SIZEARR(arr)                        (sizeof(arr)/sizeof(arr[0]))

#define SLOT_LEFT	0
#define SLOT_RIGHT	1
#define SLOT_INTERNAL	2

#define SLOT_ENTRY_LIST_LENGTH	16

#define AI_PROFILE_INT_DEFAULT	1000	// default/error value from GetProfileInt
#define AI_PROFILE_STR_DEFAULT	"%%"	// default/error value from GetProfileStr

// Error codes
#define AI_ERR_INI_FILE_READ	100		// problem reading .ini file, section, or key
#define AI_ERR_SOURCE_FILENAME_READ	101	// Problem reading source file name from .ini
#define AI_ERR_TARGET_MEDIA_READ	102	// Problem reading target media from .ini
#define AI_ERR_UNKNOWN_TARGET_TYPE	103	// Strange value in TARGET key
#define AI_ERR_FOLDER_READ			104	// Problem reading Folder key from .ini
#define AI_ERR_UNKNOWN				105	// Unknown error - shouldn't happen
#define AI_ERR_PALM_USER_INFO		106	// Problem getting info from user.dat file.

// Useful constants
#define TAPWAVE_INSTALL_CONDUIT_CREATOR 'TWci'

//
// External declarations of global vars.
//
extern TCHAR gAppName[MAX_PATH];
extern TCHAR gIniFile[MAX_PATH];	// The name of the .ini file driving the installation.

// Select is a high level function for collecting the neccessary data
// for the installation from the user; typically, an installation needs
// more than just target account and extension slot, so you may want to
// extend that function to a little installation wizzard which will collect
// and prepare the installation preferences.
HRESULT WINAPI Select (HINSTANCE hInstance,DWORD* dwUser,DWORD* dwSlot);

// Install is the core installation function which takes the configuration
// data collected by Select() and does the core installation.
HRESULT WINAPI Install(HINSTANCE hInstance,DWORD  dwUser,DWORD  dwSlot);

// Final installation screen prompting the users to sync; in real life 
// this would not be neccessary as it should be simply the last screen
// of the interface wizard
VOID    WINAPI LastMessage(HINSTANCE hInstance,DWORD  dwError);
