#pragma once

/*QtBox의 m_stereotype*/
#define ST_UTILITY 1 //기본
#define ST_ABSTRACT 2 //추상클래스
#define ST_INTERFACE 3 //인터페이스

/*QtLine의 m_relation*/
#define REL_GENERALIZATION 1 //일반화
#define REL_REALIZATION 2 //실체화
#define REL_DEPENDENCY 3 //의존
#define REL_ASSOCIATION 4 //연관

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
	static CPoint getDirection(CPoint relPos); //해당 relPos에서 빠져나가는 방향을 구하는 함수, 5 pixel
	~QtShape();
};
