// SectionSet.cpp : implementation file
//

#include "stdafx.h"
#include "MedMan.h"
#include "SectionSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SectionSet

IMPLEMENT_DYNAMIC(SectionSet, CRecordset)

SectionSet::SectionSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SectionSet)
	m_Section_name = _T("");
	m_I_O = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString SectionSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=Medicine");
}

CString SectionSet::GetDefaultSQL()
{
	return _T("[Section]");
}

void SectionSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SectionSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Section_name]"), m_Section_name);
	RFX_Int(pFX, _T("[I_O]"), m_I_O);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SectionSet diagnostics

#ifdef _DEBUG
void SectionSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void SectionSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
