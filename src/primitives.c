/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:11:18 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/25 14:33:13 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtprim.h"

t_surface	pl_intersect(t_vec3 ro, t_vec3 rd, t_pl *pl)
{
	t_surface	surface;
	float		a;
	float		b;

	a = v3_dot(v3_sub(ro, pl->coord), pl->ori);
	b = v3_dot(rd, pl->ori);
	if (b == 0)
	{
		surface.sd = -1;
		surface.n = v3_new(-1, -1, -1);
		return (surface);
	}
	surface.sd = -a / b;
	if (v3_dot(rd, pl->ori) < 0)
		surface.n = pl->ori;
	else
		surface.n = v3_multf(pl->ori, -1);
	surface.col = pl->col;
	return (surface);
}

t_surface	elli_intersect( t_vec3 ro, t_vec3 rd, t_vec3 r )
{
	t_surface	surface;
	float		a;
	float		b;
	float		c;
	float		h;

	r = v3_mult(r, r);
	a = v3_dot(rd, v3_new(rd.x / r.x, rd.y / r.y, rd.z / r.z));
	b = v3_dot(ro, v3_new(rd.x / r.x, rd.y / r.y, rd.z / r.z));
	c = v3_dot(ro, v3_new(ro.x / r.x, ro.y / r.y, ro.z / r.z));
	h = b * b - a * (c - 1.0);
	if (h < 0.0)
	{
		surface.sd = -1;
		surface.n = v3_new(-1, -1, -1);
		return (surface);
	}
	surface.sd = (-b - sqrt(h)) / a;
	surface.n = v3_normalize(v3_new(
				(ro.x + surface.sd * rd.x) / r.x,
				(ro.y + surface.sd * rd.y) / r.y,
				(ro.z + surface.sd * rd.z) / r.z)
			);
	surface.col = v3_new(255, 0, 0);
	return (surface);
}

t_surface	sph_intersect(t_vec3 ro, t_vec3 rd, t_sph *sph)
{
	t_surface	surface;
	t_vec3		pc;
	double		a;
	double		b;
	double		c;

	pc = v3_sub(ro, sph->coord);
	a = v3_dot(rd, rd);
	b = 2 * v3_dot(rd, pc);
	c = v3_dot(pc, pc) - pow((sph->dia / 2), 2);
	if (b * b - (4 * a * c) < 0)
	{
		surface.sd = -1;
		surface.n = v3_new(-1, -1, -1);
		return (surface);
	}
	surface.sd = (-b - sqrt(b * b - (4 * a * c))) / (2 * a);
	surface.n = v3_normalize(v3_sub(
				v3_add(ro, v3_multf(rd, surface.sd)),
				sph->coord));
	surface.col = sph->col;
	return (surface);
}
