/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 22:59:10 by bmoudach          #+#    #+#             */
/*   Updated: 2024/02/26 15:44:09 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*buff;
	size_t	i;

	i = 0;
	if (nitems > sizeof(char) * 2147483424 || size > sizeof(char) * 2147483424)
		return (NULL);
	if (nitems == 0 || size == 0)
	{
		nitems = 1;
		size = 1;
	}
	buff = (void *)malloc(nitems * size);
	if (!buff)
		return (perror("calloc"), NULL);
	while (i < nitems * size)
	{
		((unsigned char *)buff)[i] = 0;
		i++;
	}
	return (buff);
}
