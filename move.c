/*
 * move.c
 * 	연속적으로 움직이게 하기 위한 함수
 */
#include	<stdio.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	"snake.h"

extern int waitinput;

void *getinput(void *p) 
{   
		waitinput = 0;
		int c = getchar();

		int change = 1;
		switch (*(int *) p)
		{
				case 'w':					
						if (c == 's' || c ==  'S') change = 0;
						break;
				case 's': 
						if (c == 'w' || c ==  'W') change = 0;
						break;
				case 'a': 
						if (c == 'd' || c ==  'D') change = 0;
						break;
				case 'd': 
						if (c == 'a' || c ==  'A') change = 0;
						break;
		} 

		if (change)
				switch (c) 
				{ 
						case 'w': case 'a': case 's': case 'd':   		  
								*(int *) p = c;
								break;
				}
		waitinput = 1;
}

void speedcontrol( int length, int level ) {
	int speed;
	speed = 100-length*level;
	if (speed > 0)
		usleep(speed*1000/1000*1000);
	else
		usleep(speed*10/1000*1000);
}
