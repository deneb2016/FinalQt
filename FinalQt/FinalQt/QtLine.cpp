#include "stdafx.h"
#include "QtLine.h"
#include "QtBox.h"



/*
class QtLine

CPoint m_absStart, m_absEnd; // 절대 좌표
QtBox* m_pboxStart, m_pboxEnd; // 가리키는 상자
CPoint m_relStart, m_relEnd; // 상대 좌표(0~100, 퍼센트)
int m_relation; // 두 클래스의 관계
bool m_diagonal; //직선이면 0, 사선이면 1
*/

QtLine::QtLine(QtBox* startBox, CPoint relStart, int relation, bool diagonal) {
	key = nextKey++;

	// 어떤 박스위에 있는지, 상대좌표를 받아서 StartPoint 지정, EndPoint는 처음에는 해당 없음
	m_pboxStart = startBox;
	m_pboxEnd = nullptr;
	m_relStart = relStart;
	m_relEnd = { -1,-1 };
	m_relation = relation;
	m_diagonal = diagonal;

	m_absStart = relativeToAbsolute(startBox->getLu(), startBox->getRd(), relStart);
}


int QtLine::pointCheck(CPoint pos) { // START(1) / END(0) 포인트 중 어느 포인트 주변에 있는지 리턴, 둘중 해당안되면 - 1리턴
	int nearStart = nearPoint(pos, m_absStart);
	int nearEnd = nearPoint(pos, m_absEnd);

	if (nearStart >= 0 && nearEnd >= 0) {//양 점 전부에 근접해당
		return (nearStart < nearEnd) ? 1 : 0; //더 근접한 점 값 리턴
	}
	else if (nearStart >= 0) return 1; //Start에만 근접
	else if (nearEnd >= 0) return 0; //End에만 근접
	else return -1; //근접한 점 없음
}

void QtLine::setAbsEndPoint(CPoint pos) {
	// end가 허공에 있을 때만 동작, m_relEnd가 0일때
	if (m_pboxEnd == nullptr) {
		m_absEnd = pos;
	}
	else return;
}

void QtLine::setRelEndPoint(QtBox* endBox, CPoint relEnd) {
	//Box가 NULL로 호출될 수도 있음. 얘가 바뀌면, 절대좌표도 바꿔줘야됨.
	if (endBox == NULL) {
		m_pboxEnd = endBox;
		m_relEnd = { -1,-1 };
	}
	m_pboxEnd = endBox;
	m_relEnd = relEnd;
	m_absEnd = relativeToAbsolute(endBox->getLu(), endBox->getRd(), relEnd);
}

void QtLine::setAbsStartPoint(CPoint pos) {
	// start가 허공에 있을 때만 동작, m_relStart가 0일때
	if (m_pboxStart == nullptr) {
		m_absStart = pos;
	}
	else return;

}
void QtLine::setRelStartPoint(QtBox* startBox, CPoint relStart) {
	//Box가 NULL로 호출될 수도 있음. 얘가 바뀌면, 절대좌표도 바꿔줘야됨.
	if (startBox == NULL) {
		m_pboxStart = startBox;
		m_relStart = { -1,-1 };
	}
	m_pboxStart = startBox;
	m_relStart = relStart;
	m_absStart = relativeToAbsolute(startBox->getLu(), startBox->getRd(), relStart);
}

void QtLine::redraw(CClientDC & dc, bool selected, CPoint framePos) {
	// 자기자신 그리기, selected이면 강조(시작점 / 끝점에 큰 원 표시), 그리기 전에 상대좌표를 절대좌표로 바꿔주기
	
	int penStyle = PS_NULL;
	if (m_relation == 1 || m_relation == 4) penStyle = PS_SOLID;
	if (m_relation == 2 || m_relation == 3) penStyle = PS_DASH;
	CPen MyPen(penStyle, 1, RGB(0, 0, 0));

	dc.SelectObject(&MyPen);

	//'화면상의 절대좌표'구하기
	CPoint posEnd = framePos + m_absEnd;
	CPoint posStart = framePos + m_absStart;

	/*1. 선그리기*/
	if (m_diagonal == true) {
		dc.MoveTo(posStart);
		dc.LineTo(posEnd);
	}
	else {
		//////////////////저절로 꺾이는
		
	}


	/*2. 화살표캡 그리기*/
	int arrayStyle = 0;
	if (m_relation == 1 || m_relation == 2) arrayStyle = 1;//검은원점
	else if (m_relation == 3) arrayStyle = 2; //빈 원점

	if(arrayStyle != 0){
		COLORREF arrayColor;
		if (arrayStyle == 1) arrayColor = RGB(0, 0, 0);
		else arrayColor = RGB(255, 255, 255);

		CBrush MyBrush(arrayColor);
		dc.SelectObject(&MyBrush);
		dc.Ellipse(posEnd.x - 1, posEnd.y - 1, posEnd.x + 1, posEnd.y + 1);
	}
	


}

void QtLine::move(CPoint vec) {
	// 허공에 있는 점들만 절대좌표 이동
	if (m_pboxStart == nullptr) {
		setAbsStartPoint(m_absStart + vec);
	}
	if (m_pboxEnd == nullptr) {
		setAbsEndPoint(m_absEnd + vec);
	}
}
bool QtLine::select(CPoint pos) { //해당 선분 위에 정확하게 마우스가 위치할때만 1 리턴, 아니면 0 리턴
	//+-1point
	

	return 0;
}

bool QtLine::selectArea(CPoint lu, CPoint rd) {
	// 직선 양 점 모두가 Area내에 포함되면 1리턴, 아니면 0
	int inclStart = (lu.x <= m_absStart.x && m_absStart.x <= rd.x && lu.y <= m_absStart.y && m_absStart.y <= rd.y);
	int inclEnd = (lu.x <= m_absEnd.x && m_absEnd.x <= rd.x && lu.y <= m_absEnd.y && m_absEnd.y <= rd.y);

	return inclStart && inclEnd;
}