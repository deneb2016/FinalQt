#pragma once
#define STRAIGHT 0
#define SQUARE 1
#define BOX 1
#define LINE 2
#define FROM 3
#define TO 4
#define INH 1
#define DEP 3

/*QtBox의 m_stereotype*/
#define ST_UTILITY 1 //기본
#define ST_ABSTRACT 2 //추상클래스
#define ST_INTERFACE 3 //인터페이스

/*QtLine의 m_relation*/
#define REL_GENERALIZATION 1 //일반화
#define REL_REALIZATION 2 //실체화
#define REL_DEPENDENCY 3 //의존
#define REL_ASSOCIATION 4 //연관