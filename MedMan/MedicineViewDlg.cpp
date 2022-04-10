// MedicineViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MedMan.h"
#include "MedicineViewDlg.h"

#include "ItemSet.h"
#include "EditInformationDlg.h"
#include "AddMedicineDlg.h"

#include "GetSpell.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMedicineViewDlg dialog


CMedicineViewDlg::CMedicineViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMedicineViewDlg::IDD, pParent)
{
	m_strOperator="";
	//{{AFX_DATA_INIT(CMedicineViewDlg)
	m_strName = _T("");
	//}}AFX_DATA_INIT
}


void CMedicineViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMedicineViewDlg)
	DDX_Control(pDX, IDC_CHECK_SHOWINPRICE, m_ctrlCheckInprice);
	DDX_Control(pDX, IDC_LIST_ITEM, m_ctrlListItem);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 30);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMedicineViewDlg, CDialog)
	//{{AFX_MSG_MAP(CMedicineViewDlg)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ITEM, OnClickListItem)
	ON_BN_CLICKED(IDC_VIEW_EDIT, OnViewEdit)
	ON_BN_CLICKED(IDC_VIEW_ADD, OnViewAdd)
	ON_BN_CLICKED(IDC_VIEW_DELETE, OnViewDelete)
	ON_EN_CHANGE(IDC_EDIT_NAME, OnChangeEditName)
	ON_BN_CLICKED(IDC_CHECK_SHOWINPRICE, OnCheckShowinprice)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMedicineViewDlg message handlers

BOOL CMedicineViewDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//1.初始化表格(表头显示)
	m_ctrlListItem.InsertColumn(0,_T("商品名称"),LVCFMT_LEFT,80,-1);
	m_ctrlListItem.InsertColumn(1,_T("规 格"),LVCFMT_LEFT,80,-1);
	m_ctrlListItem.InsertColumn(2,_T("生产厂家"),LVCFMT_LEFT,80,-1);
	m_ctrlListItem.InsertColumn(3,_T("计量单位"),LVCFMT_LEFT,80,-1);
	m_ctrlListItem.InsertColumn(4,_T("当前存量"),LVCFMT_LEFT,80,-1);
	m_ctrlListItem.InsertColumn(5,_T("最小存量"),LVCFMT_LEFT,80,-1);
	m_ctrlListItem.InsertColumn(6,_T("进货单价"),LVCFMT_LEFT,0,-1);
	m_ctrlListItem.InsertColumn(7,_T("出货单价"),LVCFMT_LEFT,80,-1);
	m_ctrlListItem.InsertColumn(8,_T("金 额"),LVCFMT_LEFT,80,-1);
	m_ctrlListItem.InsertColumn(9,_T("批 号"),LVCFMT_LEFT,80,-1);
	m_ctrlListItem.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);	

	//2.加载物品
	LoadItems();
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMedicineViewDlg::OnClickListItem(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CString Temp(_T(""));
	if(m_ctrlListItem.GetSelectionMark()!=-1)
	{
		m_nCurrentSelect=m_ctrlListItem.GetSelectionMark()+1;
		Temp.Format(_T("%d"),m_nCurrentSelect);
		SetDlgItemText(IDC_EDIT_SELECT,Temp);
	}
	else
	{
		m_nCurrentSelect=0;
		Temp.Format(_T("%d"),m_nCurrentSelect);
		SetDlgItemText(IDC_EDIT_SELECT,Temp);
	}
	
	*pResult = 0;
}

