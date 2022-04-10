#if !defined(AFX_ADDACCOUNTDLG_H__561797C9_00CE_448D_B5B7_05739AA8D8A1__INCLUDED_)
#define AFX_ADDACCOUNTDLG_H__561797C9_00CE_448D_B5B7_05739AA8D8A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddAccountDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddAccountDlg dialog

class CAddAccountDlg : public CDialog
{
// Construction
public:
	CAddAccountDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddAccountDlg)
	enum { IDD = IDD_ADD_ACCOUNT_DIALOG };
	CString	m_strAccount;
	CString	m_strPassword;
	CString	m_strPasswordConfirm;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddAccountDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddAccountDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDACCOUNTDLG_H__561797C9_00CE_448D_B5B7_05739AA8D8A1__INCLUDED_)
