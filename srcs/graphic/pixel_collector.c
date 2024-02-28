#include "cub3d.h"
#include <math.h>
#include <stdio.h>

int	convert_map_to_pixel(char **map, int x, int y)
{
    printf("[%d;%d]\n",(int)trunc(x / 50), (int)trunc(y / 50));
    printf("%c\n",map[(int)trunc(x / 50)][(int)trunc(y / 50)]);
	/*if (map[(int)trunc(x / 50)][(int)trunc(y / 50)] == 1)
		return (0);
	else if (map[(int)trunc(x / 50)][(int)trunc(y / 50)] == 0)
		return (1);
    */
    return (0);
}
