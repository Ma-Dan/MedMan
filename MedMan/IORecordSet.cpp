// IORecordSet.cpp : implementation file
//

#include "stdafx.h"
#include "MedMan.h"
#include "IORecordSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// IORecordSet

IMPLEMENT_DYNAMIC(IORecordSet, CRecordset)

IORecordSet::IORecordSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(IORecordSet)
	m_Batch_number = _T("");
	m_Method = _T("");
	m_Name = _T("");
	m_Number = 0.0f;
	m_Remaining = 0.0f;
	m_Section = _T("");
	m_Standard = _T("");
	m_Unit = _T("");
	m_In_price = 0.0f;
	m_Out_price = 0.0f;
	m_nFields = 11;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString IORecordSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=");
}

CString IORecordSet::GetDefaultSQL()
{
	return _T("");
}

void IORecordSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(IORecordSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Batch_number]"), m_Batch_number);
	RFX_Date(pFX, _T("[Date]"), m_Date);
	RFX_Text(pFX, _T("[Method]"), m_Method);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Single(pFX, _T("[Number]"), m_Number);
	RFX_Single(pFX, _T("[Remaining]"), m_Remaining);
	RFX_Text(pFX, _T("[Section]"), m_Section);
	RFX_Text(pFX, _T("[Standard]"), m_Standard);
	RFX_Text(pFX, _T("[Unit]"), m_Unit);
	RFX_Single(pFX, _T("[In_price]"), m_In_price);
	RFX_Single(pFX, _T("[Out_price]"), m_Out_price);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// IORecordSet diagnostics

#ifdef _DEBUG
void IORecordSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void IORecordSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
