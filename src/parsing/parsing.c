/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 13:58:02 by arivera           #+#    #+#             */
/*   Updated: 2023/08/15 12:01:43 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minirt.h"
#include "rtparsing.h"

static int	init_parsing(t_parsing *p, char *file_path, int fd)
{
	p->fd = fd;
	p->amb_count = 0;
	p->lit_count = 0;
	p->cam_count = 0;
	p->line_index = 0;
	p->line = 0;
	p->file_path = ft_strdup(file_path);
	p->err.malloc_err = 0;
	p->err.info = NULL;
	if (!file_path)
	{
		p->err.malloc_err = 1;
		return (1);
	}
	return (0);
}

int	parsing(int argc, char **argv, t_elem *e)
{
	t_parsing	p;
	int			fd;

	fd = input_parsing(argc, argv);
	if (fd == -1)
		return (1);
	if (init_parsing(&p, argv[1], fd))
		return (print_err_msg(&p, 0), free_parsing(&p));
	if (file_parsing(&p, e))
		return (print_err_msg(&p, 0), free_parsing(&p));
	free_parsing(&p);
	return (0);
}
