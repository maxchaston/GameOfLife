#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

#define SCREEN_W 16
#define SCREEN_H 16

/* Conway's game of life simulation:
 *  Any live cell with fewer than two live neighbours dies, as if by underpopulation.
    Any live cell with two or three live neighbours lives on to the next generation.
    Any live cell with more than three live neighbours dies, as if by overpopulation.
    Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
*/

int neighbour_count(int x, int y, char *char_array)
{
	int count = 0;
	for (int xi=-1;xi<2;xi++)
	{
		for (int yj=-1;yj<2;yj++)
		{
			if (x+xi<SCREEN_W && x+xi>=0 && y+yj<SCREEN_H && y+yj>=0 && !(xi==0 && yj==0)) 
			{
				/* printf("testing %d,%d (found '%c')\n",x+xi,y+yj, char_array[(y+yj)*SCREEN_W + (x+xi)]); */
				if (char_array[(y+yj)*SCREEN_W + (x+xi)] == '#')
				{
					count++;
				}
			}
		}
	}
	return count;
}

void draw(char* state)
{
	for (int x=0; x<SCREEN_W; x++)
	{
		for (int y=0; y<SCREEN_H; y++)
		{
			if (state[y * SCREEN_W + x] == '#')
				mvprintw(y,x,"#");
		}
	}
}

char* step(char* state)
{
	char* new_state = malloc(sizeof(char)*SCREEN_W*SCREEN_H);
	for (int x=0; x<SCREEN_W; x++)
	{
		for (int y=0; y<SCREEN_H; y++)
		{
			int neighbours = neighbour_count(x,y,state);
			if (state [y*SCREEN_W + x] == '#')
			{
				if (neighbours<2)
					new_state[y*SCREEN_W + x] = ' ';
				if (neighbours == 2 || neighbours == 3)
					new_state[y*SCREEN_W + x] = '#';
				if (neighbours > 3)
					new_state[y*SCREEN_W + x] = ' ';
			}
			else
			{
				if (neighbours == 3)
					new_state[y*SCREEN_W + x] = '#';
			}
		}
	}
	return new_state;
}

int main()
{
	initscr();
	char *initial_points = 
		"  #             "
		"   #            "
		" ###            "
		"                "
		"                "
		"                "
		"                "
		"                "
		"                "
		"                "
		"                "
		"                "
		"                "
		"                "
		"                "
		"                ";

	char *current_state = initial_points;
	while (1)
	{
		clear();
		draw(current_state);
		refresh();
		current_state = step(current_state);
		getch();
	}
	getch();
	endwin();
	free(current_state);
	return 0;
}


