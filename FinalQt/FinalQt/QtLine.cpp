#include "stdafx.h"
#include "QtLine.h"
#include "QtBox.h"
#include <vector>


/*
class QtLine

CPoint m_absStart, m_absEnd; // ���� ��ǥ
QtBox* m_pboxStart, m_pboxEnd; // ����Ű�� ����
CPoint m_relStart, m_relEnd; // ��� ��ǥ(0~100, �ۼ�Ʈ)
int m_relation; // �� Ŭ������ ����
bool m_diagonal; //�����̸� 0, �缱�̸� 1
*/

QtLine::QtLine(QtBox* startBox, CPoint relStart, int relation, bool diagonal) {
	key = nextKey++;

	if (startBox == nullptr) {//relStart�� ������ǥ�� ���´�
		m_pboxStart = nullptr;
		m_pboxEnd = nullptr;
		m_relStart = { -1,-1 };
		m_relEnd = { -1,-1 };
		m_absStart = relStart;
		m_absEnd = relStart;
	}
	else {
		// � �ڽ����� �ִ���, �����ǥ�� �޾Ƽ� StartPoint ����, EndPoint�� ó������ �ش� ����
		m_pboxStart = startBox;
		m_pboxEnd = nullptr;
		m_relStart = relStart;
		m_relEnd = { -1,-1 };
		m_absStart = relativeToAbsolute(startBox->getLu(), startBox->getRd(), relStart);
	}
	m_relation = relation;
	m_diagonal = diagonal;
}


int QtLine::pointCheck(CPoint pos) { // START(1) / END(0) ����Ʈ �� ��� ����Ʈ �ֺ��� �ִ��� ����, ���� �ش�ȵǸ� - 1����
	int nearStart = nearPoint(pos, m_absStart);
	int nearEnd = nearPoint(pos, m_absEnd);

	if (nearStart >= 0 && nearEnd >= 0) {//�� �� ���ο� �����ش�
		return (nearStart < nearEnd) ? 1 : 0; //�� ������ �� �� ����
	}
	else if (nearStart >= 0) return 1; //Start���� ����
	else if (nearEnd >= 0) return 0; //End���� ����
	else return -1; //������ �� ����
}

void QtLine::setAbsEndPoint(CPoint pos) {
	// end�� ����� ���� ���� ����, m_relEnd�� 0�϶�
	if (m_pboxEnd == nullptr) {
		m_absEnd = pos;
	}
	else return;
}

