/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:16:33 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/23 17:52:35 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtrender.h"

typedef enum e_viewport {
	PIXDELTA_U = 0,
	PIXDELTA_V,
	PIX00LOC,
}			t_viewport;

typedef enum e_uvw {
	U = 0,
	V,
	W,
}			t_uvw;

t_surface	prim_intersect(t_vec3 ro, t_vec3 rd, t_list *prim_list)
{
	t_surface	nearest_surface;
	t_surface	hit;
	t_prim		*prim;

	nearest_surface.sd = 1e10;
	while (prim_list)
	{
		prim = (t_prim *)(prim_list->content);
		if (prim->type == PRIM_PLN)
			hit = plIntersect(ro, rd, (t_pl *)(prim->content));
		if (prim->type == PRIM_SPH)
			hit = sphIntersect(ro, rd, (t_sph *)(prim->content));
		if (prim->type == PRIM_CYL)
			hit = cyl_intersect(ro, rd, (t_cyl *)(prim->content));
		prim_list = prim_list->next;
		if (hit.sd > 1e-5 && hit.sd < nearest_surface.sd)
		{
			nearest_surface = hit;
			nearest_surface.prim = prim;
		}
	}
	return (nearest_surface);
}

// Diffuse light
// Hard Shadow
// Ambient light
t_vec3	pixelcompute(t_vec3 ro, t_vec3 rd, t_elem *elem)
{
	const t_lit		*light = (t_lit *)(elem->lit->content);
	t_vec3			light_dir;
	t_vec3			col;
	t_surface		hit;
	t_vec3			hitpoint;

	col = elem->amb.col;
	hit = prim_intersect(ro, rd, elem->prim_list);
	hitpoint = v3_add(ro, v3_multf(rd, hit.sd));
	light_dir = v3_normalize(v3_sub(light->coord, hitpoint));
	if (hit.sd < 1000)
	{
		col = hit.col;
		col = v3_multf(col, clamp(v3_dot(hit.n, light_dir), 0, 1));
		if (prim_intersect(hitpoint, light_dir, elem->prim_list).sd < 1000)
			col = v3_multf(col, 0);
		col = v3_add(col, v3_multf(elem->amb.col, elem->amb.ratio));
	}
	col = v3_multf(col, 1.0 / 255.0);
	col = v3_new(sqrtf(col.x), sqrtf(col.y), sqrtf(col.z));
	return (v3_multf(col, 255));
}

// uvw => Referencial -rd
// viewport_uv => viewport size
t_vec3	*get_viewport(t_elem *elem, float theta)
{
	const float	ratio = (double)WIDTH / (double)HEIGHT;
	t_vec3		*data;
	t_vec3		uvw[3];
	t_vec3		viewport_uv[2];
	t_vec3		viewport_upperleft;

	data = ft_calloc(3, sizeof(*data));
	uvw[W] = v3_normalize(v3_multf(elem->cam.ori, -1));
	uvw[U] = v3_normalize(v3_cross(v3_new(0, 1, 0), uvw[W]));
	uvw[V] = v3_cross(uvw[W], uvw[U]);
	viewport_uv[U] = v3_multf(uvw[U], 2 * tan(theta / 2) * ratio);
	viewport_uv[V] = v3_multf(uvw[V], -2 * tan(theta / 2));
	data[PIXDELTA_U] = v3_multf(viewport_uv[U], 1.0 / (double)WIDTH);
	data[PIXDELTA_V] = v3_multf(viewport_uv[V], 1.0 / (double)HEIGHT);
	viewport_upperleft = v3_sub(
			v3_sub(elem->cam.coord, v3_multf(uvw[W], 1)),
			v3_add(v3_multf(viewport_uv[U], 0.5f),
				v3_multf(viewport_uv[V], 0.5f)));
	data[PIX00LOC] = v3_add(viewport_upperleft,
			v3_multf(v3_add(data[0], data[1]), 0.5f));
	return (data);
}

t_vec3	get_rd(t_vec3 *data, int x, int y, t_elem *elem)
{
	t_vec3	pixel_center;

	pixel_center = v3_add(
			data[PIX00LOC],
			v3_add(v3_multf(data[PIXDELTA_U], x), v3_multf(data[PIXDELTA_V], y))
			);
	return (v3_sub(pixel_center, elem->cam.coord));
}

void	render(mlx_image_t *img, t_elem *elem)
{
	int		x;
	int		y;
	t_vec3	c;
	t_vec3	*data;

	data = get_viewport(elem, elem->cam.fov * M_PI / 180.0f);
	y = -1;
	while (y++ < HEIGHT - 1)
	{
		printf("\e[1;36m\r%05.1f%%\e[0m", (float)y / (HEIGHT - 1) * 100.0f);
		fflush(stdout);
		x = -1;
		while (x++ < WIDTH - 1)
		{
			c = pixelcompute(elem->cam.coord, get_rd(data, x, y, elem), elem);
			mlx_put_pixel(img, x, y, hexcol(c.x, c.y, c.z, 255));
		}
	}
	free(data);
	printf("\n");
}
