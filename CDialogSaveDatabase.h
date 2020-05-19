#pragma once


// CDialogSaveDatabase dialog

class CDialogSaveDatabase : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogSaveDatabase)

public:
	CDialogSaveDatabase(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDialogSaveDatabase();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SAVE_DATABASE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_strDiagramName;
};
