// AddMedicineDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MedMan.h"
#include "AddMedicineDlg.h"

#include "UnitSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddMedicineDlg dialog


CAddMedicineDlg::CAddMedicineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddMedicineDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddMedicineDlg)
	m_strManufactory = _T("");
	m_fMinimum = 0.0f;
	m_strName = _T("");
	m_strStandard = _T("");
	m_fSum = 0.0f;
	m_fInPrice = 0.0f;
	m_fOutPrice = 0.0f;
	m_fNumber = 0.0f;
	m_strUnit = _T("");
	m_strBatchNumber = _T("");
	//}}AFX_DATA_INIT
}


void CAddMedicineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddMedicineDlg)
	DDX_Control(pDX, IDC_COMBO_UNIT, m_ctrlComboUnit);
	DDX_Text(pDX, IDC_EDIT_MANUFACTORY, m_strManufactory);
	DDV_MaxChars(pDX, m_strManufactory, 30);
	DDX_Text(pDX, IDC_EDIT_MINIMUM, m_fMinimum);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 30);
	DDX_Text(pDX, IDC_EDIT_STANDARD, m_strStandard);
	DDV_MaxChars(pDX, m_strStandard, 20);
	DDX_Text(pDX, IDC_EDIT_SUM, m_fSum);
	DDX_Text(pDX, IDC_EDIT_IN_PRICE, m_fInPrice);
	DDX_Text(pDX, IDC_EDIT_OUT_PRICE, m_fOutPrice);
	DDX_Text(pDX, IDC_EDIT_NUMBER, m_fNumber);
	DDX_CBString(pDX, IDC_COMBO_UNIT, m_strUnit);
	DDV_MaxChars(pDX, m_strUnit, 10);
	DDX_Text(pDX, IDC_EDIT_BATCH_NUMER, m_strBatchNumber);
	DDV_MaxChars(pDX, m_strBatchNumber, 15);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddMedicineDlg, CDialog)
	//{{AFX_MSG_MAP(CAddMedicineDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_UNIT, OnSelchangeComboUnit)
	ON_EN_CHANGE(IDC_EDIT_NUMBER, OnChangeEditNumber)
	ON_EN_CHANGE(IDC_EDIT_OUT_PRICE, OnChangeEditOutPrice)
	ON_EN_CHANGE(IDC_EDIT_IN_PRICE, OnChangeEditInPrice)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddMedicineDlg message handlers

BOOL CAddMedicineDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//1.添加计量单位到计量单位的下拉框中
	UnitSet m_Set;
	
	m_Set.Open();
	m_Set.MoveFirst();

	while(!m_Set.IsEOF())
	{
		m_ctrlComboUnit.AddString(m_Set.m_Unit);
		m_Set.MoveNext();
	}

	m_Set.Close();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAddMedicineDlg::OnSelchangeComboUnit() 
{
	int nIndex=m_ctrlComboUnit.GetCurSel();
	UnitSet m_Set;
	m_Set.Open();
	m_Set.MoveFirst();
    for(int i=0;i<nIndex;i++)
	{
		m_Set.MoveNext();
	}
	m_strUnit=m_Set.m_Unit;
	m_Set.Close();
}

void CAddMedicineDlg::OnChangeEditNumber() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	UpdateData();
	m_fSum=m_fNumber*m_fInPrice;
	CString Temp;
	Temp.Format(_T("%.2f"),m_fSum);
	SetDlgItemText(IDC_EDIT_SUM,Temp);
}

void CAddMedicineDlg::OnChangeEditOutPrice() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.	
	
}

void CAddMedicineDlg::OnChangeEditInPrice() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	UpdateData();
	m_fSum=m_fNumber*m_fInPrice;
	CString Temp;
	Temp.Format(_T("%.2f"),m_fSum);
	SetDlgItemText(IDC_EDIT_SUM,Temp);
	
}
