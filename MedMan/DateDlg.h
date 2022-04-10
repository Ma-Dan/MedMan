#if !defined(AFX_DATEDLG_H__72867D50_F8E4_4E18_8A8C_B5CFA4ACA3B1__INCLUDED_)
#define AFX_DATEDLG_H__72867D50_F8E4_4E18_8A8C_B5CFA4ACA3B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DateDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDateDlg dialog

class CDateDlg : public CDialog
{
// Construction
public:
	CDateDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDateDlg)
	enum { IDD = IDD_DATE_DIALOG };
	CTime	m_tDateTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDateDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATEDLG_H__72867D50_F8E4_4E18_8A8C_B5CFA4ACA3B1__INCLUDED_)
