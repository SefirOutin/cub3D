/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:07:47 by soutin            #+#    #+#             */
/*   Updated: 2024/03/29 16:06:08 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_pixel_img(t_img img, int x, int y)
{
	return (*(unsigned int *)(((char *)img.addr + (y * img.line_l) + (x
				* img.bpp / 8))));
}
