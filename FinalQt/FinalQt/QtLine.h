#pragma once
#include "QtShape.h"
#include <vector>
class QtBox;


class QtLine : public QtShape {
private:
	CPoint m_absStart, m_absEnd; // ���� ��ǥ
	CPoint m_relStart, m_relEnd; // ��� ��ǥ(0~100, �ۼ�Ʈ)
	int m_relation; // �� Ŭ������ ����
	bool m_diagonal; //�����̸� 0, �缱�̸� 1
	std::vector<CPoint> m_trace; //�׸� ���͵�, start->end������
public:
	QtLine() {};
	QtBox *m_pboxStart, *m_pboxEnd; // ����Ű�� ����
	QtLine(QtBox* startBox, CPoint relStart, int relation, bool diagonal);  // � �ڽ����� �ִ���, �����ǥ�� �޾Ƽ� StartPoint ����, EndPoint�� ó������ �ش� ����
	int pointCheck(CPoint pos); // START(1) / END(0) ����Ʈ �� ��� ����Ʈ �ֺ��� �ִ��� ����, ���� �ش�ȵǸ� - 1����
	void setAbsEndPoint(CPoint pos); // end�� ����� ���� ���� ����, m_relEnd�� 0�϶�
	void setRelEndPoint(QtBox* endBox, CPoint relEnd); //�갡 �ٲ��, ������ǥ�� �ٲ���ߵ�.
	void setAbsStartPoint(CPoint pos); // start�� ����� ���� ���� ����, m_relStart�� 0�϶�
	void setRelStartPoint(QtBox* startBox, CPoint relStart); //�갡 �ٲ��, ������ǥ�� �ٲ���ߵ�.
															 //	(*�����ǥ set �Ҷ�, �ڽ��� NULL�� ȣ��ɼ��� ����.)
	void redraw(CClientDC & dc, bool selected); // �ڱ��ڽ� �׸���, selected�̸� ����(������ / ������ ū �� ǥ��);, �׸��� ���� �����ǥ�� ������ǥ�� �ٲ��ֱ�
	void move(CPoint vec); // ����� �ִ� ���鸸 ������ǥ �̵�
	bool select(CPoint position); //+-1point
	bool selectArea(CPoint lu, CPoint rd); // ���� �� �� ��ΰ� Area���� ���ԵǸ� 1����, �ƹ̳� 0

	virtual void save(CArchive& ar);
	virtual void load(CArchive& ar);

};