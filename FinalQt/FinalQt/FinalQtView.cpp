
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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
	ON_COMMAND(ID_CREATERELATION, &CFinalQtView::OnCreaterelation)
	ON_COMMAND(ID_CREATELINE1, &CFinalQtView::OnCreateline1)
	ON_COMMAND(ID_CREATELINE2, &CFinalQtView::OnCreateline2)
END_MESSAGE_MAP()

// CFinalQtView 생성/소멸

CFinalQtView::CFinalQtView()
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
	//pDoc->redrawAllObj(dc, selectedObj_key);
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


void CFinalQtView::OnCreaterelation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

}



//직선
void CFinalQtView::OnCreateline1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

}


//꺾인 선
void CFinalQtView::OnCreateline2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

}


void CFinalQtView::createLine(CPoint pt, int lineType, int lineShape)
{
	CFinalQtDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->createLine(pt, lineType, lineShape);
}
