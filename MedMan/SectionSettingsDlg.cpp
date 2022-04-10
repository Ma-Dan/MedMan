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
	
	//1.初始化表头
	m_ctrlListSection.InsertColumn(0,_T("单位名称"),LVCFMT_LEFT,100,-1);
	m_ctrlListSection.InsertColumn(1,_T("进销状况"),LVCFMT_LEFT,100,-1);
	m_ctrlListSection.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	//2.更新单位列表
	LoadSections();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSectionSettingsDlg::LoadSections()
{
	//1.清空列表
	m_ctrlListSection.DeleteAllItems();

	m_nSectionSelect=-1;

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
	tableName="Section";

	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s ORDER BY I_O",tableName);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		AfxMessageBox("没有用户帐户记录!");
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


	m_nSectionTotal=0;
	recordset.MoveFirst();
	while(!recordset.IsEOF())
	{
		recordset.GetFieldValue((short)0,Temp);
		m_ctrlListSection.InsertItem(m_nSectionTotal,Temp,-1);
		recordset.GetFieldValue((short)1,Temp);
		if(atoi(Temp.GetBuffer(0))==0)
		{
			Temp="进货部门";
		}
		else
		{
			Temp="出货部门";
		}
		m_ctrlListSection.SetItemText(m_nSectionTotal,1,Temp);
				
		recordset.MoveNext();
		m_nSectionTotal++;
	}

	m_nSectionTotal=recordset.GetRecordCount();

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
				AfxMessageBox("进销单位名称不能为空!");
				continue;
			}
			if(Dialog1.In_or_out==-1)
			{
				AfxMessageBox("尚未选择是进货还是出货单位!");
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

	//添加这个单位
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
	tableName="Section";

	//查找这个单位是否已经存在
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Section_name = '%s'",tableName,SectionName);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		//单位不存在,可以添加
	}
	else
	{
		AfxMessageBox("该单位已经存在,不能重复添加!");
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


	//将单位添加到表格
	sSql.Format("INSERT INTO %s (Section_name, I_O) VALUES ('%s', %d)",tableName,SectionName,In_or_out);
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

	//刷新列表
	LoadSections();
	
}

void CSectionSettingsDlg::OnDeleteSection() 
{
	if(m_nSectionTotal==1)
	{
		AfxMessageBox("只有一个单位,不能删除!");
		return;
	}

	if(m_nSectionSelect==-1)
	{
		AfxMessageBox("尚未选择需要删除的单位!");
		return;
	}

	if(AfxMessageBox("确实要删除该单位吗?",MB_YESNO)==IDNO)
	{
		return;
	}

	CString SectionName;
	SectionName=m_ctrlListSection.GetItemText(m_nSectionSelect,0);

	//删除帐户
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
	tableName="Section";

	//查找这个帐户是否已经存在
	recordset.m_strFilter="";
	sSql.Format("SELECT * FROM %s WHERE Section_name = '%s'",tableName,SectionName);
	recordset.Open(CRecordset::dynaset,sSql);

	if(recordset.IsBOF()&&recordset.IsEOF())
	{
		//单位不存在,无法删除
		AfxMessageBox("该单位不存在,无法删除!");
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
	else
	{
		
	}


	//删除单位
	sSql.Format("DELETE FROM %s WHERE Section_name = '%s'",tableName,SectionName);
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

	//刷新列表
	LoadSections();
}

void CSectionSettingsDlg::OnClickListSection(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//选中一条记录
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
