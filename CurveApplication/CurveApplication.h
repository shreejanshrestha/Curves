// CurveApplication.h : main header file for the CURVEAPPLICATION application
//

#if !defined(AFX_CURVEAPPLICATION_H__B44F67BE_10E3_4A8C_A96C_1D7CFF144909__INCLUDED_)
#define AFX_CURVEAPPLICATION_H__B44F67BE_10E3_4A8C_A96C_1D7CFF144909__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCurveApplicationApp:
// See CurveApplication.cpp for the implementation of this class
//

class CCurveApplicationApp : public CWinApp
{
public:
	CCurveApplicationApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurveApplicationApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCurveApplicationApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURVEAPPLICATION_H__B44F67BE_10E3_4A8C_A96C_1D7CFF144909__INCLUDED_)
