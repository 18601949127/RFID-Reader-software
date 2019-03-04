// StringGridctrl.h : main header file for the STRINGGRIDCTRL application
//

#if !defined(AFX_STRINGGRIDCTRL_H__3A13405B_11A8_4688_801B_112D29CCA9C1__INCLUDED_)
#define AFX_STRINGGRIDCTRL_H__3A13405B_11A8_4688_801B_112D29CCA9C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CStringGridctrlApp:
// See StringGridctrl.cpp for the implementation of this class
//

class CStringGridctrlApp : public CWinApp
{
public:
	CStringGridctrlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStringGridctrlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CStringGridctrlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STRINGGRIDCTRL_H__3A13405B_11A8_4688_801B_112D29CCA9C1__INCLUDED_)
