#pragma once
#define STRAIGHT 0
#define SQUARE 1
#define BOX 1
#define LINE 2
#define FROM 3
#define TO 4
#define INH 1
#define DEP 3

/*QtBox�� m_stereotype*/
#define ST_UTILITY 1 //�⺻
#define ST_ABSTRACT 2 //�߻�Ŭ����
#define ST_INTERFACE 3 //�������̽�

/*QtLine�� m_relation*/
#define REL_GENERALIZATION 1 //�Ϲ�ȭ
#define REL_REALIZATION 2 //��üȭ
#define REL_DEPENDENCY 3 //����
#define REL_ASSOCIATION 4 //����