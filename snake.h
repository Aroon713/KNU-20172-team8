/*
 *	snake.h
 *
 */
#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>
#include <time.h>
#include <pthread.h>

void *getinput(void *p);
void speedcontrol(int, int);

typedef struct body{//바디를 이루는 문양이 될 예정
		int pos_x;//x축 위치
		int pos_y;//y축 위치
		struct body *next_body;
		struct body *before_body;//바디는 링크드 리스트로 구현
}body;
typedef struct body* pbody;

typedef struct food{

	int pos_x;
	int pos_y;
}food;
typedef struct food *pfood;
