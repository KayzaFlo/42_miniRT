/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_rotations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:48:50 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/25 15:07:45 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtmath.h"

t_vec3	v3_rotx(t_vec3 p, double angle)
{
	const double	rad = angle * M_PI / 180.0f;
	t_vec3			new_p;

	new_p.x = p.x;
	new_p.y = cos(rad) * p.y - sin(rad) * p.z;
	new_p.z = sin(rad) * p.y + cos(rad) * p.z;
	return (new_p);
}

t_vec3	v3_roty(t_vec3 p, double angle)
{
	const double	rad = angle * M_PI / 180.0f;
	t_vec3			new_p;

	new_p.x = cos(rad) * p.x + sin(rad) * p.z;
	new_p.y = p.y;
	new_p.z = -sin(rad) * p.x + cos(rad) * p.z;
	return (new_p);
}

t_vec3	v3_rotz(t_vec3 p, double angle)
{
	const double	rad = angle * M_PI / 180.0f;
	t_vec3			new_p;

	new_p.x = cos(rad) * p.x - sin(rad) * p.y;
	new_p.y = sin(rad) * p.x + cos(rad) * p.y;
	new_p.z = p.z;
	return (new_p);
}

// xyz = point
// abc = point a axis
// uvw = axis dir
t_vec3	v3_rotatearoundaxis(t_vec3 point, t_vec3 axis, double angle)
{
	const double	theta = angle * M_PI / 180.0;
	t_vec3			new_p;

	point = v3_normalize(point);
	axis = v3_normalize(axis);
	new_p.x = (axis.x * v3_dot(point, axis)) * (1 - cos(theta))
		+ point.x * cos(theta)
		+ (-axis.z * point.y + axis.y * point.z) * sin(theta);
	new_p.y = (axis.y * v3_dot(point, axis)) * (1 - cos(theta))
		+ point.y * cos(theta)
		+ (axis.z * point.x - axis.x * point.z) * sin(theta);
	new_p.z = (axis.z * v3_dot(point, axis)) * (1 - cos(theta))
		+ point.z * cos(theta)
		+ (-axis.y * point.x + axis.x * point.y) * sin(theta);
	return (new_p);
}
