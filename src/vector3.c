/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:48:50 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/07 11:07:06 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

t_vec3	v3_new(float x, float y, float z)
{
	t_vec3 new;
	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

float	v3_dot(t_vec3 v1, t_vec3 v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

float	v3_length(t_vec3 v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

t_vec3	v3_normalize(t_vec3 v)
{
	float	l;
	t_vec3	normalized;

	l = v3_length(v);
	normalized.x = v.x / l;
	normalized.y = v.y / l;
	normalized.z = v.z / l;
	return (normalized);
}

t_vec3	v3_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3	add;

	add.x = v1.x + v2.x;
	add.y = v1.y + v2.y;
	add.z = v1.z + v2.z;
	return (add);
}

t_vec3	v3_sub(t_vec3 v1, t_vec3 v2)
{
	t_vec3	sub;

	sub.x = v1.x - v2.x;
	sub.y = v1.y - v2.y;
	sub.z = v1.z - v2.z;
	return (sub);
}

t_vec3	v3_mult(t_vec3 v1, t_vec3 v2)
{
	t_vec3	mult;

	mult.x = v1.x * v2.x;
	mult.y = v1.y * v2.y;
	mult.z = v1.z * v2.z;
	return (mult);
}
