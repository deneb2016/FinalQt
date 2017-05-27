
// FinalQtView.cpp : CFinalQtView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "FinalQt.h"
#endif

#include "FinalQtDoc.h"
#include "FinalQtView.h"
#include "ClassEditDlg.h"
#include "Resource.h"
#include "FinalQtDoc.h"
#include "Global.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

enum {QT_DEFAULT, QT_CREATE_CLASS, QT_CREATE_RELATION, QT_MOVE_CLASS, QT_MOVE_RELATION, QT_MOUSELDOWN, QT_MOVE_SHAPE, QT_SELECT_MANY, QT_MOVE_ALLSHAPE, QT_SPACECLICK
}qt_flgtyp;
// CFinalQtView

IMPLEMENT_DYNCREATE(CFinalQtView, CView)

BEGIN_MESSAGE_MAP(CFinalQtView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFinalQtView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_CREATBOX, &CFinalQtView::OnCreatbox)
	ON_COMMAND(ID_CREATELINE1, &CFinalQtView::OnCreateline1)
	ON_COMMAND(ID_CREATELINE2, &CFinalQtView::OnCreateline2)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CFinalQtView 생성/소멸

CFinalQtView::CFinalQtView()
	: m_flag(0)
	, m_relationType(0)
	, m_lineType(0)
	, key_createRelation(0)
	, m_ptS(0)
	, m_prevPt(0)
	, m_lastSelectObj(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CFinalQtView::~CFinalQtView()
{
}

BOOL CFinalQtView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CFinalQtView 그리기

void CFinalQtView::OnDraw(CDC* pDC)
{
	CFinalQtDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CClientDC dc(this);
	pDoc->redrawAllObj(dc, selectedObj_key);
	//MessageBox(strAttribute);
};


// CFinalQtView 인쇄


void CFinalQtView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CFinalQtView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CFinalQtView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CFinalQtView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CFinalQtView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CFinalQtView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CFinalQtView 진단

#ifdef _DEBUG
void CFinalQtView::AssertValid() const
{
	CView::AssertValid();
}

void CFinalQtView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFinalQtDoc* CFinalQtView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFinalQtDoc)));
	return (CFinalQtDoc*)m_pDocument;
}
#endif //_DEBUG


// CFinalQtView 메시지 처리기


void CFinalQtView::OnCreatbox()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CClassEditDlg dlg;
	int res = dlg.DoModal();

	if (res == IDOK) {
		//객체 생성
		CString strClassName;
		CString strAttribute;
		CString strOperation;
		strClassName.Format(_T("%s"), dlg.m_ClassName);
		strAttribute.Format(_T("%s"), dlg.m_Attribute);
		strOperation.Format(_T("%s"), dlg.m_Operation);
		int f = dlg.cIndex;

		CFinalQtDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		
		CRect rect;
		GetClientRect(&rect);		
		CPoint pt;
		pt.SetPoint(rect.Width() / 2, rect.Height() / 2);
		pDoc->createBox(pt, f+1, strClassName, strAttribute, strOperation);
		Invalidate();
	}
		//생성 취소
}



//직선
void CFinalQtView::OnCreateline1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_flag = QT_CREATE_RELATION;
	m_lineType = INH;
	m_relationType = STRAIGHT;

}


//꺾인 선
void CFinalQtView::OnCreateline2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_flag = QT_CREATE_RELATION;
	m_lineType = INH;
	m_relationType = SQUARE;
}


void CFinalQtView::createLine(CPoint pt, int lineType, int lineShape)
{
	CFinalQtDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	key_createRelation = pDoc->createLine(pt, lineType, lineShape);
}

void CFinalQtView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CFinalQtDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CClientDC dc(this);
	switch (m_flag) {
	case QT_DEFAULT:
		m_prevPt = m_ptS = point;
		m_flag = QT_MOUSELDOWN;
		m_lastSelectObj = pDoc->find(point);
		/*if (m_lastSelectObj)
		{
			if (hasKey(m_lastSelectObj))
				selectedObj_key.clear();
			pushKey(m_lastSelectObj);
		}*/
		//else
		if(m_lastSelectObj < 1)
			m_flag = QT_SPACECLICK;
		return;		
	case QT_CREATE_RELATION:
		createLine(point, m_lineType, m_relationType);
		Invalidate();
		break;
	case QT_MOVE_CLASS:
		break;
	case QT_MOVE_RELATION:
		break;
	}
	CView::OnLButtonDown(nFlags, point);
}


