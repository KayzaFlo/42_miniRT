/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientation_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:26:50 by arivera           #+#    #+#             */
/*   Updated: 2023/08/07 16:11:26 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	orientation_parse(char **tab, t_vec3 *ori)
{
	if (float_parse(tab[0], &ori->x))
	{
		free_tab(tab);
		return (1);
	}
	if (float_parse(tab[1], &ori->y))
	{
		free_tab(tab);
		return (1);
	}
	if (float_parse(tab[2], &ori->z))
	{
		free_tab(tab);
		return (1);
	}
	if (ori->x < -1 || ori->x > 1 || ori->y < -1 || ori->y > 1
		|| ori->z < -1 || ori->z > 1)
	{
		free_tab(tab);
		return (1);
	}
	free_tab(tab);
	return (0);
}
