#if !defined(AFX_READCHECKDLG_H__BADBC3CE_8B42_422F_B264_FF04ED1625EE__INCLUDED_)
#define AFX_READCHECKDLG_H__BADBC3CE_8B42_422F_B264_FF04ED1625EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReadCheckDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReadCheckDlg dialog

class CReadCheckDlg : public CDialog
{
// Construction
public:
	CReadCheckDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReadCheckDlg)
	enum { IDD = IDD_READ_CHECK_DIALOG };
	float	m_fAmount;
	float	m_fInPrice;
	CString	m_strManufactory;
	CString	m_strName;
	float	m_fRealAmount;
	CString	m_strStandard;
	float	m_fSum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReadCheckDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReadCheckDlg)
	afx_msg void OnChangeEditInprice();
	afx_msg void OnChangeEditRealamount();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READCHECKDLG_H__BADBC3CE_8B42_422F_B264_FF04ED1625EE__INCLUDED_)
