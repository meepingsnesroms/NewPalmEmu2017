/*
	File:			SimpleInstaller.cpp

	Description:	Main program file, defines the program entry point WinMain().

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
#include "SimpleInstaller.rc.hpp"

#ifdef _DEBUG
#pragma comment(lib,"../../Desktop/InstAided")
#pragma comment(lib,"../../Desktop//UserDatad")
#pragma comment(linker,"/delayload:InstAided.dll")
#pragma comment(linker,"/delayload:UserDatad.dll")
#else
#pragma comment(lib,"../../Desktop/InstAide")
#pragma comment(lib,"../../Desktop//UserData")
#pragma comment(linker,"/delayload:InstAide.dll")
#pragma comment(linker,"/delayload:UserData.dll")
#endif


// Palm key in the registry where the Hotsync settings are stored;
// note that using this key is against the recommendations of the
// Palm Conduit Development kit; see LoadPalmModules() note for details.
//
#define REG_PALM  "Software\\U.S. Robotics\\Pilot Desktop\\Core"

//
// Global vars
//
TCHAR gIniFile[MAX_PATH];		// The name of the .ini file driving the installation.
TCHAR gAppName[MAX_PATH];		// The name of the app being installed.


////////////////////////////////////////////////////////////////
// Global module definitions
//
STATIC HMODULE gInstAide;				// InstAide DLL module handle
STATIC HMODULE gUserData;				// UserData DLL module handle


////////////////////////////////////////////////////////////////
// Name: LoadSpecial
// Desc: Helper function, contactenates the passed path and file name
// and returns the result of a LoadLibrary attempt over the result.
//
STATIC HMODULE WINAPI LoadSpecial(LPCTSTR path,LPCTSTR name)
{
  TCHAR work[MAX_PATH];
  
  PathCombine(work,path,name);
  return LoadLibraryEx(work,0,LOAD_WITH_ALTERED_SEARCH_PATH);
}


////////////////////////////////////////////////////////////////
// Name: LoadPalmModules
// Desc: High-level function to load the HotSync DLLs that we
// need in order to operate; note we use DELAY LOADed DLLs.
// Also note that we search for them in a folder that we obtain
// directly from the registry. Using a registry key presents
// sime compatibility risks and the Palm CDK advises against
// such practices. Instead, it suggests that you pack an InstAide
// file with your installation and use it to obtain the path
// via UmGetRootDirectory or other similar function.
// Input: none
// Exit : TRUE on success, FALSE else
//
STATIC BOOL WINAPI LoadPalmModules(VOID)
{
  HKEY  hKey = 0;
  BOOL  bExit = FALSE;
  
  //  Get the location where Hotsync was installed and where our DLLs should be located...
  //  UmGetRootDirectory
  if (S_OK == RegOpenKey(HKEY_CURRENT_USER,REG_PALM,&hKey))
  {
    TCHAR path[MAX_PATH];
    DWORD size = SIZEARR(path);
    DWORD type;
    
    if (S_OK == RegQueryValueEx(hKey,"DesktopPath",0,&type,LPBYTE(path),&size))
    {
      // Attempt to load the DLLs we are about to use...
#ifdef _DEBUG
      gInstAide = LoadSpecial(path,"InstAided.dll");
      gUserData = LoadSpecial(path,"UserDatad.dll");
#else
      gInstAide = LoadSpecial(path,"InstAide.dll");
      gUserData = LoadSpecial(path,"UserData.dll");
#endif
      bExit = (NULL != gInstAide) && (NULL != gUserData);
    }
    
    RegCloseKey(hKey);
  }
  
  return bExit;
}


/////////////////////////////////////////////////////////////////////////////////
// Name: WinMain
// Desc: Main program entry point
// Note: 
//
INT WINAPI WinMain(HINSTANCE hInstance,HINSTANCE,LPTSTR,INT)
{
  DWORD dwUser,dwSlot;
  
  // Common application UI initialization
  InitCommonControls();
  
  // In order to function properly we need to access certain Hotsync DLL APIs;
  // those are DELAY LINK-ed to our project via LIB files because we expect them
  // to be available on the destination computer although not in our directory.
  // So our very first job is to find where they are and load them.
  if (!LoadPalmModules())
  {
    // Hotsync was not found, most probably Palm Desktop was not installed
    MessageBox(HWND_DESKTOP,"The installation could not find HotSync on this machine and is unable to continue.",0,MB_OK);
	goto CommonEnd;
  }
  
  // Make sure the InstAide supports the extra TapWave function for direct
  // installation to card as we plan on using it; note that unless you NEED to use
  // that function you may as well simply go on and NOT install to card (but in RAM for example).
  // The required library version is 5.2.6 or greater for Userdata.dll and 5.2.7 for
  // instaide.dll.
  DWORD vmaj, vmin;
  PlmGetLibVersion(&vmaj, &vmin);
  if ((vmaj < 5) || ((vmaj == 5) && (vmin < 2))) {
    MessageBox(HWND_DESKTOP,"The installer requires an updated version of HotSync Manager (Instaide.dll).  Please install HotSync Manager from the Tapwave CD-ROM.",0,MB_OK);
	goto CommonEnd;
  }

    UmGetLibVersion (&vmaj, &vmin);
    if ((vmaj < 5) || ((vmaj == 5) && (vmin < 2))) {
        MessageBox(HWND_DESKTOP,"The installer requires an updated version of HotSync Manager (UserData.dll).  Please install HotSync Manager from the Tapwave CD-ROM.",0,MB_OK);
        goto CommonEnd;
    }

	// Set up a few global vars here by reading values in from the installer's .ini file

	// Obtain path to the installation configuration file; note it is supposed to
    // be in the same folder where the executable itself is, and has the same name (except
	// for the extension).
    GetModuleFileName(hInstance,gIniFile,SIZEARR(gIniFile));
    PathRenameExtension(gIniFile,".ini");
    
	// First, find the name of the app we are installing.  This will be used in 
	// several strings presented to the user.
    GetPrivateProfileString(
        "SimpleInstaller",			// Section Name
        "AppName",					// Key Name
        "Application",				// Default String
        gAppName,					// Buffer
        MAX_PATH,					// Size of buffer
        gIniFile					// Name of .ini file
        );

  // Here is where your actuall installation process starts.
  // In this example we are going directly to ask the user to choose account
  // and destination card for the Palm OS files; in a real installation you may need
  // to set up a simple installation wizard to collect all neccessary information for
  // the installation.
  if (S_OK == Select(hInstance,&dwUser,&dwSlot))
  {
    // Data was successfuly collected...go and install!
    HRESULT err = Install(hInstance,dwUser,dwSlot);
    LastMessage(hInstance,err);
  }
  
CommonEnd: 
  return 0;
}