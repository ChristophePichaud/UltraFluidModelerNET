// CDialogSaveDatabase.cpp : implementation file
//

#include "StdAfx.h"
#include "CDialogSaveDatabase.h"
#include "afxdialogex.h"
#include "resource.h"


// CDialogSaveDatabase dialog

IMPLEMENT_DYNAMIC(CDialogSaveDatabase, CDialogEx)

CDialogSaveDatabase::CDialogSaveDatabase(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SAVE_DATABASE, pParent)
	, m_strDiagramName(_T(""))
{

}

CDialogSaveDatabase::~CDialogSaveDatabase()
{
}

void CDialogSaveDatabase::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DIAGRAM_NAME, m_strDiagramName);
}


BEGIN_MESSAGE_MAP(CDialogSaveDatabase, CDialogEx)
END_MESSAGE_MAP()


// CDialogSaveDatabase message handlers
