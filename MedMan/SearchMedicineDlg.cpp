// SearchMedicineDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MedMan.h"
#include "SearchMedicineDlg.h"

#include "ItemSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchMedicineDlg dialog


CSearchMedicineDlg::CSearchMedicineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchMedicineDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchMedicineDlg)
	m_strName = _T("");
	//}}AFX_DATA_INIT
}


void CSearchMedicineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchMedicineDlg)
	DDX_Control(pDX, IDC_CHECK_SHOWINPRICES, m_ctrlCheckInprice);
	DDX_Control(pDX, IDC_LIST_MEDICINE, m_ctrlMedicineList);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 30);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchMedicineDlg, CDialog)
	//{{AFX_MSG_MAP(CSearchMedicineDlg)
	ON_BN_CLICKED(IDC_SEARCH, OnSearch)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MEDICINE, OnClickListMedicine)
	ON_EN_CHANGE(IDC_EDIT_NAME, OnChangeEditName)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_MEDICINE, OnDblclkListMedicine)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_MEDICINE, OnItemchangedListMedicine)
	ON_BN_CLICKED(IDC_CHECK_SHOWINPRICES, OnCheckShowinprices)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchMedicineDlg message handlers

BOOL CSearchMedicineDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//1.初始化表格(表头显示)
	m_ctrlMedicineList.InsertColumn(0,_T("商品名称"),LVCFMT_LEFT,80,-1);
	m_ctrlMedicineList.InsertColumn(1,_T("规 格"),LVCFMT_LEFT,80,-1);
	m_ctrlMedicineList.InsertColumn(2,_T("生产厂家"),LVCFMT_LEFT,80,-1);
	m_ctrlMedicineList.InsertColumn(3,_T("计量单位"),LVCFMT_LEFT,80,-1);
	m_ctrlMedicineList.InsertColumn(4,_T("当前存量"),LVCFMT_LEFT,80,-1);
	m_ctrlMedicineList.InsertColumn(5,_T("最小存量"),LVCFMT_LEFT,80,-1);
	m_ctrlMedicineList.InsertColumn(6,_T("进货单价"),LVCFMT_LEFT,0,-1);
	m_ctrlMedicineList.InsertColumn(7,_T("出货单价"),LVCFMT_LEFT,80,-1);
	m_ctrlMedicineList.InsertColumn(8,_T("金 额"),LVCFMT_LEFT,80,-1);
	m_ctrlMedicineList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);	

	//2.获取当前商品的列表
	CItemSet m_Set;
	m_Set.Open(CRecordset::dynaset,"SELECT * FROM ItemList ORDER BY Abbreviation");
	m_nTotalFind=0;
	CString Temp(_T(""));
	if(m_Set.IsEOF())
	{
		AfxMessageBox("数据库中尚未存入商品！");
	}
	else
	{
		m_Set.MoveFirst();
		m_ctrlMedicineList.DeleteAllItems();
		
		while(!m_Set.IsEOF())
		{
			//添加一个商品到列表
			m_ctrlMedicineList.InsertItem(m_nTotalFind,m_Set.m_Name,-1);
			m_ctrlMedicineList.SetItemText(m_nTotalFind,1,m_Set.m_Standard);
			m_ctrlMedicineList.SetItemText(m_nTotalFind,2,m_Set.m_Manufactory);
			m_ctrlMedicineList.SetItemText(m_nTotalFind,3,m_Set.m_Unit);
			Temp.Format(_T("%.2f"),m_Set.m_Amount);
			m_ctrlMedicineList.SetItemText(m_nTotalFind,4,Temp);
			Temp.Format(_T("%.2f"),m_Set.m_Minimum);
			m_ctrlMedicineList.SetItemText(m_nTotalFind,5,Temp);
			Temp.Format(_T("%.2f"),m_Set.m_In_price);
			m_ctrlMedicineList.SetItemText(m_nTotalFind,6,Temp);
			Temp.Format(_T("%.2f"),m_Set.m_Out_price);
			m_ctrlMedicineList.SetItemText(m_nTotalFind,7,Temp);
			Temp.Format(_T("%.2f"),m_Set.m_Sum);
			m_ctrlMedicineList.SetItemText(m_nTotalFind,8,Temp);
			
			m_Set.MoveNext();
			m_nTotalFind++;
		}
	}

	Temp.Format("%d",m_nTotalFind);
	SetDlgItemText(IDC_EDIT_SEARCH_TOTAL,Temp);

	m_Set.Close();

	//3.初始化名称以及规格
	m_strNameSelected="";
	m_strStandardSelected="";
	m_strManufactory="";
	m_strUnit="";

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSearchMedicineDlg::OnSearch() 
{
	UpdateData();
	if(m_strName=="")
	{
		return;
	}
	
	//在ItemList数据库中查找符合要求(Name=m_strName)的商品
	CDatabase database;
	CRecordset recordset;
	CString tableName;
	CString sSql;
	CString Temp;

	//打开数据库
	TRY
	{
		sSql.Format("DSN=%s;;","Medicine");
		database.OpenEx(sSql,CDatabase::noOdbcDialog);		
	}
	CATCH(CDBException, e)
	{
		//错误代码为e->m_nRetCode
	}
	END_CATCH
	recordset.m_pDatabase=&database;
	tableName="ItemList";

	//查找该商品是否已经存在
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Abbreviation LIKE '%%%s%%' ORDER BY Abbreviation",tableName,m_strName);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		AfxMessageBox("该商品尚未记录入数据库，请先增加该商品!");
		//使用完这个数据库之后,关闭数据库以及记录集
		if(recordset.IsOpen())
		{
			recordset.Close();
		}
		if(database.IsOpen())
		{
			database.Close();
		}
		return;
	}
	else
	{
		//存在这个商品,更新列表显示
		m_ctrlMedicineList.DeleteAllItems();
		m_nTotalFind=0;

		recordset.MoveFirst();
		while(!recordset.IsEOF())
		{
			//添加一个商品到列表
			recordset.GetFieldValue((short)0,Temp);
			m_ctrlMedicineList.InsertItem(m_nTotalFind,Temp,-1);
			recordset.GetFieldValue((short)1,Temp);
			m_ctrlMedicineList.SetItemText(m_nTotalFind,1,Temp);
			recordset.GetFieldValue((short)2,Temp);
			m_ctrlMedicineList.SetItemText(m_nTotalFind,2,Temp);
			recordset.GetFieldValue((short)7,Temp);
			m_ctrlMedicineList.SetItemText(m_nTotalFind,3,Temp);
			recordset.GetFieldValue((short)5,Temp);
			m_ctrlMedicineList.SetItemText(m_nTotalFind,4,Temp);
			recordset.GetFieldValue((short)6,Temp);
			m_ctrlMedicineList.SetItemText(m_nTotalFind,5,Temp);
			recordset.GetFieldValue((short)3,Temp);
			m_ctrlMedicineList.SetItemText(m_nTotalFind,6,Temp);
			recordset.GetFieldValue((short)4,Temp);
			m_ctrlMedicineList.SetItemText(m_nTotalFind,7,Temp);
			recordset.GetFieldValue((short)8,Temp);
			m_ctrlMedicineList.SetItemText(m_nTotalFind,8,Temp);
			
			recordset.MoveNext();
			m_nTotalFind++;
		}

		m_nTotalFind=recordset.GetRecordCount();
		Temp.Format("%d",m_nTotalFind);
		SetDlgItemText(IDC_EDIT_SEARCH_TOTAL,Temp);
	}

	//使用完这个数据库之后,关闭数据库以及记录集
	if(recordset.IsOpen())
	{
		recordset.Close();
	}
    if(database.IsOpen())
	{
		database.Close();
	}


}

