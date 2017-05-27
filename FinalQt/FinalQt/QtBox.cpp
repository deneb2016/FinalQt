#include "stdafx.h"
#include "QtBox.h"

/*
CPoint m_lu, m_rd; // Box�� ��ġ�� ũ�⸦ �����ϱ� ���� Rectangle
int m_stereotype; // Ŭ������ �Ӽ� ����, 0(utility, �⺻), 1(abstract, �߻�Ŭ����), 2(interface, �������̽�)
CString m_name;		// Ŭ������ �̸� ����
CString m_attribute; // Ŭ������ ���� ����
CString m_operation; // Ŭ������ �Լ� ����
*/

const CPoint DEFAULT_BOX_SIZE{ 100,300 };


CPoint QtBox::getLu() {
	return m_lu;
}
CPoint QtBox::getRd() {
	return m_rd;
}
QtBox::QtBox(CPoint pos_center, int stereotype, const CString& name, const CString& attribute, const CString& operation) {
	// ��ü ������
	key = nextKey++;
	m_stereotype = stereotype;
	m_name = name;
	m_attribute = attribute;
	m_operation = operation;

	/*!!!!!!!!!! �ڽ� ����� �����ϴ� �ڵ� !!!!!!!!!*/
	m_lu = pos_center - CPoint{ DEFAULT_BOX_SIZE.x / 2, DEFAULT_BOX_SIZE.y / 2 };
	m_rd = pos_center + CPoint{ DEFAULT_BOX_SIZE.x / 2, DEFAULT_BOX_SIZE.y / 2 };
}
void QtBox::redraw(CClientDC & dc, bool selected) {
	// �ڱ��ڽ� �׸���, selected�̸� ���� �׵θ� �׸���

	CString stereo = L"";
	stereo.Append(L"<<");
	switch (m_stereotype) {
	case ST_UTILITY: stereo.Append(L"utility"); break;
	case ST_ABSTRACT: stereo.Append(L"abstract"); break;
	case ST_INTERFACE: stereo.Append(L"interface"); break;
	}
	stereo.Append(L">>\n");
	stereo.Append(m_name);
	stereo.Append(L"-------------");
	stereo.Append(m_attribute);
	stereo.Append(L"-------------");
	stereo.Append(m_operation);


	CRect rect(m_lu.x, m_lu.y, m_rd.x, m_rd.x); //left, top, right, bottom
	dc.DrawText(stereo, rect, DT_CALCRECT);
	dc.DrawText(stereo, rect, DT_CENTER);
	m_rd.x = rect.right;
	m_rd.y = rect.bottom;

	int penWidth = (selected) ? 2 : 1;
	COLORREF penColor = (selected) ? RGB(255, 0, 0) : RGB(0, 0, 0);
	CPen pen(PS_SOLID, penWidth, penColor);
	dc.SelectObject(&pen);
	dc.MoveTo(m_lu);
	dc.LineTo(m_lu.x, m_rd.y);
	dc.MoveTo(m_lu.x, m_rd.y);
	dc.LineTo(m_rd);
	dc.MoveTo(m_rd);
	dc.LineTo(m_rd.x, m_lu.y);
	dc.MoveTo(m_rd.x, m_lu.y);
	dc.LineTo(m_lu);

}
void QtBox::move(CPoint vec) {
	m_lu += vec;
	m_rd += vec;
}
bool QtBox::select(CPoint pos) {
	//��ǥ�� ���� �ȿ� ������ true, �ƴϸ� false
	bool incl = (m_lu.x <= pos.x && pos.x <= m_rd.x && m_lu.y <= pos.y && pos.y <= m_rd.y);

	return incl;
}
bool QtBox::selectArea(CPoint lu, CPoint rd) { //lu, rd�� �Ǿ��ִ� ���簢�� �ȿ� �� ������Ʈ�� �ִ���
	CPoint mld = CPoint(m_lu.x, m_rd.y);
	CPoint mru = CPoint(m_rd.x, m_lu.y);

	bool in1 = inRect(lu, rd, mld);
	bool in2 = inRect(lu, rd, mru);
	bool in3 = inRect(lu, rd, m_lu);
	bool in4 = inRect(lu, rd, m_rd);

	return (in1 | in2 | in3 | in4);
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
	CPoint nearest;
	if (abs(pos.x - m_rd.x) <= 2) nearest.x = m_rd.x;
	else if (abs(pos.x - m_lu.x) <= 2) nearest.x = m_lu.x;
	else return{ -1,-1 };

	if (abs(pos.y - m_rd.y) <= 2) nearest.y = m_rd.y;
	else if (abs(pos.y - m_rd.y) <= 2) nearest.y = m_rd.y;
	else return{ -1,-1 };

	CPoint ret((int)(((double)pos.x*(double)100) / (double)nearest.x), (int)(((double)pos.y*(double)100) / (double)nearest.y));

	return ret;
}// ���� ����� edge���� �����ǥ ����, ������(-1, -1)