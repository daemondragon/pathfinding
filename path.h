#ifndef PATH_H
#define PATH_H

typedef struct path_directory path_directory;
struct path_directory
{
	char directory;
	path_directory *next;
};
/*
last is used for the pile
next are used for calculate the cost of tile's map
*/
typedef struct path_pos path_pos;
struct path_pos
{
	int x;
	int y;
};

typedef struct file_path_pos file_path_pos;
struct file_path_pos
{
	file_path_pos *next;
	path_pos actual;
};

typedef struct control control;
struct control
{
	file_path_pos *first;
	file_path_pos *last;
};

enum
{
	NORTH, SOUTH, EAST, WEST
};

void init_file(control *control_list, const path_pos start);
void add_to_file(control *control_list, path_pos new);
void remove_to_file(control *control_list);
void add_to_pile(path_directory **control, char directory);
path_directory* create_path(const int width, const int height, int map[][height],
				const path_pos start, const path_pos end, int pivot);
#endif
