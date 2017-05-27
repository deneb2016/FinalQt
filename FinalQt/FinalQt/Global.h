#pragma once
#define STRAIGHT 1
#define SQUARE 0
#define BOX 1
#define LINE 2
#define FROM 3
#define TO 4
#define INH 1
#define DEP 3
#define PIX 5

/*QtBox의 m_stereotype*/
#define ST_UTILITY 0 //기본
#define ST_ABSTRACT 1 //추상클래스
#define ST_INTERFACE 2 //인터페이스

/*QtLine의 m_relation*/
#define REL_GENERALIZATION 0 //일반화
#define REL_REALIZATION 1 //실체화
#define REL_DEPENDENCY 2 //의존
#define REL_ASSOCIATION 3 //연관