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

/*QtBox�� m_stereotype*/
#define ST_UTILITY 0 //�⺻
#define ST_ABSTRACT 1 //�߻�Ŭ����
#define ST_INTERFACE 2 //�������̽�

/*QtLine�� m_relation*/
#define REL_GENERALIZATION 0 //�Ϲ�ȭ
#define REL_REALIZATION 1 //��üȭ
#define REL_DEPENDENCY 2 //����
#define REL_ASSOCIATION 3 //����