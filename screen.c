#include	"snake.h"



int start()
/*
 * 초기 시작화면 출력 함수 난이도 상 중 하를 입력받고 초기 속도를 조절합니다.
 */
{
	int level, temp;
	
	curs_set(0);
	move(3, 3);
	addstr("Welcome to game!!");
	move(4, 3);
	addstr("Input level  (hard : 1, normal : 2, easy : 3)");
	refresh();
	while (1) {
		level = getch();
		if (level == '1') {
			temp = 8;
			break;
		}
		else if (level == '2') {
			temp = 4;
			break;
		}
		else if (level == '3') {
			temp = 2;
			break;
		}
		
	}
	clear();
	refresh();
	return temp;
}

int finish()
/*
 * 초기 시작화면 출력 함수 난이도 상 중 하를 입력받고 초기 속도를 조절합니다.
 */
{
	char level, temp;
	
	curs_set(0);
	move(3, 3);
	addstr("You Died!! ");
	move(4, 3);
	addstr("Input level  (hard : 1, normal : 2, easy : 3 exit : Q)");
	refresh();
	while (1) {
		level = getch();
		if (level == '1') {
			temp = 8;
			break;
		}
		else if (level == '2') {
			temp = 4;
			break;
		}
		else if (level == '3') {
			temp = 2;
			break;
		}
		else if (level == 'Q' || level == 'q'){
			temp = 0;
			break;
		}
		
	}
	clear();
	refresh();
	return temp;
}