void CFinalQtView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CFinalQtDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	switch (m_flag) {
	case QT_MOUSELDOWN:
		if (!(nFlags & MK_CONTROL))//눌려있지 않으면 다 비운다.
			selectedObj_key.clear();
		pushKey(m_lastSelectObj);
		m_flag = QT_DEFAULT;
		Invalidate();
		break;
	case QT_SPACECLICK:
		selectedObj_key.clear();
		Invalidate();
	default :
		m_flag = QT_DEFAULT;
	}
	CView::OnLButtonUp(nFlags, point);
}


void CFinalQtView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CFinalQtDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CClientDC dc(this);
	switch (m_flag) {
	case QT_DEFAULT:
		return;
	case QT_CREATE_RELATION:
		pDoc->moveLine(key_createRelation,point,TO);
		Invalidate();
		break;
	case QT_MOVE_CLASS:
		pDoc->moveObjects(point - m_prevPt, selectedObj_key);
		m_prevPt = point;
		Invalidate();
		break;
	case QT_MOVE_RELATION:
		break;
	case QT_MOVE_ALLSHAPE:
		pDoc->moveObjects(point - m_prevPt, selectedObj_key);
		m_prevPt = point;
		Invalidate();
		break;
	case QT_MOUSELDOWN:
	{
		CPoint cp = point - m_ptS;
		int d = cp.x*cp.x + cp.y*cp.y;
		if (d > 5)
		{
			//어쨌든 지금 선택한 도형이 ctrl이 안눌려있으면 현재꺼만 남아야 함
		/*	if (!(nFlags & MK_CONTROL))
			{
				selectedObj_key.clear();
				selectedObj_key.push_back(m_lastSelectObj);
			}*/
			if (!hasKey(m_lastSelectObj)) //마지막에 선택한 아이가 아직 포함 안된 아이면
			{
				if(!(nFlags & MK_CONTROL)) //컨트롤이 안눌려있으면 다 비운다
					selectedObj_key.clear();
				selectedObj_key.push_back(m_lastSelectObj);
			}
			if (selectedObj_key.size() > 1)
				m_flag = QT_MOVE_ALLSHAPE;
			else if (selectedObj_key.size() == 1)
				m_flag = QT_MOVE_CLASS;
			else
				m_flag = QT_SELECT_MANY;
		}
	}
	case QT_SELECT_MANY:

		break;
	}
	CView::OnMouseMove(nFlags, point);
}
//
//
//int key = pDoc->find(point);
//bool isSel = false;
//for (auto x : selectedObj_key)
//if (key == x)
//{
//	isSel = true;
//	break;
//}
//
////1. 이미 선택된 도형을 또 선택한 경우
//if (isSel) {
//	// - 이동의 경우 기존에 선택된 도형이 전부 이동한다.
//	// - 선택의 경우 해당 도형 하나만 선택한다.
//	// - 이동후 선택의 경우 도형 선택에 변화가 없다.
//}
//else {
//	if (key)
//	{
//		//2. 새로운 도형을 선택한 경우
//		// - 기존 도형의 선택은 모두 해제되고 새로운 도형에 대해 이동 혹은 선택을 진행한다.
//	}
//	else {
//		//3. 아무것도 선택이 아닌경우
//		//클릭이면 기존 선택이 다 삭제된다.
//		//범위 선택이면 범위 선택 함수 호출 후 선택된 도형을 업데이트 한다.
//	}
//}

void CFinalQtView::pushKey(int key)
{
	bool isInkey = false;
	for (auto x : selectedObj_key)
		if (x == key)
		{
			isInkey = true;
			break;
		}
	if (isInkey == false)
		selectedObj_key.push_back(key);
}


bool CFinalQtView::hasKey(int key)
{
	for (auto x : selectedObj_key)
		if (key == x)
			return true;
	return false;
}
