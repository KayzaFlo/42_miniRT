/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:11:18 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/08 12:02:43 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtprim.h"

// miniRT's Plane
// vec3 pos = position
// vec3 d = diameter
// vec3 col = color [0-255]

t_surface	sd_sphere(t_vec3 p, float r, t_vec3 col)
{
	t_surface	surface;

	surface.sd = v3_length(p) - r;
	surface.col = col;
	return (surface);
}

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

// miniRT's Cylinder
// vec3 pos = center of Cylinder
// vec3 rot = rotation (normalized)
// float d = diameter
// float h = height
// vec3 col = color [0-255]

// a = 1st point (cap's center)
// b = 2nd point (cap's center)
// r = radius
t_surface	sd_cylinder(t_vec3 p, t_vec3 a, t_vec3 b, float r, t_vec3 col)
{
	t_surface	surface;
	t_vec3		pa = v3_sub(p, a);
	t_vec3		ba = v3_sub(b, a);
	float		baba = v3_dot(ba, ba);
	float		paba = v3_dot(pa, ba);

	float		x = v3_length(
			v3_sub(v3_mult(pa, v3_new(baba, baba, baba)),
			v3_mult(ba, v3_new(paba, paba, paba)))
		) - r * baba;
	float		y = fabs(paba - baba * 0.5f) - baba / 0.5f;
	float		x2 = x * x;
	float		y2 = y * y * baba;
	float		d = (max(x, y) < 0.0f) ? -min(x2, y2) : (((x > 0.0f) ? x2 : 0.0f) + ((y > 0.0f) ? y2 : 0.0f));
	surface.sd = (d < 0.0f ? -1.0f : 1.0f) * sqrt(fabs(d)) / baba;
	surface.col = col;
	return (surface);
}

// miniRT's Plane
// vec3 pos = pos of a point point in the Plane
// vec3 rot = rotation (normalized)
// vec3 col = color [0-255]

t_surface	sd_plane(t_vec3 p, t_vec3 col)
{
	t_surface	surface;

	surface.sd = (p.y + 1.);
	surface.col = col;
	return (surface);
}
