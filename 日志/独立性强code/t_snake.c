#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define APPLE '@'
#define SNAKE_HEAD '+'
#define SNAKE_TAIL '-'

typedef struct{
	int row,col;
}pt;

typedef struct{
	pt head,tail;
}snake;

enum{ABOVE,BELOW,LEFT,RIGHT};
enum{NOOVERLAP,OVERLAP};

void init_snake(snake *p_snake)
{
	p_snake->head.row=rand()%(SIZE-2)+1;
	p_snake->head.col=rand()%(SIZE-2)+1;
	p_snake->tail=p_snake->head;
	switch(rand()%4)
	{
		case ABOVE:
			p_snake->tail.row--;
			break;
		case BELOW:
			p_snake->tail.row++;
			break;
		case LEFT:
			p_snake->tail.col--;
			break;
		case RIGHT:
			p_snake->tail.col++;
			break;
	}
}

void init_apple(pt *p_apple)
{
	p_apple->row=rand()%SIZE;
	p_apple->col=rand()%SIZE;
}

void move_snake(snake *p_snake)
{
	pt tmp={0};
	int direction=0;
	printf("请输入代表方向的数字，%d代表上，%d代表下，%d代表左，%d代表右：",ABOVE,BELOW,LEFT,RIGHT);
	scanf("%d",&direction);
	if(direction<0||direction>3)
		return;
	tmp=p_snake->head;
	switch(direction)
	{
		case ABOVE:
			tmp.row--;
			break;
		case BELOW:
			tmp.row++;
			break;
		case LEFT:
			tmp.col--;
			break;
		case RIGHT:
			tmp.col++;
			break;
	}
	if(tmp.row<0||tmp.row>=SIZE)
		return;
	if(tmp.col<0||tmp.col>=SIZE)
		return;
	if(tmp.row==p_snake->tail.row && tmp.col==p_snake->tail.col)
		return;
	p_snake->tail=p_snake->head;
	p_snake->head=tmp;
}

int overlap(const pt *p_apple,const snake *p_snake)
{
	if(p_apple->row==p_snake->head.row && p_apple->col==p_snake->head.col)
		return OVERLAP;
	else if(p_apple->row==p_snake->tail.row && p_apple->col==p_snake->head.col)
		return OVERLAP;
	else 
		return NOOVERLAP;
}

void show_map(const pt *p_apple,const snake *p_snake)
{
	int row=0,col=0;
	for(row=0;row<=SIZE-1;row++)
	{
		for(col=0;col<=SIZE-1;col++)
		{
			if(row==p_apple->row && col==p_apple->col)
				printf("%c",APPLE);
			else if(row==p_snake->head.row && col==p_snake->head.col)
				printf("%c",SNAKE_HEAD);
			else if(row==p_snake->tail.row && col==p_snake->tail.col)
				printf("%c",SNAKE_TAIL);
			else
				printf(" ");
		}
	  	printf("\n");
	}

}
int main()
{
	snake snk={0};
	pt apple={0};
	init_apple(&apple);
	init_snake(&snk);
	while(1)
	{	
		if(overlap(&apple,&snk))
			init_apple(&apple);
		else
			break;
	}
	show_map(&apple,&snk);
	while(1)
	{
		move_snake(&snk);
		while(1)
		{
			if(overlap(&apple,&snk))
				init_apple(&apple);
			else
				break;
		}
		show_map(&apple,&snk);
	}
	return 0;
}
