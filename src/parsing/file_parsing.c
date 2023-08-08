/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 10:48:09 by arivera           #+#    #+#             */
/*   Updated: 2023/08/08 12:27:10 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minirt.h"

static int	file_is_empty(char *file_path)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(file_path, 2);
	ft_putstr_fd(": File is empty\n", 2);
	return (1);
}

static int	vacant_elements(t_parsing *p)
{
	int	err;

	err = 0;
	if (!p->amb_count || !p->cam_count || !p->lit_count)
		ft_putstr_fd("Error\n", 2);
	if (!p->amb_count)
		err = print_err_msg(p, AMB, NB_ID, VACANT);
	if (!p->cam_count)
		err = print_err_msg(p, CAM, NB_ID, VACANT);
	if (!p->lit_count)
		err = (print_err_msg(p, LIT, NB_ID, VACANT));
	return (err);
}

int	file_parsing(t_parsing *parse, t_elem *elem)
{
	char	*line;
	
	line = get_next_line(parse->fd);
	if (!line)
		return(file_is_empty(parse->file_path));
	parse->line_index = 1;
	while (line)
	{
		if (line_parsing(parse, elem, line))
		{
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(parse->fd);
		parse->line_index++;
	}
	if (vacant_elements(parse))
		return (1);
	return (0);
}
