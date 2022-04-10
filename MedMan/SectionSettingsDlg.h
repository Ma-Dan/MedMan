#if !defined(AFX_SECTIONSETTINGSDLG_H__EF3CEBF4_527D_438E_A756_E5801393E841__INCLUDED_)
#define AFX_SECTIONSETTINGSDLG_H__EF3CEBF4_527D_438E_A756_E5801393E841__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SectionSettingsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSectionSettingsDlg dialog

class CSectionSettingsDlg : public CDialog
{
// Construction
public:
	CSectionSettingsDlg(CWnd* pParent = NULL);   // standard constructor

	int m_nSectionTotal;
	int m_nSectionSelect;

	void LoadSections();

// Dialog Data
	//{{AFX_DATA(CSectionSettingsDlg)
	enum { IDD = IDD_SECTION_SETTINGS_DIALOG };
	CListCtrl	m_ctrlListSection;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSectionSettingsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSectionSettingsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddSection();
	afx_msg void OnDeleteSection();
	afx_msg void OnClickListSection(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SECTIONSETTINGSDLG_H__EF3CEBF4_527D_438E_A756_E5801393E841__INCLUDED_)
