/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:59:20 by arivera           #+#    #+#             */
/*   Updated: 2023/08/08 10:45:09 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	light_parsing(t_parsing *p, t_elem *e)
{
    char    **tab;

    if (p->lit_count++)
        return (print_err_msg(p, LIT, NB_ID, TOO_MANY));
    if (ft_tablen(p->line) != 4)
        return (print_err_msg(p, LIT, NB_INFO, TOO_MANY));
    tab = ft_split(p->line[1], ',');
    if (!tab)
        return (malloc_error());
    if (ft_tablen(tab) != 3)
    {
        free_tab(tab);
		return (print_err_msg(p, LIT, COORD, INV_NB));
    }
    if (coord_parse(tab, &e->lit.coord))
		return (print_err_msg(p, LIT, COORD, INV_VAL));
    if (float_parse(p->line[2], &e->lit.ratio))
		return (print_err_msg(p, AMB, RATIO, INV_VAL));
    if (e->lit.ratio > 1 || e->lit.ratio < 0)
        return (print_err_msg(p, LIT, RATIO, OUT_OF_RANGE));
    tab = ft_split(p->line[3], ',');
    if (!tab)
        return (malloc_error());
    if (ft_tablen(tab) != 3)
    {
        free(tab);
		return (print_err_msg(p, LIT, NB_COL, INV_NB));
    }
    if (colors_parse(tab, &e->lit.col))
        return (print_err_msg(p, LIT, COL, INV_VAL));
    return (0);
}
