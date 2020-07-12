// Copyright (C) SAS NET Azure Rangers
// All rights reserved.

#pragma once

#include "SharedViews\Constants.h"
#include "CTextControlDialog.h"

enum SelectType : int
{
	intuitive,
	all,
	only_first_line,
	only_lines,
	only_items
};

enum SelectMode : int
{
	none,
	netselect,
	move,
	size,
};

enum ElementType : int
{
	type_unknown, 
	type_select, 
	type_shapes_simple, 
	type_image, 
	type_shapes_infrastructure, 
	type_text, 
	type_shapes_development,
	type_shapes_import,
	type_shapes_planning,
	type_selection,
	type_connection,
	type_file,
	type_connector
};

#define OffsetShapes_Simple			0
#define OffsetShapes_Image			60
#define OffsetShapes_Infrastructure 100
#define OffsetShapes_Text			200
#define OffsetShapes_Development	300
#define OffsetShapes_Import			400
#define OffsetShapes_Planning		500
#define OffsetShapes_Connectors		520

enum ShapeType : int 
{
	// Simple
	line = OffsetShapes_Simple,
	line_right,
	rectangle,
	ellipse,
	rectangle_round,
	triangle,
	line_broken,
	line_broken_right,
	notimp_igloo,
	notimpl_multi_line,
	arrow_right,
	arrow_down,
	courbe1,
	courbe2,
	parenthese_left,
	parenthese_right,
	star,
	line2 = 18,
	line_right2,
	line_left_right,
	line_broken2,
	line_broken_right2,
	line_broken_left_right,
	curve,
	curve_right,
	curve_left_right,
	courbe2_bis,
	patate,
	curve_fuzzy,
	basic_rectangle,
	basic_round_rectangle,
	basic_losange,
	basic_rectangle2,
	process_1,
	process_2,
	process_3,
	round_circle1,
	round_circle2,
	rectangle_2,
	circle1,
	basic_rectangle3,
	basic_folder,
	basic_file, 
	circle2,
	circle3,
	losange2,
	losange3,
	triangle1,
	triangle2,
	process_4,
	UnD,
	UnQ,
	basic_database,
	basic_database2,
	rectangle4,
	// Image
	image_fixed = OffsetShapes_Image,
	image_scaled,
	// Infrastructure
	infrastructure_server_ad = OffsetShapes_Infrastructure,
	infrastructure_server,
	infrastructure_server_web,
	infrastructure_server_database,
	infrastructure_workstation,
	infrastructure_laptop,
	infrastructure_firewall,
	infrastructure_network,
	infrastructure_virtual_server,
	infrastructure_virtual_server_web,
	infrastructure_virtual_server_database,
	infrastructure_virtualization_server,
	infrastructure_server_ad_grey,
	infrastructure_server_grey,
	infrastructure_server_database_grey,
	infrastructure_server_farm,
	infrastructure_workstation_grey,
	infrastructure_laptop_grey,
	// Text
	text = OffsetShapes_Text,
	text_left,
	text_center,
	text_right,
	text_justify,
	// Development
	development_class = OffsetShapes_Development,
	development_interface,
	development_enumeration,
	development_package,
	development_comment,
	development_component,
	development_association,
	development_aggregation,
	development_composition,
	development_dependency,
	development_inheritance,
	development_package_import,
	development_connector,
	import_class = OffsetShapes_Import,
	planning_month = OffsetShapes_Planning,
	planning_task,
	selection,
	connection,
	diagram,
	connector_up = OffsetShapes_Connectors,
	connector_down,
	connector_left,
	connector_right,
	connector_single_left,
	connector_single_right,
	unknown = 1000
};

enum TrackerState 
{ 
	normal, 
	selected, 
	active 
};

enum DocumentType : int
{
	document_none,
	document_file,
	document_folder,
	document_diagram
};

enum ConnectorType : int
{
	connector1,
	connector2
};

enum DashLineType : int
{
	dash_solid,
	dash_dash,
	dash_dot,
	dash_dashdot,
	dash_dashdotdot
};

enum ArrowType : int
{
	arrow_none,
	arrow_left,
	arrow_right2,
	arrow_left_right
};

// Hints for UpdateAllViews/OnUpdate
#define HINT_UPDATE_WINDOW      0
#define HINT_UPDATE_DRAWOBJ     1
#define HINT_UPDATE_SELECTION   2
#define HINT_DELETE_SELECTION   3
#define HINT_UPDATE_OLE_ITEMS   4

class CShapeType
{
	public:
		static ShapeType ToShapeType(int value);
};

class CElement;
class CModeler1View;
class CElementManager;
class CDrawingContext;
class CElementGroup;
class CConnector;
class CCharElement;

