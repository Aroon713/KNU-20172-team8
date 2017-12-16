/* score.c
 *	점수 관리를 위한 함수
 *
 *
 *
 */

#include	<stdio.h>
#include	<stdlib.h>
#include	"snake.h"

int snake_len(pbody p)
{
	int body_length = 1; 
	while ( p -> nextbody != NULL )
	{
		body_length++;
		p = p->next;
	}
	return body_length;
}
