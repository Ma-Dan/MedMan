#if !defined(AFX_SEARCHMEDICINEDLG_H__8417C9DB_CBC6_4699_8432_A34908CD6D11__INCLUDED_)
#define AFX_SEARCHMEDICINEDLG_H__8417C9DB_CBC6_4699_8432_A34908CD6D11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchMedicineDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSearchMedicineDlg dialog

class CSearchMedicineDlg : public CDialog
{
// Construction
public:
	CSearchMedicineDlg(CWnd* pParent = NULL);   // standard constructor

	int m_nTotalFind;

	CString m_strNameSelected;
	CString m_strStandardSelected;
	CString m_strManufactory;
	CString m_strUnit;

// Dialog Data
	//{{AFX_DATA(CSearchMedicineDlg)
	enum { IDD = IDD_SEARCH_MEDICINE_DIALOG };
	CButton	m_ctrlCheckInprice;
	CListCtrl	m_ctrlMedicineList;
	CString	m_strName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchMedicineDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSearchMedicineDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSearch();
	afx_msg void OnClickListMedicine(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditName();
	afx_msg void OnDblclkListMedicine(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedListMedicine(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckShowinprices();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHMEDICINEDLG_H__8417C9DB_CBC6_4699_8432_A34908CD6D11__INCLUDED_)
