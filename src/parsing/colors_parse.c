/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:07:47 by arivera           #+#    #+#             */
/*   Updated: 2023/08/07 16:40:37 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static int	rgb_pos_int(char **rgb)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (rgb[i])
	{
		j = 0;
		while (rgb[i][j])
		{
			if (!ft_isdigit(rgb[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	rgb_valid_len(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		if (ft_strlen(rgb[i]) > 3)
			return (0);
		i++;
	}
	return (1);
}	

int	colors_parse(char **rgb, t_col *col)
{
	if (!rgb_valid_len(rgb))
	{
		free_tab(rgb);
		return (1);
	}
	if (!rgb_pos_int(rgb))
	{
		free_tab(rgb);
		return (1);
	}
	col->r = ft_atoi(rgb[0]);
	col->g = ft_atoi(rgb[1]);
	col->b = ft_atoi(rgb[2]);
	if (col->r > 255 || col->r < 0 || col->g > 255 || col->g < 0
		|| col->b > 255 || col->b < 0)
	{
		free_tab(rgb);
		return (1);
	}
	free_tab(rgb);
	return (0);
}
