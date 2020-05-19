#pragma once


// CDialogLoadDatabase dialog

class SQLiteDiagramEntity;

class CDialogLoadDatabase : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogLoadDatabase)

public:
	CDialogLoadDatabase(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDialogLoadDatabase();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOAD_DATABASE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	vector<shared_ptr<SQLiteDiagramEntity>> m_vDiagrams;

public:
	CListCtrl m_lstReportDiagram;
	virtual BOOL OnInitDialog();
};
