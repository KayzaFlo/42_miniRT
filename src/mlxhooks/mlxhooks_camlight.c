/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxhooks_camlight.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:11:42 by arivera           #+#    #+#             */
/*   Updated: 2023/08/24 15:54:48 by arivera          ###   ########.fr       */
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
		s->elem->cam.ori.y += 0.1;
		if (!s->elem->cam.ori.x && !s->elem->cam.ori.z)
			s->elem->cam.ori.z = 0.2;
	}
	if (key.key == MLX_KEY_S && s->elem->cam.ori.y > -0.9)
	{
		s->elem->cam.ori.y -= 0.1;
		if (!s->elem->cam.ori.x && !s->elem->cam.ori.z)
			s->elem->cam.ori.z = 0.2;
	}
	if (key.key == MLX_KEY_A)
		s->elem->cam.ori = v3_roty(s->elem->cam.ori, 30);
	if (key.key == MLX_KEY_D)
		s->elem->cam.ori = v3_roty(s->elem->cam.ori, -30);
}

void	camera_interact(mlx_key_data_t key, t_screen *s)
{
	if (s->interaction == TRANSLATE)
	{
		if (key.key == MLX_KEY_W)
			s->elem->cam.coord = v3_add(s->elem->cam.coord, s->uvw[W]);
		if (key.key == MLX_KEY_S)
			s->elem->cam.coord = v3_sub(s->elem->cam.coord, s->uvw[W]);
		if (key.key == MLX_KEY_A)
			s->elem->cam.coord = v3_add(s->elem->cam.coord, s->uvw[U]);
		if (key.key == MLX_KEY_D)
			s->elem->cam.coord = v3_sub(s->elem->cam.coord, s->uvw[U]);
		if (key.key == MLX_KEY_SPACE)
			s->elem->cam.coord.y += TL_DST;
		if (key.key == MLX_KEY_LEFT_CONTROL)
			s->elem->cam.coord.y -= TL_DST;
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
			light->coord = v3_add(light->coord, s->uvw[W]);
		if (key.key == MLX_KEY_S)
			light->coord = v3_sub(light->coord, s->uvw[W]);
		if (key.key == MLX_KEY_A)
			light->coord = v3_add(light->coord, s->uvw[U]);
		if (key.key == MLX_KEY_D)
			light->coord = v3_sub(light->coord, s->uvw[U]);
		if (key.key == MLX_KEY_SPACE)
			light->coord.y += TL_DST;
		if (key.key == MLX_KEY_LEFT_CONTROL)
			light->coord.y -= TL_DST;
		return ;
	}
}
