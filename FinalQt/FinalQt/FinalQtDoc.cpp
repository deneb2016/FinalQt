
// FinalQtDoc.cpp : CFinalQtDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "FinalQt.h"
#endif

#include "FinalQtDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFinalQtDoc

IMPLEMENT_DYNCREATE(CFinalQtDoc, CDocument)

BEGIN_MESSAGE_MAP(CFinalQtDoc, CDocument)
END_MESSAGE_MAP()


// CFinalQtDoc ����/�Ҹ�

CFinalQtDoc::CFinalQtDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
	
}

CFinalQtDoc::~CFinalQtDoc()
{
}

BOOL CFinalQtDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CFinalQtDoc serialization

void CFinalQtDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CFinalQtDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
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

// �˻� ó���⸦ �����մϴ�.
void CFinalQtDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CFinalQtDoc::SetSearchContent(const CString& value)
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

// CFinalQtDoc ����

#ifdef _DEBUG
void CFinalQtDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFinalQtDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CFinalQtDoc ���




/* ������� ���� */
#include "QtShape.h"
#include "QtLine.h"
#include "QtBox.h"
using namespace std;
void CFinalQtDoc::createBox(CString name, CString attribute, CString operation, CPoint pt)
{

}

void CFinalQtDoc::createLine(CPoint pt, int lineType, int lineShape)
{

}

void CFinalQtDoc::deleteObject(int key)
{

}

int CFinalQtDoc::find(CPoint pt)
{
	return 0;

}
void CFinalQtDoc::redrawAllObj(const CClientDC& dc, std::vector<int> selected)
{

}
int CFinalQtDoc::getShapeType(int key) 
{
	int ret = -1;
	return ret;
}
vector<CString> CFinalQtDoc::getBoxInfo(int key)
{
	vector<CString> ret;
	return ret;

}
int CFinalQtDoc::getRectangle(CPoint pt)
{
	return 0;

}
void CFinalQtDoc::moveObjects(CPoint pt, std::vector<int> key)
{

}
void CFinalQtDoc::editBox(int key, const std::vector<CString>& infi)
{

}
vector<int> CFinalQtDoc::selectArea(CPoint lu, CPoint rd)
{
	vector<int> ret;
	return ret;
}
pair<int, int> CFinalQtDoc::isLinePoint(CPoint pt)
{
	pair<int, int> ret(0, 0);
	return ret;
}
void CFinalQtDoc::moveLine(int key, CPoint vec, int flag)
{

}
void CFinalQtDoc::save(CString filename)
{

}
void CFinalQtDoc::load(CString filename)
{

}


