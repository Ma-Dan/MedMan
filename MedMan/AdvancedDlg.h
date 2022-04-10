#if !defined(AFX_ADVANCEDDLG_H__D0133034_089C_4BB4_8853_41B678E75A7A__INCLUDED_)
#define AFX_ADVANCEDDLG_H__D0133034_089C_4BB4_8853_41B678E75A7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdvancedDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAdvancedDlg dialog

class CAdvancedDlg : public CDialog
{
// Construction
public:
	CAdvancedDlg(CWnd* pParent = NULL);   // standard constructor
	CString m_strOperator;

// Dialog Data
	//{{AFX_DATA(CAdvancedDlg)
	enum { IDD = IDD_ADVANCED_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdvancedDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAdvancedDlg)
	afx_msg void OnAccountSettings();
	afx_msg void OnSectionSettings();
	afx_msg void OnUnitSettings();
	afx_msg void OnMethodSeetings();
	afx_msg void OnAnnunalCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADVANCEDDLG_H__D0133034_089C_4BB4_8853_41B678E75A7A__INCLUDED_)
