#if !defined(AFX_UNITSETTINGSDLG_H__F7B2E5FE_73C9_4D27_93F6_4522048D8300__INCLUDED_)
#define AFX_UNITSETTINGSDLG_H__F7B2E5FE_73C9_4D27_93F6_4522048D8300__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UnitSettingsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUnitSettingsDlg dialog

class CUnitSettingsDlg : public CDialog
{
// Construction
public:
	CUnitSettingsDlg(CWnd* pParent = NULL);   // standard constructor

	int m_nUnitTotal;
	int m_nUnitSelect;

	void LoadUnits();

// Dialog Data
	//{{AFX_DATA(CUnitSettingsDlg)
	enum { IDD = IDD_UNIT_SETTINGS_DIALOG };
	CListCtrl	m_ctrlListUnit;
	CString	m_strUnit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUnitSettingsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUnitSettingsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddUnit();
	afx_msg void OnDeleteUnit();
	afx_msg void OnClickListUnit(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UNITSETTINGSDLG_H__F7B2E5FE_73C9_4D27_93F6_4522048D8300__INCLUDED_)
