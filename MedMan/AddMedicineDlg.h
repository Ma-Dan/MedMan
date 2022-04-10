#if !defined(AFX_ADDMEDICINEDLG_H__A5138F3A_68BC_479E_BC8C_2E6265FBAA9D__INCLUDED_)
#define AFX_ADDMEDICINEDLG_H__A5138F3A_68BC_479E_BC8C_2E6265FBAA9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddMedicineDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddMedicineDlg dialog

class CAddMedicineDlg : public CDialog
{
// Construction
public:
	CAddMedicineDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddMedicineDlg)
	enum { IDD = IDD_ADD_MEDICINE_DIALOG };
	CComboBox	m_ctrlComboUnit;
	CString	m_strManufactory;
	float	m_fMinimum;
	CString	m_strName;
	CString	m_strStandard;
	float	m_fSum;
	float	m_fInPrice;
	float	m_fOutPrice;
	float	m_fNumber;
	CString	m_strUnit;
	CString	m_strBatchNumber;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddMedicineDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddMedicineDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboUnit();
	afx_msg void OnChangeEditNumber();
	afx_msg void OnChangeEditOutPrice();
	afx_msg void OnChangeEditInPrice();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDMEDICINEDLG_H__A5138F3A_68BC_479E_BC8C_2E6265FBAA9D__INCLUDED_)
