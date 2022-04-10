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
	
	//1.��ʼ����ͷ
	m_ctrlListMethod.InsertColumn(0,_T("���ʽ"),LVCFMT_LEFT,100,-1);
	m_ctrlListMethod.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	//2.���µ�λ�б�
	LoadMethods();	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMethodSettingsDlg::LoadMethods()
{
	//1.����б�
	m_ctrlListMethod.DeleteAllItems();

	m_nMethodSelect=-1;

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
	tableName="Method";

	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s ",tableName);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		AfxMessageBox("û�е�λ��¼!");
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


void CMethodSettingsDlg::OnAddMethod() 
{
	UpdateData();

	if(m_strMethod=="")
	{
		AfxMessageBox("������������������λ������!");
		return;
	}

	//�������������λ
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
	tableName="Method";

	//���������λ�Ƿ��Ѿ�����
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Method = '%s'",tableName,m_strMethod);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		//��λ������,�������
	}
	else
	{
		AfxMessageBox("�ü�����λ�Ѿ�����,�����ظ����!");
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


	//��������λ��ӵ����
	sSql.Format("INSERT INTO %s (Method) VALUES ('%s')",tableName,m_strMethod);
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
	LoadMethods();
}

void CMethodSettingsDlg::OnDeleteMethod() 
{
	if(m_nMethodTotal==1)
	{
		AfxMessageBox("ֻ��һ��������λ,����ɾ��!");
		return;
	}

	if(m_nMethodSelect==-1)
	{
		AfxMessageBox("��δѡ����Ҫɾ���ļ�����λ!");
		return;
	}

	if(AfxMessageBox("ȷʵҪɾ���ü�����λ��?",MB_YESNO)==IDNO)
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
	tableName="Method";

	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Method = '%s'",tableName,Method);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		//���ʽ������,�޷�ɾ��
		AfxMessageBox("�ø��ʽ������,�޷�ɾ��!");
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


	//ɾ�����ʽ
	sSql.Format("DELETE FROM %s WHERE Method = '%s'",tableName,Method);
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
	LoadMethods();
}

void CMethodSettingsDlg::OnClickListMethod(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//ѡ��һ����¼
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
