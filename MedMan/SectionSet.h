#if !defined(AFX_SECTIONSET_H__44BBA812_0DDB_489A_B513_0C52FFD14648__INCLUDED_)
#define AFX_SECTIONSET_H__44BBA812_0DDB_489A_B513_0C52FFD14648__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SectionSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SectionSet recordset

class SectionSet : public CRecordset
{
public:
	SectionSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SectionSet)

// Field/Param Data
	//{{AFX_FIELD(SectionSet, CRecordset)
	CString	m_Section_name;
	int		m_I_O;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SectionSet)
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

#endif // !defined(AFX_SECTIONSET_H__44BBA812_0DDB_489A_B513_0C52FFD14648__INCLUDED_)
