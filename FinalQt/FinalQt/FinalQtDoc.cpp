
// FinalQtDoc.cpp : CFinalQtDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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



#include "QtShape.h"
#include "QtLine.h"
#include "QtBox.h"
#include <algorithm>
// CFinalQtDoc 생성/소멸

CFinalQtDoc::CFinalQtDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	
}

CFinalQtDoc::~CFinalQtDoc()
{
}

BOOL CFinalQtDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CFinalQtDoc serialization

void CFinalQtDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
		ar << QtShape::nextKey << boxList.size() << lineList.size();
		for (int i = 0; i < boxList.size(); ++i)
		{
			boxList[i]->save(ar);
		}
		for (int i = 0; i < lineList.size(); ++i)
		{
			lineList[i]->save(ar);
		}
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
		int bc, nc;
		ar >> QtShape::nextKey >> bc >> nc;
		for (int i = 0; i < bc; ++i)
		{
			QtBox* box = new QtBox();
			box->load(ar);
			boxList.push_back(box);
			boxHash[box->getKey()] = box;
		}
		for (int i = 0; i < nc; ++i)
		{
			QtLine* line = new QtLine();
			line->load(ar);
			line->m_pboxStart = boxHash[(int)(line->m_pboxStart)];
			line->m_pboxEnd = boxHash[(int)(line->m_pboxEnd)];
			lineList.push_back(line);
			lineHash[line->getKey()] = line;
		}
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CFinalQtDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
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

// 검색 처리기를 지원합니다.
void CFinalQtDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CFinalQtDoc 진단

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


// CFinalQtDoc 명령




/* 여기부터 내꺼 */
using namespace std;
void CFinalQtDoc::createBox(CPoint pt, int steroType, CString name, CString attribute, CString operation)
{
	QtShape* newBox = new QtBox(pt, steroType, name, attribute, operation);
	boxList.push_back((QtBox*)newBox);
	boxHash[newBox->getKey()] =  (QtBox*)newBox;
}

int CFinalQtDoc::createLine(CPoint pt, int lineType, int lineShape)
{
	QtLine* newLine = NULL;
	for (int i = 0; i < boxList.size(); ++i)
	{
		QtBox* here = boxList[i];
		CPoint ret = here->edgeCheck(pt);
		if (ret.x != -1) {
			newLine = new QtLine(here, ret, lineType, lineShape);
			lineList.push_back(newLine);
			lineHash[newLine->getKey()] = newLine;
			return newLine->getKey();
		}
	}
	newLine = new QtLine(0, pt, lineType, lineShape);
	lineList.push_back(newLine);
	lineHash[newLine->getKey()] = newLine;
	return newLine->getKey();
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
}

int CFinalQtDoc::find(CPoint pt)
{
	for (int i = lineList.size() - 1; i >= 0; --i) {
		QtShape* here = lineList[i];
		if (here->select(pt))
			return here->getKey();
	}
	for (int i = boxList.size() - 1; i >= 0; --i) {
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
void CFinalQtDoc::getBoxInfo(int key, int& steroType, CString& name, CString& attribute, CString& operation)
{
	QtBox* here = 0;
	auto iter = boxHash.find(key);
	if (iter != boxHash.end())
	{
		here = iter->second;
		steroType = here->m_stereotype;
		name = here->m_name;
		attribute = here->m_attribute;
		operation = here->m_operation;
	}
}
void CFinalQtDoc::moveObjects(CPoint pt, vector<int> selected)
{
	for (int k : selected)
	{
		QtShape* here = 0;
		if (boxHash.find(k) != boxHash.end())
			here = boxHash[k];
		else if (lineHash.find(k) != lineHash.end())
			here = lineHash[k];
		else
			continue;
		here->move(pt);
	}
}
void CFinalQtDoc::editBox(int key, int steroType, CString name, CString attribute, CString operation)
{
	QtBox* box = 0;
	if (boxHash.find(key) == boxHash.end())
		return;
	box = boxHash[key];
	box->m_stereotype = steroType;
	box->m_name = name;
	box->m_attribute = attribute;
	box->m_operation = operation;
}
vector<int> CFinalQtDoc::selectArea(CPoint lu, CPoint rd)
{
	vector<int> ret;
	for (int i = 0; i < boxList.size(); ++i) 
	{
		QtShape* here = boxList[i];
		if (here->selectArea(lu, rd))
			ret.push_back(here->getKey());
	}
	for (int i = 0; i < lineList.size(); ++i)
	{
		QtShape* here = lineList[i];
		if (here->selectArea(lu, rd))
			ret.push_back(here->getKey());
	}

	return ret;
}
pair<int, int> CFinalQtDoc::isLinePoint(CPoint pt)
{
	pair<int, int> ret(0, 0);
	for (int i = 0; i < lineList.size(); ++i)
	{
		QtLine* here = lineList[i];
		int chk = here->pointCheck(pt);
		if (chk == 1) {
			ret.first = here->getKey();
			ret.second = FROM;
			break;
		}
		else if (chk == 0) {
			ret.first = here->getKey();
			ret.second = TO;
			break;
		}
	}
	return ret;
}
void CFinalQtDoc::moveLine(int key, CPoint pos, int flag)
{
	QtLine* line = 0;
	if (lineHash.find(key) == lineHash.end())
		return;
	line = lineHash[key];
	if (flag == FROM) {
		for (int i = boxList.size() -1; i >= 0; --i) {
			QtBox* box = boxList[i];
			CPoint ret = box->edgeCheck(pos);
			if (ret.x != -1)
			{
				line->setRelStartPoint(box, ret);
				break;
			}
		}
	}
	else if (flag == TO) {
		for (int i = boxList.size() - 1; i >= 0; --i) {
			QtBox* box = boxList[i];
			CPoint ret = box->edgeCheck(pos);
			if (ret.x != -1)
			{
				line->setRelEndPoint(box, ret);
				break;
			}
		}
	}
}
void CFinalQtDoc::save(CString filename)
{

}
void CFinalQtDoc::load(CString filename)
{

}


