#if !defined(AFX_ACCOUNTSET_H__13553079_AFAC_4891_A87F_D6D26B4E5253__INCLUDED_)
#define AFX_ACCOUNTSET_H__13553079_AFAC_4891_A87F_D6D26B4E5253__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AccountSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AccountSet recordset

class AccountSet : public CRecordset
{
public:
	AccountSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(AccountSet)

// Field/Param Data
	//{{AFX_FIELD(AccountSet, CRecordset)
	CString	m_strAccount;
	CString	m_strPassword;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AccountSet)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACCOUNTSET_H__13553079_AFAC_4891_A87F_D6D26B4E5253__INCLUDED_)
