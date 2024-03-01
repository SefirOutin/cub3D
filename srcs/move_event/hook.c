#include "cub3d.h"
#include <stdio.h>

int	on_keypress(t_data *data)
{
	int	i;

	i = 0;
	while (i < 20000000)
		i++;
	if (data->player.inputs[W_KEY][1] == 1)
		move(data, 0, -1, 0);
	if (data->player.inputs[S_KEY][1] == 1)
		move(data, 0, 1, 0);
	if (data->player.inputs[A_KEY][1] == 1)
		move(data, -1, 0, 0);
	if (data->player.inputs[D_KEY][1] == 1)
		move(data, 1, 0, 0);
	if (data->player.inputs[LEFT_ROTATE][1] == 1)
		move(data, 0, 0, 1);
	if (data->player.inputs[RIGHT_ROTATE][1] == 1)
		move(data, 0, 0, -1);
	// printf("%d\n", data->player.inputs[LEFT_ROTATE][1]);
	// printf("%d\n", data->player.inputs[RIGHT_ROTATE][1]);
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