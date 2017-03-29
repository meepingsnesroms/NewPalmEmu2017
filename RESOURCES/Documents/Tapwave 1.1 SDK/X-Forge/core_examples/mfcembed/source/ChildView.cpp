// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "mfcembed.h"
#include "ChildView.h"
#include <xforge.h>
#include <xfcore/XFcEmbed.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), NULL, NULL);

	return TRUE;
}

int gSliderValue;

void CChildView::OnPaint() 
{
    gSliderValue=mSlider.GetPos();
	CPaintDC dc(this); // device context for painting
    int fb[240*320];
    for (int i=0;i<240*320;i++)
        fb[i]=rand()+(rand()<<15);
    short * t=embeddedFrame();
    for (i=0;i<320*240;i++) 
    {
        int c=t[i]&0xffff;
        c=((c&0x1f)<<3)+(((c>>6)&0x1f)<<(3+8))+(((c>>11)&0x1f)<<(3+16));
        fb[i]=c;
    }
    
    
    mFrameBuffer.SetBitmapBits(320*240*4,fb);
	CDC sdc;
    sdc.CreateCompatibleDC(NULL);
    sdc.SelectObject(mFrameBuffer);
    dc.BitBlt(0,0,240,320,&sdc,0,0,SRCCOPY);
    Sleep(5);
}

extern INT xfcAppInit();
extern void xfcAppPref(XFcAppPrefs &aAppPrefs);

void __stdcall TimerProccy(
   HWND hWnd,      // handle of CWnd that called SetTimer
   UINT /*nMsg*/,      // WM_TIMER
   UINT /*nIDEvent*/,  // timer identification
   DWORD /*dwTime*/    // system time
   ) {
  InvalidateRect(hWnd,NULL,TRUE);
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd ::OnCreate(lpCreateStruct) == -1)
		return -1;

    mSlider.Create(WS_VISIBLE,CRect(0,321,240,400),this,0);
    mSlider.SetRange(10,200);
	
    mFrameBuffer.CreateBitmap(240,320,1,32,NULL);
  
    mTimerHandle=SetTimer(0,1000/50,TimerProccy);
	
    embeddedInit(240,320,xfcAppInit,xfcAppPref);
    
	return 0;
}
