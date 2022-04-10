// AddSectionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MedMan.h"
#include "AddSectionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddSectionDlg dialog


CAddSectionDlg::CAddSectionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddSectionDlg::IDD, pParent)
{
	In_or_out=-1;
	//{{AFX_DATA_INIT(CAddSectionDlg)
	m_strSectionName = _T("");
	//}}AFX_DATA_INIT
}


void CAddSectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddSectionDlg)
	DDX_Text(pDX, IDC_EDIT_SECTION_NAME, m_strSectionName);
	DDV_MaxChars(pDX, m_strSectionName, 50);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddSectionDlg, CDialog)
	//{{AFX_MSG_MAP(CAddSectionDlg)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddSectionDlg message handlers

void CAddSectionDlg::OnRadio1() 
{
	In_or_out=0;
}

void CAddSectionDlg::OnRadio2() 
{
	In_or_out=1;
}
