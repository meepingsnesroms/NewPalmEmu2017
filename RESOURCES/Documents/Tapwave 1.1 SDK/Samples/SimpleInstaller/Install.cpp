/*
	File:			Install.cpp

	Description:	Exports the top-level Install() function called by WinMain() 
					in SimpleInstaller.cpp.

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

#include "SimpleInstaller.hpp"


////////////////////////////////////////////////////////////////////////
// Name: GetRealPath (utility)
// Desc: Generates full path name given a path and a file.
//
STATIC LPTSTR GetRealPath(LPCTSTR ini,LPCTSTR source)
{
  STATIC TCHAR work[MAX_PATH];
  lstrcpyn(work,ini,SIZEARR(work));
  PathRemoveFileSpec(work);
  PathCombine(work,work,source);
  return work;
}

///////////////////////////////////////////////////////////////////////
// Name: InstallToRAM
// Desc: Core installer routine. Schedules a file for installation to
//		 RAM by invoking the appropraite InstAide API function.
// Input:
//		dwUser	- Hotsync user account iD
//		ini		- project (INI) file; needed to produce full source path name
//		source	- name of the source file, relative to the project (INI) file
//
// Returns: S_OK - all is well
//			an error from UmGetUserName
//			an error from PltInstallFile
//
//	kcr		9/29/03		When destination is not internal card, send files
//						to external card.
//
STATIC HRESULT WINAPI InstallToRAM (DWORD dwUser, DWORD dwSlot, LPCTSTR ini,
									LPCTSTR source)
{
	TCHAR name[256];
	SHORT size = SIZEARR(name);
	HRESULT rv = S_OK;

	DWORD list[SLOT_ENTRY_LIST_LENGTH] = { 0 };
	WORD  listLen = SLOT_ENTRY_LIST_LENGTH;

	//
	// Translate the Tapwave DAL numbering of cards (SLOT_LEFT, SLOT_RIGHT,
	// SLOT_INTERNAL) into the slot IDs that were last returned from the device.
	// First fetch the slot list for this user:
	rv = UmSlotGetInfo(dwUser, list, &listLen);
	if (rv != S_OK)
		return rv;
 
	// Get the user name
	rv = UmGetUserName(dwUser,name,&size);
	if (rv > 0)
	{
		// Install the file - if destination is SLOT_INTERNAL,
		// use the standard RAM-install option.  If the destination
		// is one of the external slots, use the standard slot
		// install function.
		if (dwSlot == list[SLOT_INTERNAL])
		{	// Writing whole package of files to internal card
			rv = PltInstallFile(name,GetRealPath(ini,source));
			if (rv != S_OK)
			  return rv;	// A PltInstallFile error
		}
		else // Destination is an external card
		{
			rv = PlmSlotInstallFile (dwUser, dwSlot, source);
			if (rv != S_OK)
				return rv;
		}
	}
    
    return rv;		// A UmGetUserName error
}

///////////////////////////////////////////////////////////////////////
// Name: InstallToCARD
// Desc: Core installer routine. Schedules a file for installation to
//		 an external media card by invoking the appropraite InstAide API function.
// Input:
//		dwUser,
//		dwSlot	- installation configuration settings selected by the user
//		ini		- project (INI) file; needed to produce full source path name
//		source	- name of the source file, relative to the project (INI) file
//		folder	- target directory for the file
//
// Returns: an error from PlmSlotInstallToFile or 0
//
STATIC HRESULT WINAPI InstallToCARD(DWORD dwUser,DWORD dwSlot,LPCTSTR ini,LPCTSTR source,LPCTSTR folder)
{
  return PlmSlotInstallFileToDir(dwUser,dwSlot,GetRealPath(ini,source),folder,
        TAPWAVE_INSTALL_CONDUIT_CREATOR);
}

////////////////////////////////////////////////////////////////////////
// Name: FileInstall
// Desc: Install() helper, processes one file from the INI file.
// Input:
//		ini		- full path of our project (INI) file
//		index	- index of the file to install from the project file
//		dwUser,dwSlot - user installation preferences
//
STATIC HRESULT WINAPI FileInstall(LPCTSTR ini,UINT index,DWORD dwUser,DWORD dwSlot)
{
  TCHAR key[32];
  TCHAR source[MAX_PATH];   // Source file path, relative to .INI file
  TCHAR target[MAX_PATH];   // RAM or (CARD or SLOT)
  TCHAR folder[MAX_PATH];   // Folder to install, if target is CARD
  TCHAR defaultSource[MAX_PATH];	// default source path from .ini file
  DWORD	sourceLen;
  typedef enum FileTarget { trgNone=0, trgRAM, trgCard };
  
  // Get the source file path
  lstrcpy (defaultSource, AI_PROFILE_STR_DEFAULT);

  wsprintf(key,"PalmFile%u",index + 1);	// Construct a section name for the i'th file.
  sourceLen = GetPrivateProfileString(key,"Source", defaultSource, source,
			SIZEARR(source),ini);

  if ((sourceLen == 0) || !lstrcmp (source, AI_PROFILE_STR_DEFAULT))
    return AI_ERR_SOURCE_FILENAME_READ;
  
  // Obtain the target media for this file and convert it to an internal type
  // appropraite for processing
  sourceLen = GetPrivateProfileString(key,"Target", defaultSource, target,
			SIZEARR(target),ini);

  if ((sourceLen == 0) || !lstrcmp (target, AI_PROFILE_STR_DEFAULT))
    return AI_ERR_TARGET_MEDIA_READ;
  
  FileTarget trg = trgNone;
  if (0 == lstrcmpi(target,"RAM"))
    trg = trgRAM;
  else if (0 == lstrcmpi(target,"CARD"))
    trg = trgCard;
  else 
    return AI_ERR_UNKNOWN_TARGET_TYPE;			// Incorrect INI file
  
  // Get the target directory if we need it (if the file goes to a card)
  if (trg==trgCard)
  {
	  sourceLen = GetPrivateProfileString(key,"Folder", AI_PROFILE_STR_DEFAULT,
		  folder,SIZEARR(folder),ini);
	  if ((sourceLen == 0) || !lstrcmp (folder, AI_PROFILE_STR_DEFAULT))
		return AI_ERR_FOLDER_READ;
  }
  
  // Install the file according to its type
  switch(trg) 
  {
  case trgRAM:
    return InstallToRAM(dwUser, dwSlot, ini,source);
  case trgCard:
    return InstallToCARD(dwUser,dwSlot,ini,source,folder);
  }
  
  // Should never get here since possible values for trg are tightly controlled
  // above;
  return AI_ERR_UNKNOWN;
}

////////////////////////////////////////////////////////////////////////
// Name: Install
// Desc: Core installation routine called after the user preferences
//		 were taken and we are ready to perform the installation.
// Input:
//		hInstance - our module instance file
//		dwUser,dwSlot - installation variables; in a more common case
//		there should be a structure or object carrying the installation
//		preferences collected from the user.
// Exit:S_OK on OK; Palm CDK error othewise
//
HRESULT WINAPI Install(HINSTANCE hInstance,DWORD dwUser,DWORD dwSlot)
{
  UINT  i,max;
  TCHAR file[MAX_PATH];
  HRESULT rv = S_OK;
  
  // Obtain path to the installation configuration file; note it is supposed to
  // be in the same folder where the executable itself is.
  GetModuleFileName(hInstance,file,SIZEARR(file));
  PathRenameExtension(file,".ini");
  
  // Read the number of files we need to install; note here we presume there will
  // be at least one such file...
  max = GetPrivateProfileInt("SimpleInstaller","PalmFiles",AI_PROFILE_INT_DEFAULT,file);
  
  // Process...
  if (max == AI_PROFILE_INT_DEFAULT)
	  // Error: either .ini file not found or section or key not found.
	  return (AI_ERR_INI_FILE_READ);

  for (i=0;i<max;i++)
  {
    rv = FileInstall(file,i,dwUser,dwSlot);
    if (S_OK != rv)
      return rv;
  }
  
  return rv;
}