/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxhooks_misc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:16:47 by arivera           #+#    #+#             */
/*   Updated: 2023/08/24 14:24:00 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtrender.h"
#include "rtparsing.h"

void	ft_get_selection(t_screen *s, int32_t x, int32_t y)
{
	t_vec3		ro;
	t_vec3		rd;
	t_surface	hit;
	t_vec3		*data;

	data = get_viewport(s->elem, s->elem->cam.fov * M_PI / 180.0f);
	ro = s->elem->cam.coord;
	rd = get_rd(data, x, y, s->elem);
	free(data);
	s->selected = 0;
	s->prim = 0;
	if (x > 5 && x < 90 && y > HEIGHT - 25)
		return (s->selected = T_CAM, ft_putstr_fd("Camera selected\n", 1));
	if (x > 5 && x < 70 && y > HEIGHT - 50)
		return (s->selected = T_LIGHT, ft_putstr_fd("Light selected\n", 1));
	hit = prim_intersect(ro, rd, s->elem->prim_list);
	if (hit.sd >= 1000)
		return ;
	if (hit.prim->type == PRIM_PLN)
		ft_putstr_fd("Plan selected\n", 1);
	if (hit.prim->type == PRIM_SPH)
		ft_putstr_fd("Sphere selected\n", 1);
	if (hit.prim->type == PRIM_CYL)
		ft_putstr_fd("Cylinder selected\n", 1);
	s->prim = hit.prim;
}

int	cam_dir(double cam_ori)
{
	if (cam_ori >= 0)
		return (1);
	return (-1);
}

int	valid_key(mlx_key_data_t key)
{
	if (key.key != MLX_KEY_Q && key.key != MLX_KEY_ESCAPE
		&& key.key != MLX_KEY_W && key.key != MLX_KEY_A && key.key != MLX_KEY_S
		&& key.key != MLX_KEY_D && key.key != MLX_KEY_SPACE
		&& key.key != MLX_KEY_LEFT_CONTROL && key.key != MLX_KEY_UP
		&& key.key != MLX_KEY_DOWN)
		return (0);
	return (1);
}

void	ft_hook(void *param)
{
	t_screen	*screen;

	screen = (t_screen *)param;
	if (screen->ismovepressed)
		render(screen->img, screen->elem);
}
