/*
	File:			Select.cpp

	Description:	Exports the top-level Select() function called by WinMain() in 
					SimpleInstaller.cpp.

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

STATIC DWORD gUser,gSlot;

///////////////////////////////////////////////////////////////////////////////
// Name: GetLastUser (utility)
// Desc: Helper function returning the account that was last sync-ed to the
//		 host; uses explicit registry lookup, which is NOT recommended;
//		 there should be a reglamented InstAIDE or USER function for doing that...
//Misc: TODO: look up for standard way to do that.
STATIC LPCTSTR WINAPI GetLastUser(VOID)
{
  STATIC TCHAR last[256];
  HKEY hKey = 0;
  RegOpenKey(HKEY_CURRENT_USER,"Software\\U.S. Robotics\\Pilot Desktop\\Preferences",&hKey);
  
  if (hKey)
  {
    DWORD type;
    DWORD size = SIZEARR(last);
    RegQueryValueEx(hKey,"LastUserName",NULL,&type,LPBYTE(last),&size);
    RegCloseKey(hKey);
  }

  return last;
}

///////////////////////////////////////////////////////////////////////////////
// Name: GetSelectedUser (utility)
// Desc: UI helper.
//
STATIC DWORD WINAPI GetSelectedUser(HWND hWndCombo)
{
  DWORD dwID;
  TCHAR name[256];
  UINT  uSel = SendMessage(hWndCombo,CB_GETCURSEL,0,0);
  SendMessage(hWndCombo,CB_GETLBTEXT,uSel,LPARAM(name));
  
  if (S_OK != PlmGetUserIDFromName(name,&dwID))
    dwID = 0;

  return dwID;
}

///////////////////////////////////////////////////////////////////////////////
// Name: UpdateSelection (utility)
// Desc: UI helper.
//
//	Note:	This routine has no protection against users who have
//			fewer than 3 slots or differnt types of slots.  In the future,
//			this should dynamically build a pulldown list of slots based
//			on the user's saved slot configuration (sync.ini).
//

STATIC VOID WINAPI UpdateSelection(HWND hWnd)
{
  DWORD list[SLOT_ENTRY_LIST_LENGTH] = { 0 };
  WORD  size = SLOT_ENTRY_LIST_LENGTH;
  DWORD id = GetSelectedUser(GetDlgItem(hWnd,IDC_USER));

  gUser = id;		// Set this before we return.  This will be the external
					// sign that something went wrong in user
					// selection if it is 0.
  //
  // Translate the Tapwave DAL numbering of cards (SLOT_LEFT, SLOT_RIGHT,
  // SLOT_INTERNAL) into the slot IDs that were last returned from the device.
  //
  if (S_OK == UmSlotGetInfo(id,list,&size))
  {
    if (IsDlgButtonChecked(hWnd,IDC_CARD_PRIMARY))
      gSlot = list[SLOT_LEFT];
    else if (IsDlgButtonChecked(hWnd,IDC_CARD_SECONDARY))
      gSlot = list[SLOT_RIGHT];
    else if (IsDlgButtonChecked(hWnd,IDC_CARD_INTERNAL))
      gSlot = list[SLOT_INTERNAL];
    else
      gSlot = MAXDWORD;
  }
}

///////////////////////////////////////////////////////////////////////////////
// Name: EnableControl(utility)
// Desc: Simple UI helper, takes care of providing correct default selection.
//
STATIC VOID WINAPI EnableControl(HWND hWnd,UINT uID,BOOL bEnable)
{
  EnableWindow(GetDlgItem(hWnd,uID),bEnable);
  if (!bEnable)
    CheckDlgButton(hWnd,uID,bEnable ? BST_CHECKED : BST_UNCHECKED);
}

///////////////////////////////////////////////////////////////////////////////
// Name: UpdateMemorySlotsWhenUserChanged
// Desc: Different user accounts may correspond to different devices and hence
// different device capabilities; this function queries the card availability
// for the currently selected user account and updates the card options
// accordingly.
// Note: This is a simplified function which only deals with up to 3 possible
// card slots; you will need to enhance it for devices with more slots.
//
STATIC VOID WINAPI UpdateMemorySlotsWhenUserChanged(HWND hWnd,DWORD id)
{
  WORD  max = 0;

  // Presume no cards are available
  EnableControl(hWnd,IDC_CARD_PRIMARY,FALSE);
  EnableControl(hWnd,IDC_CARD_SECONDARY,FALSE);
  EnableControl(hWnd,IDC_CARD_INTERNAL,FALSE);

  UmSlotGetSlotCount(id,&max);
  if (max)
  {
	// If at least one slot available, enable the Install button
	EnableControl (hWnd, IDOK, TRUE);
	SetDlgItemText(hWnd, IDC_STATUS_NO_SLOTS, "");

	// If at least one slot is available then we have a default selection
    CheckDlgButton(hWnd,IDC_CARD_INTERNAL,BST_CHECKED);
    EnableControl(hWnd,IDC_CARD_INTERNAL,TRUE);

	// More than one slot? Enable the second radio button
	if (1 < max)
      EnableControl(hWnd,IDC_CARD_PRIMARY,TRUE);

	// More than two slots? Enable the third radio button
	if (2 < max)
      EnableControl(hWnd,IDC_CARD_SECONDARY,TRUE);
  }
  else
  {	// max slots was 0 - meaning no slots found so far.
	// Either this user has none, or he has not been sync'd yet.
	  EnableControl (hWnd, IDOK, FALSE);
	  SetDlgItemText(hWnd, IDC_STATUS_NO_SLOTS, "User has no known slots.  Please sync or select another user.");
  }
}

///////////////////////////////////////////////////////////////////////////////
// Name: OnSelect (listener)
// Desc: Dispatches the user selection change notification to the appropriate
//		 event processor.
STATIC VOID WINAPI OnSelect(HWND hWnd,HWND hWndCombo)
{
  UpdateMemorySlotsWhenUserChanged(hWnd,GetSelectedUser(hWndCombo));
}

///////////////////////////////////////////////////////////////////////////////
// Name: AddUser (utility)
// Desc: Helper for adding entry to a combo box.
STATIC VOID WINAPI AddUser(HWND hWnd,HWND hWndCombo,LPCTSTR name)
{
  DWORD ind = SendMessage(hWndCombo,CB_ADDSTRING,0,LPARAM(name));
  if (0 == ind)
  {
    SendMessage(hWndCombo,CB_SETCURSEL,0,0);
    UpdateMemorySlotsWhenUserChanged(hWnd,0);
  }
}

///////////////////////////////////////////////////////////////////////////////
// Name: OnCreate
// Desc: Classic dialog initialization routing.
//		 Populates the list box with user accounts by enumerating all HotSync
//		 registered accounts. Also provides default slot selection.
//
STATIC BOOL WINAPI OnCreate(HWND hWnd)
{
  SHORT max=UmGetUserCount();

  if (max)
  {
    for (SHORT i=0;i<max;i++)
    {
      DWORD id;
      TCHAR name[256];
      SHORT size = SIZEARR(name);
      UmGetUserID(i,&id);
      UmGetUserName(id,name,&size);
      AddUser(hWnd,GetDlgItem(hWnd,IDC_USER),name);
    }

	// Walk the extra mile...get the last user and set it up as default selection
	UINT uIndex = SendDlgItemMessage(hWnd,IDC_USER,CB_FINDSTRING,0,LPARAM(GetLastUser()));

	// Provide default selection for the target card
	SendDlgItemMessage(hWnd,IDC_USER,CB_SETCURSEL,uIndex,0);
    UpdateMemorySlotsWhenUserChanged(hWnd,GetSelectedUser(GetDlgItem(hWnd,IDC_USER)));

    TCHAR tempstring[1024];
    
    GetPrivateProfileString(
        "SimpleInstaller",     
        "Welcome",       
        "Welcome to Tapwave Install",
        tempstring, 
        1024,       
        gIniFile        
        );
    
    
    SetDlgItemText(hWnd,IDC_WELCOME,tempstring);
    GetPrivateProfileString(
        "SimpleInstaller",     
        "WelcomeText",       
        "Some files need to be copied onto your Zodiac device.",
        tempstring, 
        1024,       
        gIniFile        
        );

	// Turn the newline strings into real newline characters.
    char *a = tempstring;
    while (*a)
    {
        if (*a == '\\' && *(a+1) == 'n')
        {
            *a = ' ';
            *(a + 1) = '\n';
        }
        a++;
    }
    
    SetDlgItemText(hWnd,IDC_WELCOMEMESSAGE,tempstring);
  }

  return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Name: OnCommand
// Desc: Installer preferences dialog command processor
//
STATIC BOOL WINAPI OnCommand(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
  BOOL bExit = FALSE;
  
  switch(wParam)
  {
  // User cancel
  case SC_CLOSE   :
  case IDCANCEL   :
    bExit = EndDialog(hWnd,FALSE);
    break;

  // OK button: collect selection, close dialog
  case IDOK       :
    UpdateSelection(hWnd);
    bExit = EndDialog(hWnd,TRUE);
    break;

  // User selection change notification
  case MAKELONG(IDC_USER,LBN_SELCHANGE) :
    OnSelect(hWnd,HWND(lParam));
    break;
  }

  return bExit;
}


///////////////////////////////////////////////////////////////////////////////
// Name: MyDlgProc
// Desc: Main application dialog's handler.
//
STATIC BOOL WINAPI MyDlgProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
  BOOL bExit = FALSE;

  switch(uMsg)
  {
  case WM_INITDIALOG  : bExit = OnCreate(hWnd); break;
  case WM_SYSCOMMAND  : bExit = OnCommand(hWnd,0xFFF0 & wParam,lParam); break;
  case WM_COMMAND     : bExit = OnCommand(hWnd,wParam,lParam); break;
  }

  return bExit;
}


///////////////////////////////////////////////////////////////////////////////
// Name: Select
// Desc: Top-level function for collection installation preferences from the user.
// Input:hInstance - our DLL instance handle, needed by various UI function
//		 dwUser	   - pointer to a variable where we should store the ID of the
//					 user account in HotSync to install the files to.
//		 dwSlot	   - pointer to a variable to select destination slot for the
//					 files that need to be installed on external card.
// Exit: TRUE on success, FALSE on user cancel
// Misc: In real life one would probably want to pass a structure or object
//		 for the user preferences.
//
HRESULT WINAPI Select(HINSTANCE hInstance,DWORD* dwUser,DWORD* dwSlot)
{
  BOOL bExit = DialogBoxParam(hInstance,MAKEINTRESOURCE(IDD_MAIN),HWND_DESKTOP,MyDlgProc, 0);
  if (bExit)
  {
    *dwUser = gUser;
    *dwSlot = gSlot;
  }

  return bExit ? S_OK : E_FAIL;
}