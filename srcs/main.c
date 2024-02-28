/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:09:51 by soutin            #+#    #+#             */
/*   Updated: 2024/02/28 00:40:35by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_err(char *err_message)
{
	ft_printf("Error\n%s\n", err_message);
}

void    draw_circle(t_data *data, int y_center, int x_center, int r)
{
    int x;
    int y;
    int d;
    
	x = 0;
	y = r;
	d = r - 1;
	while (y >=x)
    {
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x+x_center , y+y_center, 0xFF0000);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, y+x_center , x+y_center, 0xFF0000);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, -x+x_center , y+y_center, 0xFF0000);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, -y+x_center , x+y_center, 0xFF0000);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x+x_center , -y+y_center, 0xFF0000);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, y+x_center , -x+y_center, 0xFF0000);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, -x+x_center , -y+y_center, 0xFF0000);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, -y+x_center , -x+y_center, 0xFF0000);
        if (d >= 2 * x)
        {
            d -= - 2 * x - 1;
            x++;
        }
        else if (d <= 2 * (r - y))
        {
            d += 2 * y - 1;
            y--;
        }
        else
        {
            d += + 2 * (y-x-1);
            y--;
            x++;
        }
    }
}

void circle_erase(t_data *data, int centerX, int centerY, int radius)
{
    int x = 0;
    int y = radius;
    int m = 3 - 4 * radius;
	int	xx;

	xx = 0;
    while (x <= y)
    {
		xx = centerX - y;
        while (xx <= centerX + y)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, xx , centerY - x, 0xFFFFFF);
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, xx , centerY + x, 0xFFFFFF);
			xx++;
		}
        if (m > 0)
        {
			xx = centerX - x;
        	while (xx <= centerX + x)
			{
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, xx , centerY - y, 0xFFFFFF);
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, xx , centerY + y, 0xFFFFFF);
				xx++;
			}
            y--;
            m -= 8 * y;
		}
        x++;
        m += 8 * x + 4;
    }
}

void circle(t_data *data, int centerX, int centerY, int radius)
{
    int x = 0;
    int y = radius;
    int m = 3 - 4 * radius;
	int	xx;

	xx = 0;
    while (x <= y)
    {
		xx = centerX - y;
        while (xx <= centerX + y)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, xx , centerY - x, 0xFF0000);
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, xx , centerY + x, 0xFF0000);
			xx++;
		}
        if (m > 0)
        {
			xx = centerX - x;
        	while (xx <= centerX + x)
			{
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, xx , centerY - y, 0xFF0000);
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, xx , centerY + y, 0xFF0000);
				xx++;
			}
            y--;
            m -= 8 * y;
        }

        x++;
        m += 8 * x + 4;
    }
}

int circle_collision(t_data *data, int x_centre, int y_centre, int r)
{
    int x = r;
	int	y = 0;
    int P = 1 - r;
     
    while (x > y)
    { 
        y++;
        if (P <= 0)
            P = P + 2*y + 1;
        else
        {
            x--;
            P = P + 2*y - 2*x + 1;
        }
        if (x < y)
            break;
		if (data->map[(y + y_centre + 1) / 50][(x + x_centre + 1) / 50] == 1
			|| data->map[(y + y_centre + 1) / 50][(-x + x_centre - 1) / 50] == 1
			|| data->map[(-y + y_centre - 1) / 50][(x + x_centre + 1) / 50] == 1
			|| data->map[(-y + y_centre - 1) / 50][(-x + x_centre - 1) / 50] == 1)
			return (1);
		if (x != y)
        {
			if (data->map[(x + y_centre + 1) / 50][(y + x_centre + 1) / 50] == 1
				|| data->map[(-x + y_centre - 1) / 50][(y + x_centre + 1) / 50] == 1
				|| data->map[(x + y_centre + 1) / 50][(-y + x_centre - 1) / 50] == 1
				|| data->map[(-x + y_centre - 1) / 50][(-y + x_centre - 1) / 50] == 1)
				return (1);
		}
    }
	return (0);
}

void midPointCircleErase(t_data *data, int x_centre, int y_centre, int r)
{
    int x = r;
	int	y = 0;
    int P = 1 - r;
     
    // Printing the initial point on the axes 
    // after translation
    // printf("(%d, %d) ", x + x_centre, y + y_centre);
     
    // When radius is zero only a single
    // point will be printed
    // if (r > 0)
    // {
    //     printf("(%d, %d) ", x + x_centre, -y + y_centre);
    //     printf("(%d, %d) ", y + x_centre, x + y_centre);
    //     printf("(%d, %d)\n", -y + x_centre, x + y_centre);
    // }
     
    // Initialising the value of P
    while (x > y)
    { 
        y++;
         
        // Mid-point is inside or on the perimeter
        if (P <= 0)
            P = P + 2*y + 1;
             
        // Mid-point is outside the perimeter
        else
        {
            x--;
            P = P + 2*y - 2*x + 1;
        }
         
        // All the perimeter points have already been printed
        if (x < y)
            break;
         
        // Printing the generated point and its reflection
        // in the other octants after translation
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + x_centre, y + y_centre, 0xFFFFFF);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, -x + x_centre, y + y_centre, 0xFFFFFF);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + x_centre, -y + y_centre, 0xFFFFFF);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, -x + x_centre, -y + y_centre, 0xFFFFFF);
         
        // If the generated point is on the line x = y then 
        // the perimeter points have already been printed
        if (x != y)
        {
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, y + x_centre, x + y_centre, 0xFFFFFF);
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, y + x_centre, -x + y_centre, 0xFFFFFF);
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, -y + x_centre, x + y_centre, 0xFFFFFF);
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, -y + x_centre, -x + y_centre, 0xFFFFFF);
        }
    } 
}

void midPointCircleDraw(t_data *data, int x_centre, int y_centre, int r)
{
    int x = r;
	int	y = 0;
    int P = 1 - r;
	
    while (x > y)
    { 
        y++;
        if (P <= 0)
            P = P + 2*y + 1;
        else
        {
            x--;
            P = P + 2*y - 2*x + 1;
        }
        if (x < y)
            break;
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + x_centre, y + y_centre, 0xFF0000);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, -x + x_centre, y + y_centre, 0xFF0000);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + x_centre, -y + y_centre, 0xFF0000);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, -x + x_centre, -y + y_centre, 0xFF0000);
        if (x != y)
        {
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, y + x_centre, x + y_centre, 0xFF0000);
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, y + x_centre, -x + y_centre, 0xFF0000);
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, -y + x_centre, x + y_centre, 0xFF0000);
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, -y + x_centre, -x + y_centre, 0xFF0000);
        }
    } 
}

int	check_collision(t_data *data, double x, double y)
{
	if (data->map[(int)((data->player.py + y) / 50)][(int)((data->player.px + x + 6)
			/ 50)] == '1')
		return (1);	
	if (data->map[(int)((data->player.py + y + 6) / 50)][(int)((data->player.px + x)
			/ 50)] == '1')
		return (1);
	if (data->map[(int)((data->player.py + y - 6) / 50)][(int)((data->player.px + x - 6)
			/ 50)] == '1')
		return (1);
	if (data->map[(int)((data->player.py + y + 6) / 50)][(int)((data->player.px + x)
			/ 50)] == '1')
		return (1);
	if (data->map[(int)((data->player.py + y - 3) / 50)][(int)((data->player.px + x - 3)
			/ 50)] == '1')
		return (1);
	if (data->map[(int)((data->player.py + y + 3) / 50)][(int)((data->player.px + x - 3)
			/ 50)] == '1')
		return (1);
	if (data->map[(int)((data->player.py + y - 3) / 50)][(int)((data->player.px + x + 3)
			/ 50)] == '1')
		return (1);
	if (data->map[(int)((data->player.py + y + 3) / 50)][(int)((data->player.px + x + 3)
			/ 50)] == '1')
		return (1);
	return (0);
}

void	move(t_data *data, double x, double y)
{
	if (check_collision(data, x, y))
		return ;
	// erased_ray(data);
	circle_erase(data, data->player.px, data->player.py, 6);
	midPointCircleErase(data, data->player.px, data->player.py, 9);
	
	// erase_square(data, (int)data->player.px, (int)data->player.py);
	data->player.px += x;
	data->player.py += y;
	put_ray(data);
	// draw_circle(data, data->player.py, data->player.px, 6);
	circle(data, data->player.px, data->player.py, 6);
	midPointCircleDraw(data, data->player.px, data->player.py, 9);
	// midPointCircleDraw(data, data->player.px, data->player.py, 6);
	// put_square((int)data->player.px, (int)data->player.py, data);
	return ;
}

void	print_int_tab(int tab[6][2], int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf("i:%d ::::  %d\n", i, tab[i][1]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (parsing(&data, argv[1]))
		return (1);
	data.img.size_x = 50;
	data.img.size_y = 50;
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (-1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.img.x_max * 50,
			(data.img.y_max + 1) * 50, "MazeCub3D");
	if (!data.win_ptr)
		return (free(data.win_ptr), -1);
	init_img(&data);
	display_map(&data);
	circle(&data, data.player.px, data.player.py, 6);
	// draw_circle(&data, data.player.py, data.player.px, 6);
	midPointCircleDraw(&data, data.player.px, data.player.py, 9);
	// dislay_player(&data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, release_inputs, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, get_inputs, &data);
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &exit_and_free,
		&data);
	mlx_loop_hook(data.mlx_ptr, on_keypress, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
