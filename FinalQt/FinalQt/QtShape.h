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
	static bool inRect(CPoint lu, CPoint rd, CPoint pos); //pos가 해당 Rectangle 내에 있는지 리턴하는 함수
	static CPoint getDirection(CPoint relPos); //해당 relPos에서 빠져나가는 방향을 구하는 함수, 5 pixel
	~QtShape();
};
