/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathplus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:19:33 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/07 12:22:13 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mathplus.h"

float	min(float a, float b)
{
	if (a < b)
		return a;
	return b;
}

float	max(float a, float b)
{
	if (a < b)
		return a;
	return b;
}

float	clamp(float n, float min, float max)
{
	if (n < min)
		return min;
	if (n > max)
		return max;
	return n;
}