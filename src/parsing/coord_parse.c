/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:47:25 by arivera           #+#    #+#             */
/*   Updated: 2023/08/08 10:45:46 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	coord_parse(char **coord, t_coord *c)
{
	if (float_parse(coord[0], &c->x))
	{
		free_tab(coord);
		return (1);	
	}
	if (float_parse(coord[1], &c->y))
	{
		free_tab(coord);
		return (1);	
	}
	if (float_parse(coord[2], &c->z))
	{
		free_tab(coord);
		return (1);
	}
	free_tab(coord);
	return (0);
}
