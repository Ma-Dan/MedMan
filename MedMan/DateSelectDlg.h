#if !defined(AFX_DATESELECTDLG_H__B47C54A5_2F11_4061_B6B2_E8E05590330F__INCLUDED_)
#define AFX_DATESELECTDLG_H__B47C54A5_2F11_4061_B6B2_E8E05590330F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DateSelectDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDateSelectDlg dialog

class CDateSelectDlg : public CDialog
{
// Construction
public:
	CDateSelectDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDateSelectDlg)
	enum { IDD = IDD_DATE_SELECT };
	CTime	m_tDateTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDateSelectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDateSelectDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATESELECTDLG_H__B47C54A5_2F11_4061_B6B2_E8E05590330F__INCLUDED_)
