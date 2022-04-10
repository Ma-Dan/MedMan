// DateSelectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MedMan.h"
#include "DateSelectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDateSelectDlg dialog


CDateSelectDlg::CDateSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDateSelectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDateSelectDlg)
	m_tDateTime = 0;
	//}}AFX_DATA_INIT
}


void CDateSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDateSelectDlg)
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_tDateTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDateSelectDlg, CDialog)
	//{{AFX_MSG_MAP(CDateSelectDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDateSelectDlg message handlers
