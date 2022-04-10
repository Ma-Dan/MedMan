#if !defined(AFX_ACCOUNTSETTINGSDLG_H__515777F5_CA66_40A0_8AB5_A64C9E2DCAAD__INCLUDED_)
#define AFX_ACCOUNTSETTINGSDLG_H__515777F5_CA66_40A0_8AB5_A64C9E2DCAAD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AccountSettingsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAccountSettingsDlg dialog

class CAccountSettingsDlg : public CDialog
{
// Construction
public:
	CAccountSettingsDlg(CWnd* pParent = NULL);   // standard constructor

	int m_nAccountTotal;
	int m_nAccountSelect;

	void LoadAccounts();

// Dialog Data
	//{{AFX_DATA(CAccountSettingsDlg)
	enum { IDD = IDD_ACCOUNT_SETTINGS_DIALOG };
	CListCtrl	m_ctrlListAccount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAccountSettingsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAccountSettingsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListAccount(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAddAccount();
	afx_msg void OnModifyAccount();
	afx_msg void OnDeleteAccount();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACCOUNTSETTINGSDLG_H__515777F5_CA66_40A0_8AB5_A64C9E2DCAAD__INCLUDED_)
