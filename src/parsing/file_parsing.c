/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:53:41 by arivera           #+#    #+#             */
/*   Updated: 2023/08/04 16:57:57 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static void	init_parsing(t_parsing *parsing)
{
	parsing->amb_count = 0;
	parsing->cam_count = 0;
	parsing->light_count = 0;
	parsing->line_index = 1;
}

static int	verify_split_line(char **line, t_parsing *parsing)
{
	int	i;
	int	j;

	if (ft_strncmp("A", line[0], 2) && ft_strncmp("C", line[0], 2)
		&& ft_strncmp("L", line[0], 2) && ft_strncmp("sp", line[0], 3)
		&& ft_strncmp("pl", line[0], 3) && ft_strncmp("cy", line[0], 3))
	{
		i = 0;
		while (line[0][i])
			i++;
		if (line[0][i - 1] == '\n')
			parsing_line_err("no value assigned to the identifier\n", parsing);
		else
			parsing_line_err("wrong identifier\n", parsing);
		return (1);
	}
	i = 1;
	while (line[i])
	{
		j = 0;
		while (line[i][j] && line[i][j] != '\n')
		{
			if (!ft_isdigit(line[i][j]))
			{
				parsing_line_err("non-numeric value was assigned\n", parsing);
				return (1);
			}
			j++;
		}
	}
	return (0);
}

static int	parsing_line(char *line, t_parsing *parsing)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split)
		parsing_error("malloc error\n");
	if (split[0][0] == '\n')
	{
		free_tab(split);
		return (0);
	}
	if (verify_split_line(split, parsing))
	{
		free_tab(split);
		return (1);
	}
	return (0);
}

void	file_parsing(int fd)
{
	t_parsing	parsing;
	char			*line;

	line = get_next_line(fd);
	if (!line)
		parsing_error("umm, file is empty\n");
	init_parsing(&parsing);
	while (line)
	{
		if (parsing_line(line, &parsing))
		{
			free(line);
			close(fd);
			exit(1);
		}
		free(line);
		line = get_next_line(fd);
		parsing.line_index++;
	}
}
