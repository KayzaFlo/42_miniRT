/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxhooks_prim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:14:39 by arivera           #+#    #+#             */
/*   Updated: 2023/08/24 11:04:47 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtrender.h"
#include "rtparsing.h"

static void	sphere_interact(mlx_key_data_t key, t_screen *s, t_sph *sp)
{
	if (key.key == MLX_KEY_UP && sp->dia < INT32_MAX)
		sp->dia += 0.25;
	if (key.key == MLX_KEY_DOWN && sp->dia > 0.25)
		sp->dia -= 0.25;
	if (s->interaction == TRANSLATE)
	{
		if (key.key == MLX_KEY_W)
			sp->coord.z -= TL_DST * cam_dir(s->elem->cam.ori.z);
		if (key.key == MLX_KEY_S)
			sp->coord.z += TL_DST * cam_dir(s->elem->cam.ori.z);
		if (key.key == MLX_KEY_A)
			sp->coord.x -= TL_DST * -1 * cam_dir(s->elem->cam.ori.z);
		if (key.key == MLX_KEY_D)
			sp->coord.x += TL_DST * -1 * cam_dir(s->elem->cam.ori.z);
		if (key.key == MLX_KEY_SPACE)
			sp->coord.y += TL_DST;
		if (key.key == MLX_KEY_LEFT_CONTROL)
			sp->coord.y -= TL_DST;
	}
}

static void	cylinder_interact(mlx_key_data_t key, t_screen *s, t_cyl *cyl)
{
	if (key.key == MLX_KEY_UP && key.action == 1 && cyl->dia < INT32_MAX)
		cyl->dia += 0.25;
	if (key.key == MLX_KEY_DOWN && cyl->dia > 0.25)
		cyl->dia -= 0.25;
	if (s->interaction == TRANSLATE)
	{
		if (key.key == MLX_KEY_W)
			cyl->coord.z -= TL_DST * cam_dir(s->elem->cam.ori.z);
		if (key.key == MLX_KEY_S)
			cyl->coord.z += TL_DST * cam_dir(s->elem->cam.ori.z);
		if (key.key == MLX_KEY_A)
			cyl->coord.x -= TL_DST * -1 * cam_dir(s->elem->cam.ori.z);
		if (key.key == MLX_KEY_D)
			cyl->coord.x += TL_DST * -1 * cam_dir(s->elem->cam.ori.z);
		if (key.key == MLX_KEY_SPACE)
			cyl->coord.y += TL_DST;
		if (key.key == MLX_KEY_LEFT_CONTROL)
			cyl->coord.y -= TL_DST;
	}
}

static void	plan_interact(mlx_key_data_t key, t_screen *s, t_pl *pl)
{
	if (s->interaction == TRANSLATE)
	{
		if (key.key == MLX_KEY_W)
			pl->coord.z -= TL_DST * cam_dir(s->elem->cam.ori.z);
		if (key.key == MLX_KEY_S)
			pl->coord.z += TL_DST * cam_dir(s->elem->cam.ori.z);
		if (key.key == MLX_KEY_A)
			pl->coord.x -= TL_DST * cam_dir(s->elem->cam.ori.z);
		if (key.key == MLX_KEY_D)
			pl->coord.x += TL_DST * cam_dir(s->elem->cam.ori.z);
		if (key.key == MLX_KEY_SPACE)
			pl->coord.y += TL_DST;
		if (key.key == MLX_KEY_LEFT_CONTROL)
			pl->coord.y -= TL_DST;
	}
}

void	prim_interact(mlx_key_data_t keydata, t_screen *s)
{
	t_sph	*sp;
	t_cyl	*cyl;
	t_pl	*pl;

	if (s->prim->type == PRIM_SPH)
	{
		sp = (t_sph *)s->prim->content;
		sphere_interact(keydata, s, sp);
	}
	if (s->prim->type == PRIM_CYL)
	{
		cyl = (t_cyl *)s->prim->content;
		cylinder_interact(keydata, s, cyl);
	}
	if (s->prim->type == PRIM_PLN)
	{
		pl = (t_pl *)s->prim->content;
		plan_interact(keydata, s, pl);
	}
}
