/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxhooks_prim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:14:39 by arivera           #+#    #+#             */
/*   Updated: 2023/08/23 16:59:39 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtrender.h"
#include "rtparsing.h"

static void	sphere_interact(mlx_key_data_t key, t_screen *s, t_sph *sp)
{
	if (key.key == MLX_KEY_UP && key.action == 1 && sp->dia < INT32_MAX)
		sp->dia += 0.25;
	if (key.key == MLX_KEY_DOWN && key.action == MLX_PRESS && sp->dia > 0.25)
		sp->dia -= 0.25;
	if (s->interaction == TRANSLATE)
	{
		if (key.key == MLX_KEY_W && key.action == MLX_PRESS)
			sp->coord.z -= TL_DST * cam_dir(s->elem->cam.ori.z);
		if (key.key == MLX_KEY_S && key.action == MLX_PRESS)
			sp->coord.z += TL_DST * cam_dir(s->elem->cam.ori.z);
		if (key.key == MLX_KEY_A && key.action == MLX_PRESS)
			sp->coord.x -= TL_DST * -1 * cam_dir(s->elem->cam.ori.z);
		if (key.key == MLX_KEY_D && key.action == MLX_PRESS)
			sp->coord.x += TL_DST * -1 * cam_dir(s->elem->cam.ori.z);
		if (key.key == MLX_KEY_SPACE && key.action == MLX_PRESS)
			sp->coord.y += TL_DST;
		if (key.key == MLX_KEY_LEFT_CONTROL && key.action == MLX_PRESS)
			sp->coord.y -= TL_DST;
	}
}

static void	cylinder_interact(mlx_key_data_t key, t_screen *s, t_cyl *cyl)
{
	if (key.key == MLX_KEY_UP && key.action == 1 && cyl->dia < INT32_MAX)
		cyl->dia += 0.25;
	if (key.key == MLX_KEY_DOWN && key.action == MLX_PRESS && cyl->dia > 0.25)
		cyl->dia -= 0.25;
	if (s->interaction == TRANSLATE)
	{
		if (key.key == MLX_KEY_W && key.action == MLX_PRESS)
			cyl->coord.z -= TL_DST * cam_dir(s->elem->cam.ori.z);
		if (key.key == MLX_KEY_S && key.action == MLX_PRESS)
			cyl->coord.z += TL_DST * cam_dir(s->elem->cam.ori.z);
		if (key.key == MLX_KEY_A && key.action == MLX_PRESS)
			cyl->coord.x -= TL_DST * -1 * cam_dir(s->elem->cam.ori.z);
		if (key.key == MLX_KEY_D && key.action == MLX_PRESS)
			cyl->coord.x += TL_DST * -1 * cam_dir(s->elem->cam.ori.z);
		if (key.key == MLX_KEY_SPACE && key.action == MLX_PRESS)
			cyl->coord.y += TL_DST;
		if (key.key == MLX_KEY_LEFT_CONTROL && key.action == MLX_PRESS)
			cyl->coord.y -= TL_DST;
	}
}

static void	plan_interact(mlx_key_data_t key, t_screen *s, t_pl *pl)
{
	if (s->interaction == TRANSLATE)
	{
		if (key.key == MLX_KEY_W && key.action == MLX_PRESS)
			pl->coord.z -= TL_DST * cam_dir(s->elem->cam.ori.z);
		if (key.key == MLX_KEY_S && key.action == MLX_PRESS)
			pl->coord.z += TL_DST * cam_dir(s->elem->cam.ori.z);
		if (key.key == MLX_KEY_A && key.action == MLX_PRESS)
			pl->coord.x -= TL_DST * cam_dir(s->elem->cam.ori.z);
		if (key.key == MLX_KEY_D && key.action == MLX_PRESS)
			pl->coord.x += TL_DST * cam_dir(s->elem->cam.ori.z);
		if (key.key == MLX_KEY_SPACE && key.action == MLX_PRESS)
			pl->coord.y += TL_DST;
		if (key.key == MLX_KEY_LEFT_CONTROL && key.action == MLX_PRESS)
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
