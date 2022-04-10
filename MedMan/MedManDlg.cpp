// MedManDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MedMan.h"
#include "MedManDlg.h"

//���ݿ�֧��
#include "afxdb.h" 
#include <odbcinst.h>

#include "AccountSet.h"
#include "ItemSet.h"
#include "IORecordSet.h"

#include "LoginDlg.h"
#include "MedicineViewDlg.h"
#include "AddMedicineDlg.h"
#include "SearchMedicineDlg.h"
#include "MedicineIORecordDlg.h"
#include "IOMedicineDlg.h"
#include "AdvancedDlg.h"
#include "DateDlg.h"

#include "GetSpell.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMedManDlg dialog

CMedManDlg::CMedManDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMedManDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMedManDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMedManDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMedManDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMedManDlg, CDialog)
	//{{AFX_MSG_MAP(CMedManDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_STORE_VIEW, OnStoreView)
	ON_BN_CLICKED(IDC_NEW_MEDICINE, OnNewMedicine)
	ON_BN_CLICKED(IDC_MED_IN_OUT, OnMedInOut)
	ON_BN_CLICKED(IDC_MEDICINE_RECORD, OnMedicineRecord)
	ON_BN_CLICKED(IDC_ADVANCED, OnAdvanced)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMedManDlg message handlers

BOOL CMedManDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//1.��ʼ�����ݿ�
	InitDatabase();

	m_strOperator="";

	//2.�û���¼
	BOOL Accepted=FALSE;
	CString Account,Password;
	CLoginDlg Dialog1;
	AccountSet m_Set;
	m_Set.Open();
	while(!Accepted)
	{
		if(Dialog1.DoModal()==IDOK)
		{
			Account=Dialog1.m_strAccount;
			
			m_Set.m_strFilter.Format("Account='%s'",Account);
			m_Set.Requery();
			
			Password=m_Set.m_strPassword;
			if(Dialog1.m_strPassword==Password)
			{
				m_strOperator=Account;
				Accepted=TRUE;
				break;
			}
			if(!Accepted)
			{
				AfxMessageBox("�������������������!");
			}
		}
		else
		{
			exit(-1);
		}
	}
	m_Set.Close();

	//3.�ڲ˵��ײ���ʾϵͳʱ��
	GetTimeOfSystem();
	SetDlgItemText(IDC_TIME,m_strTime);
	m_nTimer=SetTimer(1,1000,NULL);

	//4.����ѡ��(20070217)
	m_bDateSelected=FALSE;

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMedManDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMedManDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMedManDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//��ʼ�����ݿ�
void CMedManDlg::InitDatabase()
{
	//Access���ݿ��ʼ��
	char* szDesc;	
	TCHAR Temppath[MAX_PATH];
	CString tem ;
	::GetCurrentDirectory(MAX_PATH,Temppath);
	tem=Temppath;
	tem=tem+_T("\\Medicine.mdb"); //��õ�ǰ���ݿ��ļ�
	
	szDesc=new char[256];
	sprintf(szDesc,"DSN=%s;PWD=888;DBQ=%s","Medicine",tem);
 		 
	if(SQLConfigDataSource(NULL,ODBC_ADD_DSN,"Microsoft Access Driver (*.mdb)\0",(LPCSTR)szDesc)==FALSE)
	{
		//�������ݿ�ʧ��
		AfxMessageBox("����DSNʱ�����ִ���");
		return ;
	}
	
	//Ŀ�����ڵ�һ������ʱ���Զ���������Դ
	delete szDesc;
}

void CMedManDlg::GetTimeOfSystem()
{
	//�õ�ϵͳʱ��
	CTime now=CTime::GetCurrentTime();
	m_strTime=now.Format(_T("��ǰʱ��: %Y��%m��%d�� %H:%M:%S"));
}
void CMedManDlg::OnTimer(UINT nIDEvent) 
{
	//���²˵��ײ���ʾ��ʱ��
	GetTimeOfSystem();
	SetDlgItemText(IDC_TIME,m_strTime);

	if(m_bDateSelected)
	{
		SetDlgItemText(IDC_DATE,"��ѡ��ļ�¼����:"+Datetime0);
	}
	
	CDialog::OnTimer(nIDEvent);
}

BOOL CMedManDlg::PreTranslateMessage(MSG* pMsg) 
{
	//��ֹ����Esc��Enter�����˳�
	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam==VK_RETURN) return TRUE;
		if(pMsg->wParam==VK_ESCAPE) return TRUE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CMedManDlg::OnStoreView() 
{
	CMedicineViewDlg Dialog1;
	Dialog1.m_strOperator=m_strOperator;
	Dialog1.DoModal();
}

