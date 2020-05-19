// CDialogDatabaseSettings.cpp : implementation file
//

#include "StdAfx.h"
#include "CDialogDatabaseSettings.h"
#include "afxdialogex.h"
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
}


void CDialogDatabaseSettings::OnBnClickedSetDatabase()
{
	// TODO: Add your control notification handler code here
}
