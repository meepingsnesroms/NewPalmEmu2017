/*
	File:			Message.cpp

	Description:	Exports the top-level LastMessage() function called by WinMain() 
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

#include <string.h>
#include "SimpleInstaller.hpp"
#include "SimpleInstaller.rc.hpp"


///////////////////////////////////////////////////////////////////////////////
// Name: OnCommand
// Desc: Dialog command processor
//
STATIC BOOL WINAPI OnCommand(HWND hWnd,WPARAM wParam,LPARAM /* lParam */)
{
  BOOL bExit = FALSE;
  
  switch(wParam)
  {
  // User cancel
  case SC_CLOSE   :
  case IDCANCEL   :
  case IDOK       :
    bExit = EndDialog(hWnd,FALSE);
    break;
  }
  return bExit;
}

///////////////////////////////////////////////////////////////////////////////
// Name: MyDlgProc
// Desc: Dialog handler.
//
//	9/22/03		kcr		Added more error handling.
//
STATIC BOOL WINAPI MyDlgProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
  BOOL bExit = FALSE;

  switch(uMsg)
  {
  case WM_INITDIALOG  : 
	  TCHAR msg[512];

	  // Set the upper status message (IDC_STATUS2)
	  switch (lParam) {
	  case S_OK:
		wsprintf(msg, "Success.\n");
		break;

	  default:
		wsprintf(msg, "Error.\n");
		break;
	  } /* end of switch */
	
	  SetDlgItemText(hWnd, IDC_STATUS2, msg);
	  
	// Set the lower status message (IDC_STATUS)
	switch(lParam) {
	case S_OK:
		wsprintf(msg, "%s has been queued for installation.  Please perform a HotSync operation to complete installation.\n",
			gAppName);
		break;

	case ERR_PILOT_FILE_ALREADY_EXISTS:
		wsprintf(msg, "One or more %s files are already queued for installation.  Please perform a HotSync operation to complete installation.\n",
			gAppName);
		break;

	case ERR_PILOT_COPY_FAILED:
		wsprintf(msg, "Unable to copy file to Tapwave Install folder.\n");
		break;

	case ERR_PILOT_INVALID_SOURCE_FILE:
		wsprintf(msg, "Invalid source file.\n");
		break;

	case AI_ERR_INI_FILE_READ:
		wsprintf(msg, "Problem reading .ini file, section name, or key value.\n(Reading number of files.)\n");
		break;

	case AI_ERR_SOURCE_FILENAME_READ:
		wsprintf(msg, "Problem reading source file name from .ini file.\n");
		break;

	case AI_ERR_TARGET_MEDIA_READ:
		wsprintf(msg, "Problem reading target media from .ini file.\n");
		break;

	case AI_ERR_UNKNOWN_TARGET_TYPE:
		wsprintf(msg, "Unknown target media type in .ini file.\n");
		break;

	case AI_ERR_FOLDER_READ:
		wsprintf(msg, "Problem reading destination folder name from .ini file.\n");
		break;

	case AI_ERR_PALM_USER_INFO:
		wsprintf(msg, "Problem reading Palm user information.\n");
		break;

	case AI_ERR_UNKNOWN:
		wsprintf(msg, "Unknown internal error.\n");
		break;

	default:
		wsprintf(msg, "Error code: (%x).", lParam);
		break;
	} /* end of switch */

	  SetDlgItemText(hWnd, IDC_STATUS, msg);
	  bExit = TRUE;
	  break;
  case WM_SYSCOMMAND  : bExit = OnCommand(hWnd,0xFFF0 & wParam,lParam); break;
  case WM_COMMAND     : bExit = OnCommand(hWnd,wParam,lParam); break;
  }

  return bExit;
}



////////////////////////////////////////////////////////////////////////////
// Name: LastMessage
// Desc: Post-install instruction screen. User gets instruction what to do
//		 based on the installation result.
// Input: dwError - error code returned by the Install() function;
//		  in our case this can be only an InstAIDE error, but in a more generic
//		  case one may have their own error codes due to various other problems
//		  during the installation schedule.
//
VOID  WINAPI LastMessage(HINSTANCE hInstance,DWORD  dwError)
{
  DialogBoxParam(hInstance,MAKEINTRESOURCE(IDD_STATUS),HWND_DESKTOP,MyDlgProc,dwError);
}
