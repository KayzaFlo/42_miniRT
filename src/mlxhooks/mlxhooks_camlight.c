/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxhooks_camlight.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:11:42 by arivera           #+#    #+#             */
/*   Updated: 2023/08/25 13:50:24 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtrender.h"
#include "rtparsing.h"

typedef enum e_uvw {
	U = 0,
	V,
	W,
}			t_uvw;

void	camera_interact2(mlx_key_data_t key, t_screen *s)
{
	if (key.key == MLX_KEY_W && s->elem->cam.ori.y < 0.9)
	{
		s->elem->cam.ori = v3_rotatearoundaxis(s->elem->cam.ori,
				s->uvw[U], -15);
	}
	if (key.key == MLX_KEY_S && s->elem->cam.ori.y > -0.9)
	{
		s->elem->cam.ori = v3_rotatearoundaxis(s->elem->cam.ori,
				s->uvw[U], 15);
	}
	if (key.key == MLX_KEY_A)
		s->elem->cam.ori = v3_roty(s->elem->cam.ori, 30);
	if (key.key == MLX_KEY_D)
		s->elem->cam.ori = v3_roty(s->elem->cam.ori, -30);
}

void	camera_interact(mlx_key_data_t key, t_screen *s)
{
	t_cam	*camera;

	camera = &s->elem->cam;
	if (s->interaction == TRANSLATE)
	{
		if (key.key == MLX_KEY_W)
			camera->coord = v3_add(camera->coord, v3_multf(s->uvw[W], 10));
		if (key.key == MLX_KEY_S)
			camera->coord = v3_sub(camera->coord, v3_multf(s->uvw[W], 10));
		if (key.key == MLX_KEY_A)
			camera->coord = v3_add(camera->coord, v3_multf(s->uvw[U], 10));
		if (key.key == MLX_KEY_D)
			camera->coord = v3_sub(camera->coord, v3_multf(s->uvw[U], 10));
		if (key.key == MLX_KEY_SPACE)
			camera->coord.y += 10;
		if (key.key == MLX_KEY_LEFT_CONTROL)
			camera->coord.y -= 10;
		return ;
	}
	camera_interact2(key, s);
}

void	light_interact(mlx_key_data_t key, t_screen *s)
{
	t_lit	*light;

	light = (t_lit *)s->elem->lit->content;
	if (s->interaction == TRANSLATE)
	{
		if (key.key == MLX_KEY_W)
			light->coord = v3_add(light->coord, v3_multf(s->uvw[W], 10));
		if (key.key == MLX_KEY_S)
			light->coord = v3_sub(light->coord, v3_multf(s->uvw[W], 10));
		if (key.key == MLX_KEY_A)
			light->coord = v3_add(light->coord, v3_multf(s->uvw[U], 10));
		if (key.key == MLX_KEY_D)
			light->coord = v3_sub(light->coord, v3_multf(s->uvw[U], 10));
		if (key.key == MLX_KEY_SPACE)
			light->coord.y += 10;
		if (key.key == MLX_KEY_LEFT_CONTROL)
			light->coord.y -= 10;
		return ;
	}
}
