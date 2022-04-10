#if !defined(AFX_IORECORDSET_H__E2C5A282_B4F6_4A84_8DE9_6A63807A2F92__INCLUDED_)
#define AFX_IORECORDSET_H__E2C5A282_B4F6_4A84_8DE9_6A63807A2F92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IORecordSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// IORecordSet recordset

class IORecordSet : public CRecordset
{
public:
	IORecordSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(IORecordSet)

// Field/Param Data
	//{{AFX_FIELD(IORecordSet, CRecordset)
	CString	m_Batch_number;
	CTime	m_Date;
	CString	m_Method;
	CString	m_Name;
	float	m_Number;
	float	m_Remaining;
	CString	m_Section;
	CString	m_Standard;
	CString	m_Unit;
	float	m_In_price;
	float	m_Out_price;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(IORecordSet)
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

#endif // !defined(AFX_IORECORDSET_H__E2C5A282_B4F6_4A84_8DE9_6A63807A2F92__INCLUDED_)
