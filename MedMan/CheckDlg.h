#if !defined(AFX_CHECKDLG_H__D2D97920_B3F9_40BE_9FED_EBD810AC0E34__INCLUDED_)
#define AFX_CHECKDLG_H__D2D97920_B3F9_40BE_9FED_EBD810AC0E34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CheckDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCheckDlg dialog

class CCheckDlg : public CDialog
{
// Construction
public:
	CCheckDlg(CWnd* pParent = NULL);   // standard constructor

	int m_nSelect;

// Dialog Data
	//{{AFX_DATA(CCheckDlg)
	enum { IDD = IDD_CHECK_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCheckDlg)
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKDLG_H__D2D97920_B3F9_40BE_9FED_EBD810AC0E34__INCLUDED_)
