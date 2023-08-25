/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxhooks_prim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:14:39 by arivera           #+#    #+#             */
/*   Updated: 2023/08/25 15:41:46 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtrender.h"
#include "rtparsing.h"

typedef enum e_uvw {
	U = 0,
	V,
	W,
}			t_uvw;

static void	cylinder_rotate(mlx_key_data_t key, t_cyl *cyl)
{
	if (key.key == MLX_KEY_W)
	{
		if (fabs(cyl->norm.x) < 1e-2 && fabs(cyl->norm.z) < 1e-2)
		{
			if (cyl->norm.y > -1e-2)
				cyl->norm = v3_rotatearoundaxis(cyl->norm, 
						v3_cross(v3_new(0, 0, cyl->norm.y), cyl->norm), -15);
		}
		else
			cyl->norm = v3_rotatearoundaxis(cyl->norm, 
					v3_cross(v3_new(0, 1, 0), cyl->norm), -15);
	}
	if (key.key == MLX_KEY_S)
	{
		if (fabs(cyl->norm.x) < 1e-2 && fabs(cyl->norm.z) < 1e-2)
		{
			if (cyl->norm.y < 1e-2)
				cyl->norm = v3_rotatearoundaxis(cyl->norm, 
						v3_cross(v3_new(0, 0, cyl->norm.y), cyl->norm), 15);
		}
		else
			cyl->norm = v3_rotatearoundaxis(cyl->norm, 
					v3_cross(v3_new(0, 1, 0), cyl->norm), 15);
	}
}

void	cyl_interact_size(mlx_key_data_t key, t_cyl *cyl)
{
	if (key.key == MLX_KEY_UP && cyl->dia < (INT32_MAX - 0.4))
		cyl->dia += 0.25;
	if (key.key == MLX_KEY_DOWN && cyl->dia > 0.25)
		cyl->dia -= 0.25;
	if (key.key == MLX_KEY_RIGHT && cyl->hgt < (INT32_MAX - 1))
		cyl->hgt += 1;
	if (key.key == MLX_KEY_LEFT && cyl->hgt > 1)
		cyl->hgt -= 1;
}

void	cylinder_interact(mlx_key_data_t key, t_screen *s, t_cyl *cyl)
{
	cyl_interact_size(key, cyl);
	if (s->interaction == TRANSLATE)
	{
		if (key.key == MLX_KEY_W)
			cyl->coord = v3_add(cyl->coord, s->uvw[W]);
		if (key.key == MLX_KEY_S)
			cyl->coord = v3_sub(cyl->coord, s->uvw[W]);
		if (key.key == MLX_KEY_A)
			cyl->coord = v3_sub(cyl->coord, s->uvw[U]);
		if (key.key == MLX_KEY_D)
			cyl->coord = v3_add(cyl->coord, s->uvw[U]);
		if (key.key == MLX_KEY_SPACE)
			cyl->coord.y += TL_DST;
		if (key.key == MLX_KEY_LEFT_CONTROL)
			cyl->coord.y -= TL_DST;
		return ;
	}
	cylinder_rotate(key, cyl);
	if (key.key == MLX_KEY_A)
		cyl->norm = v3_roty(cyl->norm, 25);
	if (key.key == MLX_KEY_D)
		cyl->norm = v3_roty(cyl->norm, -25);
}

static void	plan_rotate(mlx_key_data_t key, t_pl *pl)
{
	if (key.key == MLX_KEY_W)
	{
		if (fabs(pl->ori.x) < 1e-2 && fabs(pl->ori.z) < 1e-2)
		{
			if (pl->ori.y > -1e-2)
				pl->ori = v3_rotatearoundaxis(pl->ori, 
						v3_cross(v3_new(0, 0, pl->ori.y), pl->ori), -10);
		}
		else
			pl->ori = v3_rotatearoundaxis(pl->ori, 
					v3_cross(v3_new(0, 1, 0), pl->ori), -10);
	}
	if (key.key == MLX_KEY_S)
	{
		if (fabs(pl->ori.x) < 1e-2 && fabs(pl->ori.z) < 1e-2)
		{
			if (pl->ori.y < 1e-2)
				pl->ori = v3_rotatearoundaxis(pl->ori, 
						v3_cross(v3_new(0, 0, pl->ori.y), pl->ori), 10);
		}
		else
			pl->ori = v3_rotatearoundaxis(pl->ori, 
					v3_cross(v3_new(0, 1, 0), pl->ori), 10);
	}
}

void	plan_interact(mlx_key_data_t key, t_screen *s, t_pl *pl)
{
	if (s->interaction == TRANSLATE)
	{
		if (key.key == MLX_KEY_W)
			pl->coord = v3_add(pl->coord, s->uvw[W]);
		if (key.key == MLX_KEY_S)
			pl->coord = v3_sub(pl->coord, s->uvw[W]);
		if (key.key == MLX_KEY_A)
			pl->coord = v3_sub(pl->coord, s->uvw[U]);
		if (key.key == MLX_KEY_D)
			pl->coord = v3_add(pl->coord, s->uvw[U]);
		if (key.key == MLX_KEY_SPACE)
			pl->coord.y += TL_DST;
		if (key.key == MLX_KEY_LEFT_CONTROL)
			pl->coord.y -= TL_DST;
		return ;
	}
	plan_rotate(key, pl);
	if (key.key == MLX_KEY_A)
		pl->ori = v3_roty(pl->ori, 25);
	if (key.key == MLX_KEY_D)
		pl->ori = v3_roty(pl->ori, -25);
}
