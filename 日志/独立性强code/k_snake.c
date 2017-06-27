#include<stdio,h>
typedef struct{
	int row,col;
}pt;
typedef struct{
	pt head,tail;
}snake;

void init snake(snake *p_snake)
{
	
}

void init_apple(pt *p_apple)
{
	
}

void move_snake(snake *p_snake)
{
	
}

int overlap(const pt *p_apple,const snake *p_snake)
{
		
}

void show_map(const pt *p_apple,const snake *p_snake)
{

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
