// MethodSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MedMan.h"
#include "MethodSettingsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMethodSettingsDlg dialog


CMethodSettingsDlg::CMethodSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMethodSettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMethodSettingsDlg)
	m_strMethod = _T("");
	//}}AFX_DATA_INIT
}


void CMethodSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMethodSettingsDlg)
	DDX_Control(pDX, IDC_LIST_METHOD, m_ctrlListMethod);
	DDX_Text(pDX, IDC_EDIT_METHOD, m_strMethod);
	DDV_MaxChars(pDX, m_strMethod, 20);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMethodSettingsDlg, CDialog)
	//{{AFX_MSG_MAP(CMethodSettingsDlg)
	ON_BN_CLICKED(IDC_ADD_METHOD, OnAddMethod)
	ON_BN_CLICKED(IDC_DELETE_METHOD, OnDeleteMethod)
	ON_NOTIFY(NM_CLICK, IDC_LIST_METHOD, OnClickListMethod)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMethodSettingsDlg message handlers

BOOL CMethodSettingsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//1.初始化表头
	m_ctrlListMethod.InsertColumn(0,_T("付款方式"),LVCFMT_LEFT,100,-1);
	m_ctrlListMethod.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	//2.更新单位列表
	LoadMethods();	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMethodSettingsDlg::LoadMethods()
{
	//1.清空列表
	m_ctrlListMethod.DeleteAllItems();

	m_nMethodSelect=-1;

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
	tableName="Method";

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


	m_nMethodTotal=0;
	recordset.MoveFirst();
	while(!recordset.IsEOF())
	{
		recordset.GetFieldValue((short)0,Temp);
		m_ctrlListMethod.InsertItem(m_nMethodTotal,Temp,-1);
				
		recordset.MoveNext();
		m_nMethodTotal++;
	}

	m_nMethodTotal=recordset.GetRecordCount();

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


void CMethodSettingsDlg::OnAddMethod() 
{
	UpdateData();

	if(m_strMethod=="")
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
	tableName="Method";

	//查找这个单位是否已经存在
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Method = '%s'",tableName,m_strMethod);
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
	sSql.Format("INSERT INTO %s (Method) VALUES ('%s')",tableName,m_strMethod);
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
	LoadMethods();
}

void CMethodSettingsDlg::OnDeleteMethod() 
{
	if(m_nMethodTotal==1)
	{
		AfxMessageBox("只有一个计量单位,不能删除!");
		return;
	}

	if(m_nMethodSelect==-1)
	{
		AfxMessageBox("尚未选择需要删除的计量单位!");
		return;
	}

	if(AfxMessageBox("确实要删除该计量单位吗?",MB_YESNO)==IDNO)
	{
		return;
	}

	CString Method;
	Method=m_ctrlListMethod.GetItemText(m_nMethodSelect,0);

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
	tableName="Method";

	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Method = '%s'",tableName,Method);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		//付款方式不存在,无法删除
		AfxMessageBox("该付款方式不存在,无法删除!");
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


	//删除付款方式
	sSql.Format("DELETE FROM %s WHERE Method = '%s'",tableName,Method);
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
	LoadMethods();
}

void CMethodSettingsDlg::OnClickListMethod(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//选中一条记录
	if(m_ctrlListMethod.GetSelectionMark()!=-1)
	{
		m_nMethodSelect=m_ctrlListMethod.GetSelectionMark();
	}
	else
	{
		m_nMethodSelect=-1;
	}

	*pResult = 0;
}
