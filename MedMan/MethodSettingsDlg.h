#if !defined(AFX_METHODSETTINGSDLG_H__A6A5B743_27F3_42BB_980C_019F871474E5__INCLUDED_)
#define AFX_METHODSETTINGSDLG_H__A6A5B743_27F3_42BB_980C_019F871474E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MethodSettingsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMethodSettingsDlg dialog

class CMethodSettingsDlg : public CDialog
{
// Construction
public:
	CMethodSettingsDlg(CWnd* pParent = NULL);   // standard constructor

	int m_nMethodTotal;
	int m_nMethodSelect;

	void LoadMethods();

// Dialog Data
	//{{AFX_DATA(CMethodSettingsDlg)
	enum { IDD = IDD_METHOD_SETTINGS_DIALOG };
	CListCtrl	m_ctrlListMethod;
	CString	m_strMethod;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMethodSettingsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMethodSettingsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddMethod();
	afx_msg void OnDeleteMethod();
	afx_msg void OnClickListMethod(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_METHODSETTINGSDLG_H__A6A5B743_27F3_42BB_980C_019F871474E5__INCLUDED_)