class AFX_EXT_CLASS CElement : public CObject
{
public:
	DECLARE_SERIAL(CElement);
	CElement();
	CElement(const CElement& element);
	virtual ~CElement(void);

// Internal ID is a GUID
	static int m_counter;
	void SetGuid();
	void SetName();

// Copy an object
	std::shared_ptr<CElement> MakeCopy();

// Virtual Operations
public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual void Draw(CModeler1View * pView, CDC* pDC);
	virtual void Draw(CDrawingContext & ctxt);
	static shared_ptr<CElement> FromJSON(const web::json::object& object);
	web::json::value CElement::AsJSON() const;


// Operations
public:
	static CString ToString(shared_ptr<CElement> pElement);
	CString ToString();
	CString ToString(ElementType type);
	CString ToString(ShapeType type);
	static CString static_ToString(ShapeType type);
	static ElementType From(ShapeType type);
	CString ToString(shared_ptr<CConnector> pConnector);
	CString ToString(DocumentType type);
	CString ToString(DashLineType type);
	CString ToString(ArrowType type);
	DocumentType FromString(wstring type);
	DashLineType CElement::FromStringEx(wstring type);
	ArrowType FromStringEx2(wstring type);
	CString DragHandleToString(int nHandle);
	int DragHandleFromString(wstring value);
	//static bool IsDrawable(ElementType type);
	bool Intersects(const CRect& rect);
	void InvalidateObj(void);
	void CheckForKeepingAMinimumSize();
	void BuildPen(Pen& pen);
	void BuildPenEx(Pen& pen);

// Managing/Viewing Object Selection & Tracker helpers
public:
	int GetHandleCount();
	int HitTest(CPoint point, CModeler1View* pView, bool bSelected);
	CRect GetHandleRect(int nHandleID, CModeler1View* pView);
	CPoint GetHandle(int nHandle);
	void DrawTracker(CDrawingContext & ctxt, TrackerState state);
	HCURSOR GetHandleCursor(int nHandle);
	void MoveHandleTo(int nHandle, CPoint point, CModeler1View* pView);	
	void DrawTracker(CPoint cnx, CDrawingContext& ctxt, CModeler1View* pView);
	void DrawTracker(CModeler1View* pView);
	CRect GetRectTextConnector(ConnectorType connector);

// Managing Object Format
public:
	virtual bool CanChangeFillColor() const;
	virtual bool CanChangeLineColor() const;
	virtual bool CanChangeLineWidth() const;

// Text
public:
	void BuildVChar();

// Attributes
public:
	std::wstring m_name;
	ElementType m_type;
	ShapeType m_shapeType;
	std::wstring m_objectId;
	std::wstring m_caption;
	std::wstring m_text;
	std::wstring m_textConnector1;
	std::wstring m_textConnector2;
	std::wstring m_code;
	std::wstring m_textAlign;
	std::wstring m_fontName;
	int m_fontSize;
	bool m_bBold;
	bool m_bItalic;
	bool m_bUnderline;
	bool m_bStrikeThrough;
	CRect m_rect;
	CPoint m_point;
	CPoint m_last;
	COLORREF m_colorText;
	COLORREF m_colorFill;
	bool m_bColorFill;
	COLORREF m_colorLine;
	bool m_bSolidColorFill;
	bool m_bColorLine;
	int m_lineWidth;
	bool m_bLineWidth;
	std::wstring m_image;
	bool m_bFixed;
	// Handling Moving stuff
	bool m_bMoving;
	// Connectivity
	CElementManager * m_pManager;
	CModeler1View * m_pView;
	// Grouping
	shared_ptr<CElementGroup> m_pElementGroup;
	bool m_bGrouping;
	shared_ptr<CConnector> m_pConnector;
	std::wstring m_connectorName1;
	std::wstring m_connectorName2;
	int m_connectorDragHandle1;
	int m_connectorDragHandle2;
	std::wstring m_document;
	static std::wstring m_elementGroupNames;
	static std::wstring m_elementGroupElements;
	DocumentType m_documentType;
	std::wstring m_documentTypeText;
	std::wstring m_version;
	std::wstring m_product;
	int m_leftMargin;
	int m_topMargin;
	int m_rotateAngle;
	static std::wstring m_team;
	static std::wstring m_authors;
	static bool m_bShowElementName;
	static COLORREF m_standardShapesTextColor;
	static COLORREF m_connectorShapesTextColor;
	static bool m_bShowConnectors;
	DashLineType m_dashLineType;
	ArrowType m_arrowType;

	// Drawing Text feature
	bool m_bDrawCaret = false;
	//CBitmap m_bmpCaret;
	//bool m_bCaretCreated = false;
	//vector<char> m_vChar;
	vector<shared_ptr<CCharElement>> m_vCharElement;
	PointF m_lastCaretPoint;
	PointF m_pointF;

// Methods for Attributes
public:
	bool IsLine();
	bool IsText();
	std::wstring GetImageFilePath();
	bool HasColorFill()	const { return m_bColorFill; }
	bool IsSolidColorFill()	const { return m_bSolidColorFill; }
	bool HasColorLine()	const { return m_bColorLine; }
	bool IsFixed() const{ return m_bFixed; }

// Extra Pointer plumbing
public:
	CElementManager * GetManager() const { return m_pManager; }
	CModeler1View * GetView() const	{ return m_pView; }
};

class AFX_EXT_CLASS CCharElement
{
public:
	char m_char;
	RectF m_rectf;
};

class AFX_EXT_CLASS CConnector
{
public:
	std::shared_ptr<CElement> m_pElement1;
	std::shared_ptr<CElement> m_pElement2;
};

class AFX_EXT_CLASS CElementGroup
{
public:
	std::wstring m_name;
	std::vector<std::shared_ptr<CElement>> m_Groups;
};

void CallDraw(CDrawingContext & ctxt, std::shared_ptr<CElement> pElement);

class AFX_EXT_CLASS CMethodData
{
public:
	bool m_IsPublic;
	std::wstring m_Name;
};

class AFX_EXT_CLASS CFieldData
{
public:
	bool m_IsPublic;
	std::wstring m_Type;
	std::wstring m_Name;
};

class AFX_EXT_CLASS CPropertyData
{
public:
	std::wstring m_Type;
	std::wstring m_Name;
};

class AFX_EXT_CLASS CTypeData
{
public:
	std::wstring m_Name;
	std::wstring m_FullName;
	std::vector<std::shared_ptr<CMethodData>> m_Methods;
	std::vector<std::shared_ptr<CFieldData>> m_Fields;
	std::vector<std::shared_ptr<CPropertyData>> m_Properties;
};



