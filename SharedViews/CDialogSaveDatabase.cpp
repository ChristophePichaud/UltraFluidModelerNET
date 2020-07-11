// CDialogSaveDatabase.cpp : implementation file
//

#include "pch.h"
#include "SharedViews\Dialogs\CDialogSaveDatabase.h"
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


BOOL CDialogSaveDatabase::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
