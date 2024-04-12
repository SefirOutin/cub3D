/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vertical_line_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:04:03 by soutin            #+#    #+#             */
/*   Updated: 2024/03/29 15:37:16 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_vertical_line(t_img *img, t_ipoint start, int len, int color)
{
	while (len--)
	{
		put_pixel_to_image(img, start.x, start.y, color);
		start.y++;
	}
}
