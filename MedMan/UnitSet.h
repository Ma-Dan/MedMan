#if !defined(AFX_UNITSET_H__9F794FAE_2449_4042_B396_2D91456F0422__INCLUDED_)
#define AFX_UNITSET_H__9F794FAE_2449_4042_B396_2D91456F0422__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UnitSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// UnitSet recordset

class UnitSet : public CRecordset
{
public:
	UnitSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(UnitSet)

// Field/Param Data
	//{{AFX_FIELD(UnitSet, CRecordset)
	CString	m_Unit;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(UnitSet)
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

#endif // !defined(AFX_UNITSET_H__9F794FAE_2449_4042_B396_2D91456F0422__INCLUDED_)
