// MedMan.h : main header file for the MEDMAN application
//

#if !defined(AFX_MEDMAN_H__610BABEA_D765_4FD8_B2FD_0DC8D7F17FAB__INCLUDED_)
#define AFX_MEDMAN_H__610BABEA_D765_4FD8_B2FD_0DC8D7F17FAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMedManApp:
// See MedMan.cpp for the implementation of this class
//

class CMedManApp : public CWinApp
{
public:
	CMedManApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMedManApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMedManApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEDMAN_H__610BABEA_D765_4FD8_B2FD_0DC8D7F17FAB__INCLUDED_)
