/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_elem_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:14:54 by arivera           #+#    #+#             */
/*   Updated: 2023/08/14 11:56:03 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minirt.h"
#include "rtparsing.h"

int	light_parsing(t_parsing *p, t_elem *e)
{
	t_lit	*light;
	t_list	*new_elem;

	light = (t_lit *)malloc(sizeof(t_lit));
	if (!light)
		return (p->err.malloc_err = 1, 1);
	p->err.elem = LIT;
	if (p->lit_count++)
		return (free(light), p->err.info = TOO_MANY, 1);
	if (ft_tablen(p->line) != 4)
		return (free(light), p->err.info = WRONG_NB_INFO, 1);
	if (coord_parse(p->line[1], &light->coord, p))
		return (free(light), p->err.info = COORD, 1);
	if (float_parse(p->line[2], &light->ratio))
		return (free(light), p->err.info = RATIO, 1);
	if (light->ratio > 1 || light->ratio < 0)
		return (free(light), p->err.info = RATIO, 1);
	if (colors_parse(p->line[3], &light->col, p))
		return (p->err.info = COL, 1);
	new_elem = ft_lstnew((void *)light);
	if (!new_elem)
		return (free(light), p->err.malloc_err = 1, 1);
	ft_lstadd_back(&e->lit, new_elem);
	return (0);
}

int	camera_parsing(t_parsing *p, t_elem *e)
{
	p->err.elem = CAM;
	if (p->cam_count++)
		return (p->err.info = TOO_MANY, 1);
	if (ft_tablen(p->line) != 4)
		return ((p->err.info = WRONG_NB_INFO), 1);
	if (coord_parse(p->line[1], &e->cam.coord, p))
		return ((p->err.info = COORD), 1);
	if (vec3_parse(p->line[2], &e->cam.ori, p))
		return (1);
	if (int_parse(p->line[3], &e->cam.fov))
		return (p->err.info = FOV, 1);
	if (e->cam.fov > 180 || e->cam.fov < 0)
		return (p->err.info = FOV, 1);
	return (0);
}

int	ambiance_parsing(t_parsing *p, t_elem *e)
{
	p->err.elem = AMB;
	if (p->amb_count++)
		return (p->err.info = TOO_MANY, 1);
	if (ft_tablen(p->line) != 3)
		return ((p->err.info = WRONG_NB_INFO), 1);
	if (float_parse(p->line[1], &e->amb.ratio))
		return (p->err.info = RATIO, 1);
	if (e->amb.ratio > 1.0 || e->amb.ratio < 0.0)
		return (p->err.info = RATIO, 1);
	if (colors_parse(p->line[2], &e->amb.col, p))
		return (p->err.info = COL, 1);
	return (0);
}
