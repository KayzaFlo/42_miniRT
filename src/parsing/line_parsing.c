/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 11:18:45 by arivera           #+#    #+#             */
/*   Updated: 2023/08/07 16:19:49 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static int	check_id(char *id)
{
	if (ft_strncmp("A", id, 2) && ft_strncmp("L", id, 2)
		&& ft_strncmp("C", id, 2))
		return (1);
	return (0);
}

int	line_parsing(t_parsing *parse, t_elem *elem, char *line)
{
	char	**nl_rm;
	int		i;

	i = 0;
	while(line[i] == ' ')
		i++;
	if (line[i] == '\n' || line[i] == 0)
		return (0);
	nl_rm = ft_split(line, '\n');
	if (!nl_rm)
		return (malloc_error());
	parse->line = ft_split(nl_rm[0], ' ');
	free_tab(nl_rm);
	if (!parse->line)
		return (malloc_error());
	if (check_id(parse->line[0]))
		return (print_err_msg(parse, INVALID_ID, 0, 0));
	if (assign_values(parse, elem))
		return (1);
	free_tab(parse->line);
	parse->line = 0;
	return (0);
}