void CSearchMedicineDlg::OnClickListMedicine(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//选择商品后，更新名称以及规格信息
	if(m_ctrlMedicineList.GetSelectionMark()!=-1)
	{
		m_strNameSelected=m_ctrlMedicineList.GetItemText(m_ctrlMedicineList.GetSelectionMark(),0);
		SetDlgItemText(IDC_EDIT_NAMESELECTED,m_strNameSelected);
		m_strStandardSelected=m_ctrlMedicineList.GetItemText(m_ctrlMedicineList.GetSelectionMark(),1);
		SetDlgItemText(IDC_EDIT_STANDARDSELECTED,m_strStandardSelected);
		m_strManufactory=m_ctrlMedicineList.GetItemText(m_ctrlMedicineList.GetSelectionMark(),2);
		m_strUnit=m_ctrlMedicineList.GetItemText(m_ctrlMedicineList.GetSelectionMark(),3);
	}
	else
	{
		
	}
	
	*pResult = 0;
}

void CSearchMedicineDlg::OnChangeEditName() 
{
	UpdateData();
	/*if(m_strName=="")
	{
		return;
	}*/
	
	//在ItemList数据库中查找符合要求(Name=m_strName)的商品
	CDatabase database;
	CRecordset recordset;
	CString tableName;
	CString sSql;
	CString Temp;

	//打开数据库
	TRY
	{
		sSql.Format("DSN=%s;;","Medicine");
		database.OpenEx(sSql,CDatabase::noOdbcDialog);		
	}
	CATCH(CDBException, e)
	{
		//错误代码为e->m_nRetCode
	}
	END_CATCH
	recordset.m_pDatabase=&database;
	tableName="ItemList";

	//查找该商品是否已经存在
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Abbreviation LIKE '%%%s%%' ORDER BY Abbreviation",tableName,m_strName);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		AfxMessageBox("该商品尚未记录入数据库，请先增加该商品!");
		//使用完这个数据库之后,关闭数据库以及记录集
		if(recordset.IsOpen())
		{
			recordset.Close();
		}
		if(database.IsOpen())
		{
			database.Close();
		}
		return;
	}
	else
	{
		//存在这个商品,更新列表显示
		m_ctrlMedicineList.DeleteAllItems();
		m_nTotalFind=0;

		recordset.MoveFirst();
		while(!recordset.IsEOF())
		{
			//添加一个商品到列表
			recordset.GetFieldValue((short)0,Temp);
			m_ctrlMedicineList.InsertItem(m_nTotalFind,Temp,-1);
			recordset.GetFieldValue((short)1,Temp);
			m_ctrlMedicineList.SetItemText(m_nTotalFind,1,Temp);
			recordset.GetFieldValue((short)2,Temp);
			m_ctrlMedicineList.SetItemText(m_nTotalFind,2,Temp);
			recordset.GetFieldValue((short)7,Temp);
			m_ctrlMedicineList.SetItemText(m_nTotalFind,3,Temp);
			recordset.GetFieldValue((short)5,Temp);
			m_ctrlMedicineList.SetItemText(m_nTotalFind,4,Temp);
			recordset.GetFieldValue((short)6,Temp);
			m_ctrlMedicineList.SetItemText(m_nTotalFind,5,Temp);
			recordset.GetFieldValue((short)3,Temp);
			m_ctrlMedicineList.SetItemText(m_nTotalFind,6,Temp);
			recordset.GetFieldValue((short)4,Temp);
			m_ctrlMedicineList.SetItemText(m_nTotalFind,7,Temp);
			recordset.GetFieldValue((short)8,Temp);
			m_ctrlMedicineList.SetItemText(m_nTotalFind,8,Temp);
			
			recordset.MoveNext();
			m_nTotalFind++;
		}

		m_nTotalFind=recordset.GetRecordCount();
		Temp.Format("%d",m_nTotalFind);
		SetDlgItemText(IDC_EDIT_SEARCH_TOTAL,Temp);
	}

	//使用完这个数据库之后,关闭数据库以及记录集
	if(recordset.IsOpen())
	{
		recordset.Close();
	}
    if(database.IsOpen())
	{
		database.Close();
	}
	
}

