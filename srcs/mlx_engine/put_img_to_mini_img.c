/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_img_to_mini_img.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:41:08 by bmoudach          #+#    #+#             */
/*   Updated: 2024/03/29 16:32:05 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_img_to_mini_img(t_img *dst, t_img src, t_ipoint point, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel_mini_img(dst, point.x + i, point.y + j, get_pixel_img(src,
					i, j));
			j++;
		}
		i++;
	}
}