void CMedicineViewDlg::LoadItems()
{
	m_ctrlListItem.DeleteAllItems();
	//1.获取当前商品的列表
	CItemSet m_Set;
	m_Set.Open(CRecordset::dynaset,"SELECT * FROM ItemList ORDER BY Abbreviation");
	m_nTotalItems=0;
	m_nCurrentSelect=0;
	CString Temp(_T(""));
	if(m_Set.IsEOF())
	{
		AfxMessageBox("数据库中尚未存入商品！");
	}
	else
	{
		m_Set.MoveFirst();
		m_ctrlListItem.DeleteAllItems();
		
		while(!m_Set.IsEOF())
		{
			//添加一个商品到列表
			m_ctrlListItem.InsertItem(m_nTotalItems,m_Set.m_Name,-1);
			m_ctrlListItem.SetItemText(m_nTotalItems,1,m_Set.m_Standard);
			m_ctrlListItem.SetItemText(m_nTotalItems,2,m_Set.m_Manufactory);
			m_ctrlListItem.SetItemText(m_nTotalItems,3,m_Set.m_Unit);
			Temp.Format(_T("%.2f"),m_Set.m_Amount);
			m_ctrlListItem.SetItemText(m_nTotalItems,4,Temp);
			Temp.Format(_T("%.2f"),m_Set.m_Minimum);
			m_ctrlListItem.SetItemText(m_nTotalItems,5,Temp);
			Temp.Format(_T("%.2f"),m_Set.m_In_price);
			m_ctrlListItem.SetItemText(m_nTotalItems,6,Temp);
			Temp.Format(_T("%.2f"),m_Set.m_Out_price);
			m_ctrlListItem.SetItemText(m_nTotalItems,7,Temp);
			Temp.Format(_T("%.2f"),m_Set.m_Sum);
			m_ctrlListItem.SetItemText(m_nTotalItems,8,Temp);
			m_ctrlListItem.SetItemText(m_nTotalItems,9,m_Set.m_Batch_number);
			
			m_Set.MoveNext();
			m_nTotalItems++;
		}
	}

	m_Set.Close();

	//2.更新商品总数以及当前选择数显示
	Temp.Format(_T("%d"),m_nTotalItems);
	SetDlgItemText(IDC_EDIT_TOTAL,Temp);
	Temp.Format(_T("%d"),m_nCurrentSelect);
	SetDlgItemText(IDC_EDIT_SELECT,Temp);
}

void CMedicineViewDlg::OnViewEdit() 
{
	//更改商品信息(这里可以更新厂家,计量单位,最小余量以及进出价格信息,不修改记录表,只修改物品表,因为影响不大)
	//其他的信息不准在这里更改

	//1.获取当前显示的商品信息(名称以及规格)
	if(m_nCurrentSelect==0)
	{
		AfxMessageBox("你尚未选择商品");
		return;
	}

	CString Name,Standard,Manufactory,Unit,BatchNumber;
	float Minimum,InPrice,OutPrice,Amount;
	Name=m_ctrlListItem.GetItemText(m_nCurrentSelect-1,0);
	Standard=m_ctrlListItem.GetItemText(m_nCurrentSelect-1,1);
	Manufactory=m_ctrlListItem.GetItemText(m_nCurrentSelect-1,2);
	Unit=m_ctrlListItem.GetItemText(m_nCurrentSelect-1,3);
	Amount=atof(m_ctrlListItem.GetItemText(m_nCurrentSelect-1,4).GetBuffer(0));
	Minimum=atof(m_ctrlListItem.GetItemText(m_nCurrentSelect-1,5).GetBuffer(0));
	InPrice=atof(m_ctrlListItem.GetItemText(m_nCurrentSelect-1,6).GetBuffer(0));
	OutPrice=atof(m_ctrlListItem.GetItemText(m_nCurrentSelect-1,7).GetBuffer(0));
	BatchNumber=m_ctrlListItem.GetItemText(m_nCurrentSelect-1,9);

	//2.进行更改对话框操作
	CEditInformationDlg Dialog1;

	Dialog1.m_strName=Name;
	Dialog1.m_strStandard=Standard;
	Dialog1.m_strManufactory=Manufactory;
	Dialog1.m_strUnit=Unit;
	Dialog1.m_fMinimum=Minimum;
	Dialog1.m_fInPrice=InPrice;
	Dialog1.m_fOutPrice=OutPrice;
	Dialog1.m_strBatchNumber=BatchNumber;

	BOOL Accepted=FALSE;

	while(!Accepted)
	{
		if(Dialog1.DoModal()==IDOK)
		{
			Manufactory=Dialog1.m_strManufactory;
			Minimum=Dialog1.m_fMinimum;
			Unit=Dialog1.m_strUnit;
			if(Unit=="")
			{
				AfxMessageBox("单位不能为空!");
				continue;
			}
			InPrice=Dialog1.m_fInPrice;
			OutPrice=Dialog1.m_fOutPrice;
			BatchNumber=Dialog1.m_strBatchNumber;
			if(InPrice==0.0||OutPrice==0.0)
			{
				AfxMessageBox("单价不能为零!");
				continue;
			}
			Accepted=TRUE;
			break;
		}
		else
		{
			return;
		}
	}

	//3.已经取得正确信息，进行修改
	CDatabase database;
	CRecordset recordset;
	CString tableName;
	CString sSql;
	
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
	sSql.Format("SELECT * FROM %s WHERE Name = '%s' AND Standard = '%s' ",tableName,Name,Standard);
	
	recordset.Open(CRecordset::dynaset,sSql);
	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		//该商品不存在,无法操作,这种情况实际不会出现
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
	
	//该商品存在,更新信息
	sSql.Format("UPDATE %s SET Manufactory = '%s', Unit = '%s', In_price=%.2f, Out_price=%.2f, Minimum = %.2f, Sum = %.2f, Batch_number = '%s' WHERE Name = '%s' AND Standard = '%s'",tableName,Manufactory,Unit,InPrice,OutPrice,Minimum,Amount*InPrice,BatchNumber,Name,Standard);
	database.ExecuteSQL(sSql);	
	
	//使用完这个数据库之后,关闭数据库以及记录集
	if(recordset.IsOpen())
	{
		recordset.Close();
	}
    if(database.IsOpen())
	{
		database.Close();
	}

	LoadItems();

}

