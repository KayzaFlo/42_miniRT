/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mand_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:19:10 by arivera           #+#    #+#             */
/*   Updated: 2023/08/14 11:56:05 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minirt.h"
#include "rtparsing.h"

void	*cylinder_parsing(t_parsing *p)
{
	t_cyl	*cyl;

	p->err.elem = CYL;
	cyl = (t_cyl *)malloc(sizeof(t_cyl));
	if (!cyl)
		return (p->err.malloc_err = 1, NULL);
	if (ft_tablen(p->line) != 6)
		return (free(cyl), p->err.info = WRONG_NB_INFO, NULL);
	if (coord_parse(p->line[1], &cyl->coord, p))
		return (free(cyl), NULL);
	if (vec3_parse(p->line[2], &cyl->norm, p))
		return (free(cyl), p->err.info = NORM, NULL);
	if (float_parse(p->line[3], &cyl->dia))
		return (free(cyl), p->err.info = DIA, NULL);
	if (cyl->dia < 0)
		return (free(cyl), p->err.info = DIA, NULL);
	if (float_parse(p->line[4], &cyl->hgt))
		return (free(cyl), p->err.info = HGT, NULL);
	if (cyl->hgt < 0)
		return (free(cyl), p->err.info = HGT, NULL);
	if (colors_parse(p->line[5], &cyl->col, p))
		return (free(cyl), p->err.info = COL, NULL);
	return ((void *)cyl);
}

void	*sphere_parsing(t_parsing *p)
{
	t_sph	*sph;

	p->err.elem = SPH;
	sph = (t_sph *)malloc(sizeof(t_sph));
	if (!sph)
		return (p->err.malloc_err = 1, NULL);
	if (ft_tablen(p->line) != 4)
		return (free(sph), p->err.info = WRONG_NB_INFO, NULL);
	if (coord_parse(p->line[1], &sph->coord, p))
		return (free(sph), p->err.info = COORD, NULL);
	if (float_parse(p->line[2], &sph->dia))
		return (free(sph), p->err.info = DIA, NULL);
	if (sph->dia < 0)
		return (free(sph), p->err.info = DIA, NULL);
	if (colors_parse(p->line[3], &sph->col, p))
		return (free(sph), p->err.info = COL, NULL);
	return ((void *)sph);
}

void	*plan_parsing(t_parsing *p)
{
	t_pl	*pl;

	p->err.elem = PLN;
	pl = (t_pl *)malloc(sizeof(t_pl));
	if (!pl)
		return (p->err.malloc_err = 1, NULL);
	if (ft_tablen(p->line) != 4)
		return (free(pl), p->err.info = WRONG_NB_INFO, NULL);
	if (coord_parse(p->line[1], &pl->coord, p))
		return (free(pl), p->err.info = COORD, NULL);
	if (vec3_parse(p->line[2], &pl->ori, p))
		return (free(pl), p->err.info = ORI, NULL);
	if (colors_parse(p->line[3], &pl->col, p))
		return (free(pl), p->err.info = COL, NULL);
	return ((void *)pl);
}
