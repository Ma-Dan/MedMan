#if !defined(AFX_EDITINFORMATIONDLG_H__FC4C403B_1751_4005_9F9D_6670DAB398E7__INCLUDED_)
#define AFX_EDITINFORMATIONDLG_H__FC4C403B_1751_4005_9F9D_6670DAB398E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditInformationDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditInformationDlg dialog

class CEditInformationDlg : public CDialog
{
// Construction
public:
	CEditInformationDlg(CWnd* pParent = NULL);   // standard constructor

	CString m_strName;
	CString m_strStandard;

	void LoadUnits();

// Dialog Data
	//{{AFX_DATA(CEditInformationDlg)
	enum { IDD = IDD_EDIT_INFORMATION_DIALOG };
	CComboBox	m_ctrlUnit;
	CString	m_strUnit;
	float	m_fOutPrice;
	float	m_fInPrice;
	CString	m_strManufactory;
	float	m_fMinimum;
	CString	m_strBatchNumber;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditInformationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditInformationDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITINFORMATIONDLG_H__FC4C403B_1751_4005_9F9D_6670DAB398E7__INCLUDED_)
