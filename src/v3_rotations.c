/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_rotations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:48:50 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/23 16:58:44 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtmath.h"

t_vec3	v3_rotx(t_vec3 o, t_vec3 p, double angle)
{
	const double	rad = angle * M_PI / 180.0f;
	t_vec3			vec;
	double			len;

	vec = v3_sub(p, o);
	len = v3_length(vec);
	vec.x = vec.x;
	vec.y = cos(rad) * vec.y - sin(rad) * vec.z;
	vec.z = sin(rad) * vec.y + cos(rad) * vec.z;
	vec = v3_multf(v3_normalize(vec), len);
	return (v3_add(vec, o));
}

t_vec3	v3_roty(t_vec3 o, t_vec3 p, double angle)
{
	const double	rad = angle * M_PI / 180.0f;
	t_vec3			vec;
	double			len;

	vec = v3_sub(p, o);
	len = v3_length(vec);
	vec.x = cos(rad) * vec.x + sin(rad) * vec.z;
	vec.y = vec.y;
	vec.z = -sin(rad) * vec.x + cos(rad) * vec.z;
	vec = v3_multf(v3_normalize(vec), len);
	return (v3_add(vec, o));
}

t_vec3	v3_rotz(t_vec3 o, t_vec3 p, double angle)
{
	const double	rad = angle * M_PI / 180.0f;
	t_vec3			vec;
	double			len;

	vec = v3_sub(p, o);
	len = v3_length(vec);
	vec.x = cos(rad) * vec.x - sin(rad) * vec.y;
	vec.y = sin(rad) * vec.x + cos(rad) * vec.y;
	vec.z = vec.z;
	vec = v3_multf(v3_normalize(vec), len);
	return (v3_add(vec, o));
}

t_vec3	v3_rot(t_vec3 o, t_vec3 p, t_vec3 angle)
{
	v3_rotz(o, p, angle.z);
	v3_rotz(o, p, angle.x);
	v3_rotz(o, p, angle.y);
	return (p);
}
