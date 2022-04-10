// EditInformationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MedMan.h"
#include "EditInformationDlg.h"

#include "UnitSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditInformationDlg dialog


CEditInformationDlg::CEditInformationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditInformationDlg::IDD, pParent)
{
	m_strName="";
	m_strStandard="";
	//{{AFX_DATA_INIT(CEditInformationDlg)
	m_strUnit = _T("");
	m_fOutPrice = 0.0f;
	m_fInPrice = 0.0f;
	m_strManufactory = _T("");
	m_fMinimum = 0.0f;
	m_strBatchNumber = _T("");
	//}}AFX_DATA_INIT
}


void CEditInformationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditInformationDlg)
	DDX_Control(pDX, IDC_COMBO_UNIT, m_ctrlUnit);
	DDX_CBString(pDX, IDC_COMBO_UNIT, m_strUnit);
	DDX_Text(pDX, IDC_EDIT_OUTPRICE, m_fOutPrice);
	DDX_Text(pDX, IDC_EDIT_INPRICE, m_fInPrice);
	DDX_Text(pDX, IDC_EDIT_MANUFACTORY, m_strManufactory);
	DDX_Text(pDX, IDC_EDIT_MINIMUM, m_fMinimum);
	DDX_Text(pDX, IDC_EDIT_BATCH_NUMER, m_strBatchNumber);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditInformationDlg, CDialog)
	//{{AFX_MSG_MAP(CEditInformationDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditInformationDlg message handlers

BOOL CEditInformationDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//1.显示商品信息
	CString Temp;
	Temp="商品名称:"+m_strName+" 规格:"+m_strStandard;
	SetDlgItemText(IDC_STATIC_INFORMATION,Temp);

	//2.获取计量单位列表并填入下拉框
	LoadUnits();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditInformationDlg::LoadUnits()
{
	UnitSet m_Set;

	m_Set.Open();
	m_ctrlUnit.ResetContent();

	if(m_Set.IsEOF())
	{
		return;
	}

	m_Set.MoveFirst();
	while(!m_Set.IsEOF())
	{
		m_ctrlUnit.AddString(m_Set.m_Unit);
		m_Set.MoveNext();
	}

	m_Set.Close();
}