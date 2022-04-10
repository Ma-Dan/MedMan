// AccountSet.cpp : implementation file
//

#include "stdafx.h"
#include "MedMan.h"
#include "AccountSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AccountSet

IMPLEMENT_DYNAMIC(AccountSet, CRecordset)

AccountSet::AccountSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(AccountSet)
	m_strAccount=_T("");
	m_strPassword=_T("");
	m_nFields=2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString AccountSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=Medicine");
}

CString AccountSet::GetDefaultSQL()
{
	return _T("[Account]");
}

void AccountSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(AccountSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Account]"), m_strAccount);
	RFX_Text(pFX, _T("[Password]"), m_strPassword);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// AccountSet diagnostics

#ifdef _DEBUG
void AccountSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void AccountSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
