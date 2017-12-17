/*#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>
#include <time.h>
#include <pthread.h>*/
#include "snake.h"

int body_length=1;//먹이 먹고 나면 1씩 올릴 예정;

pfood food_target;
int row, col;
void move_next_frame(pbody);//다음 프레임으로 넘어가기 전, 바디의 좌표를 다음 위치로 옮긴다.
void update_frame(pbody);//프레임 새로고침
void is_get_food(pbody);//음식과 헤드의 위치가 같은지 확인
void drop_food(pbody);//음식을 랜덤한 위치에 생성
int check_collision(pbody);
int waitinput = 1;

void start();//초기 시작화면

void main()
{
	pbody head=(pbody)malloc(sizeof(body));
	int c;
	pthread_t inputkey;

	initscr();
	noecho();
	crmode();
	clear();
	getmaxyx(stdscr, row, col);
	/* 초기 시작화면 */
	start();

	food_target=(pfood)malloc(sizeof(food));
	food_target->pos_x=row/2;
	food_target->pos_y=col/2;
	head->pos_x=row/2;
	head->pos_y=col/2;
	head->next_body=NULL;
	head->before_body=NULL;
	move(food_target->pos_x, food_target->pos_y);
	addch('F');
	move(head->pos_x, head->pos_y);
	addch('O');
	refresh();
	is_get_food(head);
	c = 'w';
	while(1)
	{
		move_next_frame(head);
		refresh();
		while(1){
		if(c=='w'||c=='W'){head->pos_x-=1;break;}
		else if(c=='s'||c=='S'){head->pos_x+=1;break;}
		else if(c=='a'||c=='A'){head->pos_y-=1;break;}
		else if(c=='d'||c=='D'){head->pos_y+=1;break;}
		else continue;}
		if(check_collision(head)==9)break;
		is_get_food(head);
		update_frame(head);
		//if (waitinput) pthread_create(&inputkey, NULL, getinput, &c);//스레드를 추가해 입력받기
		
		speedcontrol(body_length, 5);//속도 조절부
	}
	
	clear();
	refresh();
	endwin();
}

void start()
/*
 * 초기 시작화면 출력 함수 난이도 상 중 하를 입력받고 초기 속도를 조절합니다.
 */
{
	char level;
	
	curs_set(0);
	move(3, 3);
	addstr("Welcome to game!!");
	move(4, 3);
	addstr("Input level  (hard : 1, normal : 2, easy : 3)");
	refresh();
	while (1) {
		level = getch();
		if (level == '1') {
			speedcontrol(body_length, 7);
			break;
		}
		else if (level == '2') {
			speedcontrol(body_length, 5);
			break;
		}
		else if (level == '3') {
			speedcontrol(body_length, 3);
			break;
		}
		
	}
	clear();
	refresh();
}

void move_next_frame(pbody head)
{
	pbody current_body=head;
	int temp_x, temp_y, to_x, to_y;//temp:임시 저장, to:실제 사용하는 부분
	to_x=current_body->pos_x;//현재 데이터를 사용할 부분으로 이동
	to_y=current_body->pos_y;
	while(current_body->next_body!=NULL)//구조체 body의 next_body의 기본 값이 NULL이므로, 꼬리에 도달하면 멈추게 됨.
	{
		temp_x=current_body->next_body->pos_x;
		temp_y=current_body->next_body->pos_y;//다음 바디의 데이터 저장
		current_body->next_body->pos_x=to_x;
		current_body->next_body->pos_y=to_y;//다음 바디의 데이터를 현재 데이터로 덮어씀
		to_x=temp_x;
		to_y=temp_y;//저장해 둔 다음 바디의 데이터를 사용할 부분으로 이동
		current_body=current_body->next_body;//다음 바디로 이동
	}//마지막 꼬리 부분에 대해선 while이 실행되지 않으므로 밑에서 추가 실행
	current_body->pos_x=to_x;
	current_body->pos_y=to_y;
}

void update_frame(pbody head)
{
	pbody current_body=head;
	clear();
	move(food_target->pos_x, food_target->pos_y);
	addch('F');
	do
	{
		move(current_body->pos_x, current_body->pos_y);
		addch('O');
		if(current_body->next_body)current_body=current_body->next_body;
	}while(current_body->next_body!=NULL);
	refresh();
}

void is_get_food(pbody head)
{
	pbody new,current;
	if(head->pos_x==food_target->pos_x&&head->pos_y==food_target->pos_y)
	{
		new=(pbody)malloc(sizeof(body));
		current=head;
		while(current->next_body!=NULL)current=current->next_body;
		current->next_body=new;
		new->before_body=current;
		new->next_body=NULL;
		new->pos_y=row+1;
		new->pos_x=col+1;
		drop_food(head);
		body_length += 1;
		
	}
}

void drop_food(pbody head)
{
	int pos_x, pos_y;
	pbody current;
	srand((unsigned int)time(NULL));
	pos_x=rand()%row;
	pos_y=rand()%col;

/*	while(current->next_body!=NULL)
	{
		if(pos_x==current->pos_x&&pos_y==current->pos_y)
		{
			pos_x=rand()%row;
			pos_y=rand()%col;
			current=head;
		}
		else if(current->next_body==NULL)break;
		
		current=current->next_body;
	} *///음식이 바디가 없는 곳에만 생성되게 만들고 싶음
	food_target->pos_x=pos_x;
	food_target->pos_y=pos_y;

}

int check_collision(pbody head)
{
	pbody current;

	if(head->next_body==NULL)
		if(head->next_body->next_body==NULL)
			return 1;
	
	current=head;
	while(current->next_body!=NULL)
	{
		current=current->next_body;
		if(head->pos_x==0 || head->pos_x==row || head->pos_y == 0 || head->pos_y == col)
			return 9;
		if(head->pos_x==current->pos_x&&head->pos_y==current->pos_y)
			return 9;
	}
	return 1;
}
