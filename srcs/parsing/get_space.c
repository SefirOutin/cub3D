/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:47:18 by bmoudach          #+#    #+#             */
/*   Updated: 2024/04/12 13:35:20 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	g_s(char *str)
{
	int	i;

	i = 0;
	while (*str == ' ' || *str == '\t')
	{
		str++;
		i++;
	}
	i += 2;
	return (i);
}

int	g_s_color(char *str)
{
	int	i;

	i = 0;
	while (*str == ' ' || *str == '\t')
	{
		str++;
		i++;
	}
	i++;
	return (i);
}
