#pragma once
#include "Global.h"

class QtShape
{
protected:
	int key;
public:
	static int nextKey;
public:
	QtShape();

	virtual bool select(CPoint position) = 0;
	virtual bool selectArea(CPoint lu, CPoint rd) = 0;
	virtual void move(CPoint vec) = 0;
	virtual void redraw(CClientDC & dc, bool selected) = 0;
	virtual void save(CArchive& ar) = 0;
	virtual void load(CArchive& ar) = 0;
	int getKey();
	static int nearPoint(CPoint pos1, CPoint pos2);
	static CPoint relativeToAbsolute(CPoint lu, CPoint rd, CPoint relPos);
	static bool inRect(CPoint lu, CPoint rd, CPoint pos); //pos�� �ش� Rectangle ���� �ִ��� �����ϴ� �Լ�
	static CPoint getDirection(CPoint relPos); //�ش� relPos���� ���������� ������ ���ϴ� �Լ�, 5 pixel
	~QtShape();
};
