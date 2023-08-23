/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxhooks_prim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:14:39 by arivera           #+#    #+#             */
/*   Updated: 2023/08/23 16:14:49 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtrender.h"
#include "rtparsing.h"

int	get_dir(double cam_ori)
{
	if (cam_ori >= 0)
		return (-1);
	return (1);
}

static void	sphere_interact(mlx_key_data_t keydata, t_screen *s, t_sph *sp)
{
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS && sp->dia < INT32_MAX)
		sp->dia += 0.25;
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS && sp->dia > 0.25)
		sp->dia -= 0.25;
	if (s->interaction == TRANSLATE)
	{
		if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
			sp->coord.z -= TRANSLATE_DIST * get_dir(s->elem->cam.ori.z);
		if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
			sp->coord.z += TRANSLATE_DIST * get_dir(s->elem->cam.ori.z);
		if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
			sp->coord.x -= TRANSLATE_DIST * -1 * get_dir(s->elem->cam.ori.z);
		if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
			sp->coord.x += TRANSLATE_DIST * -1 * get_dir(s->elem->cam.ori.z);
		if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
			sp->coord.y += TRANSLATE_DIST;
		if (keydata.key == MLX_KEY_LEFT_CONTROL && keydata.action == MLX_PRESS)
			sp->coord.y -= TRANSLATE_DIST;
	}
}

static void	plan_interact(mlx_key_data_t keydata, t_screen *s, t_pl *pl)
{
	if (s->interaction == TRANSLATE)
	{
		if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
			pl->coord.z -= TRANSLATE_DIST * get_dir(s->elem->cam.ori.z);
		if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
			pl->coord.z += TRANSLATE_DIST * get_dir(s->elem->cam.ori.z);
		if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
			pl->coord.x -= TRANSLATE_DIST * get_dir(s->elem->cam.ori.z);
		if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
			pl->coord.x += TRANSLATE_DIST * get_dir(s->elem->cam.ori.z);
		if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
			pl->coord.y += TRANSLATE_DIST;
		if (keydata.key == MLX_KEY_LEFT_CONTROL && keydata.action == MLX_PRESS)
			pl->coord.y -= TRANSLATE_DIST;
	}
}

void	prim_interact(mlx_key_data_t keydata, t_screen *s)
{
	t_sph	*sp;
	// t_cyl	*cyl;
	t_pl	*pl;
	
	if (s->prim->type == PRIM_SPH)
	{
		sp = (t_sph *)s->prim->content;
		sphere_interact(keydata, s, sp);
	}
	// if (s->prim->type == PRIM_CYL)
	// {
	// 	cyl = (t_cyl *)s->prim->content;
	// 	cylinder_interact(keydata, s, cyl);
	// }
	if (s->prim->type == PRIM_PLN)
	{
		pl = (t_pl *)s->prim->content;
		plan_interact(keydata, s, pl);
	}
}
