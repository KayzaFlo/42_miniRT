/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiance_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:17:52 by arivera           #+#    #+#             */
/*   Updated: 2023/08/07 16:40:15 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	ambiance_parsing(t_parsing *p, t_elem *e)
{
	char	**rgb;
	
	if (p->amb_count++)
		return (print_err_msg(p, AMB, NB_ID, TOO_MANY));
	if (ft_tablen(p->line) != 3)
		return (print_err_msg(p, AMB, NB_INFO, INV_NB));
	if (float_parse(p->line[1], &e->amb.ratio))
		return (print_err_msg(p, AMB, RATIO, INV_VAL));
	if (e->amb.ratio > 1.0 || e->amb.ratio < 0.0)
		return (print_err_msg(p, AMB, RATIO, OUT_OF_RANGE));
	rgb = ft_split(p->line[2],',');
	if (!rgb)
		return (malloc_error());
	if (ft_tablen(rgb) != 3)
	{
		free(rgb);
		return (print_err_msg(p, AMB, NB_COL, INV_NB));
	}
	if (colors_parse(rgb, &e->amb.col))
		return (print_err_msg(p, AMB, COL, INV_VAL));
	return (0);
}