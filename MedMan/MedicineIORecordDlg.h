#if !defined(AFX_MEDICINEIORECORDDLG_H__DA04211F_AABE_4F50_8E9F_093727E3065D__INCLUDED_)
#define AFX_MEDICINEIORECORDDLG_H__DA04211F_AABE_4F50_8E9F_093727E3065D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MedicineIORecordDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMedicineIORecordDlg dialog

class CMedicineIORecordDlg : public CDialog
{
// Construction
public:
	CMedicineIORecordDlg(CWnd* pParent = NULL);   // standard constructor
	CString m_strName;
	CString m_strStandard;
	CString m_strManufactory;
	CString m_strUnit;

	CString m_strOperator;

	int m_nRecordTotal;
	int m_nRecordSelect;

	void ViewMedicineIORecord();

	BOOL CompareDateTime(CString Time1,CString Time2);

// Dialog Data
	//{{AFX_DATA(CMedicineIORecordDlg)
	enum { IDD = IDD_MEDICINE_IO_RECORD_DIALOG };
	CListCtrl	m_ctrlRecordList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMedicineIORecordDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMedicineIORecordDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListRecord(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnModifyRecord();
	afx_msg void OnInsertRecord();
	afx_msg void OnDeleteRecord();
	afx_msg void OnIoMedicine();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEDICINEIORECORDDLG_H__DA04211F_AABE_4F50_8E9F_093727E3065D__INCLUDED_)
