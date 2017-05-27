
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
#include <algorithm>
using namespace std;
void CFinalQtDoc::createBox(CPoint pt, int steroType, CString name, CString attribute, CString operation)
{
	QtShape* newBox = new QtBox(pt, steroType, name, attribute, operation);
	boxList.push_back((QtBox*)newBox);
	boxHash[newBox->getKey()] =  (QtBox*)newBox;
}

void CFinalQtDoc::createLine(CPoint pt, int lineType, int lineShape)
{
}

void CFinalQtDoc::deleteObject(int key)
{
	QtShape* target = NULL;
	if (boxHash.find(key) != boxHash.end())
	{
		boxHash.erase(key);
		for (auto iter = boxList.begin(); iter != boxList.end(); ++iter)
		{
			target = *iter;
			if (target->getKey() == key) {
				boxList.erase(iter);
				break;
			}
		}
	}
	else if (lineHash.find(key) != lineHash.end())
	{
		lineHash.erase(key);
		for (auto iter = lineList.begin(); iter != lineList.end(); ++iter)
		{
			target = *iter;
			if (target->getKey() == key) {
				lineList.erase(iter);
				break;
			}
		}
	}
	else {
		abort();
	}
}

int CFinalQtDoc::find(CPoint pt)
{
	for (int i = lineList.size(); i >= 0; --i) {
		QtShape* here = lineList[i];
		if (here->select(pt))
			return here->getKey();
	}
	for (int i = boxList.size(); i >= 0; --i) {
		QtShape* here = boxList[i];
		if (here->select(pt))
			return here->getKey();
	}
	return 0;
}
void CFinalQtDoc::redrawAllObj(CClientDC& dc, std::vector<int> selected)
{
	sort(selected.begin(), selected.end());
	for (int i = 0; i < boxList.size(); ++i)
	{
		QtShape* here = boxList[i];
		bool flag = binary_search(selected.begin(), selected.end(), here->getKey());
		here->redraw(dc, flag);
	}
	for (int i = 0; i < lineList.size(); ++i)
	{
		QtShape* here = lineList[i];
		bool flag = binary_search(selected.begin(), selected.end(), here->getKey());
		here->redraw(dc, flag);
	}
}
int CFinalQtDoc::getShapeType(int key) 
{
	if (lineHash.find(key) != lineHash.end())
		return LINE;
	if (boxHash.find(key) != boxHash.end())
		return BOX;
	return 0;
}
vector<CString> CFinalQtDoc::getBoxInfo(int key)
{
	vector<CString> ret;
	QtBox* here = 0;
	auto iter = boxHash.find(key);
	if (iter != boxHash.end())
	{
		here = iter->second;
		//dddsf
	}
	return ret;
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


