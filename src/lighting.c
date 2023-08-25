/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:24:23 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/25 13:24:34 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtrender.h"

static t_vec3	get_specular(t_surface hit, t_vec3 ld, t_vec3 lc, t_vec3 rd)
{
	t_vec3	reflec;
	double	spec;

	reflec = v3_rotatearoundaxis(ld, hit.n, 180);
	spec = (max(-v3_dot(reflec, v3_normalize(rd)), 0.9) - 0.9) * 10;
	return (v3_multf(lc, spec));
}

static t_vec3	get_ambient(t_surface hit, t_elem *elem)
{
	return (v3_mult(hit.col, v3_multf(elem->amb.col, elem->amb.ratio / 255.0)));
}

static t_vec3	get_diffuse(t_surface hit, t_lit *l, double shad, t_vec3 ld)
{
	float	diffuse;

	diffuse = max(v3_dot(hit.n, ld), 0);
	return (v3_mult(hit.col, v3_multf(l->col, min(shad, diffuse) / 255.0)));
}

t_vec3	get_light(t_vec3 ro, t_vec3 rd, t_elem *elem, t_surface hit)
{
	t_lit	*light;
	t_vec3	light_dir;
	t_vec3	hitpoint;
	float	shad_coef;
	t_vec3	col;

	light = (t_lit *)(elem->lit->content);
	hitpoint = v3_add(ro, v3_multf(rd, hit.sd));
	light_dir = v3_normalize(v3_sub(light->coord, hitpoint));
	if (prim_intersect(hitpoint, light_dir, elem->prim_list).sd
		< v3_length(v3_sub(hitpoint, light->coord)) + 1e-3)
		shad_coef = 0;
	else
		shad_coef = 1;
	col = get_diffuse(hit, light, shad_coef, light_dir);
	col = v3_add(col, get_ambient(hit, elem));
	col = v3_add(col, v3_multf(get_specular(hit, light_dir, light->col, rd),
				shad_coef));
	return (col);
}
