/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:16:33 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/11 11:09:38 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtrender.h"

void	v3_print(t_vec3 v) { printf("[%.4f, %.4f, %.4f]\n", v.x, v.y, v.z); }

t_surface	primIntersect(t_vec3 ro, t_vec3 rd, t_list *prim_list)
{
	t_surface	nearest_surface;
	t_surface	hit;
	t_prim		*prim;
	int c = 0;

	nearest_surface.sd = 1e10;
	while (prim_list)
	{
		c++;
		if (c > 10) exit(-1);

		prim = (t_prim *)(prim_list->content);
		if (prim->type == PRIM_PLN)
			hit = plIntersect(ro, rd, (t_pl *)(prim->content));
		if (prim->type == PRIM_SPH)
			hit = sphIntersect(ro, rd, (t_sph *)(prim->content));
		// if (prim->type == PRIM_CYL)
		// 	hit = cylIntersect(ro, rd, (t_cyl *)(prim->content));
		prim_list = prim_list->next;
		if (hit.sd > 0 && hit.sd < nearest_surface.sd)
			nearest_surface = hit;
	}
		// ** PRIM TEST **
		hit = elliIntersect(v3_sub(ro, v3_new(-4, 0, -4)), rd, v3_new(2, 1, 1));
		if (hit.sd > 0 && hit.sd < nearest_surface.sd)
			nearest_surface = hit;
		// ***************
	return (nearest_surface);
}

uint32_t	pixelcompute(int x, int y, t_elem *elem)
{
	t_vec3		ro = elem->cam.coord;
	t_vec3		rd = v3_normalize(v3_new(x - WIDTH / 2, (y - HEIGHT / 2) * -1, -600));
	t_lit		*light = (t_lit *)(elem->lit->content);
	t_vec3		light_dir;
	t_vec3		col = elem->amb.col;
	t_surface	hit;
	t_vec3		hitpoint;


	hit = primIntersect(ro, rd, elem->prim_list);
	hitpoint = v3_add(ro, v3_new(rd.x * hit.sd, rd.y * hit.sd, rd.z * hit.sd));
	light_dir = v3_normalize(v3_sub(light->coord, hitpoint));
	if (hit.sd < 1000)
	{
		col = hit.col;
		//Normal diff
		col = v3_multf(col, clamp(v3_dot(hit.n, light_dir), 0, 1));
		// Hard Shadow
		// col = v3_multf(col, primIntersect(hitpoint, light_dir, elem->prim_list).sd < 1000 ? 0 : 1);
		// ambient - temp formula
		col = v3_add(col, v3_multf(elem->amb.col, elem->amb.ratio));
		//col = norm;		//DEBUG NORMAL
	}
	col = v3_multf(col, 1.0 / 255.0);
	col = v3_new(sqrtf(col.x), sqrtf(col.y) ,sqrtf(col.z));
	// col = v3_mult(col, col);
	// return (hexcol(col.x, col.y, col.z, 255));
	return (hexcol(col.x * 255, col.y * 255, col.z * 255, 255));
}

void	render(mlx_image_t *img, t_elem *elem)
{
	int	x;
	int	y;

	y = -1;
	while (y++ < HEIGHT)
	{
		x = -1;
		while (x++ < WIDTH)
		{
			mlx_put_pixel(img, x, y, pixelcompute(x, y, elem));
		}
	}
}
