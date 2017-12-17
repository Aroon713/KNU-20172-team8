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
	while ( p->next_body != NULL )
	{
		body_length++;
		p = p->next_body;
	}
	return body_length;
}
