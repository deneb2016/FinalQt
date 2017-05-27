
// FinalQtView.h : CFinalQtView Ŭ������ �������̽�
//

#pragma once


class CFinalQtView : public CView
{
protected: // serialization������ ��������ϴ�.
	CFinalQtView();
	DECLARE_DYNCREATE(CFinalQtView)

// Ư���Դϴ�.
public:
	CFinalQtDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CFinalQtView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	std::vector<int> selectedObj_key;
	afx_msg void OnCreatbox();
	CString strClassName;
	CString strAttribute;
	CString strOperation;
	afx_msg void OnCreaterelation();
	afx_msg void OnCreateline1();
	afx_msg void OnCreateline2();
	void createLine(CPoint pt, int lineType, int lineShape);
};

#ifndef _DEBUG  // FinalQtView.cpp�� ����� ����
inline CFinalQtDoc* CFinalQtView::GetDocument() const
   { return reinterpret_cast<CFinalQtDoc*>(m_pDocument); }
#endif

