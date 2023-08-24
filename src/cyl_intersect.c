/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:44:24 by arivera           #+#    #+#             */
/*   Updated: 2023/08/24 15:50:41 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtprim.h"

double	cyl_hp_dst(t_vec3 ro, t_vec3 rd, t_surface closest_cap, t_vec3 cap_hit)
{
	t_vec3	hit_point;
	t_vec3	vec_hp_to_cap;
	double	dst_hp_to_cap;

	if (closest_cap.sd == -1)
		return (INT32_MAX);
	hit_point = v3_add(ro, v3_multf(rd, closest_cap.sd));
	vec_hp_to_cap = (v3_sub(hit_point, cap_hit));
	dst_hp_to_cap = v3_length(vec_hp_to_cap);
	return (dst_hp_to_cap);
}

t_pl	init_cyl_cap(t_cyl *cyl, t_vec3 c, t_vec3 l, int end)
{
	t_pl	cap;

	if (!end)
	{
		cap.col = cyl->col;
		cap.coord = c;
		cap.ori = v3_multf(cyl->norm, -1);
	}
	else
	{
		cap.col = cyl->col;
		cap.coord = l;
		cap.ori = cyl->norm;
	}
	return (cap);
}

// tab[0] = coord of the cap that was hit (cap_hit)
// tab[1] = norm. vector of orientation of the cyl (v)
// tab[2] = coord of the opposite end of the cyl (l)

t_surface	cyl_cap_intersect(t_vec3 ro, t_vec3 rd, t_cyl *cyl, t_vec3 c)
{
	t_surface	surface_cap;
	t_surface	closest_cap;
	t_pl		cap;
	t_vec3		tab[3];

	tab[1] = v3_normalize(cyl->norm);
	tab[2] = v3_add(c, v3_multf(tab[1], cyl->hgt));
	cap = init_cyl_cap(cyl, c, tab[2], 0);
	closest_cap.sd = -1;
	surface_cap = pl_intersect(ro, rd, &cap);
	if (surface_cap.sd > 0)
	{
		tab[0] = c;
		closest_cap = surface_cap;
	}
	cap = init_cyl_cap(cyl, c, tab[2], 1);
	surface_cap = pl_intersect(ro, rd, &cap);
	if (surface_cap.sd > 0 && surface_cap.sd < closest_cap.sd)
	{
		tab[0] = tab[2];
		closest_cap = surface_cap;
	}
	if (cyl_hp_dst(ro, rd, closest_cap, tab[0]) > (cyl->dia / 2))
		closest_cap.sd = -1;
	return (closest_cap);
}

// var[0] = a, var[1] = b, var[2] = c, var[3] = delta, var[4] = m
// vc[0] = v, vc[1] = c, vc[2] = x

t_surface	cyl_intersect(t_vec3 ro, t_vec3 rd, t_cyl *cyl)
{
	t_surface	surface;
	t_vec3		v[3];
	t_vec3		pc;
	double		var[5];

	v[0] = v3_normalize(cyl->norm);
	v[1] = v3_sub(cyl->coord, (v3_multf(v[0], cyl->hgt / 2)));
	v[2] = v3_sub(ro, v[1]);
	var[0] = v3_dot(rd, rd) - pow(v3_dot(rd, v[0]), 2);
	var[1] = 2 * (v3_dot(rd, v[2]) - (v3_dot(rd, v[0]) * v3_dot(v[2], v[0])));
	var[2] = v3_dot(v[2], v[2]) - pow(v3_dot(v[2], v[0]), 2);
	var[2] = var[2] - pow((cyl->dia / 2), 2);
	var[3] = (var[1] * var[1] - (4 * var[0] * var[2]));
	if (var[3] < 0)
		return (surface.sd = -1, surface.n = v3_new(-1, -1, -1), surface);
	surface.sd = (-var[1] - sqrt(var[3])) / (2 * var[0]);
	var[4] = v3_dot(rd, v3_multf(v[0], surface.sd)) + v3_dot(v[2], v[0]);
	if (var[4] < 0 || var[4] > cyl->hgt)
		return (cyl_cap_intersect(ro, rd, cyl, v[1]));
	pc = v3_sub(v3_add(ro, v3_multf(rd, surface.sd)), v[1]);
	surface.n = v3_normalize(v3_sub(pc, v3_multf(v[0], var[4])));
	surface.col = cyl->col;
	return (surface);
}
