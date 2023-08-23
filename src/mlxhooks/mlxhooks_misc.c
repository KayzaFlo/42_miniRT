/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxhooks_misc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:16:47 by arivera           #+#    #+#             */
/*   Updated: 2023/08/22 14:29:27 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtrender.h"
#include "rtparsing.h"

void	ft_get_selection(t_screen *s, int32_t x, int32_t y)
{
	t_vec3		ro = s->elem->cam.coord;
	t_vec3		rd;
	t_surface	hit;
	const float	rfov = s->elem->cam.fov * M_PI / 180.0f;

	rd.x = tan(((x - WIDTH / 2) / (float)WIDTH) * rfov);
	rd.y = tan(((y - HEIGHT / 2) * -1 / (float)WIDTH) * rfov);
	rd.z = 1;
	rd = v3_normalize(rd);
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

void	ft_hook(void* param)
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