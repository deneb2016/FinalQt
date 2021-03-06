
// FinalQtDoc.h : CFinalQtDoc 클래스의 인터페이스
//


#pragma once
#include <vector>
#include <unordered_map>


class QtShape;
class QtBox;
class QtLine;

class CFinalQtDoc : public CDocument
{
private:
	std::vector<QtBox*> boxList;
	std::unordered_map<int, QtBox*> boxHash;
	std::vector<QtLine*> lineList;
	std::unordered_map<int, QtLine*> lineHash;
	static std::vector<QtBox*> boxCopy;
	static std::vector<QtLine*> lineCopy;
public:
	void createBox(CPoint pt, int steroType, CString name, CString attribute, CString operation);
	int createLine(CPoint pt, int lineType, int lineShape);
	void deleteObject(int key);
	int find(CPoint pt);
	void redrawAllObj(CClientDC& dc, std::vector<int> selected);
	int getShapeType(int key);
	void getBoxInfo(int key, int& steroType, CString& name, CString& attribute, CString& operation);
	void moveObjects(CPoint pt, std::vector<int> selected);
	void editBox(int key, int steroType, CString name, CString attribute, CString operation);
	std::vector<int> selectArea(CPoint lu, CPoint rd);
	std::pair<int, int> isLinePoint(CPoint pt);
	void moveLine(int key, CPoint pos, int flag);
	void save(CString filename);
	void load(CString filename);
	void copyObjects(std::vector<int> keys);
	void pasteObjects();
	//type, shape 리턴
	std::pair<int, int> getLineInfo(int key);// Line의 정보를 가지고온다. //순서대로.
	void editLine(int key, int type, int shape); //라인의 속성을0 바꾼다.

protected: // serialization에서만 만들어집니다.
	CFinalQtDoc();
	DECLARE_DYNCREATE(CFinalQtDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CFinalQtDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
