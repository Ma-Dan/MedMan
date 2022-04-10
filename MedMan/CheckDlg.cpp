// CheckDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MedMan.h"
#include "CheckDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCheckDlg dialog


CCheckDlg::CCheckDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCheckDlg::IDD, pParent)
{
	m_nSelect=1;
	//{{AFX_DATA_INIT(CCheckDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCheckDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCheckDlg, CDialog)
	//{{AFX_MSG_MAP(CCheckDlg)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckDlg message handlers

void CCheckDlg::OnRadio1() 
{
	m_nSelect=1;
}

void CCheckDlg::OnRadio2() 
{
	m_nSelect=2;
}

BOOL CCheckDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
