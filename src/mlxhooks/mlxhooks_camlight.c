/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxhooks_camlight.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:11:42 by arivera           #+#    #+#             */
/*   Updated: 2023/08/22 13:59:24 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtrender.h"
#include "rtparsing.h"

void	camera_interact(mlx_key_data_t keydata, t_screen *s)
{
	if (s->interaction == TRANSLATE)
	{
		if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
			s->elem->cam.coord.z -= TRANSLATE_DIST;
		if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
			s->elem->cam.coord.z += TRANSLATE_DIST;
		if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
			s->elem->cam.coord.x -= TRANSLATE_DIST;
		if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
			s->elem->cam.coord.x += TRANSLATE_DIST;
		if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
			s->elem->cam.coord.y += TRANSLATE_DIST;
		if (keydata.key == MLX_KEY_LEFT_CONTROL && keydata.action == MLX_PRESS)
			s->elem->cam.coord.y -= TRANSLATE_DIST;
		return ;
	}
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		ft_putstr_fd("Camera would look up\n", 2);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		ft_putstr_fd("Camera would look down\n", 2);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		ft_putstr_fd("Camera would look left\n", 2);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		ft_putstr_fd("Camera would look right\n", 2);
}

void	light_interact(mlx_key_data_t keydata, t_screen *s)
{
	t_lit	*light;

	light = (t_lit *)s->elem->lit->content;
	if (s->interaction == TRANSLATE)
	{
		if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
			light->coord.z -= TRANSLATE;
		if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
			light->coord.z += TRANSLATE;
		if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
			light->coord.x -= TRANSLATE;
		if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
			light->coord.x += TRANSLATE;
		if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
			light->coord.y += TRANSLATE;
		if (keydata.key == MLX_KEY_LEFT_CONTROL && keydata.action == MLX_PRESS)
			light->coord.y -= TRANSLATE;
	}
}