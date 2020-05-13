// CTextControlDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "CTextControlDialog.h"
#include "Element.h"
#include "ElementManager.h"
#include "afxdialogex.h"
#include "resource.h"

// CTextControlDialog dialog

IMPLEMENT_DYNAMIC(CTextControlDialog, CDialogEx)

CTextControlDialog::CTextControlDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TEXT, pParent)
{

}

CTextControlDialog::~CTextControlDialog()
{
}

void CTextControlDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXT, m_Text);
}


BEGIN_MESSAGE_MAP(CTextControlDialog, CDialogEx)
    ON_BN_CLICKED(IDOK, &CTextControlDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTextControlDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// CTextControlDialog message handlers


void CTextControlDialog::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString data;
	m_Text.GetWindowText(data);

	m_pElement->m_text = (LPTSTR)(LPCTSTR)data;
	ShowWindow(SW_HIDE);
	m_pElement->GetManager()->Invalidate(m_pElement->m_pView);
    //CDialogEx::OnOK();
}


void CTextControlDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
	//CDialogEx::OnCancel();
}
