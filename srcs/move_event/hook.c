#include "cub3d.h"
#include <stdio.h>

int	on_keypress(t_data *data)
{
	if (data->player.inputs[W_KEY][1] == 1)
		move(data, cos(fix_ang(deg_to_rad(data->player.direction))),
			-sin(fix_ang(deg_to_rad(data->player.direction))), 0);
	if (data->player.inputs[S_KEY][1] == 1)
		move(data, cos(fix_ang(deg_to_rad(data->player.direction + 180))),
			-sin(fix_ang(deg_to_rad(data->player.direction + 180))), 0);
	if (data->player.inputs[A_KEY][1] == 1)
		move(data, cos(fix_ang(deg_to_rad(data->player.direction + 90))),
			-sin(fix_ang(deg_to_rad(data->player.direction + 90))), 0);
	if (data->player.inputs[D_KEY][1] == 1)
		move(data, cos(fix_ang(deg_to_rad(data->player.direction + 270))),
			-sin(fix_ang(deg_to_rad(data->player.direction + 270))), 0);
	if (data->player.inputs[LEFT_ROTATE][1] == 1)
		move(data, 0, 0, +0.3);
	if (data->player.inputs[RIGHT_ROTATE][1] == 1)
		move(data, 0, 0, -0.3);
	return (0);
}


int	release_inputs(int keysym, t_data *data)
{
	if (keysym == 119 && data->player.inputs[W_KEY][1] == 1)
		data->player.inputs[W_KEY][1] = 0;
	if (keysym == 115 && data->player.inputs[S_KEY][1] == 1)
		data->player.inputs[S_KEY][1] = 0;
	if (keysym == 97 && data->player.inputs[A_KEY][1] == 1)
		data->player.inputs[A_KEY][1] = 0;
	if (keysym == 100 && data->player.inputs[D_KEY][1] == 1)
		data->player.inputs[D_KEY][1] = 0;
	if (keysym == 65361 && data->player.inputs[LEFT_ROTATE][1] == 1)
		data->player.inputs[LEFT_ROTATE][1] = 0;
	if (keysym == 65363 && data->player.inputs[RIGHT_ROTATE][1] == 1)
		data->player.inputs[RIGHT_ROTATE][1] = 0;
	return (0);
}

int	get_inputs(int keysym, t_data *data)
{
	// printf("%d\n", keysym);
	if (keysym == 65307)
		exit_and_free(data);
	if (keysym == 119)
		data->player.inputs[W_KEY][1] = 1;
	if (keysym == 115)
		data->player.inputs[S_KEY][1] = 1;
	if (keysym == 97)
		data->player.inputs[A_KEY][1] = 1;
	if (keysym == 100)
		data->player.inputs[D_KEY][1] = 1;
	if (keysym == 65361)
		data->player.inputs[LEFT_ROTATE][1] = 1;
	if (keysym == 65363)
		data->player.inputs[RIGHT_ROTATE][1] = 1;
	return (0);
}

// int	mouse(int x, int y, t_data *data)
// {
// 	// data->player.px + x;
// 	// data->player.py + y;
	
// 	printf ("Ax:%d Ay:%d\n", (int)data->player.px, (int)data->player.py);
// 	printf("Cx:%d Cy:%d\n", x, y);
// 	// printf ("Bx:%d By:%d\n");
// 	return (0);
// }
