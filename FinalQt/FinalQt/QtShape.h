#pragma once

#define ST_UTILITY 1 //STEREOTYPE
#define ST_ABSTRACT 2
#define ST_INTERFACE 3

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
	static bool inRect(CPoint lu, CPoint rd, CPoint pos); //pos가 해당 Rectangle 내에 있는지 리턴하는 함수
	~QtShape();
};
