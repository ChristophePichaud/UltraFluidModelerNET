// Copyright (C) SAS NET Azure Rangers
// All rights reserved.

// Modeler1Doc.cpp : implementation of the CModeler1Doc class
//

#include "pch.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "UFMCore\Modeler1.h"
#endif
#include "UFMCore\Modeler1Doc.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CModeler1Doc

IMPLEMENT_DYNCREATE(CModeler1Doc, CDocument)

BEGIN_MESSAGE_MAP(CModeler1Doc, CDocument)
END_MESSAGE_MAP()


// CModeler1Doc construction/destruction

CModeler1Doc::CModeler1Doc()
{
	// TODO: add one-time construction code here
	m_pManager = new CElementManager();
}

CModeler1Doc::~CModeler1Doc()
{
}

BOOL CModeler1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	//CFactory::g_counter = 0;

	return TRUE;
}

// CModeler1Doc serialization

void CModeler1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
	GetManager()->Serialize(ar);
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CModeler1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CModeler1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CModeler1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CModeler1Doc diagnostics

#ifdef _DEBUG
void CModeler1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CModeler1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CModeler1Doc commands
