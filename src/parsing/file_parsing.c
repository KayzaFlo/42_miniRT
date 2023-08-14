/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 10:48:09 by arivera           #+#    #+#             */
/*   Updated: 2023/08/14 11:55:42 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minirt.h"
#include "rtparsing.h"

static int	file_is_empty(char *file_path)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(file_path, 2);
	ft_putstr_fd(": File is empty\n", 2);
	return (1);
}

static int	check_id(char *id)
{
	const char		*ids[] = {
		"A",
		"L",
		"C",
		"sp",
		"cy",
		"pl"
	};
	unsigned long	i;

	i = 0;
	while (i < sizeof(ids) / sizeof(ids[0]))
	{
		if (!ft_strncmp(ids[i], id, ft_strlen(id) + 1))
			return (0);
		i++;
	}
	return (1);
}

static int	vacant_elements(t_parsing *p)
{
	int	err;

	err = 0;
	if (!p->amb_count || !p->cam_count || !p->lit_count)
	{
		err = 1;
		ft_putstr_fd("Error\n", 2);
		p->err.info = VACANT;
	}
	if (!p->amb_count)
	{
		p->err.elem = AMB;
		print_err_msg(p, 1);
	}
	if (!p->cam_count)
	{
		p->err.elem = CAM;
		print_err_msg(p, 1);
	}
	if (!p->lit_count)
	{
		p->err.elem = LIT;
		print_err_msg(p, 1);
	}
	return (p->err.info = NULL, err);
}

static int	line_parsing(t_parsing *parse, t_elem *elem, char *line)
{
	char	**nl_rm;
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\n' || line[i] == 0)
		return (0);
	nl_rm = ft_split(line, '\n');
	if (!nl_rm)
		return (parse->err.malloc_err = 1, 1);
	parse->line = ft_split_ultra(nl_rm[0], ISSPACE);
	free_tab(nl_rm);
	if (!parse->line)
		return (1);
	if (check_id(parse->line[0]))
		return (parse->err.elem = INV_ID, parse->err.info = VAL_ID, 1);
	if (assign_values(parse, elem))
		return (1);
	free_tab(parse->line);
	parse->line = 0;
	return (0);
}

int	file_parsing(t_parsing *parse, t_elem *elem)
{
	char	*line;

	line = get_next_line(parse->fd);
	if (!line)
		return (file_is_empty(parse->file_path));
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
