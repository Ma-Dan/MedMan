// GetSpell.h: interface for the CGetSpell class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GETSPELL_H__1410A58E_F5E7_45C6_8DF0_C8488D8FD8AB__INCLUDED_)
#define AFX_GETSPELL_H__1410A58E_F5E7_45C6_8DF0_C8488D8FD8AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGetSpell  
{
public:
	CGetSpell();
	virtual ~CGetSpell();
	CString GetChineseSpell(CString Chinese);

private:
	CString ChineseFirstPY;

};

#endif // !defined(AFX_GETSPELL_H__1410A58E_F5E7_45C6_8DF0_C8488D8FD8AB__INCLUDED_)