void CMedManDlg::OnNewMedicine() 
{
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
		sSql.Format("INSERT INTO %s (Name,Standard,Manufactory,In_price,Out_price,Amount,Minimum,Unit,Sum,Abbreviation,Batch_number ) VALUES ('%s','%s','%s',%.2f,%.2f,%.2f,%.2f,'%s',%.2f,'%s','%s' )",tableName,m_strName,m_strStandard,m_strManufactory,m_fInPrice,m_fOutPrice,m_fNumber,m_fMinimum,m_strUnit,m_fSum,Abbreviation,m_strBatchNumber);
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

}

void CMedManDlg::OnMedInOut() 
{
	//0.ȡ�ò�������(20070217)	
	BOOL DateAccepted=FALSE;
	if(!m_bDateSelected)
	{
		CDateDlg Dialog2;		
		while(!DateAccepted)
		{
			Dialog2.m_tDateTime=CTime::GetCurrentTime();
			if(Dialog2.DoModal()==IDOK)
			{
				if(Dialog2.m_tDateTime>CTime::GetCurrentTime())
				{
					AfxMessageBox("ѡ������ڲ����ڽ���֮��!");
					continue;
				}
				Datetime0=Dialog2.m_tDateTime.Format(_T("%Y-%m-%d"));				
				DateAccepted=TRUE;
			}
			else
			{
				CTime now=CTime::GetCurrentTime();
				Datetime0=now.Format(_T("%Y-%m-%d"));
				DateAccepted=TRUE;
			}
		}
		m_bDateSelected=TRUE;
	}

	CTime now=CTime::GetCurrentTime();
	CString Datetime1=now.Format(_T("%H:%M:%S"));
	
	Datetime=Datetime0+" "+Datetime1;

	//1.���Ȳ����Լ�ѡ����Ҫ��������Ʒ
	CSearchMedicineDlg Dialog1;
	CString Name(_T(""));
	CString Standard(_T(""));
	CString Manufactory(_T(""));
	CString Unit(_T(""));
	CString Section(_T(""));
	CString Method(_T(""));
	float Amount=0.0;
	float Remaining=0.0;
	int IO=0;

	//������Ʒ����Ʒ���͹�����Name��Standard��������
	if(Dialog1.DoModal()==IDOK)
	{
		//��ȡ��Ʒ�����Լ����
		Name=Dialog1.m_strNameSelected;
		Standard=Dialog1.m_strStandardSelected;
		Manufactory=Dialog1.m_strManufactory;
		Unit=Dialog1.m_strUnit;
	}
	else
	{
		return;
	}

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

	CString BatchNumber(_T(""));
	CString Temp;
	float InPrice=0.0;
	float OutPrice=0.0;

	//������һ�μ�¼����Ϣ�Ա���ν��м���
	CDatabase database;
	CRecordset recordset;
	CString tableName;
	CString sSql;

	CString starttime;

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
		return;
	}
	else
	{
		//ȡ�õ�һ����¼��ʱ�䣬���������ӵ�����Ʒ�ĵ�һ����¼֮ǰ
		recordset.MoveFirst();
		recordset.GetFieldValue((short)0,starttime);

		/*
		//����Ʒ���м�¼,�������һ������ȡֵ
		recordset.MoveLast();
		recordset.GetFieldValue((short)3,BatchNumber); //�õ�����
		recordset.GetFieldValue((short)8,Temp);
		InPrice=atof(Temp.GetBuffer(0)); //�õ�����
		recordset.GetFieldValue((short)9,Temp);
		OutPrice=atof(Temp.GetBuffer(0)); //�õ�����
		recordset.GetFieldValue((short)10,Temp);
		Remaining=atof(Temp.GetBuffer(0)); //�õ�����
		*/
		
	}	

	if(CompareDateTime(starttime,Datetime))
	{
		AfxMessageBox("�����������Ʒ��¼�ڸ���Ʒ��������¼֮ǰ��\r���˳���������ѡ�����ں��ٲ��������Ʒ�ļ�¼��");
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

	//20070217�޸�,������������¼Ҫ���������¼�����м�¼����֮ǰ�����
	int i=0;
	recordset.MoveFirst();
	CString timerecord;
	while(!recordset.IsEOF())
	{
		recordset.GetFieldValue((short)0,timerecord);
		if(CompareDateTime(timerecord,Datetime))
		{
			//�Ƚϵ���һ���������ڴ��ڼ�¼���ڵļ�¼
			//�������¼��ʼ�޸�
			break;
		}
		i++;
		recordset.MoveNext();
	}
	int StartNumber=i;

	recordset.MoveFirst();
	for(i=0;i<StartNumber-1;i++)
	{
		recordset.MoveNext();
	}

	recordset.GetFieldValue((short)3,BatchNumber); //�õ�����
	recordset.GetFieldValue((short)8,Temp);
	InPrice=atof(Temp.GetBuffer(0)); //�õ�����
	recordset.GetFieldValue((short)9,Temp);
	OutPrice=atof(Temp.GetBuffer(0)); //�õ�����
	recordset.GetFieldValue((short)10,Temp);
	Remaining=atof(Temp.GetBuffer(0)); //�õ�����


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
	float Changing;
	if(IO==0) //����
	{
		Remaining+=Amount;
		Changing=Amount;
	}
	else
	{
		Remaining-=Amount;
		Changing=-Amount;
	}

	//����������¼
	
	//�����λ�ÿ�ʼ�޸�
	CString Date_time;
	CString strRemaining;
	CString strIn_price;
	float Remaining1;
	float In_price;
	recordset.MoveFirst();
	for(i=0;i<StartNumber;i++)
	{
		recordset.MoveNext();
	}
	while(!recordset.IsEOF())
	{
		//ȡ��һ����¼�����޸�
		recordset.GetFieldValue((short)0,Date_time);
		recordset.GetFieldValue((short)10,strRemaining);
		recordset.GetFieldValue((short)8,strIn_price);
		Remaining1=atof(strRemaining.GetBuffer(0));
		In_price=atof(strIn_price.GetBuffer(0));

		sSql.Format("UPDATE %s SET Remaining = %.2f, Sum = %.2f WHERE Date_time = '%s' AND Name = '%s' AND Standard = '%s'",tableName,(Remaining1+Changing),In_price*(Remaining1+Changing),Date_time,Name,Standard);
		database.ExecuteSQL(sSql);

		recordset.MoveNext();
	}
	
	sSql.Format("INSERT INTO %s (Date_time,Name,Standard,Batch_number,Section,Method,Amount,Unit,In_price,Out_price,Remaining,Sum,In_or_out,Operator ) VALUES ('%s','%s','%s','%s','%s','%s',%.2f,'%s',%.2f,%.2f,%.2f,%.2f,%d,'%s' )",tableName,Datetime,Name,Standard,BatchNumber,Section,Method,Amount,Unit,InPrice,OutPrice,Remaining,InPrice*Remaining,IO,m_strOperator);
	database.ExecuteSQL(sSql);	


	if(recordset.IsOpen())
	{
		recordset.Close();
	}
	sSql.Format("SELECT * FROM %s WHERE Name = '%s' AND Standard = '%s' ORDER BY Date_time",tableName,Name,Standard);
	recordset.Open(CRecordset::dynaset,sSql);

	recordset.MoveLast();
	recordset.GetFieldValue((short)0,Date_time);
	recordset.GetFieldValue((short)10,strRemaining);
	recordset.GetFieldValue((short)8,strIn_price);
	Remaining=atof(strRemaining.GetBuffer(0));
	In_price=atof(strIn_price.GetBuffer(0));


	//ʹ����������ݿ�֮��,�ر����ݿ��Լ���¼��
	if(recordset.IsOpen())
	{
		recordset.Close();
	}
	if(database.IsOpen())
	{
		database.Close();
	}

	//3.������Ʒ�б��4����Ϣ(����,����,����,���)(�Լ�����20070217)
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


}

