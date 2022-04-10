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
	
	//1.更新商品信息
	SetDlgItemText(IDC_EDIT_NAME,m_strName);
	SetDlgItemText(IDC_EDIT_STANDARD,m_strStandard);
	SetDlgItemText(IDC_EDIT_MANUFACTORY,m_strManufactory);
	SetDlgItemText(IDC_EDIT_UNIT,m_strUnit);

	//2.初始化表格(表头显示)
	m_ctrlRecordList.InsertColumn(0,_T("日 期"),LVCFMT_LEFT,100,-1);
	m_ctrlRecordList.InsertColumn(1,_T("批 号"),LVCFMT_LEFT,80,-1);
	m_ctrlRecordList.InsertColumn(2,_T("进出单位"),LVCFMT_LEFT,80,-1);
	m_ctrlRecordList.InsertColumn(3,_T("付款方式"),LVCFMT_LEFT,80,-1);
	m_ctrlRecordList.InsertColumn(4,_T("进货单价"),LVCFMT_LEFT,80,-1);
	m_ctrlRecordList.InsertColumn(5,_T("出货单价"),LVCFMT_LEFT,80,-1);
	m_ctrlRecordList.InsertColumn(6,_T("进出量"),LVCFMT_LEFT,80,-1);
	m_ctrlRecordList.InsertColumn(7,_T("存 量"),LVCFMT_LEFT,80,-1);
	m_ctrlRecordList.InsertColumn(8,_T("金 额"),LVCFMT_LEFT,80,-1);
	m_ctrlRecordList.InsertColumn(9,_T("操作员"),LVCFMT_LEFT,80,-1);
	m_ctrlRecordList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	//3.显示列表
	ViewMedicineIORecord();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMedicineIORecordDlg::ViewMedicineIORecord()
{
	//1.清空列表
	m_ctrlRecordList.DeleteAllItems();

	m_nRecordSelect=-1;

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
	tableName="RecordList";

	//查找这种商品的进销记录
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Name = '%s' AND Standard = '%s' ORDER BY Date_time",tableName,m_strName,m_strStandard);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		AfxMessageBox("这种商品没有进销记录!");
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

	//将进销记录添加到表格
	m_nRecordTotal=0;
	recordset.MoveFirst();
	while(!recordset.IsEOF())
	{
		//添加一个记录到列表
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
void CMedicineIORecordDlg::OnClickListRecord(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//选中一条记录
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
		AfxMessageBox("尚未选择需要修改的记录!");
		return;
	}
	//1.获取需要修改的记录的信息,只获取时间和名称,规格 其他的重新填写，因为将原来数据放上去的意义不大
	CString Date_time;
	CString BatchNumber(_T(""));
	CString Section(_T(""));
	CString Method(_T(""));
	float Amount,OldAmount; //如果Amount发生改变,则要改变后面所有记录
	float In_price;
	float Out_price;
	float Remaining,OldRemaining;
	int In_or_out,OldIn_or_out; //如果In_or_out发生改变,则要改变后面所有记录

	CString Temp;
	
	Date_time=m_ctrlRecordList.GetItemText(m_nRecordSelect,0);
	BatchNumber=m_ctrlRecordList.GetItemText(m_nRecordSelect,1);
	Section=m_ctrlRecordList.GetItemText(m_nRecordSelect,2);
	Method=m_ctrlRecordList.GetItemText(m_nRecordSelect,3);
	In_price=atof(m_ctrlRecordList.GetItemText(m_nRecordSelect,4).GetBuffer(0));
	Out_price=atof(m_ctrlRecordList.GetItemText(m_nRecordSelect,5).GetBuffer(0));
	OldAmount=Amount=atof(m_ctrlRecordList.GetItemText(m_nRecordSelect,6).GetBuffer(0));
	Remaining=atof(m_ctrlRecordList.GetItemText(m_nRecordSelect,7).GetBuffer(0));

	//使用进出的对话框重新填写
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
				AfxMessageBox("进出量不能为零!");
				continue;
			}
			if(Dialog1.m_fInPrice==0.0||Dialog1.m_fOutPrice==0.0)
			{
				AfxMessageBox("单价不能为零!");
				continue;
			}
			if(Dialog1.m_strSection=="")
			{
				AfxMessageBox("尚未选择进出单位!");
				continue;
			}
			if(Dialog1.m_nIO==0&&Dialog1.m_strMethod=="")
			{
				AfxMessageBox("尚未选择付款方式!");
				continue;
			}
			//取得正确数据
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
	
	//2.对数据库进行修改
	CDatabase database;
	CRecordset recordset;
	CString tableName;
	CString sSql;
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
	tableName="RecordList";

	//查找这条进销记录
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Date_time = '%s' AND Name = '%s' AND Standard = '%s' ORDER BY Date_time",tableName,Date_time,m_strName,m_strStandard);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		AfxMessageBox("没有这条进销记录!"); //这种情况不存在
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
	
	//检查进出状况是否改变,如果是,计算出改变的量,并据此更新后面所有记录以及物品列表
	float Changing=0.0;  //改变量
	recordset.GetFieldValue(short(12),Temp);
	OldIn_or_out=atoi(Temp.GetBuffer(0));
	recordset.GetFieldValue(short(10),Temp);
	OldRemaining=atoi(Temp.GetBuffer(0));

	if(OldIn_or_out==In_or_out)
	{
		if(In_or_out==0) //进货
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
		if(In_or_out==0) //出货变进货
		{
			Changing=Amount+OldAmount;
		}
		else
		{
			Changing=-(Amount+OldAmount);
		}
	}	

	//修改记录
	sSql.Format("UPDATE %s SET Batch_number = '%s', Section = '%s', Method = '%s', Amount = %.2f, In_price = %.2f, Out_price = %.2f, Remaining = %.2f, Sum = %.2f, In_or_out = %d, Operator = '%s' WHERE Date_time = '%s' AND Name ='%s' AND Standard = '%s'",tableName,BatchNumber,Section,Method,Amount,In_price,Out_price,OldRemaining+Changing,In_price*(OldRemaining+Changing),In_or_out,m_strOperator,Date_time,m_strName,m_strStandard);

	database.ExecuteSQL(sSql);

	if(Changing==0.0)
	{
		//使用完这个数据库之后,关闭数据库以及记录集
		if(recordset.IsOpen())
		{
			recordset.Close();
		}
		if(database.IsOpen())
		{
			database.Close();
		}
		//刷新画面数据
		ViewMedicineIORecord();
		return;
	}

	//改变量不为0,需要修改后面所有记录,只用修改余量,依据Changing
	int i;
	for(i=m_nRecordSelect+1;i<m_ctrlRecordList.GetItemCount();i++)
	{
		Date_time=m_ctrlRecordList.GetItemText(i,0);
		Remaining=atof(m_ctrlRecordList.GetItemText(i,7).GetBuffer(0));
		In_price=atof(m_ctrlRecordList.GetItemText(i,4).GetBuffer(0));
		
		sSql.Format("UPDATE %s SET Remaining = %.2f, Sum = %.2f WHERE Date_time = '%s' AND Name = '%s' AND Standard = '%s'",tableName,(Remaining+Changing),In_price*(Remaining+Changing),Date_time,m_strName,m_strStandard);
		database.ExecuteSQL(sSql);
	}
	
	//使用完这个数据库之后,关闭数据库以及记录集
	if(recordset.IsOpen())
	{
		recordset.Close();
	}
	if(database.IsOpen())
	{
		database.Close();
	}

	//3.修改物品列表
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
	tableName="ItemList";

	//查找这个商品
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Name = '%s' AND Standard = '%s'",tableName,m_strName,m_strStandard);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		AfxMessageBox("没有这种记录!"); //这种情况不存在
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

	//获取余量以及单价
	recordset.GetFieldValue(4,Temp);
	Out_price=atof(Temp.GetBuffer(0));
	recordset.GetFieldValue(5,Temp);
	Amount=atof(Temp.GetBuffer(0));

	//修改余量以及余额上次的单价
	sSql.Format("UPDATE %s SET Amount = %.2f, Sum = %.2f WHERE Name = '%s' AND Standard ='%s'",tableName,Amount+Changing,In_price*(Amount+Changing),m_strName,m_strStandard);
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

	//刷新画面数据
	ViewMedicineIORecord();

}

