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
		//AfxMessageBox("生成盘存表");

		//1.获取当前商品的列表
		CItemSet m_Set;
		m_Set.Open();
		CString Temp(_T(""));
		if(m_Set.IsEOF())
		{
			AfxMessageBox("数据库中尚未存入商品！");
			m_Set.Close();
			return;
		}

		//2.输入需要保存的Excel文件名
		CFileDialog FileDlg1(FALSE,NULL,NULL,OFN_HIDEREADONLY,TEXT("Microsoft Excel Files(*.xls)|*.xls||"));
		CString ExcelFile(_T(""));
		FileDlg1.m_ofn.lpstrTitle="请输入保存盘存表的文件的名称";
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
			if(AfxMessageBox("该文件已经存在,确实要改写吗?",MB_YESNO)==IDYES)
			{
				CFile::Remove(ExcelFile);
			}
			else
			{
				return;
			}
		}
		
		//3.将记录写入Excel文件
		CDatabase database;
		CString sDriver = "MICROSOFT EXCEL DRIVER (*.XLS)";
		CString sExcelFile,sSql;
		sExcelFile=ExcelFile;
		
		sSql.Format("DRIVER={%s};DSN='';FIRSTROWHASNAME=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s",sDriver,sExcelFile,sExcelFile);
		//AfxMessageBox(sSql);
		if(database.OpenEx(sSql,CDatabase::noOdbcDialog))
		{
			//AfxMessageBox("打开成功！");
			sSql="CREATE TABLE 盘存表(药品名称 TEXT,规格 TEXT,生产厂家 TEXT,单价 FLOAT,应有数 FLOAT,实有数 FLOAT,金额 FLOAT,备注 TEXT,已盘查 TEXT)";
			database.ExecuteSQL(sSql);

			//向Excel中写入数据
			m_Set.MoveFirst();

			while(!m_Set.IsEOF())
			{
				sSql.Format("INSERT INTO 盘存表(药品名称,规格,生产厂家,单价,应有数,金额,已盘查) VALUES ('%s','%s','%s',%.2f,%.2f,%.2f,'N')",m_Set.m_Name,m_Set.m_Standard,m_Set.m_Manufactory,m_Set.m_In_price,m_Set.m_Amount,m_Set.m_Sum);
				database.ExecuteSQL(sSql);
				m_Set.MoveNext();
			}

			database.Close(); 
		}
		m_Set.Close();
	}
	else
	{
		//AfxMessageBox("读取盘存表");
		//1.打开Excel文件
		CFileDialog FileDlg2(TRUE,NULL,NULL,OFN_HIDEREADONLY,TEXT("Microsoft Excel Files(*.xls)|*.xls||"));
		CString ReadFile(_T(""));
		FileDlg2.m_ofn.lpstrTitle="请选择需要读取盘存表文件";
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
			AfxMessageBox("该文件不存在！请重新输入！");
			return;
		}
		find1.Close();

		//2.从Excel中读取记录并进行检查
		CDatabase database;
		CRecordset recordset;
		CString sDriver = "MICROSOFT EXCEL DRIVER (*.XLS)";
		CString sExcelFile,sSql;
		sExcelFile=ReadFile;
		
		sSql.Format("DRIVER={%s};DSN='';FIRSTROWHASNAME=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s",sDriver,sExcelFile,sExcelFile);
		//AfxMessageBox(sSql);
		if(!database.OpenEx(sSql,CDatabase::noOdbcDialog))
		{
			AfxMessageBox("打开数据库错误！");
			return;
		}

		recordset.m_pDatabase=&database;
		recordset.m_strFilter="";
		sSql="SELECT * FROM 盘存表 WHERE 已盘查 = 'N'";
		recordset.Open(CRecordset::dynaset,sSql);
		
		if(recordset.IsBOF()&&recordset.IsEOF())
		{
			AfxMessageBox("该表的所有数据已经盘查完毕!");
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
		
		//开始盘点
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
			//盘查并且更新一个数据
			//显示盘存对话框				
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
			//更新物品列表数据
			//打开数据库					
			TRY
			{
				sSql1.Format("DSN=%s;;","Medicine");
				database1.OpenEx(sSql1,CDatabase::noOdbcDialog);		
			}
			CATCH(CDBException,e)
			{
				//错误代码为e->m_nRetCode
			}
			END_CATCH
				
			recordset1.m_pDatabase=&database1;
			tableName1="ItemList";
			//查找该商品已经存在的记录
			recordset1.m_strFilter="";
			sSql1.Format("SELECT * FROM %s WHERE Name = '%s' AND Standard = '%s' ",tableName1,Dialog2.m_strName,Dialog2.m_strStandard);
			recordset1.Open(CRecordset::dynaset,sSql1);
			if(recordset1.IsBOF()&&recordset1.IsEOF())
			{
				//该商品没有记录,增加一个记录,这种情况实际不会存在		
			}
			//更新记录
			sSql1.Format("UPDATE %s SET In_price = %.2f, Amount = %.2f, Sum= %.2f WHERE Name = '%s' AND Standard = '%s' ",tableName1,InPrice,Amount,Sum,Dialog2.m_strName,Dialog2.m_strStandard);
			database1.ExecuteSQL(sSql1);
			
			//使用完这个数据库之后,关闭数据库以及记录集
			if(recordset1.IsOpen())
			{
				recordset1.Close();
			}
			if(database1.IsOpen())
			{
				database1.Close();
			}

			//在进出列表中增加“盘存”记录
			//打开数据库
			TRY
			{
				sSql1.Format("DSN=%s;;","Medicine");
				database1.OpenEx(sSql1,CDatabase::noOdbcDialog);		
			}
			CATCH(CDBException,e)
			{
				//错误代码为e->m_nRetCode
			}
			END_CATCH
				
			recordset1.m_pDatabase=&database1;
			tableName1="RecordList";
			//查找该商品已经存在的记录
			recordset1.m_strFilter="";
			sSql1.Format("SELECT * FROM %s WHERE Name = '%s' AND Standard = '%s' ",tableName1,Dialog2.m_strName,Dialog2.m_strStandard);
			recordset1.Open(CRecordset::dynaset,sSql1);
			
			now1=CTime::GetCurrentTime();
			datetime=now1.Format(_T("%Y-%m-%d %H:%M:%S"));
			
			
			recordset1.MoveLast();
			recordset1.GetFieldValue((short)3,BatchNumber); //得到批号
			recordset1.GetFieldValue((short)7,Unit); //得到单位
			recordset1.GetFieldValue((short)9,Temp);
			OutPrice=atof(Temp.GetBuffer(0)); //得到出价
			
			//增加这条记录
			sSql1.Format("INSERT INTO %s (Date_time,Name,Standard,Batch_number,Section,Method,Amount,Unit,In_price,Out_price,Remaining,Sum,In_or_out,Operator ) VALUES ('%s','%s','%s','%s','盘存','',0,'%s',%.2f,%.2f,%.2f,%.2f,0,'%s' )",tableName1,datetime,Dialog2.m_strName,Dialog2.m_strStandard,BatchNumber,Unit,InPrice,OutPrice,Amount,Sum,m_strOperator);
			database1.ExecuteSQL(sSql1);	
			
			//使用完这个数据库之后,关闭数据库以及记录集
			if(recordset1.IsOpen())
			{
				recordset1.Close();
			}
			if(database1.IsOpen())
			{
				database1.Close();
			}

			//将Excel中这条记录置为已盘查
			sSql.Format("UPDATE 盘存表 SET 已盘查 = 'Y' WHERE 药品名称 = '%s' AND 规格 = '%s'",Dialog2.m_strName,Dialog2.m_strStandard);
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
