
// FinalQtDoc.h : CFinalQtDoc Ŭ������ �������̽�
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

public:
	void createBox(CString name, CString attribute, CString operation, CPoint pt);
	void createLine(CPoint pt, int lineType, int lineShape);
	void deleteObject(int key);
	int find(CPoint pt);
	void redrawAllObj(const CClientDC& dc, std::vector<int> selected);
	int getShapeType(int key);
	std::vector<CString> getBoxInfo(int key);
	int getRectangle(CPoint pt);
	void moveObjects(CPoint pt, std::vector<int> key);
	void editBox(int key, const std::vector<CString>& infi);
	std::vector<int> selectArea(CPoint lu, CPoint rd);
	std::pair<int, int> isLinePoint(CPoint pt);
	void moveLine(int key, CPoint vec, int flag);
	void save(CString filename);
	void load(CString filename);

protected: // serialization������ ��������ϴ�.
	CFinalQtDoc();
	DECLARE_DYNCREATE(CFinalQtDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CFinalQtDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
