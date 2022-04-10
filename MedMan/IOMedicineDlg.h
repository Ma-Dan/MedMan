#if !defined(AFX_IOMEDICINEDLG_H__022594C6_8991_4BEA_82BB_95D77AAD8D87__INCLUDED_)
#define AFX_IOMEDICINEDLG_H__022594C6_8991_4BEA_82BB_95D77AAD8D87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IOMedicineDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIOMedicineDlg dialog

class CIOMedicineDlg : public CDialog
{
// Construction
public:
	CIOMedicineDlg(CWnd* pParent = NULL);   // standard constructor

	CString m_strName;
	CString m_strStandard;
	CString m_strManufactory;
	CString m_strUnit;

	int m_nIO; //0-进货 1-出货

	void SetupDialogTexts();
	void SetupSections();
	void SetupMethods();

// Dialog Data
	//{{AFX_DATA(CIOMedicineDlg)
	enum { IDD = IDD_IO_MEDICINE_DIALOG };
	CComboBox	m_ctrlSection;
	CComboBox	m_ctrlMethod;
	CButton	m_ctrlMedicineOut;
	CButton	m_ctrlMedicineIn;
	CString	m_strBatchNumber;
	float	m_fInPrice;
	float	m_fOutPrice;
	CString	m_strSection;
	CString	m_strMethod;
	float	m_fAmount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIOMedicineDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIOMedicineDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IOMEDICINEDLG_H__022594C6_8991_4BEA_82BB_95D77AAD8D87__INCLUDED_)
