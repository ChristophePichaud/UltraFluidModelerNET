// CDialogDatabaseSearch.cpp : implementation file
//

#include "pch.h"
#include "SharedViews\Dialogs\CDialogDatabaseSearch.h"
#include "resource.h"

// CDialogDatabaseSearch dialog

IMPLEMENT_DYNAMIC(CDialogDatabaseSearch, CDialogEx)

CDialogDatabaseSearch::CDialogDatabaseSearch(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CDialogDatabaseSearch, pParent)
{

}

CDialogDatabaseSearch::~CDialogDatabaseSearch()
{
}

void CDialogDatabaseSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogDatabaseSearch, CDialogEx)
END_MESSAGE_MAP()


// CDialogDatabaseSearch message handlers
