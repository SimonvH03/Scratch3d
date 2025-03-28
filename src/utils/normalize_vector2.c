/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   normalize_vector2.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:51:01 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/28 01:47:07 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float quake3_heavilyinspired_rsqrt(float number)
{
	long		i;
	float 		a;
	float		b;
	const float threehalfs = 1.5f;

	a = number * 0.5f;
	b = number;
	i = * (long *) &b;
	i = 0x5f3759df - (i >> 1);
	b = * (float *) &i;
	b = b * (threehalfs - (a * b * b));
	b = b * (threehalfs - (a * b * b));

	return (b);
}

void	normalize_vector2(float *x_component, float *y_component)
{
	float	dx = *x_component;
	float	dy = *y_component;
	double	inverse_sqrt = quake3_heavilyinspired_rsqrt((dx * dx) + (dy * dy));

	*x_component *= ft_abs_float(inverse_sqrt);
	*y_component *= ft_abs_float(inverse_sqrt);
}