void CMedicineIORecordDlg::OnInsertRecord() 
{
	CString Date_timeInsert("");
	CString Temp("");
	CString Time1("");
	CString Time2("");
	int StartNumber=0;

	//增补记录,可以自己定义日期来向数据库中插入以前忘记登入的记录

	//1.获取需要增补的记录的日期
	//得到系统时间
	CTime now=CTime::GetCurrentTime();
	Temp=now.Format(_T("当前时间: %Y年%m月%d日 %H:%M:%S"));
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

	//2.得到日期时间之后,对比已经列出的记录，决定需要修改的记录的开始序数
	//使用函数CompareDateTime来比较时间,返回TRUE,表示前者大于后者
	if(Time1==Time2) //时间刚好相等,则返回,不允许这样的记录(很少出现)
	{
		return;
	}
	int i;
	for(i=0;i<m_ctrlRecordList.GetItemCount();i++)
	{
		Time2=m_ctrlRecordList.GetItemText(i,0);
		if(CompareDateTime(Time2,Time1))
		{
			//比较到了一个插入日期大于记录日期的记录
			//从这个记录开始修改
			break;
		}
	}
	StartNumber=i;
	//不能允许插在最前
	if(StartNumber==0)
	{
		AfxMessageBox("不能插到新增记录之前!");
		return;
	}

	//列表中从StartNumber开始的记录都要刷新
	//通过进出商品对话框获得这条记录的信息
	//日期时间已经获得,为Time1
	//名称、规格和计量单位也已经取得 m_strName,m_strStandard,m_strUnit
	//进出价格默认取StartNumber前一个
	//余量按照StartNumber前一个来计算
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

	//获取已经有的数值
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
				AfxMessageBox("进出量不能为零!");
				continue;
			}
			if(Dialog2.m_fInPrice==0.0||Dialog2.m_fOutPrice==0.0)
			{
				AfxMessageBox("单价不能为零!");
				continue;
			}
			if(Dialog2.m_strSection=="")
			{
				AfxMessageBox("尚未选择进出单位!");
				continue;
			}
			if(Dialog2.m_nIO==0&&Dialog2.m_strMethod=="")
			{
				AfxMessageBox("尚未选择付款方式!");
				continue;
			}
			//取得正确数据
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

	//3.已经获得改动的数值,修改记录数据库
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
	tableName="RecordList";

	//查找这种商品的进销记录
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Name = '%s' AND Standard = '%s' ORDER BY Date_time",tableName,m_strName,m_strStandard);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		AfxMessageBox("没有这种商品的进销记录!"); //这种情况不存在
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

	sSql.Format("INSERT INTO %s (Date_time,Name,Standard,Batch_number,Section,Method,Amount,Unit,In_price,Out_price,Remaining,Sum,In_or_out,Operator ) VALUES ('%s','%s','%s','%s','%s','%s',%.2f,'%s',%.2f,%.2f,%.2f,%.2f,%d,'%s' )",tableName,Date_time,Name,Standard,BatchNumber,Section,Method,Amount,Unit,In_price,Out_price,Remaining,In_price*Remaining,In_or_out,m_strOperator);
	database.ExecuteSQL(sSql);

	//从StartNumber开始,修改后面所有记录的余量和金额
	for(i=StartNumber;i<m_ctrlRecordList.GetItemCount();i++)
	{
		Date_time=m_ctrlRecordList.GetItemText(i,0);
		Remaining=atof(m_ctrlRecordList.GetItemText(i,7).GetBuffer(0));
		In_price=atof(m_ctrlRecordList.GetItemText(i,4).GetBuffer(0));
		
		sSql.Format("UPDATE %s SET Remaining = %.2f, Sum = %.2f WHERE Date_time = '%s' AND Name = '%s' AND Standard = '%s'",tableName,(Remaining+Changing),In_price*(Remaining+Changing),Date_time,m_strName,m_strStandard);
		database.ExecuteSQL(sSql);
	}

	//使用完这个数据库之后,关闭数据库以及记录集
	if(recordset.IsOpen())
	{
		recordset.Close();
	}
	if(database.IsOpen())
	{
		database.Close();
	}

	//3.修改物品列表
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
	tableName="ItemList";

	//查找这个商品
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Name = '%s' AND Standard = '%s'",tableName,m_strName,m_strStandard);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		AfxMessageBox("没有这种记录!"); //这种情况不存在
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

	//获取余量以及单价
	recordset.GetFieldValue(3,Temp);
	In_price=atof(Temp.GetBuffer(0));
	recordset.GetFieldValue(5,Temp);
	Amount=atof(Temp.GetBuffer(0));

	//修改余量以及余额上次的单价
	sSql.Format("UPDATE %s SET Amount = %.2f, Sum = %.2f WHERE Name = '%s' AND Standard ='%s'",tableName,Amount+Changing,In_price*(Amount+Changing),m_strName,m_strStandard);
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

	//刷新画面数据
	ViewMedicineIORecord();

}