void QtLine::setRelEndPoint(QtBox* endBox, CPoint relEnd) {
	//Box�� NULL�� ȣ��� ���� ����. �갡 �ٲ��, ������ǥ�� �ٲ���ߵ�.
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
	// start�� ����� ���� ���� ����, m_relStart�� 0�϶�
	if (m_pboxStart == nullptr) {
		m_absStart = pos;
	}
	else return;

}
void QtLine::setRelStartPoint(QtBox* startBox, CPoint relStart) {
	//Box�� NULL�� ȣ��� ���� ����. �갡 �ٲ��, ������ǥ�� �ٲ���ߵ�.
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
	// �ڱ��ڽ� �׸���, selected�̸� ����(������ / ������ ū �� ǥ��), �׸��� ���� �����ǥ�� ������ǥ�� �ٲ��ֱ�

	int penWidth = (selected) ? 3 : 1;
	COLORREF penColor = (selected) ? RGB(255, 0, 0) : RGB(0, 0, 0);
	int penStyle = PS_NULL;
	if (m_relation == 1 || m_relation == 4) penStyle = PS_SOLID;
	if (m_relation == 2 || m_relation == 3) penStyle = PS_DASH;
	CPen MyPen(penStyle, penWidth, penColor);

	dc.SelectObject(&MyPen);

	//'ȭ����� ������ǥ'���ϱ�
	CPoint posEnd = m_absEnd;
	CPoint posStart = m_absStart;

	/*1. ���׸���*/
	if (m_diagonal == true) {
		dc.MoveTo(posStart);
		dc.LineTo(posEnd);
	}
	else {
		//������ ���̴�
		CPoint dirStart = getDirection(m_relStart);
		CPoint dirEnd = getDirection(m_relEnd);

		m_trace.clear();
		m_trace.push_back(dirStart);

		CPoint moveVec = posEnd + dirEnd - (posStart + dirStart);
		//���� direction�� ������ �켱���ֱ�
		bool preS = (dirStart.x * moveVec.x >= 0 && dirStart.y * moveVec.y >= 0);
		bool preE = (dirEnd.x * moveVec.x >= 0 && dirEnd.y * moveVec.y >= 0);
		if (preS && preE) {
			//0. Start, End ��� �켱��
			CPoint moveVec_p = CPoint(dirStart.x / dirStart.x * moveVec.x, dirStart.y / dirStart.y * moveVec.y); //dirStart�� ���⿡�� ���� ���� moveVec ����
			CPoint moveVec_p_half = CPoint(moveVec_p.x / 2, moveVec_p.y / 2);

			CPoint moveVec_v = moveVec - moveVec_p;

			m_trace.push_back(moveVec_p_half);
			m_trace.push_back(moveVec_v);
			m_trace.push_back(moveVec_p_half);

		}
		else if (preS) {
			//1. Start�� �켱��
			CPoint moveVec_p = CPoint(dirStart.x / dirStart.x * moveVec.x, dirStart.y / dirStart.y * moveVec.y); //dirStart�� ����� ���� direction
			CPoint moveVec_v = moveVec - moveVec_p;
			m_trace.push_back(moveVec_p);
			m_trace.push_back(moveVec_v);

		}
		else if (preE) {
			//2. End�� �켱��
			CPoint moveVec_p = CPoint(dirStart.x / dirStart.x * moveVec.x, dirStart.y / dirStart.y * moveVec.y); //dirStart�� ����� ���� direction
			CPoint moveVec_v = moveVec - moveVec_p;
			m_trace.push_back(moveVec_p);
			m_trace.push_back(moveVec_v);
		}
		else {
			//3. �Ѵ� ����������
			CPoint moveVec_v = CPoint(dirStart.y / dirStart.y * moveVec.x, dirStart.x / dirStart.x * moveVec.y); //dirStart�� ���⿡�� ���� ���� moveVec ����
			CPoint moveVec_v_half = CPoint(moveVec_v.x / 2, moveVec_v.y / 2);

			CPoint moveVec_p = moveVec - moveVec_v;

			m_trace.push_back(moveVec_v_half);
			m_trace.push_back(moveVec_p);
			m_trace.push_back(moveVec_v_half);

		}
		m_trace.push_back(dirEnd);
		/*���� m_trace �׸���*/

		CPoint v = posStart;
		for (auto& w : m_trace) {
			dc.MoveTo(v);
			dc.LineTo(v + w);
			v = v + w;
		}

	}


	/*2. ȭ��ǥĸ �׸���*/
	int arrayStyle = 0;
	if (m_relation == 1 || m_relation == 2) arrayStyle = 1;//��������
	else if (m_relation == 3) arrayStyle = 2; //�� ����

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
	// ����� �ִ� ���鸸 ������ǥ �̵�
	if (m_pboxStart == nullptr) {
		setAbsStartPoint(m_absStart + vec);
	}
	if (m_pboxEnd == nullptr) {
		setAbsEndPoint(m_absEnd + vec);
	}
}

bool QtLine::select(CPoint pos) { //�ش� ���� ���� (+-1pixel) ���콺�� ��ġ�Ҷ��� 1 ����, �ƴϸ� 0 ����
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
			double ip = (double)pV.x * (double)wV.x + (double)pV.y * (double)wV.y; //����
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
	// ���� �� �� ��ΰ� Area���� ���ԵǸ� 1����, �ƴϸ� 0
	int inclStart = (lu.x <= m_absStart.x && m_absStart.x <= rd.x && lu.y <= m_absStart.y && m_absStart.y <= rd.y);
	int inclEnd = (lu.x <= m_absEnd.x && m_absEnd.x <= rd.x && lu.y <= m_absEnd.y && m_absEnd.y <= rd.y);

	return inclStart && inclEnd;
}

void QtLine::save(CArchive& ar)
{

	ar << m_absStart << m_absEnd; // ���� ��ǥ
	ar << m_pboxStart->getKey();
	ar << m_pboxEnd->getKey(); // ����Ű�� ����
	ar << m_relStart, m_relEnd; // ��� ��ǥ(0~100, �ۼ�Ʈ)
	ar << m_relation; // �� Ŭ������ ����
	ar << m_diagonal; //�����̸� 0, �缱�̸� 1

}
void QtLine::load(CArchive& ar)
{

	ar >> m_absStart >> m_absEnd; // ���� ��ǥ
	int k1, k2;
	ar >> k1;
	ar >> k2; // ����Ű�� ����
	m_pboxStart = (QtBox*)k1;
	m_pboxEnd = (QtBox*)k2;

	ar >> m_relStart, m_relEnd; // ��� ��ǥ(0~100, �ۼ�Ʈ)
	ar >> m_relation; // �� Ŭ������ ����
	ar >> m_diagonal; //�����̸� 0, �缱�̸� 1

}
