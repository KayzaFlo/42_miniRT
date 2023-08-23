/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_algebraic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:48:50 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/23 16:54:13 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtmath.h"

double	v3_dot(t_vec3 v1, t_vec3 v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

double	v3_length(t_vec3 v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

t_vec3	v3_normalize(t_vec3 v)
{
	double	l;
	t_vec3	normalized;

	l = v3_length(v);
	normalized.x = v.x / l;
	normalized.y = v.y / l;
	normalized.z = v.z / l;
	return (normalized);
}

t_vec3	v3_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3	cross;

	cross.x = v1.y * v2.z - v1.z * v2.y;
	cross.y = v1.z * v2.x - v1.x * v2.z;
	cross.z = v1.x * v2.y - v1.y * v2.x;
	return (cross);
}
