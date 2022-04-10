// MedicineIORecordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MedMan.h"
#include "MedicineIORecordDlg.h"

#include "IOMedicineDlg.h"
#include "DateSelectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMedicineIORecordDlg dialog


CMedicineIORecordDlg::CMedicineIORecordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMedicineIORecordDlg::IDD, pParent)
{
	m_strName="";
	m_strStandard="";
	m_strManufactory="";
	m_strUnit="";
	m_strOperator="";
	//{{AFX_DATA_INIT(CMedicineIORecordDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMedicineIORecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMedicineIORecordDlg)
	DDX_Control(pDX, IDC_LIST_RECORD, m_ctrlRecordList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMedicineIORecordDlg, CDialog)
	//{{AFX_MSG_MAP(CMedicineIORecordDlg)
	ON_NOTIFY(NM_CLICK, IDC_LIST_RECORD, OnClickListRecord)
	ON_BN_CLICKED(IDC_MODIFY_RECORD, OnModifyRecord)
	ON_BN_CLICKED(IDC_INSERT_RECORD, OnInsertRecord)
	ON_BN_CLICKED(IDC_DELETE_RECORD, OnDeleteRecord)
	ON_BN_CLICKED(IDC_IO_MEDICINE, OnIoMedicine)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMedicineIORecordDlg message handlers

BOOL CMedicineIORecordDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//1.������Ʒ��Ϣ
	SetDlgItemText(IDC_EDIT_NAME,m_strName);
	SetDlgItemText(IDC_EDIT_STANDARD,m_strStandard);
	SetDlgItemText(IDC_EDIT_MANUFACTORY,m_strManufactory);
	SetDlgItemText(IDC_EDIT_UNIT,m_strUnit);

	//2.��ʼ�����(��ͷ��ʾ)
	m_ctrlRecordList.InsertColumn(0,_T("�� ��"),LVCFMT_LEFT,100,-1);
	m_ctrlRecordList.InsertColumn(1,_T("�� ��"),LVCFMT_LEFT,80,-1);
	m_ctrlRecordList.InsertColumn(2,_T("������λ"),LVCFMT_LEFT,80,-1);
	m_ctrlRecordList.InsertColumn(3,_T("���ʽ"),LVCFMT_LEFT,80,-1);
	m_ctrlRecordList.InsertColumn(4,_T("��������"),LVCFMT_LEFT,80,-1);
	m_ctrlRecordList.InsertColumn(5,_T("��������"),LVCFMT_LEFT,80,-1);
	m_ctrlRecordList.InsertColumn(6,_T("������"),LVCFMT_LEFT,80,-1);
	m_ctrlRecordList.InsertColumn(7,_T("�� ��"),LVCFMT_LEFT,80,-1);
	m_ctrlRecordList.InsertColumn(8,_T("�� ��"),LVCFMT_LEFT,80,-1);
	m_ctrlRecordList.InsertColumn(9,_T("����Ա"),LVCFMT_LEFT,80,-1);
	m_ctrlRecordList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	//3.��ʾ�б�
	ViewMedicineIORecord();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMedicineIORecordDlg::ViewMedicineIORecord()
{
	//1.����б�
	m_ctrlRecordList.DeleteAllItems();

	m_nRecordSelect=-1;

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
	tableName="RecordList";

	//����������Ʒ�Ľ�����¼
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Name = '%s' AND Standard = '%s' ORDER BY Date_time",tableName,m_strName,m_strStandard);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		AfxMessageBox("������Ʒû�н�����¼!");
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

	//��������¼��ӵ����
	m_nRecordTotal=0;
	recordset.MoveFirst();
	while(!recordset.IsEOF())
	{
		//���һ����¼���б�
		recordset.GetFieldValue((short)0,Temp);
		m_ctrlRecordList.InsertItem(m_nRecordTotal,Temp,-1);
		recordset.GetFieldValue((short)3,Temp);
		m_ctrlRecordList.SetItemText(m_nRecordTotal,1,Temp);
		recordset.GetFieldValue((short)4,Temp);
		m_ctrlRecordList.SetItemText(m_nRecordTotal,2,Temp);
		recordset.GetFieldValue((short)5,Temp);
		m_ctrlRecordList.SetItemText(m_nRecordTotal,3,Temp);
		recordset.GetFieldValue((short)8,Temp);
		m_ctrlRecordList.SetItemText(m_nRecordTotal,4,Temp);
		recordset.GetFieldValue((short)9,Temp);
		m_ctrlRecordList.SetItemText(m_nRecordTotal,5,Temp);
		recordset.GetFieldValue((short)6,Temp);
		m_ctrlRecordList.SetItemText(m_nRecordTotal,6,Temp);
		recordset.GetFieldValue((short)10,Temp);
		m_ctrlRecordList.SetItemText(m_nRecordTotal,7,Temp);
		recordset.GetFieldValue((short)11,Temp);
		m_ctrlRecordList.SetItemText(m_nRecordTotal,8,Temp);
		recordset.GetFieldValue((short)13,Temp);
		m_ctrlRecordList.SetItemText(m_nRecordTotal,9,Temp);
		
		recordset.MoveNext();
		m_nRecordTotal++;
	}

	m_nRecordTotal=recordset.GetRecordCount();
	Temp.Format("%d",m_nRecordTotal);
	SetDlgItemText(IDC_EDIT_RECORDTOTAL,Temp);

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
void CMedicineIORecordDlg::OnClickListRecord(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//ѡ��һ����¼
	if(m_ctrlRecordList.GetSelectionMark()!=-1)
	{
		m_nRecordSelect=m_ctrlRecordList.GetSelectionMark();
	}
	else
	{
		m_nRecordSelect=-1;
	}
	
	*pResult = 0;
}

void CMedicineIORecordDlg::OnModifyRecord() 
{
	if(m_nRecordSelect==-1)
	{
		AfxMessageBox("��δѡ����Ҫ�޸ĵļ�¼!");
		return;
	}
	//1.��ȡ��Ҫ�޸ĵļ�¼����Ϣ,ֻ��ȡʱ�������,��� ������������д����Ϊ��ԭ�����ݷ���ȥ�����岻��
	CString Date_time;
	CString BatchNumber(_T(""));
	CString Section(_T(""));
	CString Method(_T(""));
	float Amount,OldAmount; //���Amount�����ı�,��Ҫ�ı�������м�¼
	float In_price;
	float Out_price;
	float Remaining,OldRemaining;
	int In_or_out,OldIn_or_out; //���In_or_out�����ı�,��Ҫ�ı�������м�¼

	CString Temp;
	
	Date_time=m_ctrlRecordList.GetItemText(m_nRecordSelect,0);
	BatchNumber=m_ctrlRecordList.GetItemText(m_nRecordSelect,1);
	Section=m_ctrlRecordList.GetItemText(m_nRecordSelect,2);
	Method=m_ctrlRecordList.GetItemText(m_nRecordSelect,3);
	In_price=atof(m_ctrlRecordList.GetItemText(m_nRecordSelect,4).GetBuffer(0));
	Out_price=atof(m_ctrlRecordList.GetItemText(m_nRecordSelect,5).GetBuffer(0));
	OldAmount=Amount=atof(m_ctrlRecordList.GetItemText(m_nRecordSelect,6).GetBuffer(0));
	Remaining=atof(m_ctrlRecordList.GetItemText(m_nRecordSelect,7).GetBuffer(0));

	//ʹ�ý����ĶԻ���������д
	CIOMedicineDlg Dialog1;
	Dialog1.m_strName=m_strName;
	Dialog1.m_strStandard=m_strStandard;
	Dialog1.m_strBatchNumber=BatchNumber;
	Dialog1.m_strManufactory=m_strManufactory;
	Dialog1.m_fInPrice=In_price;
	Dialog1.m_fOutPrice=Out_price;

	BOOL Accepted=FALSE;

	while(!Accepted)
	{
		if(Dialog1.DoModal()==IDOK)
		{
			if(Dialog1.m_fAmount==0.0)
			{
				AfxMessageBox("����������Ϊ��!");
				continue;
			}
			if(Dialog1.m_fInPrice==0.0||Dialog1.m_fOutPrice==0.0)
			{
				AfxMessageBox("���۲���Ϊ��!");
				continue;
			}
			if(Dialog1.m_strSection=="")
			{
				AfxMessageBox("��δѡ�������λ!");
				continue;
			}
			if(Dialog1.m_nIO==0&&Dialog1.m_strMethod=="")
			{
				AfxMessageBox("��δѡ�񸶿ʽ!");
				continue;
			}
			//ȡ����ȷ����
			Section=Dialog1.m_strSection;
			BatchNumber=Dialog1.m_strBatchNumber;
			In_price=Dialog1.m_fInPrice;
			Out_price=Dialog1.m_fOutPrice;
			Amount=Dialog1.m_fAmount;
			In_or_out=Dialog1.m_nIO;
			if(In_or_out==0)
			{
				Method=Dialog1.m_strMethod;
			}
			else
			{
				Method="";
			}

			Accepted=TRUE;
			break;
		}
		else
		{
			return;
		}
	}
	
	//2.�����ݿ�����޸�
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
	tableName="RecordList";

	//��������������¼
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Date_time = '%s' AND Name = '%s' AND Standard = '%s' ORDER BY Date_time",tableName,Date_time,m_strName,m_strStandard);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		AfxMessageBox("û������������¼!"); //�������������
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
	
	//������״���Ƿ�ı�,�����,������ı����,���ݴ˸��º������м�¼�Լ���Ʒ�б�
	float Changing=0.0;  //�ı���
	recordset.GetFieldValue(short(12),Temp);
	OldIn_or_out=atoi(Temp.GetBuffer(0));
	recordset.GetFieldValue(short(10),Temp);
	OldRemaining=atoi(Temp.GetBuffer(0));

	if(OldIn_or_out==In_or_out)
	{
		if(In_or_out==0) //����
		{
			Changing=Amount-OldAmount;
		}
		else
		{
			Changing=OldAmount-Amount;
		}
	}
	else
	{
		if(In_or_out==0) //���������
		{
			Changing=Amount+OldAmount;
		}
		else
		{
			Changing=-(Amount+OldAmount);
		}
	}	

	//�޸ļ�¼
	sSql.Format("UPDATE %s SET Batch_number = '%s', Section = '%s', Method = '%s', Amount = %.2f, In_price = %.2f, Out_price = %.2f, Remaining = %.2f, Sum = %.2f, In_or_out = %d, Operator = '%s' WHERE Date_time = '%s' AND Name ='%s' AND Standard = '%s'",tableName,BatchNumber,Section,Method,Amount,In_price,Out_price,OldRemaining+Changing,In_price*(OldRemaining+Changing),In_or_out,m_strOperator,Date_time,m_strName,m_strStandard);

	database.ExecuteSQL(sSql);

	if(Changing==0.0)
	{
		//ʹ����������ݿ�֮��,�ر����ݿ��Լ���¼��
		if(recordset.IsOpen())
		{
			recordset.Close();
		}
		if(database.IsOpen())
		{
			database.Close();
		}
		//ˢ�»�������
		ViewMedicineIORecord();
		return;
	}

	//�ı�����Ϊ0,��Ҫ�޸ĺ������м�¼,ֻ���޸�����,����Changing
	int i;
	for(i=m_nRecordSelect+1;i<m_ctrlRecordList.GetItemCount();i++)
	{
		Date_time=m_ctrlRecordList.GetItemText(i,0);
		Remaining=atof(m_ctrlRecordList.GetItemText(i,7).GetBuffer(0));
		In_price=atof(m_ctrlRecordList.GetItemText(i,4).GetBuffer(0));
		
		sSql.Format("UPDATE %s SET Remaining = %.2f, Sum = %.2f WHERE Date_time = '%s' AND Name = '%s' AND Standard = '%s'",tableName,(Remaining+Changing),In_price*(Remaining+Changing),Date_time,m_strName,m_strStandard);
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

	//3.�޸���Ʒ�б�
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

	//���������Ʒ
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Name = '%s' AND Standard = '%s'",tableName,m_strName,m_strStandard);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		AfxMessageBox("û�����ּ�¼!"); //�������������
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

	//��ȡ�����Լ�����
	recordset.GetFieldValue(4,Temp);
	Out_price=atof(Temp.GetBuffer(0));
	recordset.GetFieldValue(5,Temp);
	Amount=atof(Temp.GetBuffer(0));

	//�޸������Լ�����ϴεĵ���
	sSql.Format("UPDATE %s SET Amount = %.2f, Sum = %.2f WHERE Name = '%s' AND Standard ='%s'",tableName,Amount+Changing,In_price*(Amount+Changing),m_strName,m_strStandard);
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

	//ˢ�»�������
	ViewMedicineIORecord();

}

void CMedicineIORecordDlg::OnInsertRecord() 
{
	CString Date_timeInsert("");
	CString Temp("");
	CString Time1("");
	CString Time2("");
	int StartNumber=0;

	//������¼,�����Լ����������������ݿ��в�����ǰ���ǵ���ļ�¼

	//1.��ȡ��Ҫ�����ļ�¼������
	//�õ�ϵͳʱ��
	CTime now=CTime::GetCurrentTime();
	Temp=now.Format(_T("��ǰʱ��: %Y��%m��%d�� %H:%M:%S"));
	CDateSelectDlg Dialog1;
	Dialog1.m_tDateTime=now;
	if(Dialog1.DoModal()==IDOK)
	{
		Time1=Dialog1.m_tDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));
	}
	else
	{
		return;
	}

	//2.�õ�����ʱ��֮��,�Ա��Ѿ��г��ļ�¼��������Ҫ�޸ĵļ�¼�Ŀ�ʼ����
	//ʹ�ú���CompareDateTime���Ƚ�ʱ��,����TRUE,��ʾǰ�ߴ��ں���
	if(Time1==Time2) //ʱ��պ����,�򷵻�,�����������ļ�¼(���ٳ���)
	{
		return;
	}
	int i;
	for(i=0;i<m_ctrlRecordList.GetItemCount();i++)
	{
		Time2=m_ctrlRecordList.GetItemText(i,0);
		if(CompareDateTime(Time2,Time1))
		{
			//�Ƚϵ���һ���������ڴ��ڼ�¼���ڵļ�¼
			//�������¼��ʼ�޸�
			break;
		}
	}
	StartNumber=i;
	//�������������ǰ
	if(StartNumber==0)
	{
		AfxMessageBox("���ܲ嵽������¼֮ǰ!");
		return;
	}

	//�б��д�StartNumber��ʼ�ļ�¼��Ҫˢ��
	//ͨ��������Ʒ�Ի�����������¼����Ϣ
	//����ʱ���Ѿ����,ΪTime1
	//���ơ����ͼ�����λҲ�Ѿ�ȡ�� m_strName,m_strStandard,m_strUnit
	//�����۸�Ĭ��ȡStartNumberǰһ��
	//��������StartNumberǰһ��������
	CString Date_time;
	CString Name;
	CString Standard;
	CString Manufactory;
	CString Method;
	CString Unit;
	CString BatchNumber;
	CString Section;
	float Amount,In_price,Out_price,Remaining,RemainingLast;
	int In_or_out;

	//��ȡ�Ѿ��е���ֵ
	Date_time=Time1;
	Name=m_strName;
	Standard=m_strStandard;
	Manufactory=m_strManufactory;
	Unit=m_strUnit;

	i=StartNumber-1;
	BatchNumber=m_ctrlRecordList.GetItemText(i,1);
	In_price=atof(m_ctrlRecordList.GetItemText(i,4).GetBuffer(0));
	Out_price=atof(m_ctrlRecordList.GetItemText(i,5).GetBuffer(0));
	RemainingLast=atof(m_ctrlRecordList.GetItemText(i,7).GetBuffer(0));

	CIOMedicineDlg Dialog2;
	Dialog2.m_strName=Name;
	Dialog2.m_strStandard=Standard;
	Dialog2.m_strManufactory=Manufactory;
	Dialog2.m_strBatchNumber=BatchNumber;
	Dialog2.m_fInPrice=In_price;
	Dialog2.m_fOutPrice=Out_price;

	BOOL Accepted=FALSE;

	while(!Accepted)
	{
		if(Dialog2.DoModal()==IDOK)
		{
			if(Dialog2.m_fAmount==0.0)
			{
				AfxMessageBox("����������Ϊ��!");
				continue;
			}
			if(Dialog2.m_fInPrice==0.0||Dialog2.m_fOutPrice==0.0)
			{
				AfxMessageBox("���۲���Ϊ��!");
				continue;
			}
			if(Dialog2.m_strSection=="")
			{
				AfxMessageBox("��δѡ�������λ!");
				continue;
			}
			if(Dialog2.m_nIO==0&&Dialog2.m_strMethod=="")
			{
				AfxMessageBox("��δѡ�񸶿ʽ!");
				continue;
			}
			//ȡ����ȷ����
			Section=Dialog2.m_strSection;
			BatchNumber=Dialog2.m_strBatchNumber;
			In_price=Dialog2.m_fInPrice;
			Out_price=Dialog2.m_fOutPrice;
			Amount=Dialog2.m_fAmount;
			In_or_out=Dialog2.m_nIO;
			if(In_or_out==0)
			{
				Method=Dialog2.m_strMethod;
			}
			else
			{
				Method="";
			}

			Accepted=TRUE;
			break;
		}
		else
		{
			return;
		}
	}

	//3.�Ѿ���øĶ�����ֵ,�޸ļ�¼���ݿ�
	float Changing;
	if(In_or_out==0)
	{
		Remaining=RemainingLast+Amount;
		Changing=Amount;
	}
	else
	{
		Remaining=RemainingLast-Amount;
		Changing=-Amount;
	}
	
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
	tableName="RecordList";

	//����������Ʒ�Ľ�����¼
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Name = '%s' AND Standard = '%s' ORDER BY Date_time",tableName,m_strName,m_strStandard);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		AfxMessageBox("û��������Ʒ�Ľ�����¼!"); //�������������
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

	sSql.Format("INSERT INTO %s (Date_time,Name,Standard,Batch_number,Section,Method,Amount,Unit,In_price,Out_price,Remaining,Sum,In_or_out,Operator ) VALUES ('%s','%s','%s','%s','%s','%s',%.2f,'%s',%.2f,%.2f,%.2f,%.2f,%d,'%s' )",tableName,Date_time,Name,Standard,BatchNumber,Section,Method,Amount,Unit,In_price,Out_price,Remaining,In_price*Remaining,In_or_out,m_strOperator);
	database.ExecuteSQL(sSql);

	//��StartNumber��ʼ,�޸ĺ������м�¼�������ͽ��
	for(i=StartNumber;i<m_ctrlRecordList.GetItemCount();i++)
	{
		Date_time=m_ctrlRecordList.GetItemText(i,0);
		Remaining=atof(m_ctrlRecordList.GetItemText(i,7).GetBuffer(0));
		In_price=atof(m_ctrlRecordList.GetItemText(i,4).GetBuffer(0));
		
		sSql.Format("UPDATE %s SET Remaining = %.2f, Sum = %.2f WHERE Date_time = '%s' AND Name = '%s' AND Standard = '%s'",tableName,(Remaining+Changing),In_price*(Remaining+Changing),Date_time,m_strName,m_strStandard);
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

	//3.�޸���Ʒ�б�
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

	//���������Ʒ
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Name = '%s' AND Standard = '%s'",tableName,m_strName,m_strStandard);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		AfxMessageBox("û�����ּ�¼!"); //�������������
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

	//��ȡ�����Լ�����
	recordset.GetFieldValue(3,Temp);
	In_price=atof(Temp.GetBuffer(0));
	recordset.GetFieldValue(5,Temp);
	Amount=atof(Temp.GetBuffer(0));

	//�޸������Լ�����ϴεĵ���
	sSql.Format("UPDATE %s SET Amount = %.2f, Sum = %.2f WHERE Name = '%s' AND Standard ='%s'",tableName,Amount+Changing,In_price*(Amount+Changing),m_strName,m_strStandard);
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

	//ˢ�»�������
	ViewMedicineIORecord();

}

BOOL CMedicineIORecordDlg::CompareDateTime(CString Time1,CString Time2)
{
	int year1,month1,day1,hour1,minute1,second1;
	int year2,month2,day2,hour2,minute2,second2;
	
	//1.�Ƚ����
	year1=atoi(Time1.Mid(0,4).GetBuffer(0));
	year2=atoi(Time2.Mid(0,4).GetBuffer(0));
	if(year1>year2)
	{
		return TRUE;
	}
	if(year1<year2)
	{
		return FALSE;
	}

	//2.�Ƚ��·�
	month1=atoi(Time1.Mid(5,2).GetBuffer(0));
	month2=atoi(Time2.Mid(5,2).GetBuffer(0));
	if(month1>month2)
	{
		return TRUE;
	}
	if(month1<month2)
	{
		return FALSE;
	}

	//3.�Ƚ�����
	day1=atoi(Time1.Mid(8,2).GetBuffer(0));
	day2=atoi(Time2.Mid(8,2).GetBuffer(0));
	if(day1>day2)
	{
		return TRUE;
	}
	if(day1<day2)
	{
		return FALSE;
	}

	//4.�Ƚ�Сʱ
	hour1=atoi(Time1.Mid(11,2).GetBuffer(0));
	hour2=atoi(Time2.Mid(11,2).GetBuffer(0));
	if(hour1>hour2)
	{
		return TRUE;
	}
	if(hour1<hour2)
	{
		return FALSE;
	}

	//5.�ȽϷ���
	minute1=atoi(Time1.Mid(14,2).GetBuffer(0));
	minute2=atoi(Time2.Mid(14,2).GetBuffer(0));
	if(minute1>minute2)
	{
		return TRUE;
	}
	if(minute1<minute2)
	{
		return FALSE;
	}

	//6.�Ƚ���
	second1=atoi(Time1.Mid(17,2).GetBuffer(0));
	second2=atoi(Time2.Mid(17,2).GetBuffer(0));
	if(second1>second2)
	{
		return TRUE;
	}
	if(second1<second2)
	{
		return FALSE;
	}

	//ȫ�����,Ҳ����FALSE,�ڼ�¼�������
	return FALSE;
}
void CMedicineIORecordDlg::OnDeleteRecord() 
{
	if(m_nRecordTotal==1)
	{
		AfxMessageBox("ֻ��һ����¼,����ɾ��!");
		return;
	}

	if(m_nRecordSelect==-1)
	{
		AfxMessageBox("��δѡ����Ҫ�޸ĵļ�¼!");
		return;
	}

	//ɾ��֮ǰ����һ��ȷ��
	if(AfxMessageBox("��ȷ��Ҫɾ��������¼��",MB_YESNO)==IDNO)
	{
		return;
	}

	//1.��ȡ��Ҫɾ���ļ�¼����Ϣ,��ȡʱ�������,���,�Լ���εĽ�����,�ݴ��޸ĸ��б�������к�����¼
	CString Date_time;
	CString BatchNumber(_T(""));
	CString Section(_T(""));
	CString Method(_T(""));
	float Amount; 
	float In_price;
	float Out_price;
	float Remaining;
	int In_or_out;

	CString Temp;
	
	Date_time=m_ctrlRecordList.GetItemText(m_nRecordSelect,0);
	BatchNumber=m_ctrlRecordList.GetItemText(m_nRecordSelect,1);
	Section=m_ctrlRecordList.GetItemText(m_nRecordSelect,2);
	Method=m_ctrlRecordList.GetItemText(m_nRecordSelect,3);
	In_price=atof(m_ctrlRecordList.GetItemText(m_nRecordSelect,4).GetBuffer(0));
	Out_price=atof(m_ctrlRecordList.GetItemText(m_nRecordSelect,5).GetBuffer(0));
	Amount=atof(m_ctrlRecordList.GetItemText(m_nRecordSelect,6).GetBuffer(0));
	Remaining=atof(m_ctrlRecordList.GetItemText(m_nRecordSelect,7).GetBuffer(0));
		
	//2.�����ݿ�����޸�
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
	tableName="RecordList";

	//��������������¼
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Date_time = '%s' AND Name = '%s' AND Standard = '%s' ORDER BY Date_time",tableName,Date_time,m_strName,m_strStandard);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		AfxMessageBox("û������������¼!"); //�������������
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
	
	//������ı����,���ݴ˸��º������м�¼�Լ���Ʒ�б�
	float Changing=0.0;  //�ı���
	recordset.GetFieldValue(short(12),Temp);
	In_or_out=atoi(Temp.GetBuffer(0));

	if(In_or_out==0) //ɾ��������¼
	{
		Changing=-Amount;
	}
	else
	{
		Changing=Amount;
	}		

	//ɾ����¼
	sSql.Format("DELETE FROM %s WHERE Date_time = '%s' AND Name ='%s' AND Standard = '%s'",tableName,Date_time,m_strName,m_strStandard);
	database.ExecuteSQL(sSql);
	
	//�޸ĺ������м�¼,ֻ���޸�����,����Changing
	int i;
	for(i=m_nRecordSelect+1;i<m_ctrlRecordList.GetItemCount();i++)
	{
		Date_time=m_ctrlRecordList.GetItemText(i,0);
		Remaining=atof(m_ctrlRecordList.GetItemText(i,7).GetBuffer(0));
		In_price=atof(m_ctrlRecordList.GetItemText(i,4).GetBuffer(0));
		
		sSql.Format("UPDATE %s SET Remaining = %.2f, Sum = %.2f WHERE Date_time = '%s' AND Name = '%s' AND Standard = '%s'",tableName,(Remaining+Changing),In_price*(Remaining+Changing),Date_time,m_strName,m_strStandard);
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

	//3.�޸���Ʒ�б�
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

	//���������Ʒ
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Name = '%s' AND Standard = '%s'",tableName,m_strName,m_strStandard);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		AfxMessageBox("û�����ּ�¼!"); //�������������
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

	//��ȡ�����Լ�����
	recordset.GetFieldValue(3,Temp);
	In_price=atof(Temp.GetBuffer(0));
	recordset.GetFieldValue(5,Temp);
	Amount=atof(Temp.GetBuffer(0));

	//�޸������Լ�����ϴεĵ���
	sSql.Format("UPDATE %s SET Amount = %.2f, Sum = %.2f WHERE Name = '%s' AND Standard ='%s'",tableName,Amount+Changing,In_price*(Amount+Changing),m_strName,m_strStandard);
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

	//ˢ�»�������
	ViewMedicineIORecord();
}

void CMedicineIORecordDlg::OnIoMedicine() 
{
	//1.�����Ѿ������ƺ͹����Ϣ
	CString Name("");
	CString Standard("");
	CString Manufactory("");
	CString Unit("");

	float Amount=0.0;
	float Remaining=0.0;
	int IO=0;

	Name=m_strName;
	Standard=m_strStandard;
	Manufactory=m_strManufactory;
	Unit=m_strUnit;

	//2.���н�������
	if(Name=="")
	{
		AfxMessageBox("��δѡ����Ʒ!");
		return;
	}

	CIOMedicineDlg Dialog2;
	
	Dialog2.m_strName=Name;
	Dialog2.m_strStandard=Standard;
	Dialog2.m_strManufactory=Manufactory;
	Dialog2.m_strUnit=Unit;
	CString Section(_T(""));
	CString Method(_T(""));
	CString BatchNumber(_T(""));
	CString Temp;
	float InPrice=0.0;
	float OutPrice=0.0;

	//������һ�μ�¼����Ϣ�Ա���ν��м���
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
	CATCH(CDBException,e)
	{
		//�������Ϊe->m_nRetCode
	}
	END_CATCH
	recordset.m_pDatabase=&database;
	tableName="RecordList";
	//���Ҹ���Ʒ�Ѿ����ڵļ�¼
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Name = '%s' AND Standard = '%s' ORDER BY Date_time",tableName,Name,Standard);
	recordset.Open(CRecordset::dynaset,sSql);
	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		//����Ʒû�м�¼,��ȡֵ��Ϊ0���߿�		
	}
	else
	{
		//����Ʒ���м�¼,�������һ������ȡֵ
		recordset.MoveLast();
		recordset.GetFieldValue((short)3,BatchNumber); //�õ�����
		recordset.GetFieldValue((short)8,Temp);
		InPrice=atof(Temp.GetBuffer(0)); //�õ�����
		recordset.GetFieldValue((short)9,Temp);
		OutPrice=atof(Temp.GetBuffer(0)); //�õ�����
		recordset.GetFieldValue((short)10,Temp);
		Remaining=atof(Temp.GetBuffer(0)); //�õ�����
	}


	//Ĭ�ϵ����źͽ����۸������һ�μ�¼��ͬ
	Dialog2.m_strBatchNumber=BatchNumber;
	Dialog2.m_fInPrice=InPrice;
	Dialog2.m_fOutPrice=OutPrice;

	BOOL Accepted=FALSE;

	while(!Accepted)
	{
		if(Dialog2.DoModal()==IDOK)
		{
			IO=Dialog2.m_nIO;
			Section=Dialog2.m_strSection;
			BatchNumber=Dialog2.m_strBatchNumber;
			Amount=Dialog2.m_fAmount;
			InPrice=Dialog2.m_fInPrice;
			OutPrice=Dialog2.m_fOutPrice;
			if(Section=="")
			{
				AfxMessageBox("������λ����Ϊ��!");
				continue;
			}
			if(Amount==0.0)
			{
				AfxMessageBox("������������Ϊ��!");
				continue;
			}
			if(InPrice==0.0||OutPrice==0.0)
			{
				AfxMessageBox("���۲���Ϊ��!����������!");
				continue;
			}
			if(Dialog2.m_nIO==0&&Dialog2.m_strMethod=="")
			{
				AfxMessageBox("�������ʽ����Ϊ��!");
				continue;
			}
			Section=Dialog2.m_strSection;
			if(Dialog2.m_nIO==1) //����
			{
				Method="";
			}
			else
			{
				Method=Dialog2.m_strMethod;
			}
			Accepted=TRUE;
			break;
		}
		else
		{
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
	}

	//���ӽ�����¼
	if(IO==0) //����
	{
		Remaining+=Amount;
	}
	else
	{
		Remaining-=Amount;
	}

	//����������¼
	CTime now=CTime::GetCurrentTime();
	CString datetime;
	datetime=now.Format(_T("%Y-%m-%d %H:%M:%S"));
	sSql.Format("INSERT INTO %s (Date_time,Name,Standard,Batch_number,Section,Method,Amount,Unit,In_price,Out_price,Remaining,Sum,In_or_out,Operator ) VALUES ('%s','%s','%s','%s','%s','%s',%.2f,'%s',%.2f,%.2f,%.2f,%.2f,%d,'%s' )",tableName,datetime,Name,Standard,BatchNumber,Section,Method,Amount,Unit,InPrice,OutPrice,Remaining,InPrice*Remaining,IO,m_strOperator);
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

	//3.������Ʒ�б��4����Ϣ(����,����,����,���)
	//�����ݿ�
	TRY
	{
		sSql.Format("DSN=%s;;","Medicine");
		database.OpenEx(sSql,CDatabase::noOdbcDialog);		
	}
	CATCH(CDBException,e)
	{
		//�������Ϊe->m_nRetCode
	}
	END_CATCH
	recordset.m_pDatabase=&database;
	tableName="ItemList";
	//���Ҹ���Ʒ�Ѿ����ڵļ�¼
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Name = '%s' AND Standard = '%s' ",tableName,Name,Standard);
	recordset.Open(CRecordset::dynaset,sSql);
	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		//����Ʒû�м�¼,����һ����¼,�������ʵ�ʲ������		
	}
	//���¼�¼
	sSql.Format("UPDATE %s SET In_price = %.2f, Out_price = %.2f, Amount = %.2f, Sum= %.2f, Batch_number= '%s' WHERE Name = '%s' AND Standard = '%s' ",tableName,InPrice,OutPrice,Remaining,InPrice*Remaining,BatchNumber,Name,Standard);
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

	//ˢ�»�������
	ViewMedicineIORecord();
}
