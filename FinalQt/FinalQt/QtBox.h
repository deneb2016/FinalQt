#pragma once

#include "QtShape.h"

class QtBox : public QtShape {
	CPoint m_lu, m_rd; // Box의 위치와 크기를 지정하기 위한 Rectangle
public:
	int m_stereotype; // 클래스의 속성 정보, 0(utility, 기본), 1(abstract, 추상클래스), 2(interface, 인터페이스)
	CString m_name;		// 클래스의 이름 정보
	CString m_attribute; // 클래스의 변수 정보
	CString m_operation; // 클래스의 함수 정보

public:
	QtBox() {};
	QtBox(CPoint pos_center, int stereotype, const CString& name, const CString& attribute, const CString& operation); // : 객체 생성자
	void redraw(CClientDC & dc, bool selected); // 자기자신 그리기, selected이면 강조 테두리 그리기
	void move(CPoint vec); // vec 만큼 이동
	bool select(CPoint pos); //좌표가 도형 안에 있으면 true, 아니면 false
	bool selectArea(CPoint lu, CPoint rd); //lu, rd로 되어있는 직사각형 안에 이 오브젝트가 있는지
	void setStereotype(int stereotype); //
	void setName(CString name);
	void setAttribute(CString attribute);
	void setOperation(CString operation);
	CPoint getLu();
	CPoint getRd();
	CPoint edgeCheck(CPoint pos); // 가장 가까운 edge점의 상대좌표 리턴, 없으면(-1, -1)
	void save(CArchive& ar);
	void load(CArchive& ar);

};