#include "cub3d.h"
#include <stdio.h>

int	on_keypress(t_data *data)
{
	int	i;

	i = 0;
	while (i < 10000000)
		i++;
	if (data->player_move.forward == 1)
		move(data, 0, -1);
	if (data->player_move.backward == 1)
		move(data, 0, 1);
	if (data->player_move.left == 1)
		move(data, -1, 0);
	if (data->player_move.right == 1)
		move(data, 1, 0);
	return (0);
}

int	release_inputs(int keysym, t_data *data)
{
	if (keysym == 119 && data->player_move.forward == 1)
		data->player_move.forward = 0;
	if (keysym == 115 && data->player_move.backward == 1)
		data->player_move.backward = 0;
	if (keysym == 97 && data->player_move.left == 1)
		data->player_move.left = 0;
	if (keysym == 100 && data->player_move.right == 1)
		data->player_move.right = 0;
	if (keysym == 65361 && data->player_move.rotate == 1)
		data->player_move.rotate = 0;
	if (keysym == 65363 && data->player_move.rotate == 1)
		data->player_move.rotate = 0;
	return (0);
}

int	get_inputs(int keysym, t_data *data)
{
	if (keysym == 65307)
		exit_and_free(data);
	if (keysym == 119)
		data->player_move.forward = 1;
	if (keysym == 115)
		data->player_move.backward = 1;
	if (keysym == 97)
		data->player_move.left = 1;
	if (keysym == 100)
		data->player_move.right = 1;
	if (keysym == 65361)
		data->player_move.rotate = 1;
	if (keysym == 65363)
		data->player_move.rotate = 1;
	return (0);
}