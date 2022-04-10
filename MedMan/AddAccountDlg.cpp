// AddAccountDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MedMan.h"
#include "AddAccountDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddAccountDlg dialog


CAddAccountDlg::CAddAccountDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddAccountDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddAccountDlg)
	m_strAccount = _T("");
	m_strPassword = _T("");
	m_strPasswordConfirm = _T("");
	//}}AFX_DATA_INIT
}


void CAddAccountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddAccountDlg)
	DDX_Text(pDX, IDC_EDIT_ACCOUNT, m_strAccount);
	DDV_MaxChars(pDX, m_strAccount, 20);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDV_MaxChars(pDX, m_strPassword, 20);
	DDX_Text(pDX, IDC_EDIT_PASSWORDCONFIRM, m_strPasswordConfirm);
	DDV_MaxChars(pDX, m_strPasswordConfirm, 20);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddAccountDlg, CDialog)
	//{{AFX_MSG_MAP(CAddAccountDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddAccountDlg message handlers
