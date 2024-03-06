#include "cub3d.h"
#include <stdio.h>

int	on_keypress(t_data *data)
{
	int	i;

	i = 0;
	if (data->player.inputs[W_KEY][1] == 1)
		move(data, 0, -1, 0);
	if (data->player.inputs[S_KEY][1] == 1)
		move(data, 0, 1, 0);
	if (data->player.inputs[A_KEY][1] == 1)
		move(data, -1, 0, 0);
	if (data->player.inputs[D_KEY][1] == 1)
		move(data, 1, 0, 0);
	if (data->player.inputs[LEFT_ROTATE][1] == 1)
	{
		data->player.direction = fix_ang(data->player.direction);
		move(data, 0, 0, 0.5);
	}
	if (data->player.inputs[RIGHT_ROTATE][1] == 1)
	{
		data->player.direction = fix_ang(data->player.direction);
		move(data, 0, 0, -0.5);
	}
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
