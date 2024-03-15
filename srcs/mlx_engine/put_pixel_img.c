/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:07:58 by soutin            #+#    #+#             */
/*   Updated: 2024/03/15 18:48:13 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// void	put_pixel_img(t_img img, int x, int y, int color)
// {
// 	char	*dst;

// 	if (color == (int)0xFF000000)
// 		return ;
// 	if (x >= 0 && y >= 0 && x < img.w && y < img.h)
// 	{
// 		dst = (char *)img.addr + (y * img.line_l + x * (img.bpp / 8));
// 		*(unsigned int *)dst = color;
// 	}
// }