void CMedicineViewDlg::OnViewAdd() 
{
	//从这里新增商品
	//需要使用的局部变量
	CAddMedicineDlg Dialog1;
	CString m_strName(_T(""));
	CString m_strStandard(_T(""));
	CString m_strManufactory(_T(""));
	float m_fInPrice=0.0;
	float m_fOutPrice=0.0;
	float m_fNumber=0.0;
	float m_fMinimum=0.0;
	CString m_strUnit(_T(""));
	float m_fSum=0.0;
	CString m_strBatchNumber(_T(""));

	//从对话框取得数据
	BOOL Accepted=FALSE;

	while(!Accepted)
	{
		if(Dialog1.DoModal()==IDOK)
		{
			//更新数据
			m_strName=Dialog1.m_strName;
			m_strStandard=Dialog1.m_strStandard;
			m_strManufactory=Dialog1.m_strManufactory;
			m_fInPrice=Dialog1.m_fInPrice;
			m_fOutPrice=Dialog1.m_fOutPrice;
			m_fNumber=Dialog1.m_fNumber;
			m_fMinimum=Dialog1.m_fMinimum;
			m_strUnit=Dialog1.m_strUnit;
			m_fSum=Dialog1.m_fSum;
			m_strBatchNumber=Dialog1.m_strBatchNumber;
			//检查各项是否填写合格
			if(m_strName==_T(""))
			{
				AfxMessageBox("名称不能为空!");
				continue;
			}
			if(m_strUnit==_T(""))
			{
				AfxMessageBox("计量单位不能为空!");
				continue;
			}
			if(m_fInPrice==0.0||m_fOutPrice==0.0)
			{
				AfxMessageBox("单价不能为零!");
				continue;
			}

			Accepted=TRUE;
			break;
		}
		else
		{
			return;
		}
	}

	//取得拼音缩写
	CString Abbreviation("");
	CGetSpell PYSpell;
	Abbreviation=PYSpell.GetChineseSpell(m_strName);
	PYSpell.~CGetSpell();

	//取得正确的数据,更新数据库
	//1.更新商品列表数据库

	//判断是否已经在库中,按照名称和规格来判断,有则不予添加	
	
	CDatabase database;
	CRecordset recordset;
	CString tableName;
	CString sSql;

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
	sSql.Format("SELECT * FROM %s WHERE Name = '%s' AND Standard = '%s' ",tableName,m_strName,m_strStandard);
	recordset.Open(CRecordset::dynaset,sSql);
	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		//该商品不存在,可以添加这个商品
		sSql.Format("INSERT INTO %s (Name,Standard,Manufactory,In_price,Out_price,Amount,Minimum,Unit,Sum,Abbreviation ) VALUES ('%s','%s','%s',%.2f,%.2f,%.2f,%.2f,'%s',%.2f,'%s' )",tableName,m_strName,m_strStandard,m_strManufactory,m_fInPrice,m_fOutPrice,m_fNumber,m_fMinimum,m_strUnit,m_fSum,Abbreviation);
		database.ExecuteSQL(sSql);
	}
	else
	{
		//该商品存在,则退出
		AfxMessageBox("该商品已经存在,不能重复添加!");
		return;
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

	//2.更新记录数据库,增加一条叫做"新增"的进货记录
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
	tableName="RecordList";
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s ",tableName);
	recordset.Open(CRecordset::dynaset,sSql);
	//增加这条记录
	CTime now=CTime::GetCurrentTime();
	CString datetime;
	datetime=now.Format(_T("%Y-%m-%d %H:%M:%S"));
	sSql.Format("INSERT INTO %s (Date_time,Name,Standard,Batch_number,Section,Method,Amount,Unit,In_price,Out_price,Remaining,Sum,In_or_out,Operator ) VALUES ('%s','%s','%s','%s','新增','新增',%.2f,'%s',%.2f,%.2f,%.2f,%.2f,0,'%s' )",tableName,datetime,m_strName,m_strStandard,m_strBatchNumber,m_fNumber,m_strUnit,m_fInPrice,m_fOutPrice,m_fNumber,m_fInPrice*m_fNumber,m_strOperator);
	database.ExecuteSQL(sSql);
	//使用完这个数据库之后,关闭数据库以及记录集
	if(recordset.IsOpen())
	{
		recordset.Close();
	}
    if(database.IsOpen())
	{
		database.Close();
	}

	LoadItems();
}

