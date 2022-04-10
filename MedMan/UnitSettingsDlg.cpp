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
	
	//1.��ʼ����ͷ
	m_ctrlListUnit.InsertColumn(0,_T("������λ"),LVCFMT_LEFT,100,-1);
	m_ctrlListUnit.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	//2.���µ�λ�б�
	LoadUnits();	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUnitSettingsDlg::LoadUnits()
{
	//1.����б�
	m_ctrlListUnit.DeleteAllItems();

	m_nUnitSelect=-1;

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
	tableName="Unit";

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

void CUnitSettingsDlg::OnAddUnit() 
{
	UpdateData();

	if(m_strUnit=="")
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
	tableName="Unit";

	//���������λ�Ƿ��Ѿ�����
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Unit = '%s'",tableName,m_strUnit);
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
	sSql.Format("INSERT INTO %s (Unit) VALUES ('%s')",tableName,m_strUnit);
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
	LoadUnits();
}

void CUnitSettingsDlg::OnDeleteUnit() 
{
	if(m_nUnitTotal==1)
	{
		AfxMessageBox("ֻ��һ��������λ,����ɾ��!");
		return;
	}

	if(m_nUnitSelect==-1)
	{
		AfxMessageBox("��δѡ����Ҫɾ���ļ�����λ!");
		return;
	}

	if(AfxMessageBox("ȷʵҪɾ���ü�����λ��?",MB_YESNO)==IDNO)
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
	tableName="Unit";

	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Unit = '%s'",tableName,Unit);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		//������λ������,�޷�ɾ��
		AfxMessageBox("�ü�����λ������,�޷�ɾ��!");
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
	sSql.Format("DELETE FROM %s WHERE Unit = '%s'",tableName,Unit);
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
	LoadUnits();
}

void CUnitSettingsDlg::OnClickListUnit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//ѡ��һ����¼
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
