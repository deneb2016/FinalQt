#pragma once

/*QtBox�� m_stereotype*/
#define ST_UTILITY 1 //�⺻
#define ST_ABSTRACT 2 //�߻�Ŭ����
#define ST_INTERFACE 3 //�������̽�

/*QtLine�� m_relation*/
#define REL_GENERALIZATION 1 //�Ϲ�ȭ
#define REL_REALIZATION 2 //��üȭ
#define REL_DEPENDENCY 3 //����
#define REL_ASSOCIATION 4 //����

class QtShape
{
protected:
	int key;
	static int nextKey;
public:
	QtShape();
	virtual bool select(CPoint position) = 0;
	virtual bool selectArea(CPoint lu, CPoint rd) = 0;
	virtual void move(CPoint vec) = 0;
	virtual void redraw(CClientDC & dc, bool selected) = 0;
	int getKey();
	static int nearPoint(CPoint pos1, CPoint pos2);
	static CPoint relativeToAbsolute(CPoint lu, CPoint rd, CPoint relPos);
	static bool inRect(CPoint lu, CPoint rd, CPoint pos); //pos�� �ش� Rectangle ���� �ִ��� �����ϴ� �Լ�
	static CPoint getDirection(CPoint relPos); //�ش� relPos���� ���������� ������ ���ϴ� �Լ�, 5 pixel
	~QtShape();
};