void CMedicineViewDlg::OnViewDelete() 
{
	//1.获取当前选择的商品信息(名称以及规格)
	if(m_nCurrentSelect==0)
	{
		AfxMessageBox("你尚未选择商品");
		return;
	}

	//2.确认一次删除操作
	//删除之前进行一次确认
	if(AfxMessageBox("删除之后该商品对应的进出记录也将被删除，\n您确定要删除这种商品？",MB_YESNO)==IDNO)
	{
		return;
	}

	//3.取得名称和规格信息并进行删除操作
	CString Name("");
	CString Standard("");

	Name=m_ctrlListItem.GetItemText(m_nCurrentSelect-1,0);
	Standard=m_ctrlListItem.GetItemText(m_nCurrentSelect-1,1);

	CDatabase database;
	CRecordset recordset;
	CString tableName;
	CString sSql;

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
	sSql.Format("SELECT * FROM %s WHERE Name = '%s' AND Standard = '%s' ",tableName,Name,Standard);
	recordset.Open(CRecordset::dynaset,sSql);
	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		//该商品不存在,返回(这种情况不存在)
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
		//该商品存在,则删除
		sSql.Format("DELETE FROM %s WHERE Name = '%s' AND Standard = '%s'",tableName,Name,Standard);
		database.ExecuteSQL(sSql);		
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

	//2.删除记录数据库中对应的进出记录
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
	tableName="RecordList";
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Name = '%s' AND Standard = '%s' ",tableName,Name,Standard);
	recordset.Open(CRecordset::dynaset,sSql);
	
	//删除这种商品的记录
	sSql.Format("DELETE FROM %s WHERE Name = '%s' AND Standard = '%s'",tableName,Name,Standard);
	database.ExecuteSQL(sSql);	
	//使用完这个数据库之后,关闭数据库以及记录集
	if(recordset.IsOpen())
	{
		recordset.Close();
	}
    if(database.IsOpen())
	{
		database.Close();
	}

	LoadItems();
	
}

void CMedicineViewDlg::OnChangeEditName() 
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
		m_ctrlListItem.DeleteAllItems();
		m_nTotalFind=0;

		recordset.MoveFirst();
		while(!recordset.IsEOF())
		{
			//添加一个商品到列表
			recordset.GetFieldValue((short)0,Temp);
			m_ctrlListItem.InsertItem(m_nTotalFind,Temp,-1);
			recordset.GetFieldValue((short)1,Temp);
			m_ctrlListItem.SetItemText(m_nTotalFind,1,Temp);
			recordset.GetFieldValue((short)2,Temp);
			m_ctrlListItem.SetItemText(m_nTotalFind,2,Temp);
			recordset.GetFieldValue((short)7,Temp);
			m_ctrlListItem.SetItemText(m_nTotalFind,3,Temp);
			recordset.GetFieldValue((short)5,Temp);
			m_ctrlListItem.SetItemText(m_nTotalFind,4,Temp);
			recordset.GetFieldValue((short)6,Temp);
			m_ctrlListItem.SetItemText(m_nTotalFind,5,Temp);
			recordset.GetFieldValue((short)3,Temp);
			m_ctrlListItem.SetItemText(m_nTotalFind,6,Temp);
			recordset.GetFieldValue((short)4,Temp);
			m_ctrlListItem.SetItemText(m_nTotalFind,7,Temp);
			recordset.GetFieldValue((short)8,Temp);
			m_ctrlListItem.SetItemText(m_nTotalFind,8,Temp);
			recordset.GetFieldValue((short)10,Temp);
			m_ctrlListItem.SetItemText(m_nTotalFind,9,Temp);
			
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

void CMedicineViewDlg::OnCheckShowinprice() 
{
	if(m_ctrlCheckInprice.GetCheck())
	{
		m_ctrlListItem.SetColumnWidth(6, 80);
	}
	else
	{
		m_ctrlListItem.SetColumnWidth(6, 0);
	}
}
