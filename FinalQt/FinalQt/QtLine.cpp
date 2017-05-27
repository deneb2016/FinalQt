#include "stdafx.h"
#include "QtLine.h"
#include "QtBox.h"



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

	// � �ڽ����� �ִ���, �����ǥ�� �޾Ƽ� StartPoint ����, EndPoint�� ó������ �ش� ����
	m_pboxStart = startBox;
	m_pboxEnd = nullptr;
	m_relStart = relStart;
	m_relEnd = { -1,-1 };
	m_relation = relation;
	m_diagonal = diagonal;

	m_absStart = relativeToAbsolute(startBox->getLu(), startBox->getRd(), relStart);
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
	}
	m_pboxStart = startBox;
	m_relStart = relStart;
	m_absStart = relativeToAbsolute(startBox->getLu(), startBox->getRd(), relStart);
}

void QtLine::redraw(CClientDC & dc, bool selected, CPoint framePos) {
	// �ڱ��ڽ� �׸���, selected�̸� ����(������ / ������ ū �� ǥ��), �׸��� ���� �����ǥ�� ������ǥ�� �ٲ��ֱ�
	
	int penStyle = PS_NULL;
	if (m_relation == 1 || m_relation == 4) penStyle = PS_SOLID;
	if (m_relation == 2 || m_relation == 3) penStyle = PS_DASH;
	CPen MyPen(penStyle, 1, RGB(0, 0, 0));

	dc.SelectObject(&MyPen);

	//'ȭ����� ������ǥ'���ϱ�
	CPoint posEnd = framePos + m_absEnd;
	CPoint posStart = framePos + m_absStart;

	/*1. ���׸���*/
	if (m_diagonal == true) {
		dc.MoveTo(posStart);
		dc.LineTo(posEnd);
	}
	else {
		//////////////////������ ���̴�
		
	}


	/*2. ȭ��ǥĸ �׸���*/
	int arrayStyle = 0;
	if (m_relation == 1 || m_relation == 2) arrayStyle = 1;//��������
	else if (m_relation == 3) arrayStyle = 2; //�� ����

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
	// ����� �ִ� ���鸸 ������ǥ �̵�
	if (m_pboxStart == nullptr) {
		setAbsStartPoint(m_absStart + vec);
	}
	if (m_pboxEnd == nullptr) {
		setAbsEndPoint(m_absEnd + vec);
	}
}
bool QtLine::select(CPoint pos) { //�ش� ���� ���� ��Ȯ�ϰ� ���콺�� ��ġ�Ҷ��� 1 ����, �ƴϸ� 0 ����
	//+-1point
	

	return 0;
}

bool QtLine::selectArea(CPoint lu, CPoint rd) {
	// ���� �� �� ��ΰ� Area���� ���ԵǸ� 1����, �ƴϸ� 0
	int inclStart = (lu.x <= m_absStart.x && m_absStart.x <= rd.x && lu.y <= m_absStart.y && m_absStart.y <= rd.y);
	int inclEnd = (lu.x <= m_absEnd.x && m_absEnd.x <= rd.x && lu.y <= m_absEnd.y && m_absEnd.y <= rd.y);

	return inclStart && inclEnd;
}