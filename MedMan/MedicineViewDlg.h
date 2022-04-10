#if !defined(AFX_MEDICINEVIEWDLG_H__D0DF923E_247C_475C_AC0F_4A0E2D3DB57D__INCLUDED_)
#define AFX_MEDICINEVIEWDLG_H__D0DF923E_247C_475C_AC0F_4A0E2D3DB57D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MedicineViewDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMedicineViewDlg dialog

class CMedicineViewDlg : public CDialog
{
// Construction
public:
	CMedicineViewDlg(CWnd* pParent = NULL);   // standard constructor

	int m_nTotalItems; //商品总数
	int m_nCurrentSelect; //当前选择
	int m_nTotalFind;

	CString m_strOperator;

	void LoadItems();

// Dialog Data
	//{{AFX_DATA(CMedicineViewDlg)
	enum { IDD = IDD_MEDICINE_VIEW_DIALOG };
	CButton	m_ctrlCheckInprice;
	CListCtrl	m_ctrlListItem;
	CString	m_strName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMedicineViewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMedicineViewDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListItem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnViewEdit();
	afx_msg void OnViewAdd();
	afx_msg void OnViewDelete();
	afx_msg void OnChangeEditName();
	afx_msg void OnCheckShowinprice();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEDICINEVIEWDLG_H__D0DF923E_247C_475C_AC0F_4A0E2D3DB57D__INCLUDED_)
