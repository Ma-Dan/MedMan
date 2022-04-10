// MethodSet.cpp : implementation file
//

#include "stdafx.h"
#include "MedMan.h"
#include "MethodSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MethodSet

IMPLEMENT_DYNAMIC(MethodSet, CRecordset)

MethodSet::MethodSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(MethodSet)
	m_Method = _T("");
	m_nFields = 1;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString MethodSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=Medicine");
}

CString MethodSet::GetDefaultSQL()
{
	return _T("[Method]");
}

void MethodSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(MethodSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Method]"), m_Method);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// MethodSet diagnostics

#ifdef _DEBUG
void MethodSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void MethodSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
