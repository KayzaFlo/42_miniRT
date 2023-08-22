/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:48:50 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/22 13:57:08 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtmath.h"

t_vec3	v3_new(double x, double y, double z)
{
	t_vec3	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

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

t_vec3	v3_multf(t_vec3 v, double f)
{
	t_vec3	mult;

	mult.x = v.x * f;
	mult.y = v.y * f;
	mult.z = v.z * f;
	return (mult);
}

t_vec3	v3_rotx(t_vec3 o, t_vec3 p, double angle)
{
	t_vec3	vec;
	double	rad = angle * M_PI / 180.0f;

	vec = v3_sub(p, o);
	double	len = v3_length(vec);
	vec.x = vec.x;
	vec.y = cos(rad) * vec.y - sin(rad) * vec.z;
	vec.z = sin(rad) * vec.y + cos(rad) * vec.z;
	vec = v3_multf(v3_normalize(vec), len);
	return (v3_add(vec, o));
}


t_vec3	v3_roty(t_vec3 o, t_vec3 p, double angle)
{
	t_vec3	vec;
	double	rad = angle * M_PI / 180.0f;

	vec = v3_sub(p, o);
	double	len = v3_length(vec);
	vec.x = cos(rad) * vec.x + sin(rad) * vec.z;
	vec.y = vec.y;
	vec.z = -sin(rad) * vec.x + cos(rad) * vec.z;
	vec = v3_multf(v3_normalize(vec), len);
	return (v3_add(vec, o));
}


t_vec3	v3_rotz(t_vec3 o, t_vec3 p, double angle)
{
	t_vec3	vec;
	double	rad = angle * M_PI / 180.0f;

	vec = v3_sub(p, o);
	double	len = v3_length(vec);
	vec.x = cos(rad) * vec.x - sin(rad) * vec.y;
	vec.y = sin(rad) * vec.x + cos(rad) * vec.y;
	vec.z = vec.z;
	vec = v3_multf(v3_normalize(vec), len);
	return (v3_add(vec, o));
}

// t_vec3	v3_rot(t_vec3 o, t_vec3 p, t_vec3 angle)
// {
// 	// double	len = v3_length(vec);

// 	v3_rotz(o, p, angle.z);
// 	v3_rotz(o, p, angle.x);
// 	v3_rotz(o, p, angle.y);
// }
