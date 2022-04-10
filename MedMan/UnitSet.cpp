// UnitSet.cpp : implementation file
//

#include "stdafx.h"
#include "MedMan.h"
#include "UnitSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// UnitSet

IMPLEMENT_DYNAMIC(UnitSet, CRecordset)

UnitSet::UnitSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(UnitSet)
	m_Unit = _T("");
	m_nFields = 1;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString UnitSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=Medicine");
}

CString UnitSet::GetDefaultSQL()
{
	return _T("[Unit]");
}

void UnitSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(UnitSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Unit]"), m_Unit);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// UnitSet diagnostics

#ifdef _DEBUG
void UnitSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void UnitSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
