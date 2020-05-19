// CDialogLoadDatabase.cpp : implementation file
//

#include "StdAfx.h"
#include "CDialogLoadDatabase.h"
#include "afxdialogex.h"
#include "resource.h"
#include "SQLiteTools.h"


// CDialogLoadDatabase dialog

IMPLEMENT_DYNAMIC(CDialogLoadDatabase, CDialogEx)

CDialogLoadDatabase::CDialogLoadDatabase(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOAD_DATABASE, pParent)
{

}

CDialogLoadDatabase::~CDialogLoadDatabase()
{
}

void CDialogLoadDatabase::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DIAGRAM, m_lstReportDiagram);
}


BEGIN_MESSAGE_MAP(CDialogLoadDatabase, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogLoadDatabase::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogLoadDatabase message handlers


BOOL CDialogLoadDatabase::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	UpdateData(TRUE);
	// Columns
	m_lstReportDiagram.InsertColumn(0, _T("FileName"), LVCFMT_LEFT, 300, -1);
	m_lstReportDiagram.InsertColumn(1, _T("Time"), LVCFMT_LEFT, 120, -1);
	m_lstReportDiagram.InsertColumn(2, _T("ID"), LVCFMT_LEFT, 35, -1);


	// open database
	SQLite::Database db;
	string dbName = UFM_SQLITE_DATABASE;
	db.SetDatabaseName(dbName);
	if (!db.OpenEx(UFM_SQLITE_USER, UFM_SQLITE_PASSWORD))
		return FALSE;

	db.SetBusyTimeout(100000);

	// store to db
	SQLiteDiagramEntity diagramEntity(&db);
	vector<shared_ptr<SQLiteDiagramEntity>> vDiagrams = diagramEntity.SelectAll();
	db.Close();

	m_vDiagrams = vDiagrams;


	wstringstream buff;
	int count = 0;
	for (shared_ptr<SQLiteDiagramEntity> sde : vDiagrams)
	{
		wstring lu(sde->LastUpdate.begin(), sde->LastUpdate.end());
		wstring fn(sde->FileName.begin(), sde->FileName.end());
		buff << _T("Id:") << sde->DiagramPK << _T(", LastUpdate:") << lu << _T(", FileName:") << fn << _T("\n");

		m_lstReportDiagram.InsertItem(count, fn.c_str());
		m_lstReportDiagram.SetItemText(count, 1, lu.c_str());
		m_lstReportDiagram.SetItemText(count, 2, to_wstring(sde->DiagramPK).c_str());
		count++;
	}

	std::wstring str = buff.str();
	//AfxMessageBox(str.c_str());

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CDialogLoadDatabase::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int uSelectedCount = m_lstReportDiagram.GetSelectedCount();
	if (uSelectedCount == 0)
	{
		AfxMessageBox(_T("Select a Diagram..."));
		return;
	}

	int  nItem = -1;
	// Get Cmd
	nItem = m_lstReportDiagram.GetNextItem(nItem, LVNI_SELECTED);
	CString str = m_lstReportDiagram.GetItemText(nItem, 0);
	//AfxMessageBox(str);

	m_diagramName = (LPTSTR)(LPCTSTR)str;

	CDialogEx::OnOK();
}
