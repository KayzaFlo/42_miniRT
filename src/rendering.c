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

const int	MAX_MARCHING_STEPS = 255;
const float	MIN_DIST = 0.0f;
const float	MAX_DIST = 100.0f;
const float	PRECISION = 0.001f;

void	v3_print(t_vec3 v) { printf("[%.4f, %.4f, %.4f]\n", v.x, v.y, v.z); }

// operation union
t_surface	opU(t_surface obj1, t_surface obj2)
{
	if (obj2.sd < obj1.sd)
		return (obj2); // The sd component of the struct holds the "signed distance" value
	return (obj1);
}

t_surface	map(t_vec3 p, t_elem *elem)
{
	t_list		*list = elem->prim_list;
	t_surface	res;

	res.col = v3_new(0, 0, 0);
	res.sd = INFINITY;
	while (list)
	{
		t_prim	*prim = (t_prim *)(list->content);
		if (prim->type == PRIM_SPH) {
			t_sph	*sph = (t_sph *)(prim->content);
			res = opU(res, sd_sphere(v3_sub(p, sph->coord), sph->dia, sph->col));
		}
		if (prim->type == PRIM_PLN) {
			t_pl	*pl = (t_pl *)(prim->content);
			res = opU(res, sd_plane(v3_sub(p, pl->coord), v3_normalize(pl->ori), pl->col));
		}
		if (prim->type == PRIM_CYL) {
			t_cyl	*cyl = (t_cyl *)(prim->content);
			res = opU(res, sd_cylinder(v3_sub(p, cyl->coord), v3_normalize(cyl->norm), cyl->dia, cyl->hgt, cyl->col));
		}
		list = list->next;
	}
	return res;
}

t_vec3	calcNormal(t_vec3 p, t_elem *elem) {
    float e; //epsilon

    e = 0.0005f;
	return v3_normalize(v3_new(
		map(v3_new(p.x + e, p.y, p.z), elem).sd - map(v3_new(p.x - e, p.y, p.z), elem).sd,
		map(v3_new(p.x, p.y + e, p.z), elem).sd - map(v3_new(p.x, p.y - e, p.z), elem).sd,
		map(v3_new(p.x, p.y, p.z  + e), elem).sd - map(v3_new(p.x, p.y, p.z - e), elem).sd
  	));
}

t_surface	raymarch(t_vec3 ro, t_vec3 rd, t_elem *elem)
{
	float		depth;
	t_surface	co; //closet object
	int			i;

	depth = MIN_DIST;
	i = -1;
	while (i++ < MAX_MARCHING_STEPS)
	{
		t_vec3	point = v3_new(
				ro.x + rd.x * depth,
				ro.y + rd.y * depth,
				ro.z + rd.z * depth
			);
		co = map(point, elem);
		depth += co.sd;
		if (co.sd < PRECISION || depth > MAX_DIST)
			break;
	}
	co.sd = depth;
	// co.col = v3_mult(co.col, v3_new(255, 255, 255)); /// temp
	return (co);
}

void	render(mlx_image_t *img, t_elem *elem)
{
	const t_vec3	bgColor = elem->amb.col;
	const t_vec3	ro = v3_new(elem->cam.coord.x, elem->cam.coord.y, elem->cam.coord.z); // Ray Origin / Camera
	t_vec3			ray_direction; // Ray Direction
	uint32_t		color;
	int				i;
	int				j;

	i = -1;
	while (i++ < WIDTH - 1)
	{
// DEBUG Loading
printf("\e[1;36m\r%05.1f%%\e[0m", (float)i / (WIDTH - 1) * 100.0f);
fflush(stdout);
		j = -1;
		while (j++ < HEIGHT - 1)
		{
			ray_direction = v3_normalize(v3_new(i - WIDTH / 2, (j - HEIGHT / 2) * -1, -1000)); // ecran a normaliser facon uv ?
			t_surface	co = raymarch(ro, v3_normalize(ray_direction), elem); // closest object
			if (co.sd > 100.0f) // Didn't hit
				color = hexcol(bgColor.x, bgColor.y, bgColor.z, 255);
			else
			{
				t_vec3	point = v3_new(
						ro.x + ray_direction.x * co.sd,
						ro.y + ray_direction.y * co.sd,
						ro.z + ray_direction.z * co.sd
					);
				t_vec3	normal = calcNormal(point, elem);
				// t_vec3	light_pos = v3_new(2, 2, 4);
				t_lit	*light = (t_lit *)(elem->lit->content);
				t_vec3	light_pos = v3_new(light->coord.x, light->coord.y, light->coord.z);
				t_vec3	light_dir = v3_normalize(v3_sub(light_pos, point));

				float dif = clamp(v3_dot(normal, light_dir), 0, 1);

				color = hexcol(
						co.col.x * dif * 1.0f + bgColor.x * 0.2f,
						co.col.y * dif * 1.0f + bgColor.y * 0.2f,
						co.col.z * dif * 1.0f + bgColor.z * 0.2f,
						255
					);
			}
			mlx_put_pixel(img, i, j, color);
			// UV Debug
			// mlx_put_pixel(img, i, j, hexcol((float)i / WIDTH * 255.0f, (HEIGHT - (float)j) / HEIGHT * 255.0f, 0, 255));
		}
	}
// DEBUG Loading
printf("\n");
}