BOOL CMedicineIORecordDlg::CompareDateTime(CString Time1,CString Time2)
{
	int year1,month1,day1,hour1,minute1,second1;
	int year2,month2,day2,hour2,minute2,second2;
	
	//1.比较年份
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

	//2.比较月份
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

	//3.比较日期
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

	//4.比较小时
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

	//5.比较分钟
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

	//6.比较秒
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

	//全部相等,也返回FALSE,在记录最后增加
	return FALSE;
}
void CMedicineIORecordDlg::OnDeleteRecord() 
{
	if(m_nRecordTotal==1)
	{
		AfxMessageBox("只有一条记录,不能删除!");
		return;
	}

	if(m_nRecordSelect==-1)
	{
		AfxMessageBox("尚未选择需要修改的记录!");
		return;
	}

	//删除之前进行一次确认
	if(AfxMessageBox("您确定要删除这条记录？",MB_YESNO)==IDNO)
	{
		return;
	}

	//1.获取需要删除的记录的信息,获取时间和名称,规格,以及这次的进出量,据此修改该列表后面所有后续记录
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
		
	//2.对数据库进行修改
	CDatabase database;
	CRecordset recordset;
	CString tableName;
	CString sSql;
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
	tableName="RecordList";

	//查找这条进销记录
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Date_time = '%s' AND Name = '%s' AND Standard = '%s' ORDER BY Date_time",tableName,Date_time,m_strName,m_strStandard);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		AfxMessageBox("没有这条进销记录!"); //这种情况不存在
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
	
	//计算出改变的量,并据此更新后面所有记录以及物品列表
	float Changing=0.0;  //改变量
	recordset.GetFieldValue(short(12),Temp);
	In_or_out=atoi(Temp.GetBuffer(0));

	if(In_or_out==0) //删除进货记录
	{
		Changing=-Amount;
	}
	else
	{
		Changing=Amount;
	}		

	//删除记录
	sSql.Format("DELETE FROM %s WHERE Date_time = '%s' AND Name ='%s' AND Standard = '%s'",tableName,Date_time,m_strName,m_strStandard);
	database.ExecuteSQL(sSql);
	
	//修改后面所有记录,只用修改余量,依据Changing
	int i;
	for(i=m_nRecordSelect+1;i<m_ctrlRecordList.GetItemCount();i++)
	{
		Date_time=m_ctrlRecordList.GetItemText(i,0);
		Remaining=atof(m_ctrlRecordList.GetItemText(i,7).GetBuffer(0));
		In_price=atof(m_ctrlRecordList.GetItemText(i,4).GetBuffer(0));
		
		sSql.Format("UPDATE %s SET Remaining = %.2f, Sum = %.2f WHERE Date_time = '%s' AND Name = '%s' AND Standard = '%s'",tableName,(Remaining+Changing),In_price*(Remaining+Changing),Date_time,m_strName,m_strStandard);
		database.ExecuteSQL(sSql);
	}
	
	//使用完这个数据库之后,关闭数据库以及记录集
	if(recordset.IsOpen())
	{
		recordset.Close();
	}
	if(database.IsOpen())
	{
		database.Close();
	}

	//3.修改物品列表
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
	tableName="ItemList";

	//查找这个商品
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Name = '%s' AND Standard = '%s'",tableName,m_strName,m_strStandard);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		AfxMessageBox("没有这种记录!"); //这种情况不存在
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

	//获取余量以及单价
	recordset.GetFieldValue(3,Temp);
	In_price=atof(Temp.GetBuffer(0));
	recordset.GetFieldValue(5,Temp);
	Amount=atof(Temp.GetBuffer(0));

	//修改余量以及余额上次的单价
	sSql.Format("UPDATE %s SET Amount = %.2f, Sum = %.2f WHERE Name = '%s' AND Standard ='%s'",tableName,Amount+Changing,In_price*(Amount+Changing),m_strName,m_strStandard);
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

	//刷新画面数据
	ViewMedicineIORecord();
}

