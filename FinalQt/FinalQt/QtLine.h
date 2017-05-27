#pragma once
#include "QtShape.h"
#include <vector>
class QtBox;


class QtLine : public QtShape {
private:
	CPoint m_absStart, m_absEnd; // 절대 좌표
	CPoint m_relStart, m_relEnd; // 상대 좌표(0~100, 퍼센트)
	int m_relation; // 두 클래스의 관계
	bool m_diagonal; //직선이면 0, 사선이면 1
	std::vector<CPoint> m_trace; //그릴 벡터들, start->end여야함
public:
	QtLine() {};
	QtBox *m_pboxStart, *m_pboxEnd; // 가리키는 상자
	QtLine(QtBox* startBox, CPoint relStart, int relation, bool diagonal);  // 어떤 박스위에 있는지, 상대좌표를 받아서 StartPoint 지정, EndPoint는 처음에는 해당 없음
	int pointCheck(CPoint pos); // START(1) / END(0) 포인트 중 어느 포인트 주변에 있는지 리턴, 둘중 해당안되면 - 1리턴
	void setAbsEndPoint(CPoint pos); // end가 허공에 있을 때만 동작, m_relEnd가 0일때
	void setRelEndPoint(QtBox* endBox, CPoint relEnd); //얘가 바뀌면, 절대좌표도 바꿔줘야됨.
	void setAbsStartPoint(CPoint pos); // start가 허공에 있을 때만 동작, m_relStart가 0일때
	void setRelStartPoint(QtBox* startBox, CPoint relStart); //얘가 바뀌면, 절대좌표도 바꿔줘야됨.
															 //	(*상대좌표 set 할때, 박스가 NULL로 호출될수도 있음.)
	void redraw(CClientDC & dc, bool selected); // 자기자신 그리기, selected이면 강조(시작점 / 끝점에 큰 원 표시);, 그리기 전에 상대좌표를 절대좌표로 바꿔주기
	void move(CPoint vec); // 허공에 있는 점들만 절대좌표 이동
	bool select(CPoint position); //+-1point
	bool selectArea(CPoint lu, CPoint rd); // 직선 양 점 모두가 Area내에 포함되면 1리턴, 아미녀 0

	virtual void save(CArchive& ar);
	virtual void load(CArchive& ar);

};