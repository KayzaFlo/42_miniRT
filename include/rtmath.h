/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtmath.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:48:26 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/24 14:25:34 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTMATH_H
# define RTMATH_H

# include <math.h>

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

t_vec3	v3_new(double x, double y, double z);
double	v3_dot(t_vec3 v1, t_vec3 v2);
double	v3_length(t_vec3 v);
t_vec3	v3_normalize(t_vec3 v);
t_vec3	v3_cross(t_vec3 v1, t_vec3 v2);
t_vec3	v3_add(t_vec3 v1, t_vec3 v2);
t_vec3	v3_sub(t_vec3 v1, t_vec3 v2);
t_vec3	v3_mult(t_vec3 v1, t_vec3 v2);
t_vec3	v3_multf(t_vec3 v, double f);
t_vec3	v3_rotx(t_vec3 p, double angle);
t_vec3	v3_roty(t_vec3 p, double angle);
t_vec3	v3_rotz(t_vec3 p, double angle);
t_vec3	v3_rotate(t_vec3 ref, t_vec3 point, t_vec3 angle);
t_vec3	v3_localrotate(t_vec3 point, t_vec3 angle);

float	min(float a, float b);
float	max(float a, float b);
float	clamp(float n, float min, float max);
float	step(float edge, float x);
float	smoothstep(float edge0, float edge1, float x);

#endif
