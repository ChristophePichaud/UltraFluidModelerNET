// CDialogDatabaseSettings.cpp : implementation file
//

#include "StdAfx.h"
#include "CDialogDatabaseSettings.h"
#include "afxdialogex.h"
#include "SQLiteTools.h"
#include "resource.h"

// CDialogDatabaseSettings dialog

IMPLEMENT_DYNAMIC(CDialogDatabaseSettings, CDialogEx)

CDialogDatabaseSettings::CDialogDatabaseSettings(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DATABASE, pParent)
	, m_strDatabaseFile(_T(""))
{

}

CDialogDatabaseSettings::~CDialogDatabaseSettings()
{
}

void CDialogDatabaseSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DATABASE_FILE, m_strDatabaseFile);
}


BEGIN_MESSAGE_MAP(CDialogDatabaseSettings, CDialogEx)
	ON_BN_CLICKED(IDC_FOLDERS, &CDialogDatabaseSettings::OnBnClickedFolders)
	ON_BN_CLICKED(IDC_SET_DATABASE, &CDialogDatabaseSettings::OnBnClickedSetDatabase)
END_MESSAGE_MAP()


// CDialogDatabaseSettings message handlers


void CDialogDatabaseSettings::OnBnClickedFolders()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() != IDOK)
		return;

	CStringW fileName = dlg.GetPathName();
	std::wstring wfn = (LPTSTR)(LPCTSTR)fileName;

	m_strDatabaseFile = wfn.c_str();
	UpdateData(FALSE);
}


void CDialogDatabaseSettings::OnBnClickedSetDatabase()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	std::wstring filename = (LPTSTR)(LPCTSTR)m_strDatabaseFile;
	std::string fn(filename.begin(), filename.end());

	SQLiteTools tools;
	tools.CreateDatabase(fn);

	AfxMessageBox(_T("Database created OK !"));
}
