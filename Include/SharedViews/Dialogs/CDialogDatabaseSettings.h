#pragma once


// CDialogDatabaseSettings dialog

class AFX_EXT_CLASS CDialogDatabaseSettings : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogDatabaseSettings)

public:
	CDialogDatabaseSettings(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDialogDatabaseSettings();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DATABASE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_strDatabaseFile;
	afx_msg void OnBnClickedFolders();
	afx_msg void OnBnClickedSetDatabase();
};
