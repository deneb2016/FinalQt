#include "stdafx.h"
#include "QtShape.h"
int QtShape::nextKey = 1;
QtShape::QtShape()
{
}


QtShape::~QtShape()
{
}

CPoint QtShape::relativeToAbsolute(CPoint lu, CPoint rd, CPoint relPos) {
	CPoint diff = rd - lu;
	diff.x *= relPos.x / 100;
	diff.y *= relPos.y / 100;
	return diff+lu;
}

int QtShape::getKey()
{
	return key;
}

int QtShape::nearPoint(CPoint pos1, CPoint pos2) {
	int dx = abs(pos1.x - pos2.x);
	int dy = abs(pos1.y - pos2.y);

	if (abs(pos1.x - pos2.x) <= PIX && abs(pos1.y - pos2.y) <= PIX) //+-2pixel 이내에 있으면
		return dx + dy; // 0~4, 작을수록 근접
	else return -1;
}

CPoint QtShape::getDirection(CPoint relPos) {
	int pl = 5;//pixel length
	if (relPos.x == 100) return CPoint{ pl,0 };
	else if (relPos.x == 0) return CPoint{ -pl,0 };
	else if (relPos.y == 100) return CPoint{ 0,pl };
	else if (relPos.y == 0) return{ 0,-pl };
	else return -1;
}
bool QtShape::inRect(CPoint lu, CPoint rd, CPoint pos) {
	return (lu.x <= pos.x && pos.x <= rd.x && lu.y <= pos.y && pos.y <= rd.y);
}