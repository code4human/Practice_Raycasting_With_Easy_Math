#include "wall_header.h"

static int map[MAPX][MAPY] = {
	{1,1,1,1,1},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,1,0,0,1},
	{1,1,0,0,1},
	{1,1,1,1,1}
};

int		map_get_cell(int x, int y)
{
	return (x >= 0 && x < MAPX && y >= 0 && y < MAPY) ? map[x][y] : -1;
}