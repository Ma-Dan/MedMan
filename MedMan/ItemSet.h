#if !defined(AFX_ITEMSET_H__51E1C4A0_FB58_40C4_8873_56DDA41447B4__INCLUDED_)
#define AFX_ITEMSET_H__51E1C4A0_FB58_40C4_8873_56DDA41447B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ItemSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CItemSet recordset

class CItemSet : public CRecordset
{
public:
	CItemSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CItemSet)

// Field/Param Data
	//{{AFX_FIELD(CItemSet, CRecordset)
	CString	m_Name;
	CString	m_Standard;
	CString	m_Manufactory;
	float	m_In_price;
	float	m_Out_price;
	float	m_Amount;
	float	m_Minimum;
	CString	m_Unit;
	float	m_Sum;
	CString	m_Abbreviation;
	CString	m_Batch_number;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CItemSet)
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

#endif // !defined(AFX_ITEMSET_H__51E1C4A0_FB58_40C4_8873_56DDA41447B4__INCLUDED_)
