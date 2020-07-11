// Copyright (C) SAS NET Azure Rangers
// All rights reserved.

#pragma once
#include "UFMCore\Element.h"
#include "DrawingContext.h"
// CDrawingElement command target

class AFX_EXT_CLASS CLineElement : public CElement
{
//public:
//	CLineElement();
//	virtual ~CLineElement();
public:
	virtual void Draw(CDrawingContext & ctxt);
};

class AFX_EXT_CLASS CRectangleElement : public CElement
{
public:
	virtual void Draw(CDrawingContext & ctxt);
};

class AFX_EXT_CLASS CTriangleElement : public CElement
{
public:
	virtual void Draw(CDrawingContext & ctxt);
};

class AFX_EXT_CLASS CEllipseElement : public CElement
{
public:
	virtual void Draw(CDrawingContext & ctxt);
};

class AFX_EXT_CLASS CArrowRightElement : public CElement
{
public:
	virtual void Draw(CDrawingContext & ctxt);
};

class AFX_EXT_CLASS CArrowDownElement : public CElement
{
public:
	virtual void Draw(CDrawingContext & ctxt);
};

class AFX_EXT_CLASS CStarElement : public CElement
{
public:
	virtual void Draw(CDrawingContext & ctxt);
};

class AFX_EXT_CLASS CParentheseLeftElement : public CElement
{
public:
	virtual void Draw(CDrawingContext & ctxt);
};

class AFX_EXT_CLASS CParentheseRightElement : public CElement
{
public:
	virtual void Draw(CDrawingContext & ctxt);
};

class AFX_EXT_CLASS CLineBrokenElement : public CElement
{
public:
	virtual void Draw(CDrawingContext & ctxt);
};

class AFX_EXT_CLASS CDevelopmentElement : public CElement
{
public:
	virtual void Draw(CDrawingContext & ctxt);
};

class AFX_EXT_CLASS CImportElement : public CElement
{
public:
	virtual void Draw(CDrawingContext & ctxt);

public:
	std::shared_ptr<CTypeData> m_TypeData;
};

class AFX_EXT_CLASS CImageElement : public CElement
{
public:
	virtual void Draw(CDrawingContext & ctxt);
};

class AFX_EXT_CLASS CInfrastructureElement : public CElement
{
public:
	virtual void Draw(CDrawingContext & ctxt);
};

class AFX_EXT_CLASS CTextElement : public CElement
{
public:
	virtual void Draw(CDrawingContext & ctxt);
};

class AFX_EXT_CLASS CSimpleTextElement : public CElement
{
public:
	virtual void Draw(CDrawingContext & ctxt);
};

class AFX_EXT_CLASS CNotImplementedElement : public CElement
{
public:
	virtual void Draw(CDrawingContext & ctxt);
};

class AFX_EXT_CLASS CConnectableElement : public CElement
{
public:
};

class AFX_EXT_CLASS CSelectionElement : public CElement
{
public:
	virtual void Draw(CDrawingContext& ctxt);
};

class AFX_EXT_CLASS CPlanningElement : public CElement
{
public:
	virtual void Draw(CDrawingContext& ctxt);
};

class AFX_EXT_CLASS CDiagramElement : public CElement
{
public:
	virtual void Draw(CDrawingContext& ctxt);
};

class AFX_EXT_CLASS CCourbe1Element : public CElement
{
public:
	virtual void Draw(CDrawingContext& ctxt);
};

class AFX_EXT_CLASS CCourbe2Element : public CElement
{
public:
	virtual void Draw(CDrawingContext& ctxt);
};

class AFX_EXT_CLASS CCurveElement : public CElement
{
public:
	virtual void Draw(CDrawingContext& ctxt);
};

class AFX_EXT_CLASS CPatateElement : public CElement
{
public:
	virtual void Draw(CDrawingContext& ctxt);
};

class AFX_EXT_CLASS CCurveFuzzyElement : public CElement
{
public:
	virtual void Draw(CDrawingContext& ctxt);
};

class AFX_EXT_CLASS CBasicRectangleElement : public CElement
{
public:
	virtual void Draw(CDrawingContext& ctxt);
};

class AFX_EXT_CLASS CBasicRectangle2Element : public CElement
{
public:
	virtual void Draw(CDrawingContext& ctxt);
};

class AFX_EXT_CLASS CBasicRectangle3Element : public CElement
{
public:
	virtual void Draw(CDrawingContext& ctxt);
};

class AFX_EXT_CLASS CBasicLosangeElement : public CElement
{
public:
	virtual void Draw(CDrawingContext& ctxt);
};

class AFX_EXT_CLASS CBasicRoundRectangleElement : public CElement
{
public:
	virtual void Draw(CDrawingContext& ctxt);
};

class AFX_EXT_CLASS CBasicDatabaseElement : public CElement
{
public:
	virtual void Draw(CDrawingContext& ctxt);
};

class AFX_EXT_CLASS CAdvancedTextElement : public CElement
{
public:
	virtual void Draw(CDrawingContext& ctxt);
};

class AFX_EXT_CLASS CConnectorUpElement : public CElement
{
public:
	virtual void Draw(CDrawingContext& ctxt);
};

class AFX_EXT_CLASS CConnectorDownElement : public CElement
{
public:
	virtual void Draw(CDrawingContext& ctxt);
};

class AFX_EXT_CLASS CConnectorLeftElement : public CElement
{
public:
	virtual void Draw(CDrawingContext& ctxt);
};

class AFX_EXT_CLASS CConnectorRightElement : public CElement
{
public:
	virtual void Draw(CDrawingContext& ctxt);
};

class AFX_EXT_CLASS CConnectorSingleLeftElement : public CElement
{
public:
	virtual void Draw(CDrawingContext& ctxt);
};

class AFX_EXT_CLASS CConnectorSingleRightElement : public CElement
{
public:
	virtual void Draw(CDrawingContext& ctxt);
};

