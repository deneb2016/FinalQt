
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
#include "LineEdit.h"
#include "Resource.h"
#include "FinalQtDoc.h"
#include "Global.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

enum {QT_DEFAULT, QT_CREATE_CLASS, QT_CREATE_RELATION, QT_MOVE_CLASS, QT_MOVE_RELATION, QT_MOUSELDOWN, QT_MOVE_SHAPE, QT_SELECT_MANY, QT_MOVE_ALLSHAPE, QT_SPACECLICK, QT_CREATE_RELATION_CLICKED, QT_LINE_MODIFY, QT_SPACECLICK_MOVE
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
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_CHANGESHAPE, &CFinalQtView::OnChangeshape)
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
	, m_changeLine(0)
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
	dlg.cIndex = 0;
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
		pDoc->createBox(pt, f, strClassName, strAttribute, strOperation);
		Invalidate();
	}
		//���� ���
}



//����
void CFinalQtView::OnCreateline1()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_flag = QT_CREATE_RELATION;
	m_relationType = REL_GENERALIZATION;
	m_lineType = STRAIGHT;
}


//���� ��
void CFinalQtView::OnCreateline2()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_flag = QT_CREATE_RELATION;
	m_relationType = REL_GENERALIZATION;
	m_lineType = SQUARE;
}


void CFinalQtView::createLine(CPoint pt, int lineType, int lineShape)
{
	selectedObj_key.clear();
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
		if (selectedObj_key.size() == 1)
		{
			
			std::pair<int, int> lp = pDoc->isLinePoint(point);
			if (lp.first != 0 && selectedObj_key[0] == lp.first)
			{
				m_changeLine = lp.second;
				m_flag = QT_LINE_MODIFY;
			}

			/////////////
		}
		return;		
	case QT_CREATE_RELATION:
		m_prevPt = m_ptS = point;
		selectedObj_key.clear();
		createLine(point, m_relationType, m_lineType);
		m_flag = QT_CREATE_RELATION_CLICKED;
		Invalidate();
		break;
	case QT_MOVE_CLASS:
		break;
	case QT_MOVE_RELATION:
		break;
	}
	CView::OnLButtonDown(nFlags, point);
}

inline int Qt_min(int a, int b) {
	return a < b ? a : b;
}

inline int Qt_max(int a, int b) {
	return a > b ? a : b;
}


void CFinalQtView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CFinalQtDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	switch (m_flag) {
	case QT_MOUSELDOWN: //Ŭ�� �Ǵ�
		if (!(nFlags & MK_CONTROL))//�������� ������ �� ����.
			selectedObj_key.clear();
		pushKey(m_lastSelectObj);
		m_flag = QT_DEFAULT;
		Invalidate();
		break;
	case QT_SPACECLICK_MOVE: {
		selectedObj_key.clear();
		CPoint lu;
		CPoint rd;
		lu.SetPoint(Qt_min(m_ptS.x, point.x), Qt_min(m_ptS.y, point.y));
		rd.SetPoint(Qt_max(m_ptS.x, point.x), Qt_max(m_ptS.y, point.y));
		selectedObj_key = pDoc->selectArea(lu, rd);
		m_flag = QT_DEFAULT;
		Invalidate();
		break;
	}
	case QT_SPACECLICK:
		selectedObj_key.clear();
		m_flag = QT_DEFAULT;
		Invalidate();
		break;
	case QT_CREATE_RELATION_CLICKED:
		pDoc->moveLine(key_createRelation, point, TO);
		selectedObj_key.push_back(key_createRelation);
		m_flag = QT_DEFAULT;
		Invalidate();
		break;
	case QT_LINE_MODIFY:
		pDoc->moveLine(m_lastSelectObj, point, m_changeLine);
		m_flag = QT_DEFAULT;
		Invalidate();
		break;
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
	case QT_CREATE_RELATION_CLICKED:
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
	case QT_LINE_MODIFY:
		pDoc->moveLine(m_lastSelectObj, point, m_changeLine);
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
		break;
	}
	case QT_SPACECLICK: {
		CPoint cp = point - m_ptS;
		int d = cp.x*cp.x + cp.y*cp.y;
		if (d > 5)
			m_flag = QT_SPACECLICK_MOVE;
		break;
	}
	case QT_SPACECLICK_MOVE: {
		CRect rc(m_ptS, m_prevPt);
		dc.SetROP2(R2_NOTXORPEN);
		dc.Rectangle(&rc);

		rc.SetRect(m_ptS, point);
		dc.Rectangle(&rc);
		m_prevPt = point;
	}
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


void CFinalQtView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	switch (nChar)
	{
	case VK_DELETE:
		if (m_flag == QT_DEFAULT)
		{
			CFinalQtDoc* pDoc = GetDocument();
			ASSERT_VALID(pDoc);
			if (!pDoc)
				return;
			CClientDC dc(this);
			for (auto x : selectedObj_key)
				pDoc->deleteObject(x);
			Invalidate();
		}
		break;
	case VK_F2: //����
	{
		CFinalQtDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		pDoc->copyObjects(selectedObj_key);
		break;
	}
	case VK_F3: {
		CFinalQtDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		pDoc->pasteObjects();
		Invalidate();
		break;
	}
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CFinalQtView::OnChangeshape()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (selectedObj_key.size() != 1)
	{
		MessageBox(_T("������ ������ �ϳ��� �������ּ���"));
		return;
	}

	CFinalQtDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int selType = pDoc->getShapeType(selectedObj_key[0]);
	if (selType == BOX) {
		CClassEditDlg dlg;
		CString strClassName_prev;
		CString strAttribute_prev;
		CString strOperation_prev;
		int index_prev;
		pDoc->getBoxInfo(selectedObj_key[0], index_prev, strClassName_prev, strAttribute_prev, strOperation_prev);
		dlg.m_ClassName = strClassName_prev;
		dlg.m_Attribute = strAttribute_prev;
		dlg.m_Operation = strOperation_prev;
		dlg.cIndex = index_prev;
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

			pDoc->editBox(selectedObj_key[0], f, strClassName, strAttribute, strOperation);
			Invalidate();
		}
	}
	else
	{
		CLineEdit dlg;
		std::pair<int, int> tt = pDoc->getLineInfo(selectedObj_key[0]);
		dlg.cIndex = tt.first;		
		int res = dlg.DoModal();

		if (res == IDOK) {
			//��ü ����
			int f = dlg.cIndex;
			int s = tt.second;
			//���� ���� ����
			pDoc->editLine(selectedObj_key[0], f, s);
			Invalidate();
		}
	}
}

