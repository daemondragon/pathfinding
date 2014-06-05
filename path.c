#include <stdlib.h>

#include "path.h"

void init_file(control *control_list, const path_pos start)
{
	file_path_pos *add = malloc(sizeof(*add));
	if(add != NULL)
	{
		add->actual.x = start.x;
		add->actual.y = start.y;
		add->next = NULL; 
	
		control_list->fisrt = add;
		control_list->last = add;
	}
}

void add_to_file(control *control_list, path_pos new)
{
	file_path_pos *add = malloc(sizeof(*add));
	if(add != NULL)
	{
		add->actual.x = new.x;
		add->actual.y = new.y;
	
		control_list->last->next = add;
		control_list->last = add;
		add->next = NULL;
	}
}
void remove_to_file(control *control_list)
{
	file_path_pos *remove = control_list->fisrt;
	if(control_list->fisrt != NULL)
	{
		control_list->fisrt = control_list->fisrt->next;
		free(remove);
	}
}

void add_to_pile(path_directory **control, char directory)
{
	path_directory *add = malloc(sizeof(*add));
	if(add != NULL)
	{
		add->directory = directory;
		add->next = *control;
		*control = add;
	}
}


path_directory* create_path(const int width, const int height, int map[][height],
				const path_pos start, const path_pos end, int pivot)
{
	if(start.x == end.x && start.y == end.y)
	{
		return NULL;
	}
	else
	{
		char finish = 1;
		int cost[width][height];
		int i;
		int j;
		
		for(i = 0 ; i < width ; i++)
		{
			for(j = 0 ; j < height ; j++)
			{
				cost[i][j] = 0;
			}
		}

		path_pos actual;
		path_pos next;
		control control_list;
		
		cost[start.x][start.y] = 1;
		
		init_file(&control_list, start);
		/*
		increase the cost of tile according to the distance with start position
		*/
		while(control_list.fisrt != NULL && finish)
		{
			actual.x = control_list.fisrt->actual.x;
			actual.y = control_list.fisrt->actual.y;
			
			if(actual.x == end.x && actual.y == end.y)
			{
				finish = 0;
			}

			if(actual.x != 0)
			{
				if(map[actual.x-1][actual.y] >= pivot && cost[actual.x-1][actual.y] == 0)
				{
					next.x = actual.x-1;
					next.y = actual.y;
					cost[next.x][next.y] = cost[actual.x][actual.y] + 1;

					add_to_file(&control_list, next);					
				}
			}
			if(actual.x != width -1)
			{
				if(map[actual.x+1][actual.y] >= pivot && cost[actual.x+1][actual.y] == 0)
				{
					next.x = actual.x+1;
					next.y = actual.y;
					cost[next.x][next.y] = cost[actual.x][actual.y] + 1;

					add_to_file(&control_list, next);
				}
			}
			if(actual.y != 0)
			{
				if(map[actual.x][actual.y-1] >= pivot && cost[actual.x][actual.y-1] == 0)
				{				
					next.x = actual.x;
					next.y = actual.y-1;
					cost[next.x][next.y] = cost[actual.x][actual.y] + 1;
					
					add_to_file(&control_list, next);
				}
			}
			if(actual.y != height - 1)
			{
				if(map[actual.x][actual.y+1] >= pivot && cost[actual.x][actual.y+1] == 0)
				{				
					next.x = actual.x;
					next.y = actual.y+1;
					cost[next.x][next.y] = cost[actual.x][actual.y] + 1;

					add_to_file(&control_list, next);
				}
			}
			remove_to_file(&control_list);
		}
		/*free memory*/
		while(control_list.fisrt != NULL)
		{
			remove_to_file(&control_list);
		}
		if (finish == 0)
		{
			finish = 1;
			actual.x = end.x;
			actual.y = end.y;
			path_directory *control = NULL;
			char directory;
			
			/*return pile of directory (one by one)*/
			while((actual.x != start.x && finish) || (actual.y != start.y && finish))
			{
				if(cost[actual.x][actual.y+1] == cost[actual.x][actual.y] - 1)
				{
					directory = NORTH;
					actual.y++;	
				}
				else if(cost[actual.x][actual.y-1] == cost[actual.x][actual.y] - 1)
				{
					directory = SOUTH;
					actual.y--;
				}
				else if(cost[actual.x+1][actual.y] == cost[actual.x][actual.y] - 1)
				{
					directory = WEST;
					actual.x++;
				}
				else
				{
					directory = EAST;
					actual.x--;
				}
				add_to_pile(&control, directory);
			}
			return (control);
		}
		else
		{
			return NULL;
		}
	}
}
