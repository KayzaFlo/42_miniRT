/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:11:18 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/24 12:29:27 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtprim.h"
void	v3_print(t_vec3 v);

t_surface	plIntersect(t_vec3 ro, t_vec3 rd, t_pl *pl)
{
	t_surface	surface;

	float	a = v3_dot(v3_sub(ro, pl->coord), pl->ori);
	float	b = v3_dot(rd, pl->ori);
	
	if (b == 0)
	{
		surface.sd = -1;
		surface.n = v3_new(-1, -1, -1);
		return (surface);
	}
	surface.sd = -a / b;
	surface.n = pl->ori;
	surface.col = pl->col;
	return (surface);
}

t_surface elliIntersect( t_vec3 ro, t_vec3 rd, t_vec3 r )
{
	t_surface	surface;

    t_vec3	r2 = v3_mult(r, r);
    float	a = v3_dot( rd, v3_new(rd.x/r2.x, rd.y/r2.y, rd.z/r2.z) );
	float	b = v3_dot( ro, v3_new(rd.x/r2.x, rd.y/r2.y, rd.z/r2.z) );
	float	c = v3_dot( ro, v3_new(ro.x/r2.x, ro.y/r2.y, ro.z/r2.z) );
	float	h = b*b - a*(c-1.0);

	if (h < 0.0)
	{
		surface.sd = -1;
		surface.n = v3_new(-1, -1, -1);
		return (surface);
	}
	float	t = (-b - sqrt(h)) / a;
	surface.sd = t;
	surface.n = v3_normalize(v3_new((ro.x+t*rd.x)/r2.x, (ro.y+t*rd.y)/r2.y, (ro.z+t*rd.z)/r2.z) );
	surface.col = v3_new(255, 0, 0);
    return (surface);
}

t_surface	sphIntersect(t_vec3 ro, t_vec3 rd, t_sph *sph)
{
	t_surface	surface;
	
	t_vec3 pc = v3_sub(ro, sph->coord);
	double a = v3_dot(rd, rd);
	double b = 2 * v3_dot(rd, pc);
	double c = v3_dot(pc, pc) - pow((sph->dia / 2), 2);
	double delta = (b*b - (4 * a * c));

	if (delta < 0)
	{
		surface.sd = -1;
		surface.n = v3_new(-1, -1, -1);
		return (surface);
	}
	surface.sd = (- b - sqrt( delta )) / (2 * a);
	surface.n = v3_normalize(v3_sub(v3_add(ro, v3_multf(rd, surface.sd)), sph->coord));
	surface.col = sph->col;
	return (surface);
}

