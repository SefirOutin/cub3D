/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:09:51 by soutin            #+#    #+#             */
/*   Updated: 2024/02/26 18:01:24 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_err(char *err_message)
{
	ft_printf("Error\n%s\n", err_message);
}

int	parsing(t_vars *vars, char *path)
{
	ft_memset(vars, 0, sizeof(t_vars));
	if (get_map_data(vars, path) < 0)
		return (1);
	if (check_map(vars))
		return (1);
	ft_print_tab(vars->map);
	return (0);
}

int	main(int c, char **v)
{
	t_vars	vars;

	if (c == 2)
	{
		if (parsing(&vars, v[1]))
			return (1);
	}
	else
		print_err("missing map");
	return (0);
}
