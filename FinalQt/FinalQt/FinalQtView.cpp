
// FinalQtView.cpp : CFinalQtView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
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

// CFinalQtView ����/�Ҹ�

CFinalQtView::CFinalQtView()
	: m_flag(0)
	, m_relationType(0)
	, m_lineType(0)
	, key_createRelation(0)
	, m_ptS(0)
	, m_prevPt(0)
	, m_lastSelectObj(0)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CFinalQtView::~CFinalQtView()
{
}

BOOL CFinalQtView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CFinalQtView �׸���

void CFinalQtView::OnDraw(CDC* pDC)
{
	CFinalQtDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	CClientDC dc(this);
	pDoc->redrawAllObj(dc, selectedObj_key);
	//MessageBox(strAttribute);
};


// CFinalQtView �μ�


void CFinalQtView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CFinalQtView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CFinalQtView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CFinalQtView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
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


// CFinalQtView ����

#ifdef _DEBUG
void CFinalQtView::AssertValid() const
{
	CView::AssertValid();
}

void CFinalQtView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFinalQtDoc* CFinalQtView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFinalQtDoc)));
	return (CFinalQtDoc*)m_pDocument;
}
#endif //_DEBUG


// CFinalQtView �޽��� ó����


void CFinalQtView::OnCreatbox()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CClassEditDlg dlg;
	int res = dlg.DoModal();

	if (res == IDOK) {
		//��ü ����
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
		//���� ���
}



//����
void CFinalQtView::OnCreateline1()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_flag = QT_CREATE_RELATION;
	m_lineType = INH;
	m_relationType = STRAIGHT;

}


//���� ��
void CFinalQtView::OnCreateline2()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CFinalQtDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	switch (m_flag) {
	case QT_MOUSELDOWN:
		if (!(nFlags & MK_CONTROL))//�������� ������ �� ����.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
			//��·�� ���� ������ ������ ctrl�� �ȴ��������� ���粨�� ���ƾ� ��
		/*	if (!(nFlags & MK_CONTROL))
			{
				selectedObj_key.clear();
				selectedObj_key.push_back(m_lastSelectObj);
			}*/
			if (!hasKey(m_lastSelectObj)) //�������� ������ ���̰� ���� ���� �ȵ� ���̸�
			{
				if(!(nFlags & MK_CONTROL)) //��Ʈ���� �ȴ��������� �� ����
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
////1. �̹� ���õ� ������ �� ������ ���
//if (isSel) {
//	// - �̵��� ��� ������ ���õ� ������ ���� �̵��Ѵ�.
//	// - ������ ��� �ش� ���� �ϳ��� �����Ѵ�.
//	// - �̵��� ������ ��� ���� ���ÿ� ��ȭ�� ����.
//}
//else {
//	if (key)
//	{
//		//2. ���ο� ������ ������ ���
//		// - ���� ������ ������ ��� �����ǰ� ���ο� ������ ���� �̵� Ȥ�� ������ �����Ѵ�.
//	}
//	else {
//		//3. �ƹ��͵� ������ �ƴѰ��
//		//Ŭ���̸� ���� ������ �� �����ȴ�.
//		//���� �����̸� ���� ���� �Լ� ȣ�� �� ���õ� ������ ������Ʈ �Ѵ�.
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
