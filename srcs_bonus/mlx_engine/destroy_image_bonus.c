/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:07:19 by soutin            #+#    #+#             */
/*   Updated: 2024/03/29 18:39:09 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_image(t_img img, t_data *data)
{
	if (img.img)
		mlx_destroy_image(data->win.mlx_ptr, img.img);
}
