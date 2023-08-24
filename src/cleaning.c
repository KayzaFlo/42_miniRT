/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:25:54 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/24 12:40:40 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtrender.h"

static void	del_prim(void *content)
{
	t_prim	*prim;
	
	prim = (t_prim *)content;
	if (prim->type == PRIM_SPH)
		free((t_sph *)prim->content);
	else if (prim->type == PRIM_CYL)
		free((t_cyl *)prim->content);
	else if (prim->type == PRIM_PLN)
		free((t_pl *)prim->content);
	free(prim);
}

static void	del_lit(void *content)
{
	t_lit	*lit;
	
	lit = (t_lit *)content;
	free(lit);
}

void	free_elem(t_elem *e)
{
	ft_lstclear(&e->prim_list, del_prim);
	ft_lstclear(&e->lit, del_lit);
	free(e);
}
