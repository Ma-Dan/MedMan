#if !defined(AFX_METHODSET_H__A5E2C536_AE8C_45E1_85B8_367FFB6D9FB2__INCLUDED_)
#define AFX_METHODSET_H__A5E2C536_AE8C_45E1_85B8_367FFB6D9FB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MethodSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MethodSet recordset

class MethodSet : public CRecordset
{
public:
	MethodSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(MethodSet)

// Field/Param Data
	//{{AFX_FIELD(MethodSet, CRecordset)
	CString	m_Method;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MethodSet)
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

#endif // !defined(AFX_METHODSET_H__A5E2C536_AE8C_45E1_85B8_367FFB6D9FB2__INCLUDED_)
