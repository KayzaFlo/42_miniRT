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

t_surface plIntersect(t_vec3 ro, t_vec3 rd, t_pl *pl)
{
	t_surface	surface;

	float	a = v3_dot(v3_sub(ro, pl->coord), pl->ori);
	float	b = v3_dot(rd, pl->ori);
	if (b == 0)
	{
		surface.sd = -1;
		surface.n = v3_new(-1,-1,-1);
		return (surface);
	}
	surface.sd = a / b;
	surface.n = pl->ori;
	return (surface);
}

t_surface elliIntersect( t_vec3 ro, t_vec3 rd, t_vec3 r )
{
	t_surface	surface;

    t_vec3 r2 = v3_mult(r, r);
    float a = v3_dot( rd, v3_new(rd.x/r2.x, rd.y/r2.y, rd.z/r2.z) );
	float b = v3_dot( ro, v3_new(rd.x/r2.x, rd.y/r2.y, rd.z/r2.z) );
	float c = v3_dot( ro, v3_new(ro.x/r2.x, ro.y/r2.y, ro.z/r2.z) );
	float h = b*b - a*(c-1.0);
	if( h<0.0 )
	{
		surface.sd = -1;
		surface.n = v3_new(-1,-1,-1);
		return (surface);
	}
	float t = (-b - sqrt( h ))/a;
	surface.sd = t;
    t_vec3 n = v3_normalize(v3_new((ro.x+t*rd.x)/r2.x, (ro.y+t*rd.y)/r2.y, (ro.z+t*rd.z)/r2.z) );
	surface.n = n;
    return (surface);
}

// t_surface	cylIntersect(t_vec3 ro, t_vec3 rd, t_cyl *cyl)
// {
// 	t_surface	surface;
// 	//caps
// 	return (surface);
// }

t_surface sphIntersect(t_vec3 ro, t_vec3 rd, t_sph *sph)
{
	t_surface	surface;
	
	t_vec3 oc = v3_sub(ro, sph->coord);		// p-c			p-->c
	float b = v3_dot( oc, rd );			// p-c . d		p-->c . p-->d
	float c = v3_dot( oc, oc ) - pow(sph->dia / 2, 2);	// c
	float h = b*b - c;
	if( h < 0.0 )
	{
		surface.sd = -1;
		surface.n = v3_new(-1,-1,-1);
		return (surface);
	}
	surface.sd = - b - sqrt( h );
	surface.n = v3_normalize(v3_sub(v3_add(ro, v3_new(rd.x*surface.sd, rd.y*surface.sd, rd.z*surface.sd)), sph->coord));
	return (surface);
}
