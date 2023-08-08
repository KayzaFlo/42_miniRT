/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 13:58:02 by arivera           #+#    #+#             */
/*   Updated: 2023/08/08 12:29:51 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static void	init_elem(t_elem *e)
{
	e->sph = 0;
	e->cyl = 0;
	e->pl = 0;
}

static int	init_parsing(t_parsing *p, char *file_path, int fd)
{
	p->fd = fd;
	p->amb_count = 0;
	p->lit_count = 0;
	p->cam_count = 0;
	p->line_index = 0;
	p->line = 0;
	p->file_path = ft_strdup(file_path);
	if (!file_path)
		return (malloc_error());
	return (0);
}

int	parsing(int	argc, char **argv, t_elem *e)
{
	t_parsing	p;
	int			fd;
	
	fd = input_parsing(argc, argv);
	if (init_parsing(&p, argv[1], fd))
		free_parsing(&p, true);
	init_elem(e);
	if (file_parsing(&p, e))
		free_parsing(&p, true);
	free_parsing(&p, false);
	return (0);
}
