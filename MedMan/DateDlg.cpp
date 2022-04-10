// DateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MedMan.h"
#include "DateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDateDlg dialog


CDateDlg::CDateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDateDlg)
	m_tDateTime = 0;
	//}}AFX_DATA_INIT
}


void CDateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDateDlg)
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_tDateTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDateDlg, CDialog)
	//{{AFX_MSG_MAP(CDateDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDateDlg message handlers
