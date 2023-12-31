/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathplus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:19:33 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/24 14:32:42 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtmath.h"

float	min(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

float	max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

float	clamp(float n, float min, float max)
{
	if (n < min)
		return (min);
	if (n > max)
		return (max);
	return (n);
}

float	step(float edge, float x)
{
	if (x < edge)
		return (0);
	return (1);
}

float	smoothstep(float edge0, float edge1, float x)
{
	float	t;

	t = clamp((x - edge0) / (edge1 - edge0), 0, 1);
	return (t * t * (3.0 - 2.0 * t));
}