void CSearchMedicineDlg::OnDblclkListMedicine(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//选择商品后，更新名称以及规格信息
	if(m_ctrlMedicineList.GetSelectionMark()!=-1)
	{
		m_strNameSelected=m_ctrlMedicineList.GetItemText(m_ctrlMedicineList.GetSelectionMark(),0);
		SetDlgItemText(IDC_EDIT_NAMESELECTED,m_strNameSelected);
		m_strStandardSelected=m_ctrlMedicineList.GetItemText(m_ctrlMedicineList.GetSelectionMark(),1);
		SetDlgItemText(IDC_EDIT_STANDARDSELECTED,m_strStandardSelected);
		m_strManufactory=m_ctrlMedicineList.GetItemText(m_ctrlMedicineList.GetSelectionMark(),2);
		m_strUnit=m_ctrlMedicineList.GetItemText(m_ctrlMedicineList.GetSelectionMark(),3);
	}
	else
	{
		
	}

	OnOK();
	
	*pResult = 0;
}

void CSearchMedicineDlg::OnItemchangedListMedicine(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	TRACE("%d",m_ctrlMedicineList.GetSelectionMark());
	//选择商品后，更新名称以及规格信息
	if(m_ctrlMedicineList.GetSelectionMark()!=-1)
	{
		m_strNameSelected=m_ctrlMedicineList.GetItemText(m_ctrlMedicineList.GetSelectionMark(),0);
		SetDlgItemText(IDC_EDIT_NAMESELECTED,m_strNameSelected);
		m_strStandardSelected=m_ctrlMedicineList.GetItemText(m_ctrlMedicineList.GetSelectionMark(),1);
		SetDlgItemText(IDC_EDIT_STANDARDSELECTED,m_strStandardSelected);
		m_strManufactory=m_ctrlMedicineList.GetItemText(m_ctrlMedicineList.GetSelectionMark(),2);
		m_strUnit=m_ctrlMedicineList.GetItemText(m_ctrlMedicineList.GetSelectionMark(),3);
	}
	else
	{
		
	}
	
	*pResult = 0;
}

void CSearchMedicineDlg::OnCheckShowinprices() 
{
	if(m_ctrlCheckInprice.GetCheck())
	{
		m_ctrlMedicineList.SetColumnWidth(6, 80);
	}
	else
	{
		m_ctrlMedicineList.SetColumnWidth(6, 0);
	}
}
