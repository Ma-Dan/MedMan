// UnitSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MedMan.h"
#include "UnitSettingsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUnitSettingsDlg dialog


CUnitSettingsDlg::CUnitSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUnitSettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUnitSettingsDlg)
	m_strUnit = _T("");
	//}}AFX_DATA_INIT
}


void CUnitSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUnitSettingsDlg)
	DDX_Control(pDX, IDC_LIST_UNIT, m_ctrlListUnit);
	DDX_Text(pDX, IDC_EDIT_UNIT, m_strUnit);
	DDV_MaxChars(pDX, m_strUnit, 10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUnitSettingsDlg, CDialog)
	//{{AFX_MSG_MAP(CUnitSettingsDlg)
	ON_BN_CLICKED(IDC_ADD_UNIT, OnAddUnit)
	ON_BN_CLICKED(IDC_DELETE_UNIT, OnDeleteUnit)
	ON_NOTIFY(NM_CLICK, IDC_LIST_UNIT, OnClickListUnit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUnitSettingsDlg message handlers

BOOL CUnitSettingsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//1.初始化表头
	m_ctrlListUnit.InsertColumn(0,_T("计量单位"),LVCFMT_LEFT,100,-1);
	m_ctrlListUnit.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	//2.更新单位列表
	LoadUnits();	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUnitSettingsDlg::LoadUnits()
{
	//1.清空列表
	m_ctrlListUnit.DeleteAllItems();

	m_nUnitSelect=-1;

	//2.查询记录数据库并填写列表
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
	tableName="Unit";

	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s ",tableName);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		AfxMessageBox("没有单位记录!");
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


	m_nUnitTotal=0;
	recordset.MoveFirst();
	while(!recordset.IsEOF())
	{
		recordset.GetFieldValue((short)0,Temp);
		m_ctrlListUnit.InsertItem(m_nUnitTotal,Temp,-1);
				
		recordset.MoveNext();
		m_nUnitTotal++;
	}

	m_nUnitTotal=recordset.GetRecordCount();

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

void CUnitSettingsDlg::OnAddUnit() 
{
	UpdateData();

	if(m_strUnit=="")
	{
		AfxMessageBox("请先在左边输入计量单位的名称!");
		return;
	}

	//增加这个计量单位
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
	tableName="Unit";

	//查找这个单位是否已经存在
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Unit = '%s'",tableName,m_strUnit);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		//单位不存在,可以添加
	}
	else
	{
		AfxMessageBox("该计量单位已经存在,不能重复添加!");
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


	//将计量单位添加到表格
	sSql.Format("INSERT INTO %s (Unit) VALUES ('%s')",tableName,m_strUnit);
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

	//刷新列表
	LoadUnits();
}

void CUnitSettingsDlg::OnDeleteUnit() 
{
	if(m_nUnitTotal==1)
	{
		AfxMessageBox("只有一个计量单位,不能删除!");
		return;
	}

	if(m_nUnitSelect==-1)
	{
		AfxMessageBox("尚未选择需要删除的计量单位!");
		return;
	}

	if(AfxMessageBox("确实要删除该计量单位吗?",MB_YESNO)==IDNO)
	{
		return;
	}

	CString Unit;
	Unit=m_ctrlListUnit.GetItemText(m_nUnitSelect,0);

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
	tableName="Unit";

	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Unit = '%s'",tableName,Unit);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		//计量单位不存在,无法删除
		AfxMessageBox("该计量单位不存在,无法删除!");
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
		
	}


	//删除单位
	sSql.Format("DELETE FROM %s WHERE Unit = '%s'",tableName,Unit);
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

	//刷新列表
	LoadUnits();
}

void CUnitSettingsDlg::OnClickListUnit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//选中一条记录
	if(m_ctrlListUnit.GetSelectionMark()!=-1)
	{
		m_nUnitSelect=m_ctrlListUnit.GetSelectionMark();
	}
	else
	{
		m_nUnitSelect=-1;
	}
	
	*pResult = 0;
}
