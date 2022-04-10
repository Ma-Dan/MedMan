// IOMedicineDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MedMan.h"
#include "IOMedicineDlg.h"

#include "SectionSet.h"
#include "MethodSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIOMedicineDlg dialog


CIOMedicineDlg::CIOMedicineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIOMedicineDlg::IDD, pParent)
{
	m_strName="";
	m_strStandard="";
	m_strManufactory="";
	m_strUnit="";

	//默认为出货(出货次数多于进货次数)
	m_nIO=1;
	
	//{{AFX_DATA_INIT(CIOMedicineDlg)
	m_strBatchNumber = _T("");
	m_fInPrice = 0.0f;
	m_fOutPrice = 0.0f;
	m_strSection = _T("");
	m_strMethod = _T("");
	m_fAmount = 0.0f;
	//}}AFX_DATA_INIT
}


void CIOMedicineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIOMedicineDlg)
	DDX_Control(pDX, IDC_COMBO_SECTION, m_ctrlSection);
	DDX_Control(pDX, IDC_COMBO_METHOD, m_ctrlMethod);
	DDX_Control(pDX, IDC_CHECK2, m_ctrlMedicineOut);
	DDX_Control(pDX, IDC_CHECK1, m_ctrlMedicineIn);
	DDX_Text(pDX, IDC_EDIT_BATCHNUMBER, m_strBatchNumber);
	DDV_MaxChars(pDX, m_strBatchNumber, 15);
	DDX_Text(pDX, IDC_EDIT_INPRICE, m_fInPrice);
	DDX_Text(pDX, IDC_EDIT_OUTPRICE, m_fOutPrice);
	DDX_CBString(pDX, IDC_COMBO_SECTION, m_strSection);
	DDX_CBString(pDX, IDC_COMBO_METHOD, m_strMethod);
	DDX_Text(pDX, IDC_EDIT_AMOUNT, m_fAmount);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIOMedicineDlg, CDialog)
	//{{AFX_MSG_MAP(CIOMedicineDlg)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIOMedicineDlg message handlers

BOOL CIOMedicineDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//1.进行信息显示
	CString Information;
	Information="商品名称:"+m_strName+" 生产厂家:"+m_strManufactory+" 规格:"+m_strStandard+" 计量单位:"+m_strUnit;
	SetDlgItemText(IDC_INFORMATION,Information);

	//2.根据是进还是出设置对话框的文字
	SetupDialogTexts();

	//3.设置进出单位
	SetupSections();

	//4.设置付款方式
	SetupMethods();	

	//5.设置按钮状态
	if(m_nIO==1)
	{
		m_ctrlMedicineIn.SetCheck(FALSE);
		m_ctrlMedicineOut.SetCheck(TRUE);
	}
	else
	{
		m_ctrlMedicineIn.SetCheck(TRUE);
		m_ctrlMedicineOut.SetCheck(FALSE);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CIOMedicineDlg::SetupDialogTexts()
{
	if(m_nIO==1) //出货
	{
		SetWindowText("出货");
		SetDlgItemText(IDC_STATIC_SECTION,"出货单位:");
		SetDlgItemText(IDC_STATIC_NUMBER,"出货数量:");
		SetDlgItemText(IDC_STATIC_METHOD,"");
		m_ctrlMethod.ShowWindow(SW_HIDE);
	}
	else
	{
		SetWindowText("进货");
		SetDlgItemText(IDC_STATIC_SECTION,"进货单位:");
		SetDlgItemText(IDC_STATIC_NUMBER,"进货数量:");
		SetDlgItemText(IDC_STATIC_METHOD,"付款方式");
		m_ctrlMethod.ShowWindow(SW_SHOW);
	}
}
void CIOMedicineDlg::OnCheck1() 
{
	if(m_nIO==1)
	{
		m_nIO=0;
		m_ctrlMedicineOut.SetCheck(FALSE);
		SetupDialogTexts();
		SetupSections();
	}
}

void CIOMedicineDlg::OnCheck2() 
{
	if(m_nIO==0)
	{
		m_nIO=1;
		m_ctrlMedicineIn.SetCheck(FALSE);
		SetupDialogTexts();
		SetupSections();
	}
}

void CIOMedicineDlg::SetupSections()
{
	SectionSet m_Set;
	m_Set.Open();
	
	if(m_Set.IsEOF()) //没有记载进出单位
	{
		m_Set.Close();
		return;
	}

	m_ctrlSection.ResetContent();
	m_Set.MoveFirst();	
	if(m_nIO==1) //出货
	{
		while(!m_Set.IsEOF())
		{
			if(m_Set.m_I_O==1)
			{
				m_ctrlSection.AddString(m_Set.m_Section_name);
			}
			m_Set.MoveNext();
		}
	}
	else
	{
		while(!m_Set.IsEOF())
		{
			if(m_Set.m_I_O==0)
			{
				m_ctrlSection.AddString(m_Set.m_Section_name);
			}
			m_Set.MoveNext();
		}
	}

	m_Set.Close();
}

void CIOMedicineDlg::SetupMethods()
{
	MethodSet m_Set;

	m_Set.Open();
	
	if(m_Set.IsEOF())
	{
		return;
	}

	m_ctrlMethod.ResetContent();
	m_Set.MoveFirst();
	while(!m_Set.IsEOF())
	{
		m_ctrlMethod.AddString(m_Set.m_Method);
		m_Set.MoveNext();
	}

	m_Set.Close();
}