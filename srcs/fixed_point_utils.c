/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_point_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:03:30 by soutin            #+#    #+#             */
/*   Updated: 2024/03/19 18:28:56 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double fixed_to_double(fxpoint input)
{
    return ((double)input / (double)(1 << SHIFT_AMOUNT));
}

fxpoint double_to_fixed(double input)
{
    return (fxpoint)(round(input * (1 << SHIFT_AMOUNT)));
}

int	unshift(fxpoint input)
{
	return (input >> SHIFT_AMOUNT);
}

fxpoint shift(int input)
{
	return (input << SHIFT_AMOUNT);
}

fxpoint fx_mul(fxpoint a, fxpoint b)
{
    return (fxpoint)((__uint64_t)(a * (unshift(b))));
}

fxpoint fx_div(fxpoint a, fxpoint b)
{
    return (fxpoint)(a / (unshift(b)));
}