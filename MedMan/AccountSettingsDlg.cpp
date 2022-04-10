// AccountSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MedMan.h"
#include "AccountSettingsDlg.h"

#include "AddAccountDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAccountSettingsDlg dialog


CAccountSettingsDlg::CAccountSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAccountSettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAccountSettingsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAccountSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAccountSettingsDlg)
	DDX_Control(pDX, IDC_LIST_ACCOUNT, m_ctrlListAccount);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAccountSettingsDlg, CDialog)
	//{{AFX_MSG_MAP(CAccountSettingsDlg)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ACCOUNT, OnClickListAccount)
	ON_BN_CLICKED(IDC_ADD_ACCOUNT, OnAddAccount)
	ON_BN_CLICKED(IDC_MODIFY_ACCOUNT, OnModifyAccount)
	ON_BN_CLICKED(IDC_DELETE_ACCOUNT, OnDeleteAccount)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAccountSettingsDlg message handlers

BOOL CAccountSettingsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//1.初始化表头
	m_ctrlListAccount.InsertColumn(0,_T("用户名"),LVCFMT_LEFT,100,-1);
	m_ctrlListAccount.InsertColumn(1,_T("密 码"),LVCFMT_LEFT,100,-1);
	m_ctrlListAccount.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	//2.更新帐户列表
	LoadAccounts();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAccountSettingsDlg::LoadAccounts()
{
	//1.清空列表
	m_ctrlListAccount.DeleteAllItems();

	m_nAccountSelect=-1;

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
	tableName="Account";

	//查找这些帐户
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s",tableName);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		AfxMessageBox("没有用户帐户记录!");
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

	//将帐户添加到表格
	m_nAccountTotal=0;
	recordset.MoveFirst();
	while(!recordset.IsEOF())
	{
		//添加一个记录到列表
		recordset.GetFieldValue((short)0,Temp);
		m_ctrlListAccount.InsertItem(m_nAccountTotal,Temp,-1);
		recordset.GetFieldValue((short)1,Temp);
		Temp="******";
		m_ctrlListAccount.SetItemText(m_nAccountTotal,1,Temp);
				
		recordset.MoveNext();
		m_nAccountTotal++;
	}

	m_nAccountTotal=recordset.GetRecordCount();

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
void CAccountSettingsDlg::OnClickListAccount(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//选中一条记录
	if(m_ctrlListAccount.GetSelectionMark()!=-1)
	{
		m_nAccountSelect=m_ctrlListAccount.GetSelectionMark();
	}
	else
	{
		m_nAccountSelect=-1;
	}
	
	*pResult = 0;
}

void CAccountSettingsDlg::OnAddAccount() 
{
	CString Account("");
	CString Password("");
	CAddAccountDlg Dialog1;

	//1.从对话框取得数据
	BOOL Accepted=FALSE;

	while(!Accepted)
	{
		if(Dialog1.DoModal()==IDOK)
		{
			if(Dialog1.m_strAccount=="")
			{
				AfxMessageBox("用户名不能为空!");
				continue;
			}
			if(Dialog1.m_strPassword!=Dialog1.m_strPasswordConfirm)
			{
				AfxMessageBox("两次输入的密码不一致!");
				continue;
			}
			Account=Dialog1.m_strAccount;
			Password=Dialog1.m_strPassword;
			Accepted=TRUE;
			break;
		}
		else
		{
			return;
		}
	}

	//2.修改数据库
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
	tableName="Account";

	//查找这个帐户是否已经存在
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Account = '%s'",tableName,Account);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		//帐户不存在,可以添加
	}
	else
	{
		AfxMessageBox("该帐户已经存在,不能重复添加!");
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


	//将帐户添加到表格
	sSql.Format("INSERT INTO %s (Account, Password) VALUES ('%s', '%s')",tableName,Account,Password);
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
	LoadAccounts();

}

void CAccountSettingsDlg::OnModifyAccount() 
{
	CString Account("");
	CString Password("");
	CAddAccountDlg Dialog1;

	//1.从对话框取得数据
	BOOL Accepted=FALSE;

	Dialog1.m_strAccount=m_ctrlListAccount.GetItemText(m_nAccountSelect,0);

	while(!Accepted)
	{
		if(Dialog1.DoModal()==IDOK)
		{
			if(Dialog1.m_strAccount=="")
			{
				AfxMessageBox("用户名不能为空!");
				continue;
			}
			if(Dialog1.m_strPassword!=Dialog1.m_strPasswordConfirm)
			{
				AfxMessageBox("两次输入的密码不一致!");
				continue;
			}
			Account=Dialog1.m_strAccount;
			Password=Dialog1.m_strPassword;
			Accepted=TRUE;
			break;
		}
		else
		{
			return;
		}
	}

	//2.修改数据库
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
	tableName="Account";

	//查找这个帐户是否已经存在
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Account = '%s'",tableName,Account);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		//帐户不存在,无法修改
		AfxMessageBox("该帐户不存在,无法修改!");
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


	//修改帐户
	sSql.Format("UPDATE %s SET Password = '%s' WHERE Account = '%s'",tableName,Password,Account);
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
	LoadAccounts();
}

void CAccountSettingsDlg::OnDeleteAccount() 
{
	if(m_nAccountTotal==1)
	{
		AfxMessageBox("只有一个帐户,不能删除!");
		return;
	}

	if(m_nAccountSelect==-1)
	{
		AfxMessageBox("尚未选择需要删除的帐户!");
		return;
	}

	if(AfxMessageBox("确实要删除该帐户吗?",MB_YESNO)==IDNO)
	{
		return;
	}

	CString Account;
	Account=m_ctrlListAccount.GetItemText(m_nAccountSelect,0);

	//删除帐户
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
	tableName="Account";

	//查找这个帐户是否已经存在
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Account = '%s'",tableName,Account);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		//帐户不存在,无法删除
		AfxMessageBox("该帐户不存在,无法删除!");
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


	//删除帐户
	sSql.Format("DELETE FROM %s WHERE Account = '%s'",tableName,Account);
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
	LoadAccounts();

}
