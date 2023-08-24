/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxhooks_misc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:16:47 by arivera           #+#    #+#             */
/*   Updated: 2023/08/24 11:15:28 by fgeslin          ###   ########.fr       */
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
	s->cam = 0;
	s->light = 0;
	s->prim = 0;
	if (x > 5 && x < 90 && y > HEIGHT - 25)
		return (s->cam = 1, ft_putstr_fd("Camera selected\n", 1));
	if (x > 5 && x < 70 && y > HEIGHT - 50)
		return (s->light = 1, ft_putstr_fd("Light selected\n", 1));
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
		return (-1);
	return (1);
}

void	ft_hook(void *param)
{
	t_screen	*screen;

	screen = (t_screen *)param;
	if(screen->ismovepressed)
		render(screen->img, screen->elem);
}