void CMedicineIORecordDlg::OnIoMedicine() 
{
	//1.这里已经有名称和规格信息
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

	//2.进行进出操作
	if(Name=="")
	{
		AfxMessageBox("尚未选择商品!");
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

	//获得最近一次记录的信息以便这次进行计算
	CDatabase database;
	CRecordset recordset;
	CString tableName;
	CString sSql;

	//打开数据库
	TRY
	{
		sSql.Format("DSN=%s;;","Medicine");
		database.OpenEx(sSql,CDatabase::noOdbcDialog);		
	}
	CATCH(CDBException,e)
	{
		//错误代码为e->m_nRetCode
	}
	END_CATCH
	recordset.m_pDatabase=&database;
	tableName="RecordList";
	//查找该商品已经存在的记录
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Name = '%s' AND Standard = '%s' ORDER BY Date_time",tableName,Name,Standard);
	recordset.Open(CRecordset::dynaset,sSql);
	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		//该商品没有记录,则取值均为0或者空		
	}
	else
	{
		//该商品已有记录,按照最后一个进行取值
		recordset.MoveLast();
		recordset.GetFieldValue((short)3,BatchNumber); //得到批号
		recordset.GetFieldValue((short)8,Temp);
		InPrice=atof(Temp.GetBuffer(0)); //得到进价
		recordset.GetFieldValue((short)9,Temp);
		OutPrice=atof(Temp.GetBuffer(0)); //得到进价
		recordset.GetFieldValue((short)10,Temp);
		Remaining=atof(Temp.GetBuffer(0)); //得到余量
	}


	//默认的批号和进出价格与最近一次记录相同
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
				AfxMessageBox("进出单位不能为空!");
				continue;
			}
			if(Amount==0.0)
			{
				AfxMessageBox("进出数量不能为零!");
				continue;
			}
			if(InPrice==0.0||OutPrice==0.0)
			{
				AfxMessageBox("单价不能为零!请重新输入!");
				continue;
			}
			if(Dialog2.m_nIO==0&&Dialog2.m_strMethod=="")
			{
				AfxMessageBox("进货付款方式不能为空!");
				continue;
			}
			Section=Dialog2.m_strSection;
			if(Dialog2.m_nIO==1) //进货
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
	}

	//增加进出记录
	if(IO==0) //进货
	{
		Remaining+=Amount;
	}
	else
	{
		Remaining-=Amount;
	}

	//增加这条记录
	CTime now=CTime::GetCurrentTime();
	CString datetime;
	datetime=now.Format(_T("%Y-%m-%d %H:%M:%S"));
	sSql.Format("INSERT INTO %s (Date_time,Name,Standard,Batch_number,Section,Method,Amount,Unit,In_price,Out_price,Remaining,Sum,In_or_out,Operator ) VALUES ('%s','%s','%s','%s','%s','%s',%.2f,'%s',%.2f,%.2f,%.2f,%.2f,%d,'%s' )",tableName,datetime,Name,Standard,BatchNumber,Section,Method,Amount,Unit,InPrice,OutPrice,Remaining,InPrice*Remaining,IO,m_strOperator);
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

	//3.更新商品列表的4项信息(进价,出价,余量,金额)
	//打开数据库
	TRY
	{
		sSql.Format("DSN=%s;;","Medicine");
		database.OpenEx(sSql,CDatabase::noOdbcDialog);		
	}
	CATCH(CDBException,e)
	{
		//错误代码为e->m_nRetCode
	}
	END_CATCH
	recordset.m_pDatabase=&database;
	tableName="ItemList";
	//查找该商品已经存在的记录
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Name = '%s' AND Standard = '%s' ",tableName,Name,Standard);
	recordset.Open(CRecordset::dynaset,sSql);
	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		//该商品没有记录,增加一个记录,这种情况实际不会存在		
	}
	//更新记录
	sSql.Format("UPDATE %s SET In_price = %.2f, Out_price = %.2f, Amount = %.2f, Sum= %.2f, Batch_number= '%s' WHERE Name = '%s' AND Standard = '%s' ",tableName,InPrice,OutPrice,Remaining,InPrice*Remaining,BatchNumber,Name,Standard);
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

	//刷新画面数据
	ViewMedicineIORecord();
}
