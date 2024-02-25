/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:09:51 by soutin            #+#    #+#             */
/*   Updated: 2024/02/25 21:29:46 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int c, char **v)
{
	t_vars	vars;

	ft_memset(&vars, 0, sizeof(t_vars));
	if (c == 2)
	{
		if (get_map_data(&vars, v[1]) < 0)
			return (1);
		check_map(&vars);
	}
	return (0);
}
