// SectionSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MedMan.h"
#include "SectionSettingsDlg.h"

#include "AddSectionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSectionSettingsDlg dialog


CSectionSettingsDlg::CSectionSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSectionSettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSectionSettingsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSectionSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSectionSettingsDlg)
	DDX_Control(pDX, IDC_LIST_SECTION, m_ctrlListSection);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSectionSettingsDlg, CDialog)
	//{{AFX_MSG_MAP(CSectionSettingsDlg)
	ON_BN_CLICKED(IDC_ADD_SECTION, OnAddSection)
	ON_BN_CLICKED(IDC_DELETE_SECTION, OnDeleteSection)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SECTION, OnClickListSection)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSectionSettingsDlg message handlers

BOOL CSectionSettingsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//1.��ʼ����ͷ
	m_ctrlListSection.InsertColumn(0,_T("��λ����"),LVCFMT_LEFT,100,-1);
	m_ctrlListSection.InsertColumn(1,_T("����״��"),LVCFMT_LEFT,100,-1);
	m_ctrlListSection.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	//2.���µ�λ�б�
	LoadSections();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSectionSettingsDlg::LoadSections()
{
	//1.����б�
	m_ctrlListSection.DeleteAllItems();

	m_nSectionSelect=-1;

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
	tableName="Section";

	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s ORDER BY I_O",tableName);
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


	m_nSectionTotal=0;
	recordset.MoveFirst();
	while(!recordset.IsEOF())
	{
		recordset.GetFieldValue((short)0,Temp);
		m_ctrlListSection.InsertItem(m_nSectionTotal,Temp,-1);
		recordset.GetFieldValue((short)1,Temp);
		if(atoi(Temp.GetBuffer(0))==0)
		{
			Temp="��������";
		}
		else
		{
			Temp="��������";
		}
		m_ctrlListSection.SetItemText(m_nSectionTotal,1,Temp);
				
		recordset.MoveNext();
		m_nSectionTotal++;
	}

	m_nSectionTotal=recordset.GetRecordCount();

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

void CSectionSettingsDlg::OnAddSection() 
{
	CAddSectionDlg Dialog1;

	CString SectionName;
	int In_or_out;

	BOOL Accepted=FALSE;

	while(!Accepted)
	{
		if(Dialog1.DoModal()==IDOK)
		{
			if(Dialog1.m_strSectionName=="")
			{
				AfxMessageBox("������λ���Ʋ���Ϊ��!");
				continue;
			}
			if(Dialog1.In_or_out==-1)
			{
				AfxMessageBox("��δѡ���ǽ������ǳ�����λ!");
				continue;
			}

			SectionName=Dialog1.m_strSectionName;
			In_or_out=Dialog1.In_or_out;
			Accepted=TRUE;
			break;
		}
		else
		{
			return;
		}
	}

	//��������λ
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
	tableName="Section";

	//���������λ�Ƿ��Ѿ�����
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Section_name = '%s'",tableName,SectionName);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		//��λ������,�������
	}
	else
	{
		AfxMessageBox("�õ�λ�Ѿ�����,�����ظ����!");
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


	//����λ��ӵ����
	sSql.Format("INSERT INTO %s (Section_name, I_O) VALUES ('%s', %d)",tableName,SectionName,In_or_out);
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
	LoadSections();
	
}

void CSectionSettingsDlg::OnDeleteSection() 
{
	if(m_nSectionTotal==1)
	{
		AfxMessageBox("ֻ��һ����λ,����ɾ��!");
		return;
	}

	if(m_nSectionSelect==-1)
	{
		AfxMessageBox("��δѡ����Ҫɾ���ĵ�λ!");
		return;
	}

	if(AfxMessageBox("ȷʵҪɾ���õ�λ��?",MB_YESNO)==IDNO)
	{
		return;
	}

	CString SectionName;
	SectionName=m_ctrlListSection.GetItemText(m_nSectionSelect,0);

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
	tableName="Section";

	//��������ʻ��Ƿ��Ѿ�����
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Section_name = '%s'",tableName,SectionName);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		//��λ������,�޷�ɾ��
		AfxMessageBox("�õ�λ������,�޷�ɾ��!");
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


	//ɾ����λ
	sSql.Format("DELETE FROM %s WHERE Section_name = '%s'",tableName,SectionName);
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
	LoadSections();
}

void CSectionSettingsDlg::OnClickListSection(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//ѡ��һ����¼
	if(m_ctrlListSection.GetSelectionMark()!=-1)
	{
		m_nSectionSelect=m_ctrlListSection.GetSelectionMark();
	}
	else
	{
		m_nSectionSelect=-1;
	}
	
	*pResult = 0;
}
