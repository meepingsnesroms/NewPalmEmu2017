// mfcembed.h : main header file for the MFCEMBED application
//

#if !defined(AFX_MFCEMBED_H__D7EEB5CE_D1F1_4C8F_A7BC_EA599797703D__INCLUDED_)
#define AFX_MFCEMBED_H__D7EEB5CE_D1F1_4C8F_A7BC_EA599797703D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMfcembedApp:
// See mfcembed.cpp for the implementation of this class
//

class CMfcembedApp : public CWinApp
{
public:
	CMfcembedApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcembedApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CMfcembedApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCEMBED_H__D7EEB5CE_D1F1_4C8F_A7BC_EA599797703D__INCLUDED_)
