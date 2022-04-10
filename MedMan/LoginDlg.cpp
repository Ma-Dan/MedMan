// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MedMan.h"
#include "LoginDlg.h"

#include "AccountSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog


CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDlg)
	m_strAccount = _T("");
	m_strPassword = _T("");
	//}}AFX_DATA_INIT
}


void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
	DDX_Control(pDX, IDC_COMBO_ACCOUNT, m_ctrlAccount);
	DDX_CBString(pDX, IDC_COMBO_ACCOUNT, m_strAccount);
	DDV_MaxChars(pDX, m_strAccount, 20);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDV_MaxChars(pDX, m_strPassword, 20);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CLoginDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_ACCOUNT, OnSelchangeComboAccount)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers

BOOL CLoginDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//添加用户名列表
	AccountSet m_Set;
	m_Set.Open();
	while(!m_Set.IsEOF())
	{
		m_ctrlAccount.AddString(m_Set.m_strAccount);
		m_Set.MoveNext();
	}

	m_Set.Close();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLoginDlg::OnSelchangeComboAccount() 
{
	int nIndex=m_ctrlAccount.GetCurSel();
	AccountSet m_Set;
	m_Set.Open();
	m_Set.MoveFirst();
    for(int i=0;i<nIndex;i++)
	{
		m_Set.MoveNext();
	}
	m_strAccount=m_Set.m_strAccount;
}
