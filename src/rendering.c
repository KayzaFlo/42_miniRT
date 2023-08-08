/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:16:33 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/08 12:39:38 by fgeslin          ###   ########.fr       */
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
  	return obj2; // The sd component of the struct holds the "signed distance" value
  return (obj1);
}

t_surface	map(t_vec3 p)
{
	t_surface sphereLeft = sd_sphere(v3_sub(p, v3_new(-2.5, -1, -2)), 1., v3_new(0.0f, 0.8f, 0.8f));
	t_surface boxRight = sd_box(v3_sub(p, v3_new(2.5, 0, -2)), v3_new(0.8f, 0.8f, 0.8f), v3_new(1.0f, 0.58f, 0.29f));
	t_surface cylinder = sd_cylinder(v3_sub(p, v3_new(0.5, 0, -4)), v3_new(0.1f, -0.1f, 0.0f), v3_new(-0.1f, 0.35f, 0.1f), 1.0f, v3_new(0.8f, 0.1f, 0.89f));
	t_surface plane = sd_plane(p, v3_new(0.0f, 1.0f, 0.0f));

	t_surface res = opU(sphereLeft, boxRight);
	res = opU(res, plane);
	res = opU(res, cylinder);
	return res;
}

t_vec3	calcNormal(t_vec3 p) {
    float e; //epsilon

    e = 0.0005f;
	return v3_normalize(v3_new(
		map(v3_new(p.x + e, p.y, p.z)).sd - map(v3_new(p.x - e, p.y, p.z)).sd,
		map(v3_new(p.x, p.y + e, p.z)).sd - map(v3_new(p.x, p.y - e, p.z)).sd,
		map(v3_new(p.x, p.y, p.z  + e)).sd - map(v3_new(p.x, p.y, p.z - e)).sd
  	));
}

t_surface	raymarch(t_vec3 ro, t_vec3 rd, float start, float end)
{
	float		depth;
	t_surface	co; //closet object
	int			i;

	depth = start;
	i = -1;
	while (i++ < MAX_MARCHING_STEPS)
	{
		t_vec3	point = v3_new(
				ro.x + rd.x * depth,
				ro.y + rd.y * depth,
				ro.z + rd.z * depth
			);
		co = map(point);
		depth += co.sd;
		if (co.sd < PRECISION || depth > end)
			break;
	}
	co.sd = depth;
	co.col = v3_mult(co.col, v3_new(255, 255, 255)); /// temp
	return (co);
}

void	render(mlx_image_t *img)
{
	const t_vec3	bgColor = v3_new(155.0f, 155.0f, 255.0f);
	const t_vec3	ro = v3_new(0, 0, 5); // Ray Origin / Camera
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
			t_surface	co = raymarch(ro, v3_normalize(ray_direction), MIN_DIST, MAX_DIST); // closest object
			if (co.sd > 100.0f) // Didn't hit
				color = hexcol(bgColor.x, bgColor.y, bgColor.z, 255);
			else
			{
				t_vec3	point = v3_new(
						ro.x + ray_direction.x * co.sd,
						ro.y + ray_direction.y * co.sd,
						ro.z + ray_direction.z * co.sd
					);
				t_vec3	normal = calcNormal(point);
				t_vec3	light_pos = v3_new(2, 2, 4);
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
