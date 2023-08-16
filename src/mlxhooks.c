/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:53:46 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/16 16:47:22 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtrender.h"
#include "rtparsing.h"

void ft_hook(void* param)
{
	static int	i = 0;
	t_screen	*screen;

	if (i > 0)
		return ;
	screen = (t_screen *)param;
	// screen->elem->cam.coord.z -= 0.1f;
	// render(screen->img, screen->elem);
	if (screen->render)
		renderthreaded(screen->img, screen->elem);
	// screen->render = false;
	// i++;
}

void ft_close(void* param)
{
	mlx_t* mlx = param;

	mlx_close_window(mlx);
	mlx_terminate(mlx);
	exit(EXIT_SUCCESS);
}

void ft_keyhook(mlx_key_data_t keydata, void* param)
{
	t_screen	*s;
	// t_cyl		*cyl;
	t_sph		*sp;
	// t_pl		*pl;
	t_lit		*light;
	
	s = (t_screen *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		ft_close(s->mlx);
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
		ft_close(s->mlx);
	if (s->cam)
	{
		if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
			s->elem->cam.coord.z -= 1;
		if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
			s->elem->cam.coord.z += 1;
		if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
			s->elem->cam.coord.x -= 1;
		if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
			s->elem->cam.coord.x += 1;
		if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
			s->elem->cam.coord.y += 1;
		if (keydata.key == MLX_KEY_LEFT_CONTROL && keydata.action == MLX_PRESS)
			s->elem->cam.coord.y -= 1;
	}
	else if (s->light)
	{
		light = (t_lit *)s->elem->lit->content;
		if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
			light->coord.z -= 1;
		if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
			light->coord.z += 1;
		if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
			light->coord.x -= 1;
		if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
			light->coord.x += 1;
		if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
			light->coord.y += 1;
		if (keydata.key == MLX_KEY_LEFT_CONTROL && keydata.action == MLX_PRESS)
			light->coord.y -= 1;
	}
	else if (s->prim)
	{
		if (s->prim->type == PRIM_SPH)
		{
			sp = (t_sph *)s->prim->content;
			if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
				sp->coord.z -= 1;
			if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
				sp->coord.z += 1;
			if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
				sp->coord.x -= 1;
			if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
				sp->coord.x += 1;
			if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
				sp->coord.y += 1;
			if (keydata.key == MLX_KEY_LEFT_CONTROL && keydata.action == MLX_PRESS)
				sp->coord.y -= 1;
			if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
				sp->dia += 0.25;
			if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS && sp->dia > 0.25)
				sp->dia -= 0.25;
		}
	}
}

void	ft_translate(t_screen *s, int32_t x, int32_t y)
{
	t_vec3		ro = s->elem->cam.coord;
	t_vec3		rd = v3_normalize(v3_new(x - WIDTH / 2, (y - HEIGHT / 2) * -1, -600));
	t_surface	hit;

	s->cam = 0;
	s->light = 0;
	s->prim = 0;
	if (x > 5 && x < 90 && y > HEIGHT - 25)
	{
		s->cam = 1;
		ft_putstr_fd("Camera selected\n", 1);
		return ;
	}
	if (x > 5 && x < 70 && y > HEIGHT - 50)
	{
		s->light = 1;
		ft_putstr_fd("Light selected\n", 1);
		return ;
	}
	hit = primIntersect(ro, rd, s->elem->prim_list);
	if (hit.sd >= 1000)
		return ;
	ft_putstr_fd("Object selected\n", 1);
	s->prim = hit.prim;
}

void	ft_mouse(mouse_key_t but, action_t act, modifier_key_t mods, void* param)
{
	t_screen	*s;
	int32_t		x;
	int32_t		y;

	s = (t_screen *)param;
	(void)mods;
	(void)act;
	mlx_get_mouse_pos(s->mlx, &x, &y);
	if (but == MLX_MOUSE_BUTTON_LEFT)
		ft_translate(s, x, y);
	// if (but = MLX_MOUSE_BUTTON_RIGHT)
	// 	ft_rotate();
}

void ft_zoom(double xdelta, double ydelta, void* param)
{
	// Simple up or down detection.
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
