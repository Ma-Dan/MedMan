#if !defined(AFX_ADDSECTIONDLG_H__70434965_B776_4846_BFD2_A3C79237AB52__INCLUDED_)
#define AFX_ADDSECTIONDLG_H__70434965_B776_4846_BFD2_A3C79237AB52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddSectionDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddSectionDlg dialog

class CAddSectionDlg : public CDialog
{
// Construction
public:
	CAddSectionDlg(CWnd* pParent = NULL);   // standard constructor

	int In_or_out;

// Dialog Data
	//{{AFX_DATA(CAddSectionDlg)
	enum { IDD = IDD_ADD_SECTION_DIALOG };
	CString	m_strSectionName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddSectionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddSectionDlg)
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDSECTIONDLG_H__70434965_B776_4846_BFD2_A3C79237AB52__INCLUDED_)
