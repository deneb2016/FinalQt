#pragma once

#include "QtShape.h"

class QtBox : public QtShape {
	CPoint m_lu, m_rd; // Box�� ��ġ�� ũ�⸦ �����ϱ� ���� Rectangle
public:
	int m_stereotype; // Ŭ������ �Ӽ� ����, 0(utility, �⺻), 1(abstract, �߻�Ŭ����), 2(interface, �������̽�)
	CString m_name;		// Ŭ������ �̸� ����
	CString m_attribute; // Ŭ������ ���� ����
	CString m_operation; // Ŭ������ �Լ� ����

public:
	QtBox() {};
	QtBox(CPoint pos_center, int stereotype, const CString& name, const CString& attribute, const CString& operation); // : ��ü ������
	void redraw(CClientDC & dc, bool selected); // �ڱ��ڽ� �׸���, selected�̸� ���� �׵θ� �׸���
	void move(CPoint vec); // vec ��ŭ �̵�
	bool select(CPoint pos); //��ǥ�� ���� �ȿ� ������ true, �ƴϸ� false
	bool selectArea(CPoint lu, CPoint rd); //lu, rd�� �Ǿ��ִ� ���簢�� �ȿ� �� ������Ʈ�� �ִ���
	void setStereotype(int stereotype); //
	void setName(CString name);
	void setAttribute(CString attribute);
	void setOperation(CString operation);
	CPoint getLu();
	CPoint getRd();
	CPoint edgeCheck(CPoint pos); // ���� ����� edge���� �����ǥ ����, ������(-1, -1)
	void save(CArchive& ar);
	void load(CArchive& ar);

};