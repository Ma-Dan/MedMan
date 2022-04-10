// ReadCheckDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MedMan.h"
#include "ReadCheckDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReadCheckDlg dialog


CReadCheckDlg::CReadCheckDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReadCheckDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReadCheckDlg)
	m_fAmount = 0.0f;
	m_fInPrice = 0.0f;
	m_strManufactory = _T("");
	m_strName = _T("");
	m_fRealAmount = 0.0f;
	m_strStandard = _T("");
	m_fSum = 0.0f;
	//}}AFX_DATA_INIT
}


void CReadCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReadCheckDlg)
	DDX_Text(pDX, IDC_EDIT_AMOUNT, m_fAmount);
	DDX_Text(pDX, IDC_EDIT_INPRICE, m_fInPrice);
	DDX_Text(pDX, IDC_EDIT_MANUFACTORY, m_strManufactory);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_REALAMOUNT, m_fRealAmount);
	DDX_Text(pDX, IDC_EDIT_STANDARD, m_strStandard);
	DDX_Text(pDX, IDC_EDIT_SUM, m_fSum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReadCheckDlg, CDialog)
	//{{AFX_MSG_MAP(CReadCheckDlg)
	ON_EN_CHANGE(IDC_EDIT_INPRICE, OnChangeEditInprice)
	ON_EN_CHANGE(IDC_EDIT_REALAMOUNT, OnChangeEditRealamount)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReadCheckDlg message handlers

void CReadCheckDlg::OnChangeEditInprice() 
{
	UpdateData();
	m_fSum=m_fRealAmount*m_fInPrice;
	CString Temp;
	Temp.Format(_T("%.2f"),m_fSum);
	SetDlgItemText(IDC_EDIT_SUM,Temp);
	
}

void CReadCheckDlg::OnChangeEditRealamount() 
{
	UpdateData();
	m_fSum=m_fRealAmount*m_fInPrice;
	CString Temp;
	Temp.Format(_T("%.2f"),m_fSum);
	SetDlgItemText(IDC_EDIT_SUM,Temp);
	
}
