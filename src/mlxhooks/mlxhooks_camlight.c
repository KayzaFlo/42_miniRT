/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxhooks_camlight.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:11:42 by arivera           #+#    #+#             */
/*   Updated: 2023/08/24 14:14:54 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtrender.h"
#include "rtparsing.h"

typedef enum e_uvw {
	U = 0,
	V,
	W,
}			t_uvw;

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
	if (key.key == MLX_KEY_W)
		ft_putstr_fd("Camera would look up\n", 2);
	if (key.key == MLX_KEY_S)
		ft_putstr_fd("Camera would look down\n", 2);
	if (key.key == MLX_KEY_A)
		ft_putstr_fd("Camera would look left\n", 2);
	if (key.key == MLX_KEY_D)
		ft_putstr_fd("Camera would look right\n", 2);
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
