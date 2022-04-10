// MedManDlg.h : header file
//

#if !defined(AFX_MEDMANDLG_H__11A7D7F1_CF8B_48E8_B1B3_7312E20EE9A9__INCLUDED_)
#define AFX_MEDMANDLG_H__11A7D7F1_CF8B_48E8_B1B3_7312E20EE9A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMedManDlg dialog

class CMedManDlg : public CDialog
{
// Construction
public:
	CMedManDlg(CWnd* pParent = NULL);	// standard constructor

	void InitDatabase(); //初始化数据库

	CString m_strOperator;

	void GetTimeOfSystem();
	CString m_strTime;
	UINT m_nTimer;

	BOOL m_bDateSelected;

	BOOL CompareDateTime(CString Time1,CString Time2);

	CString Datetime;
	CString Datetime0;

// Dialog Data
	//{{AFX_DATA(CMedManDlg)
	enum { IDD = IDD_MEDMAN_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMedManDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMedManDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnStoreView();
	afx_msg void OnNewMedicine();
	afx_msg void OnMedInOut();
	afx_msg void OnMedicineRecord();
	afx_msg void OnAdvanced();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEDMANDLG_H__11A7D7F1_CF8B_48E8_B1B3_7312E20EE9A9__INCLUDED_)
