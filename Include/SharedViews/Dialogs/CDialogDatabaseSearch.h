#pragma once


// CDialogDatabaseSearch dialog

class AFX_EXT_CLASS CDialogDatabaseSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogDatabaseSearch)

public:
	CDialogDatabaseSearch(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDialogDatabaseSearch();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDialogDatabaseSearch };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
