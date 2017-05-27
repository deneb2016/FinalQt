#include "stdafx.h"
#include "QtBox.h"

/*
CPoint m_lu, m_rd; // Box의 위치와 크기를 지정하기 위한 Rectangle
int m_stereotype; // 클래스의 속성 정보, 0(utility, 기본), 1(abstract, 추상클래스), 2(interface, 인터페이스)
CString m_name;		// 클래스의 이름 정보
CString m_attribute; // 클래스의 변수 정보
CString m_operation; // 클래스의 함수 정보
*/

const CPoint DEFAULT_BOX_SIZE{ 100,300 };


CPoint QtBox::getLu() {
	return m_lu;
}
CPoint QtBox::getRd() {
	return m_rd;
}
QtBox::QtBox(CPoint pos_center, int stereotype, const CString& name, const CString& attribute, const CString& operation) {
	// 객체 생성자
	key = nextKey++;
	m_stereotype = stereotype;
	m_name = name;
	m_attribute = attribute;
	m_operation = operation;

	/*!!!!!!!!!! 박스 사이즈를 생성하는 코드 !!!!!!!!!*/
	m_lu = pos_center - CPoint{ DEFAULT_BOX_SIZE.x / 2, DEFAULT_BOX_SIZE.y / 2 };
	m_rd = pos_center + CPoint{ DEFAULT_BOX_SIZE.x / 2, DEFAULT_BOX_SIZE.y / 2 };
}
void QtBox::redraw(CClientDC & dc, bool selected) {
	// 자기자신 그리기, selected이면 강조 테두리 그리기


}
void QtBox::move(CPoint vec) {
	m_lu += vec;
	m_rd += vec;
}
bool QtBox::select(CPoint pos) {
	//좌표가 도형 안에 있으면 true, 아니면 false
	int incl = (m_lu.x <= pos.x && pos.x <= m_rd.x && m_lu.y <= pos.y && pos.y <= m_rd.y);

	return incl;
}
bool QtBox::selectArea(CPoint lu, CPoint rd) { //lu, rd로 되어있는 직사각형 안에 이 오브젝트가 있는지
	CPoint mld = CPoint(m_lu.x, m_rd.y);
	CPoint mru = CPoint(m_rd.x, m_lu.y);

	bool in1 = inRect(lu, rd, mld);
	bool in2 = inRect(lu, rd, mru);
	bool in3 = inRect(lu, rd, m_lu);
	bool in4 = inRect(lu, rd, m_rd);

	return (in1|in2|in3|in4);
}
void QtBox::setStereotype(int stereotype) {
	m_stereotype = stereotype;
}
void QtBox::setName(CString name) {
	m_name = name;
}
void QtBox::setAttribute(CString attribute) {
	m_attribute = attribute;
}
void QtBox::setOperation(CString operation) {
	m_operation = operation;
}
CPoint QtBox::edgeCheck(CPoint pos) {
	
	return { 0,0 };
}// 가장 가까운 edge점의 상대좌표 리턴, 없으면(-1, -1)