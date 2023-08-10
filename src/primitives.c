/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:11:18 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/10 13:48:47 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtprim.h"

// miniRT's Sphere
// vec3 p = position
// vec3 d = diameter
// vec3 col = color [0-255]
t_surface	sd_sphere(t_vec3 p, float d, t_vec3 col)
{
	t_surface	surface;

	surface.sd = v3_length(p) - d / 2;
	surface.col = col;
	return (surface);
}

// miniRT's Sphere
// vec3 p = position
// vec3 b = bounding box
// vec3 col = color [0-255]
t_surface	sd_box(t_vec3 p, t_vec3 b, t_vec3 col)
{
	t_surface	surface;
	t_vec3		d;

	d = v3_sub(v3_new(fabsf(p.x), fabsf(p.y), fabsf(p.z)), b);
	surface.sd = min(max(d.x, max(d.y, d.z)), 0.0f);
	surface.sd += v3_length(v3_new(max(d.x, 0), max(d.y, 0), max(d.z, 0)));
	surface.col = col;
	return (surface);
}

static float	getcyldist(float x, float y, float baba)
{
	float	d;

	d = 0;
	if (max(x, y) < 0.0f)
		d = -min(x * x, y * y * baba);
	else
	{
		if (x > 0.0f)
			d += x * x;
		if (y > 0.0f)
			d += y * y * baba;
	}
	if (d < 0.0f)
		return (-1.0f * sqrt(fabs(d)) / baba);
	else
		return (sqrt(fabs(d)) / baba);
}

// miniRT's Cylinder
// vec3 p = center of Cylinder
// vec3 r = rotation (normalized)
// float d = diameter
// float h = height
// vec3 col = color [0-255]
t_surface	sd_cylinder(t_vec3 p, t_vec3 r, float d, float h, t_vec3 col)
{
	t_surface	surface;
	t_vec3		a;
	t_vec3		b;
	float		baba;
	float		paba;

	r = v3_normalize(r);
	a = v3_new(-r.x * h / 2, -r.y * h / 2, -r.z * h / 2);
	b = v3_new(r.x * h / 2, r.y * h / 2, r.z * h / 2);
	baba = v3_dot(v3_sub(b, a), v3_sub(b, a));
	paba = v3_dot(v3_sub(p, a), v3_sub(b, a));
	surface.sd = getcyldist(v3_length(v3_sub(
					v3_mult(v3_sub(p, a), v3_new(baba, baba, baba)),
					v3_mult(v3_sub(b, a), v3_new(paba, paba, paba))
					)) - d / 2 * baba,
			fabs(paba - baba * 0.5f) - baba / 0.5f,
			baba
			);
	surface.col = col;
	return (surface);
}

// miniRT's Plane
// vec3 p = pos of a point point in the Plane
// vec3 r = rotation (normalized)    //TOADD
// vec3 col = color [0-255]
t_surface	sd_plane(t_vec3 p, t_vec3 n, t_vec3 col)
{
	t_surface	surface;

	n = v3_normalize(n);
	surface.sd = v3_dot(p, n);
	surface.col = col;
	return (surface);
}