void CMedManDlg::OnMedicineRecord() 
{
	//1.���Ȳ����Լ�ѡ����Ҫ�鿴��¼����Ʒ
	CSearchMedicineDlg Dialog1;
	CString Name(_T(""));
	CString Standard(_T(""));
	CString Manufactory(_T(""));
	CString Unit(_T(""));

	//������Ʒ����Ʒ���͹�����Name��Standard��������
	if(Dialog1.DoModal()==IDOK)
	{
		//��ȡ��Ʒ�����Լ����
		Name=Dialog1.m_strNameSelected;
		Standard=Dialog1.m_strStandardSelected;
		Manufactory=Dialog1.m_strManufactory;
		Unit=Dialog1.m_strUnit;
	}
	else
	{
		return;
	}

	//2.���в鿴
	if(Name=="")
	{
		AfxMessageBox("��δѡ����Ʒ!");
		return;
	}

	CMedicineIORecordDlg Dialog2;
	Dialog2.m_strName=Name;
	Dialog2.m_strStandard=Standard;
	Dialog2.m_strManufactory=Manufactory;
	Dialog2.m_strUnit=Unit;
	Dialog2.m_strOperator=m_strOperator;
	Dialog2.DoModal();

}

void CMedManDlg::OnAdvanced() 
{
	CAdvancedDlg Dialog1;
	Dialog1.m_strOperator=m_strOperator;
	Dialog1.DoModal();
}

BOOL CMedManDlg::CompareDateTime(CString Time1,CString Time2)
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