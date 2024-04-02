/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:09:51 by soutin            #+#    #+#             */
/*   Updated: 2024/04/02 17:57:24 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_err(char *err_message)
{
	ft_printf("Error\n%s\n", err_message);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (print_err("Error No map"), 0);
	if (parsing(&data, argv[1]))
		return (1);
	if (init_mlx_data(&data))
		return (exit_and_free(&data), 1);
	first_display(&data);
	init_hook_and_loop(&data);
	return (0);
}
