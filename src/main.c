/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:53:46 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/10 14:03:55 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Written by Bruh

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../include/minirt.h"
#define WIDTH 256
#define HEIGHT 256

void	del_prim(void *content)
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

void	del_lit(void *content)
{
	t_lit	*lit;
	
	lit = (t_lit *)content;
	free(content);
}

void	free_elem(t_elem *e)
{
	ft_lstclear(&e->prim_list, del_prim);
	ft_lstclear(&e->lit, del_lit);
	free(e);
}

int main(int argc, char *argv[])
{
	t_elem	*elem;
	
	elem = (t_elem *)malloc(sizeof(t_elem));
	if (!elem)
		return (ft_putstr_fd("Error\nmalloc error\n", 2), 1);
	elem->prim_list = 0;
	elem->lit = 0;
	if (parsing(argc, argv, elem))
		return (free_elem(elem), 1);
	free_elem(elem);
	return (EXIT_SUCCESS);
}
