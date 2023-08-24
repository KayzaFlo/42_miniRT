/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:53:46 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/24 15:42:50 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtrender.h"
#include "rtparsing.h"
#include <stdlib.h>

typedef enum e_uvw {
	U = 0,
	V,
	W,
}			t_uvw;

void	ft_close(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	mlx_close_window(mlx);
	mlx_terminate(mlx);
	exit(EXIT_SUCCESS);
}

static void	get_uvw(t_screen *s)
{
	if (s->uvw)
		free(s->uvw);
	s->uvw = (t_vec3 *)malloc(sizeof(t_vec3) * 3);
	if (!s->uvw)
	{
		free_elem(s->elem);
		exit(1);
	}
	s->uvw[W] = v3_normalize(v3_multf(s->elem->cam.ori, 1));
	s->uvw[U] = v3_normalize(v3_cross(v3_new(0, 1, 0), s->uvw[W]));
	if (!s->elem->cam.ori.x && !s->elem->cam.ori.z)
		s->uvw[U] = v3_normalize(v3_cross(v3_new(0, 0, s->elem->cam.ori.y),
					s->uvw[W]));
	s->uvw[W] = v3_cross(s->uvw[U], v3_new(0, 1, 0));
	s->uvw[V] = v3_new(0, 1, 0);
}

void	ft_keyhook(mlx_key_data_t keydata, void *param)
{
	t_screen	*s;

	s = (t_screen *)param;
	if (keydata.action == MLX_PRESS && valid_key(keydata))
	{
		get_uvw(s);
		if (keydata.key == MLX_KEY_ESCAPE)
			ft_close(s->mlx);
		if (keydata.key == MLX_KEY_Q)
			ft_close(s->mlx);
		if (s->selected == T_CAM)
			camera_interact(keydata, s);
		else if (s->selected == T_LIGHT)
			light_interact(keydata, s);
		else if (s->prim)
			prim_interact(keydata, s);
		s->ismovepressed = 1;
	}
	if (keydata.action == MLX_RELEASE)
		s->ismovepressed = 0;
}

void	ft_mouse(mouse_key_t but, action_t act, modifier_key_t mods, void *p)
{
	t_screen	*s;
	int32_t		x;
	int32_t		y;

	s = (t_screen *)p;
	(void)mods;
	(void)act;
	mlx_get_mouse_pos(s->mlx, &x, &y);
	if (but == MLX_MOUSE_BUTTON_LEFT && act == MLX_PRESS)
		s->interaction = TRANSLATE;
	else if (but == MLX_MOUSE_BUTTON_RIGHT && act == MLX_PRESS)
		s->interaction = ROTATE;
	if (act == MLX_PRESS)
		ft_get_selection(s, x, y);
}

void	handle_hooks(t_screen *screen)
{
	mlx_close_hook(screen->mlx, ft_close, screen->mlx);
	mlx_key_hook(screen->mlx, ft_keyhook, screen);
	mlx_mouse_hook(screen->mlx, ft_mouse, screen);
	(void)screen;
}
