#include "stdafx.h"
#include "QtLine.h"
#include "QtBox.h"
#include <vector>


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

	if (startBox == nullptr) {//relStart가 절대좌표로 들어온다
		m_pboxStart = nullptr;
		m_pboxEnd = nullptr;
		m_relStart = { -1,-1 };
		m_relEnd = { -1,-1 };
		m_absStart = relStart;
		m_absEnd = relStart;
	}
	else {
		// 어떤 박스위에 있는지, 상대좌표를 받아서 StartPoint 지정, EndPoint는 처음에는 해당 없음
		m_pboxStart = startBox;
		m_pboxEnd = nullptr;
		m_relStart = relStart;
		m_relEnd = { -1,-1 };
		m_absStart = relativeToAbsolute(startBox->getLu(), startBox->getRd(), relStart);
	}
	m_relation = relation;
	m_diagonal = diagonal;
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
		return;
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
		return;
	}
	m_pboxStart = startBox;
	m_relStart = relStart;
	m_absStart = relativeToAbsolute(startBox->getLu(), startBox->getRd(), relStart);
}

void QtLine::redraw(CClientDC & dc, bool selected) {
	// 자기자신 그리기, selected이면 강조(시작점 / 끝점에 큰 원 표시), 그리기 전에 상대좌표를 절대좌표로 바꿔주기

	int penWidth = (selected) ? 3 : 1;
	COLORREF penColor = (selected) ? RGB(255, 0, 0) : RGB(0, 0, 0);
	int penStyle = PS_NULL;
	if (m_relation == 1 || m_relation == 4) penStyle = PS_SOLID;
	if (m_relation == 2 || m_relation == 3) penStyle = PS_DASH;
	CPen MyPen(penStyle, penWidth, penColor);

	dc.SelectObject(&MyPen);

	//'화면상의 절대좌표'구하기
	CPoint posEnd = m_absEnd;
	CPoint posStart = m_absStart;

	/*1. 선그리기*/
	if (m_diagonal == true) {
		dc.MoveTo(posStart);
		dc.LineTo(posEnd);
	}
	else {
		//저절로 꺾이는
		CPoint dirStart = getDirection(m_relStart);
		CPoint dirEnd = getDirection(m_relEnd);

		m_trace.clear();
		m_trace.push_back(dirStart);

		CPoint moveVec = posEnd + dirEnd - (posStart + dirStart);
		//같은 direction이 있으면 우선권주기
		bool preS = (dirStart.x * moveVec.x >= 0 && dirStart.y * moveVec.y >= 0);
		bool preE = (dirEnd.x * moveVec.x >= 0 && dirEnd.y * moveVec.y >= 0);
		if (preS && preE) {
			//0. Start, End 모두 우선권
			CPoint moveVec_p = CPoint(dirStart.x / dirStart.x * moveVec.x, dirStart.y / dirStart.y * moveVec.y); //dirStart의 방향에서 꺾은 쪽의 moveVec 방향
			CPoint moveVec_p_half = CPoint(moveVec_p.x / 2, moveVec_p.y / 2);

			CPoint moveVec_v = moveVec - moveVec_p;

			m_trace.push_back(moveVec_p_half);
			m_trace.push_back(moveVec_v);
			m_trace.push_back(moveVec_p_half);

		}
		else if (preS) {
			//1. Start에 우선권
			CPoint moveVec_p = CPoint(dirStart.x / dirStart.x * moveVec.x, dirStart.y / dirStart.y * moveVec.y); //dirStart의 방향과 같은 direction
			CPoint moveVec_v = moveVec - moveVec_p;
			m_trace.push_back(moveVec_p);
			m_trace.push_back(moveVec_v);

		}
		else if (preE) {
			//2. End에 우선권
			CPoint moveVec_p = CPoint(dirStart.x / dirStart.x * moveVec.x, dirStart.y / dirStart.y * moveVec.y); //dirStart의 방향과 같은 direction
			CPoint moveVec_v = moveVec - moveVec_p;
			m_trace.push_back(moveVec_p);
			m_trace.push_back(moveVec_v);
		}
		else {
			//3. 둘다 옆방향으로
			CPoint moveVec_v = CPoint(dirStart.y / dirStart.y * moveVec.x, dirStart.x / dirStart.x * moveVec.y); //dirStart의 방향에서 꺾은 쪽의 moveVec 방향
			CPoint moveVec_v_half = CPoint(moveVec_v.x / 2, moveVec_v.y / 2);

			CPoint moveVec_p = moveVec - moveVec_v;

			m_trace.push_back(moveVec_v_half);
			m_trace.push_back(moveVec_p);
			m_trace.push_back(moveVec_v_half);

		}
		m_trace.push_back(dirEnd);
		/*구한 m_trace 그리기*/

		CPoint v = posStart;
		for (auto& w : m_trace) {
			dc.MoveTo(v);
			dc.LineTo(v + w);
			v = v + w;
		}

	}


	/*2. 화살표캡 그리기*/
	int arrayStyle = 0;
	if (m_relation == 1 || m_relation == 2) arrayStyle = 1;//검은원점
	else if (m_relation == 3) arrayStyle = 2; //빈 원점

	if (arrayStyle != 0) {
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

bool QtLine::select(CPoint pos) { //해당 선분 위에 (+-1pixel) 마우스가 위치할때만 1 리턴, 아니면 0 리턴
								  //+-1point
	if (m_diagonal) {
		CPoint lu_temp, rd_temp;
		lu_temp.x = (m_absEnd.x <= m_absStart.x) ? m_absEnd.x : m_absStart.x;
		rd_temp.x = (m_absEnd.x <= m_absStart.x) ? m_absStart.x : m_absEnd.x;
		lu_temp.y = (m_absEnd.y <= m_absStart.y) ? m_absEnd.y : m_absStart.y;
		rd_temp.y = (m_absEnd.y <= m_absStart.y) ? m_absStart.y : m_absEnd.y;

		if (inRect(lu_temp, rd_temp, pos)) {

			CPoint pV = pos - m_absStart; //part vector
			CPoint wV = m_absEnd - m_absStart; //whole vector
											   //partVect normalization
			double wvL2 = wV.x*wV.x + wV.y*wV.y;
			double ip = (double)pV.x * (double)wV.x + (double)pV.y * (double)wV.y; //내적
			CPoint dist = pV - CPoint(wV.x*ip/wvL2, wV.y*ip / wvL2);
			if (dist.x*dist.x + dist.y*dist.y < PIX*PIX) return 1;
		}
	}
	else {
		CPoint v = m_absStart;
		for (auto& w : m_trace) {
			CPoint lu_temp, rd_temp;
			lu_temp.x = (w.x >= 0) ? v.x : v.x + w.x;
			rd_temp.x = (w.x >= 0) ? v.x + w.x : v.x;
			lu_temp.y = (w.y >= 0) ? v.y : v.y + w.y;
			rd_temp.y = (w.y >= 0) ? v.y + w.y : v.y;
			lu_temp += CPoint(1, 1);
			rd_temp -= CPoint(1, 1);

			if (inRect(lu_temp, rd_temp, pos)) return 1;
			v = v + w;
		}

	}

	return 0;
}

bool QtLine::selectArea(CPoint lu, CPoint rd) {
	// 직선 양 점 모두가 Area내에 포함되면 1리턴, 아니면 0
	int inclStart = (lu.x <= m_absStart.x && m_absStart.x <= rd.x && lu.y <= m_absStart.y && m_absStart.y <= rd.y);
	int inclEnd = (lu.x <= m_absEnd.x && m_absEnd.x <= rd.x && lu.y <= m_absEnd.y && m_absEnd.y <= rd.y);

	return inclStart && inclEnd;
}

void QtLine::save(CArchive& ar)
{

	ar << m_absStart << m_absEnd; // 절대 좌표
	ar << m_pboxStart->getKey();
	ar << m_pboxEnd->getKey(); // 가리키는 상자
	ar << m_relStart, m_relEnd; // 상대 좌표(0~100, 퍼센트)
	ar << m_relation; // 두 클래스의 관계
	ar << m_diagonal; //직선이면 0, 사선이면 1

}
void QtLine::load(CArchive& ar)
{

	ar >> m_absStart >> m_absEnd; // 절대 좌표
	int k1, k2;
	ar >> k1;
	ar >> k2; // 가리키는 상자
	m_pboxStart = (QtBox*)k1;
	m_pboxEnd = (QtBox*)k2;

	ar >> m_relStart, m_relEnd; // 상대 좌표(0~100, 퍼센트)
	ar >> m_relation; // 두 클래스의 관계
	ar >> m_diagonal; //직선이면 0, 사선이면 1

}
