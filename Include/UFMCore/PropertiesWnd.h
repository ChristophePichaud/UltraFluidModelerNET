// Copyright (C) SAS NET Azure Rangers
// All rights reserved.

#pragma once
#include "Element.h"

class CMFCPropertyGridCtrl2 : public CMFCPropertyGridCtrl
{
public:
	CFont m_font;
	void Init()
	{
		m_font.CreateFont(
			12,                       // nHeight
			0,                        // nWidth
			0,                        // nEscapement
			0,                        // nOrientation
			FW_NORMAL,                // nWeight
			FALSE,                    // bItalic
			FALSE,                    // bUnderline
			0,                        // cStrikeOut
			ANSI_CHARSET,             // nCharSet
			OUT_DEFAULT_PRECIS,       // nOutPrecision
			CLIP_DEFAULT_PRECIS,      // nClipPrecision
			DEFAULT_QUALITY,          // nQuality
			DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
			_T("Segoe UI"));
		this->OnSetFont(&m_font, TRUE);
	}
}; 

class AFX_EXT_CLASS CPropertiesToolBar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class AFX_EXT_CLASS CPropertiesWnd : public CDockablePane
{
// Construction
public:
	CPropertiesWnd();

	void AdjustLayout();

// Attributes
public:
	void SetVSDotNetLook(BOOL bSet)
	{
		m_wndPropList.SetVSDotNetLook(bSet);
		m_wndPropList.SetGroupNameFullWidth(bSet);
	}
	
	CElementManager * m_pManager;
	CElementManager * GetManager() const
	{
		return m_pManager;
	}

protected:
	CFont m_fntPropList;
	CComboBox m_wndObjectCombo;
	CPropertiesToolBar m_wndToolBar;
	CMFCPropertyGridCtrl m_wndPropList;
	//CMFCPropertyGridCtrl2 m_wndPropList;

// Implementation
public:
	virtual ~CPropertiesWnd();
	void SetManager(CElementManager * pManager);
	void UpdateProperties(std::shared_ptr<CElement> pObj);
	void UpdateProperty(std::wstring strNameToFind, COleVariant vNewValue);
	BOOL GetProperty(std::wstring name, std::wstring & value);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnExpandAllProperties();
	afx_msg void OnUpdateExpandAllProperties(CCmdUI* pCmdUI);
	afx_msg void OnSortProperties();
	afx_msg void OnUpdateSortProperties(CCmdUI* pCmdUI);
	afx_msg void OnProperties1();
	afx_msg void OnUpdateProperties1(CCmdUI* pCmdUI);
	afx_msg void OnProperties2();
	afx_msg void OnUpdateProperties2(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg LRESULT OnPropertyChanged(WPARAM,LPARAM);

	DECLARE_MESSAGE_MAP()

	void InitPropList();
	void SetPropListFont();
};

