/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct3_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:28:59 by arivera           #+#    #+#             */
/*   Updated: 2023/08/10 11:29:31 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	vec3_parse(char *vectors, t_vec3 *vec, t_parsing *p)
{
	char	**tab;

	tab = ft_split(vectors, ',');
	if (!tab)
		return (p->err.malloc_err = 1, 1);
	if (ft_tablen(tab) != 3)
		return (free_tab(tab), 1);
	if (float_parse(tab[0], &vec->x))
		return (free_tab(tab), 1);
	if (float_parse(tab[1], &vec->y))
		return (free_tab(tab), 1);
	if (float_parse(tab[2], &vec->z))
		return (free_tab(tab), 1);
	if (vec->x < -1 || vec->x > 1 || vec->y < -1 || vec->y > 1
		|| vec->z < -1 || vec->z > 1)
		return (free_tab(tab), 1);
	return (free_tab(tab), 0);
}

int	colors_parse(char *line, t_col *col, t_parsing *p)
{
	char	**rgb;

	rgb = ft_split(line, ',');
	if (!rgb)
		return (p->err.malloc_err = 1, 1);
	if (ft_tablen(rgb) != 3)
		return (free_tab(rgb), 1);
	if (int_parse(rgb[0], &col->r))
		return (free_tab(rgb), 1);
	if (int_parse(rgb[1], &col->g))
		return (free_tab(rgb), 1);
	if (int_parse(rgb[2], &col->b))
		return (free_tab(rgb), 1);
	if (col->r > 255 || col->r < 0 || col->g > 255 || col->g < 0
		|| col->b > 255 || col->b < 0)
		return (free_tab(rgb), 1);
	return (free_tab(rgb), 0);
}

int	coord_parse(char *str, t_coord *c, t_parsing *p)
{
	char	**coord;

	p->err.info = COORD;
	coord = ft_split(str, ',');
	if (!coord)
		return (p->err.malloc_err = 1, 1);
	if (ft_tablen(coord) != 3)
		return (free_tab(coord), 1);
	if (float_parse(coord[0], &c->x))
		return (free_tab(coord), 1);
	if (float_parse(coord[1], &c->y))
		return (free_tab(coord), 1);
	if (float_parse(coord[2], &c->z))
		return (free_tab(coord), 1);
	return (free_tab(coord), 0);
}
