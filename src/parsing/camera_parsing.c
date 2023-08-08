/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:04:38 by arivera           #+#    #+#             */
/*   Updated: 2023/08/07 16:03:20 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

// check_tab_len(tab, req) vs ft_tablen(tab)

static int	fov_parse(char *s, int *fov)
{
	int	i;

	i  = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (1);
		i++;
	}
	if (ft_strlen(s) > 3)
		return (1);
	*fov = ft_atoi(s);
	if (*fov > 180 || *fov < 0)
		return (1);
	return (0);
}

int	camera_parsing(t_parsing *p, t_elem *e)
{
	char	**tab;
	
	if (p->cam_count++)
		return (print_err_msg(p, CAM, NB_ID, TOO_MANY));
	if (ft_tablen(p->line) != 4)
		return (print_err_msg(p, CAM, NB_INFO, INV_NB));
	tab = ft_split(p->line[1], ',');
	if (!tab)
		return (malloc_error());
	if (ft_tablen(tab) != 3)
	{
		free_tab(tab);
		return (print_err_msg(p, CAM, COORD, INV_NB));
	}
	if (coord_parse(tab, &e->cam.coord))
		return (print_err_msg(p, CAM, COORD, INV_VAL));
	tab = ft_split(p->line[2], ',');
	if (!tab)
		return (malloc_error());
	if (ft_tablen(tab) != 3)
	{
		free_tab(tab);
		return (print_err_msg(p, CAM, ORI, INV_NB));
	}
	if (orientation_parse(tab, &e->cam.ori))
		return (print_err_msg(p, CAM, ORI, INV_VAL));
	if (fov_parse(p->line[3], &e->cam.fov))
		return (print_err_msg(p, CAM, FOV, INV_VAL));
	return (0);
}
