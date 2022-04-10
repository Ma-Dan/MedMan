// ItemSet.cpp : implementation file
//

#include "stdafx.h"
#include "MedMan.h"
#include "ItemSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CItemSet

IMPLEMENT_DYNAMIC(CItemSet, CRecordset)

CItemSet::CItemSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CItemSet)
	m_Name = _T("");
	m_Standard = _T("");
	m_Manufactory = _T("");
	m_In_price = 0.0f;
	m_Out_price = 0.0f;
	m_Amount = 0.0f;
	m_Minimum = 0.0f;
	m_Unit = _T("");
	m_Sum = 0.0f;
	m_Abbreviation = _T("");
	m_Batch_number = _T("");
	m_nFields = 11;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CItemSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=Medicine");
}

CString CItemSet::GetDefaultSQL()
{
	return _T("[ItemList]");
}

void CItemSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CItemSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[Standard]"), m_Standard);
	RFX_Text(pFX, _T("[Manufactory]"), m_Manufactory);
	RFX_Single(pFX, _T("[In_price]"), m_In_price);
	RFX_Single(pFX, _T("[Out_price]"), m_Out_price);
	RFX_Single(pFX, _T("[Amount]"), m_Amount);
	RFX_Single(pFX, _T("[Minimum]"), m_Minimum);
	RFX_Text(pFX, _T("[Unit]"), m_Unit);
	RFX_Single(pFX, _T("[Sum]"), m_Sum);
	RFX_Text(pFX, _T("[Abbreviation]"), m_Abbreviation);
	RFX_Text(pFX, _T("[Batch_number]"), m_Batch_number);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CItemSet diagnostics

#ifdef _DEBUG
void CItemSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CItemSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
