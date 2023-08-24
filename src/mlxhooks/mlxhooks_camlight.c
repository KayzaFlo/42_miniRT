/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxhooks_camlight.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:11:42 by arivera           #+#    #+#             */
/*   Updated: 2023/08/24 11:03:57 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtrender.h"
#include "rtparsing.h"

void	camera_interact(mlx_key_data_t keydata, t_screen *s)
{
	if (s->interaction == TRANSLATE)
	{
		if (keydata.key == MLX_KEY_W)
			s->elem->cam.coord.z -= TL_DST * cam_dir(s->elem->cam.ori.z);
		if (keydata.key == MLX_KEY_S)
			s->elem->cam.coord.z += TL_DST * cam_dir(s->elem->cam.ori.z);
		if (keydata.key == MLX_KEY_A)
			s->elem->cam.coord.x -= TL_DST;
		if (keydata.key == MLX_KEY_D)
			s->elem->cam.coord.x += TL_DST;
		if (keydata.key == MLX_KEY_SPACE)
			s->elem->cam.coord.y += TL_DST;
		if (keydata.key == MLX_KEY_LEFT_CONTROL)
			s->elem->cam.coord.y -= TL_DST;
		return ;
	}
	if (keydata.key == MLX_KEY_W)
		ft_putstr_fd("Camera would look up\n", 2);
	if (keydata.key == MLX_KEY_S)
		ft_putstr_fd("Camera would look down\n", 2);
	if (keydata.key == MLX_KEY_A)
		ft_putstr_fd("Camera would look left\n", 2);
	if (keydata.key == MLX_KEY_D)
		ft_putstr_fd("Camera would look right\n", 2);
}

void	light_interact(mlx_key_data_t keydata, t_screen *s)
{
	t_lit	*light;

	light = (t_lit *)s->elem->lit->content;
	if (s->interaction == TRANSLATE)
	{
		if (keydata.key == MLX_KEY_W)
			light->coord.z -= TL_DST;
		if (keydata.key == MLX_KEY_S)
			light->coord.z += TL_DST;
		if (keydata.key == MLX_KEY_A)
			light->coord.x -= TL_DST;
		if (keydata.key == MLX_KEY_D)
			light->coord.x += TL_DST;
		if (keydata.key == MLX_KEY_SPACE)
			light->coord.y += TL_DST;
		if (keydata.key == MLX_KEY_LEFT_CONTROL)
			light->coord.y -= TL_DST;
	}
}
