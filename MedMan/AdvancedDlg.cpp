// AdvancedDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MedMan.h"
#include "AdvancedDlg.h"

#include "AccountSettingsDlg.h"
#include "SectionSettingsDlg.h"
#include "UnitSettingsDlg.h"
#include "MethodSettingsDlg.h"
#include "CheckDlg.h"
#include "ReadCheckDlg.h"

#include "ItemSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdvancedDlg dialog


CAdvancedDlg::CAdvancedDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAdvancedDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAdvancedDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_strOperator=_T("");
}


void CAdvancedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdvancedDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAdvancedDlg, CDialog)
	//{{AFX_MSG_MAP(CAdvancedDlg)
	ON_BN_CLICKED(IDC_ACCOUNT_SETTINGS, OnAccountSettings)
	ON_BN_CLICKED(IDC_SECTION_SETTINGS, OnSectionSettings)
	ON_BN_CLICKED(IDC_UNIT_SETTINGS, OnUnitSettings)
	ON_BN_CLICKED(IDC_METHOD_SEETINGS, OnMethodSeetings)
	ON_BN_CLICKED(IDC_ANNUNAL_CHECK, OnAnnunalCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdvancedDlg message handlers

void CAdvancedDlg::OnAccountSettings() 
{
	CAccountSettingsDlg Dialog1;
	Dialog1.DoModal();
}

void CAdvancedDlg::OnSectionSettings() 
{
	CSectionSettingsDlg Dialog1;
	Dialog1.DoModal();
}

void CAdvancedDlg::OnUnitSettings() 
{
	CUnitSettingsDlg Dialog1;
	Dialog1.DoModal();
}

void CAdvancedDlg::OnMethodSeetings() 
{
	CMethodSettingsDlg Dialog1;
	Dialog1.DoModal();
}

void CAdvancedDlg::OnAnnunalCheck() 
{
	CCheckDlg Dialog1;
	if(Dialog1.DoModal()==IDCANCEL)
	{
		return;
	}
	if(Dialog1.m_nSelect==1)
	{
		//AfxMessageBox("�����̴��");

		//1.��ȡ��ǰ��Ʒ���б�
		CItemSet m_Set;
		m_Set.Open();
		CString Temp(_T(""));
		if(m_Set.IsEOF())
		{
			AfxMessageBox("���ݿ�����δ������Ʒ��");
			m_Set.Close();
			return;
		}

		//2.������Ҫ�����Excel�ļ���
		CFileDialog FileDlg1(FALSE,NULL,NULL,OFN_HIDEREADONLY,TEXT("Microsoft Excel Files(*.xls)|*.xls||"));
		CString ExcelFile(_T(""));
		FileDlg1.m_ofn.lpstrTitle="�����뱣���̴����ļ�������";
		if(FileDlg1.DoModal()==IDOK)
		{
			ExcelFile=FileDlg1.GetPathName();
		}
		else
		{
			m_Set.Close();
			return;
		}

		if(ExcelFile.Right(4)!=".xls")
		{
			ExcelFile+=".xls";
		}

		CFileFind find;
		if(find.FindFile(ExcelFile,0))
		{
			find.Close();
			if(AfxMessageBox("���ļ��Ѿ�����,ȷʵҪ��д��?",MB_YESNO)==IDYES)
			{
				CFile::Remove(ExcelFile);
			}
			else
			{
				return;
			}
		}
		
		//3.����¼д��Excel�ļ�
		CDatabase database;
		CString sDriver = "MICROSOFT EXCEL DRIVER (*.XLS)";
		CString sExcelFile,sSql;
		sExcelFile=ExcelFile;
		
		sSql.Format("DRIVER={%s};DSN='';FIRSTROWHASNAME=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s",sDriver,sExcelFile,sExcelFile);
		//AfxMessageBox(sSql);
		if(database.OpenEx(sSql,CDatabase::noOdbcDialog))
		{
			//AfxMessageBox("�򿪳ɹ���");
			sSql="CREATE TABLE �̴��(ҩƷ���� TEXT,��� TEXT,�������� TEXT,���� FLOAT,Ӧ���� FLOAT,ʵ���� FLOAT,��� FLOAT,��ע TEXT,���̲� TEXT)";
			database.ExecuteSQL(sSql);

			//��Excel��д������
			m_Set.MoveFirst();

			while(!m_Set.IsEOF())
			{
				sSql.Format("INSERT INTO �̴��(ҩƷ����,���,��������,����,Ӧ����,���,���̲�) VALUES ('%s','%s','%s',%.2f,%.2f,%.2f,'N')",m_Set.m_Name,m_Set.m_Standard,m_Set.m_Manufactory,m_Set.m_In_price,m_Set.m_Amount,m_Set.m_Sum);
				database.ExecuteSQL(sSql);
				m_Set.MoveNext();
			}

			database.Close(); 
		}
		m_Set.Close();
	}
	else
	{
		//AfxMessageBox("��ȡ�̴��");
		//1.��Excel�ļ�
		CFileDialog FileDlg2(TRUE,NULL,NULL,OFN_HIDEREADONLY,TEXT("Microsoft Excel Files(*.xls)|*.xls||"));
		CString ReadFile(_T(""));
		FileDlg2.m_ofn.lpstrTitle="��ѡ����Ҫ��ȡ�̴���ļ�";
		if(FileDlg2.DoModal()==IDOK)
		{
			ReadFile=FileDlg2.GetPathName();
		}
		else
		{
			return;
		}

		CFileFind find1;
		if(!find1.FindFile(ReadFile,0))
		{
			AfxMessageBox("���ļ������ڣ����������룡");
			return;
		}
		find1.Close();

		//2.��Excel�ж�ȡ��¼�����м��
		CDatabase database;
		CRecordset recordset;
		CString sDriver = "MICROSOFT EXCEL DRIVER (*.XLS)";
		CString sExcelFile,sSql;
		sExcelFile=ReadFile;
		
		sSql.Format("DRIVER={%s};DSN='';FIRSTROWHASNAME=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s",sDriver,sExcelFile,sExcelFile);
		//AfxMessageBox(sSql);
		if(!database.OpenEx(sSql,CDatabase::noOdbcDialog))
		{
			AfxMessageBox("�����ݿ����");
			return;
		}

		recordset.m_pDatabase=&database;
		recordset.m_strFilter="";
		sSql="SELECT * FROM �̴�� WHERE ���̲� = 'N'";
		recordset.Open(CRecordset::dynaset,sSql);
		
		if(recordset.IsBOF()&&recordset.IsEOF())
		{
			AfxMessageBox("�ñ�����������Ѿ��̲����!");
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
		
		//��ʼ�̵�
		recordset.MoveFirst();
		
		CString BatchNumber(_T(""));
		CString Unit(_T(""));
		float OutPrice=0.0;
		CString Temp(_T(""));
		float Amount,InPrice,Sum;
		CReadCheckDlg Dialog2;
		CTime now1;
		CString datetime;
		
		CDatabase database1;
		CRecordset recordset1;
		CString tableName1;
		CString sSql1;
		
		while(!recordset.IsEOF())
		{
			//�̲鲢�Ҹ���һ������
			//��ʾ�̴�Ի���				
			Amount=0.0;
			InPrice=0.0;
			Sum=0.0;
			recordset.GetFieldValue(short(0),Dialog2.m_strName);
			recordset.GetFieldValue(short(1),Dialog2.m_strStandard);
			recordset.GetFieldValue(short(2),Dialog2.m_strManufactory);
			recordset.GetFieldValue(short(3),Temp);
			Dialog2.m_fInPrice=atof(Temp.GetBuffer(0));
			recordset.GetFieldValue(short(4),Temp);
			Dialog2.m_fAmount=atof(Temp.GetBuffer(0));
			recordset.GetFieldValue(short(5),Temp);
			Dialog2.m_fRealAmount=atof(Temp.GetBuffer(0));
			recordset.GetFieldValue(short(6),Temp);
			Dialog2.m_fSum=atof(Temp.GetBuffer(0));
			
			if(Dialog2.DoModal()==IDCANCEL)
			{
				break;
			}

			Amount=Dialog2.m_fRealAmount;
			InPrice=Dialog2.m_fInPrice;
			Sum=Amount*InPrice;
			//������Ʒ�б�����
			//�����ݿ�					
			TRY
			{
				sSql1.Format("DSN=%s;;","Medicine");
				database1.OpenEx(sSql1,CDatabase::noOdbcDialog);		
			}
			CATCH(CDBException,e)
			{
				//�������Ϊe->m_nRetCode
			}
			END_CATCH
				
			recordset1.m_pDatabase=&database1;
			tableName1="ItemList";
			//���Ҹ���Ʒ�Ѿ����ڵļ�¼
			recordset1.m_strFilter="";
			sSql1.Format("SELECT * FROM %s WHERE Name = '%s' AND Standard = '%s' ",tableName1,Dialog2.m_strName,Dialog2.m_strStandard);
			recordset1.Open(CRecordset::dynaset,sSql1);
			if(recordset1.IsBOF()&&recordset1.IsEOF())
			{
				//����Ʒû�м�¼,����һ����¼,�������ʵ�ʲ������		
			}
			//���¼�¼
			sSql1.Format("UPDATE %s SET In_price = %.2f, Amount = %.2f, Sum= %.2f WHERE Name = '%s' AND Standard = '%s' ",tableName1,InPrice,Amount,Sum,Dialog2.m_strName,Dialog2.m_strStandard);
			database1.ExecuteSQL(sSql1);
			
			//ʹ����������ݿ�֮��,�ر����ݿ��Լ���¼��
			if(recordset1.IsOpen())
			{
				recordset1.Close();
			}
			if(database1.IsOpen())
			{
				database1.Close();
			}

			//�ڽ����б������ӡ��̴桱��¼
			//�����ݿ�
			TRY
			{
				sSql1.Format("DSN=%s;;","Medicine");
				database1.OpenEx(sSql1,CDatabase::noOdbcDialog);		
			}
			CATCH(CDBException,e)
			{
				//�������Ϊe->m_nRetCode
			}
			END_CATCH
				
			recordset1.m_pDatabase=&database1;
			tableName1="RecordList";
			//���Ҹ���Ʒ�Ѿ����ڵļ�¼
			recordset1.m_strFilter="";
			sSql1.Format("SELECT * FROM %s WHERE Name = '%s' AND Standard = '%s' ",tableName1,Dialog2.m_strName,Dialog2.m_strStandard);
			recordset1.Open(CRecordset::dynaset,sSql1);
			
			now1=CTime::GetCurrentTime();
			datetime=now1.Format(_T("%Y-%m-%d %H:%M:%S"));
			
			
			recordset1.MoveLast();
			recordset1.GetFieldValue((short)3,BatchNumber); //�õ�����
			recordset1.GetFieldValue((short)7,Unit); //�õ���λ
			recordset1.GetFieldValue((short)9,Temp);
			OutPrice=atof(Temp.GetBuffer(0)); //�õ�����
			
			//����������¼
			sSql1.Format("INSERT INTO %s (Date_time,Name,Standard,Batch_number,Section,Method,Amount,Unit,In_price,Out_price,Remaining,Sum,In_or_out,Operator ) VALUES ('%s','%s','%s','%s','�̴�','',0,'%s',%.2f,%.2f,%.2f,%.2f,0,'%s' )",tableName1,datetime,Dialog2.m_strName,Dialog2.m_strStandard,BatchNumber,Unit,InPrice,OutPrice,Amount,Sum,m_strOperator);
			database1.ExecuteSQL(sSql1);	
			
			//ʹ����������ݿ�֮��,�ر����ݿ��Լ���¼��
			if(recordset1.IsOpen())
			{
				recordset1.Close();
			}
			if(database1.IsOpen())
			{
				database1.Close();
			}

			//��Excel��������¼��Ϊ���̲�
			sSql.Format("UPDATE �̴�� SET ���̲� = 'Y' WHERE ҩƷ���� = '%s' AND ��� = '%s'",Dialog2.m_strName,Dialog2.m_strStandard);
			database.ExecuteSQL(sSql);

			recordset.MoveNext();
		}

		if(recordset.IsOpen())
		{
			recordset.Close();
		}
		if(database.IsOpen())
		{
			database.Close();
		}
	}
}
