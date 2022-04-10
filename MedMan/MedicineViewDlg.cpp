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
	
	//1.��ʼ�����(��ͷ��ʾ)
	m_ctrlListItem.InsertColumn(0,_T("��Ʒ����"),LVCFMT_LEFT,80,-1);
	m_ctrlListItem.InsertColumn(1,_T("�� ��"),LVCFMT_LEFT,80,-1);
	m_ctrlListItem.InsertColumn(2,_T("��������"),LVCFMT_LEFT,80,-1);
	m_ctrlListItem.InsertColumn(3,_T("������λ"),LVCFMT_LEFT,80,-1);
	m_ctrlListItem.InsertColumn(4,_T("��ǰ����"),LVCFMT_LEFT,80,-1);
	m_ctrlListItem.InsertColumn(5,_T("��С����"),LVCFMT_LEFT,80,-1);
	m_ctrlListItem.InsertColumn(6,_T("��������"),LVCFMT_LEFT,0,-1);
	m_ctrlListItem.InsertColumn(7,_T("��������"),LVCFMT_LEFT,80,-1);
	m_ctrlListItem.InsertColumn(8,_T("�� ��"),LVCFMT_LEFT,80,-1);
	m_ctrlListItem.InsertColumn(9,_T("�� ��"),LVCFMT_LEFT,80,-1);
	m_ctrlListItem.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);	

	//2.������Ʒ
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
	//1.��ȡ��ǰ��Ʒ���б�
	CItemSet m_Set;
	m_Set.Open(CRecordset::dynaset,"SELECT * FROM ItemList ORDER BY Abbreviation");
	m_nTotalItems=0;
	m_nCurrentSelect=0;
	CString Temp(_T(""));
	if(m_Set.IsEOF())
	{
		AfxMessageBox("���ݿ�����δ������Ʒ��");
	}
	else
	{
		m_Set.MoveFirst();
		m_ctrlListItem.DeleteAllItems();
		
		while(!m_Set.IsEOF())
		{
			//���һ����Ʒ���б�
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

	//2.������Ʒ�����Լ���ǰѡ������ʾ
	Temp.Format(_T("%d"),m_nTotalItems);
	SetDlgItemText(IDC_EDIT_TOTAL,Temp);
	Temp.Format(_T("%d"),m_nCurrentSelect);
	SetDlgItemText(IDC_EDIT_SELECT,Temp);
}

void CMedicineViewDlg::OnViewEdit() 
{
	//������Ʒ��Ϣ(������Ը��³���,������λ,��С�����Լ������۸���Ϣ,���޸ļ�¼��,ֻ�޸���Ʒ��,��ΪӰ�첻��)
	//��������Ϣ��׼���������

	//1.��ȡ��ǰ��ʾ����Ʒ��Ϣ(�����Լ����)
	if(m_nCurrentSelect==0)
	{
		AfxMessageBox("����δѡ����Ʒ");
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

	//2.���и��ĶԻ������
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
				AfxMessageBox("��λ����Ϊ��!");
				continue;
			}
			InPrice=Dialog1.m_fInPrice;
			OutPrice=Dialog1.m_fOutPrice;
			BatchNumber=Dialog1.m_strBatchNumber;
			if(InPrice==0.0||OutPrice==0.0)
			{
				AfxMessageBox("���۲���Ϊ��!");
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

	//3.�Ѿ�ȡ����ȷ��Ϣ�������޸�
	CDatabase database;
	CRecordset recordset;
	CString tableName;
	CString sSql;
	
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
	tableName="ItemList";
	
	//���Ҹ���Ʒ�Ƿ��Ѿ�����
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Name = '%s' AND Standard = '%s' ",tableName,Name,Standard);
	
	recordset.Open(CRecordset::dynaset,sSql);
	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		//����Ʒ������,�޷�����,�������ʵ�ʲ������
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
	
	//����Ʒ����,������Ϣ
	sSql.Format("UPDATE %s SET Manufactory = '%s', Unit = '%s', In_price=%.2f, Out_price=%.2f, Minimum = %.2f, Sum = %.2f, Batch_number = '%s' WHERE Name = '%s' AND Standard = '%s'",tableName,Manufactory,Unit,InPrice,OutPrice,Minimum,Amount*InPrice,BatchNumber,Name,Standard);
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

	LoadItems();

}

void CMedicineViewDlg::OnViewAdd() 
{
	//������������Ʒ
	//��Ҫʹ�õľֲ�����
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

	//�ӶԻ���ȡ������
	BOOL Accepted=FALSE;

	while(!Accepted)
	{
		if(Dialog1.DoModal()==IDOK)
		{
			//��������
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
			//�������Ƿ���д�ϸ�
			if(m_strName==_T(""))
			{
				AfxMessageBox("���Ʋ���Ϊ��!");
				continue;
			}
			if(m_strUnit==_T(""))
			{
				AfxMessageBox("������λ����Ϊ��!");
				continue;
			}
			if(m_fInPrice==0.0||m_fOutPrice==0.0)
			{
				AfxMessageBox("���۲���Ϊ��!");
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

	//ȡ��ƴ����д
	CString Abbreviation("");
	CGetSpell PYSpell;
	Abbreviation=PYSpell.GetChineseSpell(m_strName);
	PYSpell.~CGetSpell();

	//ȡ����ȷ������,�������ݿ�
	//1.������Ʒ�б����ݿ�

	//�ж��Ƿ��Ѿ��ڿ���,�������ƺ͹�����ж�,���������	
	
	CDatabase database;
	CRecordset recordset;
	CString tableName;
	CString sSql;

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
	tableName="ItemList";

	//���Ҹ���Ʒ�Ƿ��Ѿ�����
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Name = '%s' AND Standard = '%s' ",tableName,m_strName,m_strStandard);
	recordset.Open(CRecordset::dynaset,sSql);
	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		//����Ʒ������,������������Ʒ
		sSql.Format("INSERT INTO %s (Name,Standard,Manufactory,In_price,Out_price,Amount,Minimum,Unit,Sum,Abbreviation ) VALUES ('%s','%s','%s',%.2f,%.2f,%.2f,%.2f,'%s',%.2f,'%s' )",tableName,m_strName,m_strStandard,m_strManufactory,m_fInPrice,m_fOutPrice,m_fNumber,m_fMinimum,m_strUnit,m_fSum,Abbreviation);
		database.ExecuteSQL(sSql);
	}
	else
	{
		//����Ʒ����,���˳�
		AfxMessageBox("����Ʒ�Ѿ�����,�����ظ����!");
		return;
	}
	//ʹ����������ݿ�֮��,�ر����ݿ��Լ���¼��
	if(recordset.IsOpen())
	{
		recordset.Close();
	}
    if(database.IsOpen())
	{
		database.Close();
	}

	//2.���¼�¼���ݿ�,����һ������"����"�Ľ�����¼
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
	tableName="RecordList";
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s ",tableName);
	recordset.Open(CRecordset::dynaset,sSql);
	//����������¼
	CTime now=CTime::GetCurrentTime();
	CString datetime;
	datetime=now.Format(_T("%Y-%m-%d %H:%M:%S"));
	sSql.Format("INSERT INTO %s (Date_time,Name,Standard,Batch_number,Section,Method,Amount,Unit,In_price,Out_price,Remaining,Sum,In_or_out,Operator ) VALUES ('%s','%s','%s','%s','����','����',%.2f,'%s',%.2f,%.2f,%.2f,%.2f,0,'%s' )",tableName,datetime,m_strName,m_strStandard,m_strBatchNumber,m_fNumber,m_strUnit,m_fInPrice,m_fOutPrice,m_fNumber,m_fInPrice*m_fNumber,m_strOperator);
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

	LoadItems();
}

void CMedicineViewDlg::OnViewDelete() 
{
	//1.��ȡ��ǰѡ�����Ʒ��Ϣ(�����Լ����)
	if(m_nCurrentSelect==0)
	{
		AfxMessageBox("����δѡ����Ʒ");
		return;
	}

	//2.ȷ��һ��ɾ������
	//ɾ��֮ǰ����һ��ȷ��
	if(AfxMessageBox("ɾ��֮�����Ʒ��Ӧ�Ľ�����¼Ҳ����ɾ����\n��ȷ��Ҫɾ��������Ʒ��",MB_YESNO)==IDNO)
	{
		return;
	}

	//3.ȡ�����ƺ͹����Ϣ������ɾ������
	CString Name("");
	CString Standard("");

	Name=m_ctrlListItem.GetItemText(m_nCurrentSelect-1,0);
	Standard=m_ctrlListItem.GetItemText(m_nCurrentSelect-1,1);

	CDatabase database;
	CRecordset recordset;
	CString tableName;
	CString sSql;

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
	tableName="ItemList";

	//���Ҹ���Ʒ�Ƿ��Ѿ�����
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Name = '%s' AND Standard = '%s' ",tableName,Name,Standard);
	recordset.Open(CRecordset::dynaset,sSql);
	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		//����Ʒ������,����(�������������)
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
		//����Ʒ����,��ɾ��
		sSql.Format("DELETE FROM %s WHERE Name = '%s' AND Standard = '%s'",tableName,Name,Standard);
		database.ExecuteSQL(sSql);		
	}
	//ʹ����������ݿ�֮��,�ر����ݿ��Լ���¼��
	if(recordset.IsOpen())
	{
		recordset.Close();
	}
    if(database.IsOpen())
	{
		database.Close();
	}

	//2.ɾ����¼���ݿ��ж�Ӧ�Ľ�����¼
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
	tableName="RecordList";
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Name = '%s' AND Standard = '%s' ",tableName,Name,Standard);
	recordset.Open(CRecordset::dynaset,sSql);
	
	//ɾ��������Ʒ�ļ�¼
	sSql.Format("DELETE FROM %s WHERE Name = '%s' AND Standard = '%s'",tableName,Name,Standard);
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

	LoadItems();
	
}

void CMedicineViewDlg::OnChangeEditName() 
{
	UpdateData();
	/*if(m_strName=="")
	{
		return;
	}*/
	
	//��ItemList���ݿ��в��ҷ���Ҫ��(Name=m_strName)����Ʒ
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
	tableName="ItemList";

	//���Ҹ���Ʒ�Ƿ��Ѿ�����
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Abbreviation LIKE '%%%s%%' ORDER BY Abbreviation",tableName,m_strName);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		AfxMessageBox("����Ʒ��δ��¼�����ݿ⣬�������Ӹ���Ʒ!");
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
		//���������Ʒ,�����б���ʾ
		m_ctrlListItem.DeleteAllItems();
		m_nTotalFind=0;

		recordset.MoveFirst();
		while(!recordset.IsEOF())
		{
			//���һ����Ʒ���б�
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
