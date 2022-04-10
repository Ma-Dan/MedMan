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
	
	//1.��ʼ����ͷ
	m_ctrlListAccount.InsertColumn(0,_T("�û���"),LVCFMT_LEFT,100,-1);
	m_ctrlListAccount.InsertColumn(1,_T("�� ��"),LVCFMT_LEFT,100,-1);
	m_ctrlListAccount.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	//2.�����ʻ��б�
	LoadAccounts();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAccountSettingsDlg::LoadAccounts()
{
	//1.����б�
	m_ctrlListAccount.DeleteAllItems();

	m_nAccountSelect=-1;

	//2.��ѯ��¼���ݿⲢ��д�б�
	CDatabase database;
	CRecordset recordset;
	CString tableName;
	CString sSql;
	CString Temp;
	//�����ݿ�
	TRY
	{
		sSql.Format("DSN=%s;;","Medicine");
		database.OpenEx(sSql,CDatabase::noOdbcDialog);		
	}
	CATCH(CDBException, e)
	{
		//�������Ϊe->m_nRetCode
	}
	END_CATCH
	recordset.m_pDatabase=&database;
	tableName="Account";

	//������Щ�ʻ�
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s",tableName);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		AfxMessageBox("û���û��ʻ���¼!");
		//ʹ����������ݿ�֮��,�ر����ݿ��Լ���¼��
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

	//���ʻ���ӵ����
	m_nAccountTotal=0;
	recordset.MoveFirst();
	while(!recordset.IsEOF())
	{
		//���һ����¼���б�
		recordset.GetFieldValue((short)0,Temp);
		m_ctrlListAccount.InsertItem(m_nAccountTotal,Temp,-1);
		recordset.GetFieldValue((short)1,Temp);
		Temp="******";
		m_ctrlListAccount.SetItemText(m_nAccountTotal,1,Temp);
				
		recordset.MoveNext();
		m_nAccountTotal++;
	}

	m_nAccountTotal=recordset.GetRecordCount();

	//ʹ����������ݿ�֮��,�ر����ݿ��Լ���¼��
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
	//ѡ��һ����¼
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

	//1.�ӶԻ���ȡ������
	BOOL Accepted=FALSE;

	while(!Accepted)
	{
		if(Dialog1.DoModal()==IDOK)
		{
			if(Dialog1.m_strAccount=="")
			{
				AfxMessageBox("�û�������Ϊ��!");
				continue;
			}
			if(Dialog1.m_strPassword!=Dialog1.m_strPasswordConfirm)
			{
				AfxMessageBox("������������벻һ��!");
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

	//2.�޸����ݿ�
	CDatabase database;
	CRecordset recordset;
	CString tableName;
	CString sSql;
	CString Temp;
	//�����ݿ�
	TRY
	{
		sSql.Format("DSN=%s;;","Medicine");
		database.OpenEx(sSql,CDatabase::noOdbcDialog);		
	}
	CATCH(CDBException, e)
	{
		//�������Ϊe->m_nRetCode
	}
	END_CATCH
	recordset.m_pDatabase=&database;
	tableName="Account";

	//��������ʻ��Ƿ��Ѿ�����
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Account = '%s'",tableName,Account);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		//�ʻ�������,�������
	}
	else
	{
		AfxMessageBox("���ʻ��Ѿ�����,�����ظ����!");
		//ʹ����������ݿ�֮��,�ر����ݿ��Լ���¼��
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


	//���ʻ���ӵ����
	sSql.Format("INSERT INTO %s (Account, Password) VALUES ('%s', '%s')",tableName,Account,Password);
	database.ExecuteSQL(sSql);

	//ʹ����������ݿ�֮��,�ر����ݿ��Լ���¼��
	if(recordset.IsOpen())
	{
		recordset.Close();
	}
	if(database.IsOpen())
	{
		database.Close();
	}

	//ˢ���б�
	LoadAccounts();

}

void CAccountSettingsDlg::OnModifyAccount() 
{
	CString Account("");
	CString Password("");
	CAddAccountDlg Dialog1;

	//1.�ӶԻ���ȡ������
	BOOL Accepted=FALSE;

	Dialog1.m_strAccount=m_ctrlListAccount.GetItemText(m_nAccountSelect,0);

	while(!Accepted)
	{
		if(Dialog1.DoModal()==IDOK)
		{
			if(Dialog1.m_strAccount=="")
			{
				AfxMessageBox("�û�������Ϊ��!");
				continue;
			}
			if(Dialog1.m_strPassword!=Dialog1.m_strPasswordConfirm)
			{
				AfxMessageBox("������������벻һ��!");
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

	//2.�޸����ݿ�
	CDatabase database;
	CRecordset recordset;
	CString tableName;
	CString sSql;
	CString Temp;
	//�����ݿ�
	TRY
	{
		sSql.Format("DSN=%s;;","Medicine");
		database.OpenEx(sSql,CDatabase::noOdbcDialog);		
	}
	CATCH(CDBException, e)
	{
		//�������Ϊe->m_nRetCode
	}
	END_CATCH
	recordset.m_pDatabase=&database;
	tableName="Account";

	//��������ʻ��Ƿ��Ѿ�����
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Account = '%s'",tableName,Account);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		//�ʻ�������,�޷��޸�
		AfxMessageBox("���ʻ�������,�޷��޸�!");
		//ʹ����������ݿ�֮��,�ر����ݿ��Լ���¼��
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


	//�޸��ʻ�
	sSql.Format("UPDATE %s SET Password = '%s' WHERE Account = '%s'",tableName,Password,Account);
	database.ExecuteSQL(sSql);

	//ʹ����������ݿ�֮��,�ر����ݿ��Լ���¼��
	if(recordset.IsOpen())
	{
		recordset.Close();
	}
	if(database.IsOpen())
	{
		database.Close();
	}

	//ˢ���б�
	LoadAccounts();
}

void CAccountSettingsDlg::OnDeleteAccount() 
{
	if(m_nAccountTotal==1)
	{
		AfxMessageBox("ֻ��һ���ʻ�,����ɾ��!");
		return;
	}

	if(m_nAccountSelect==-1)
	{
		AfxMessageBox("��δѡ����Ҫɾ�����ʻ�!");
		return;
	}

	if(AfxMessageBox("ȷʵҪɾ�����ʻ���?",MB_YESNO)==IDNO)
	{
		return;
	}

	CString Account;
	Account=m_ctrlListAccount.GetItemText(m_nAccountSelect,0);

	//ɾ���ʻ�
	CDatabase database;
	CRecordset recordset;
	CString tableName;
	CString sSql;
	CString Temp;
	//�����ݿ�
	TRY
	{
		sSql.Format("DSN=%s;;","Medicine");
		database.OpenEx(sSql,CDatabase::noOdbcDialog);		
	}
	CATCH(CDBException, e)
	{
		//�������Ϊe->m_nRetCode
	}
	END_CATCH
	recordset.m_pDatabase=&database;
	tableName="Account";

	//��������ʻ��Ƿ��Ѿ�����
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Account = '%s'",tableName,Account);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		//�ʻ�������,�޷�ɾ��
		AfxMessageBox("���ʻ�������,�޷�ɾ��!");
		//ʹ����������ݿ�֮��,�ر����ݿ��Լ���¼��
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


	//ɾ���ʻ�
	sSql.Format("DELETE FROM %s WHERE Account = '%s'",tableName,Account);
	database.ExecuteSQL(sSql);

	//ʹ����������ݿ�֮��,�ر����ݿ��Լ���¼��
	if(recordset.IsOpen())
	{
		recordset.Close();
	}
	if(database.IsOpen())
	{
		database.Close();
	}

	//ˢ���б�
	LoadAccounts();

}
