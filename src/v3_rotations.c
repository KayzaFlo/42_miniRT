/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_rotations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:48:50 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/25 11:10:10 by fgeslin          ###   ########.fr       */
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

t_vec3	v3_rotate(t_vec3 ref, t_vec3 point, t_vec3 angle)
{
	t_vec3	local_vec;

	local_vec = v3_sub(point, ref);
	local_vec = v3_rotz(local_vec, angle.z);
	local_vec = v3_rotx(local_vec, angle.x);
	local_vec = v3_roty(local_vec, angle.y);
	return (v3_add(local_vec, ref));
}

// point
// angle = [0-360] degrees
t_vec3	v3_localrotate(t_vec3 point, t_vec3 angle)
{
	point = v3_rotz(point, angle.z);
	point = v3_rotx(point, angle.x);
	point = v3_roty(point, angle.y);
	return (point);
}

// xyz = point
// abc = point a axis
// uvw = axis dir
t_vec3	v3_rotatearoundaxis(t_vec3 point, t_vec3 axis, double angle)
{
	const double	theta = angle * M_PI / 180.0f;
	point = v3_normalize(point);
	axis = v3_normalize(axis);
	const double	x = point.x;
	const double	y = point.y;
	const double	z = point.z;
	const double	u = axis.x;
	const double	v = axis.y;
	const double	w = axis.z;

	t_vec3	new_p;

	new_p.x = (u * v3_dot(point, axis)) * (1 - cos(theta)) + x * cos(theta) + (-w*y + v*z) * sin(theta);
	new_p.y = (v * v3_dot(point, axis)) * (1 - cos(theta)) + y * cos(theta) + ( w*x - u*z) * sin(theta);
	new_p.z = (w * v3_dot(point, axis)) * (1 - cos(theta)) + z * cos(theta) + (-v*x + u*y) * sin(theta);
	return (new_p);
}
