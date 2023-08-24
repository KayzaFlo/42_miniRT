/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:53:46 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/24 15:17:57 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtrender.h"
#include "rtparsing.h"


void	ft_close(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	mlx_close_window(mlx);
	mlx_terminate(mlx);
	exit(EXIT_SUCCESS);
}

void	ft_keyhook(mlx_key_data_t keydata, void *param)
{
	t_screen	*s;

	s = (t_screen *)param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			ft_close(s->mlx);
		if (keydata.key == MLX_KEY_Q)
			ft_close(s->mlx);
		if (s->cam)
			camera_interact(keydata, s);
		else if (s->light)
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

void	ft_zoom(double xdelta, double ydelta, void *param)
{
	t_elem	*elem;

	elem = (t_elem *)param;
	(void)xdelta;
	if (ydelta > 0)
		elem->cam.coord.z -= 1;
	else if (ydelta < 0)
		elem->cam.coord.z += 1;
}

void	handle_hooks(t_screen *screen)
{
	mlx_close_hook(screen->mlx, ft_close, screen->mlx);
	mlx_scroll_hook(screen->mlx, ft_zoom, screen->elem);
	mlx_key_hook(screen->mlx, ft_keyhook, screen);
	mlx_mouse_hook(screen->mlx, ft_mouse, screen);
	(void)screen;
}
