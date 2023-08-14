/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:20:05 by arivera           #+#    #+#             */
/*   Updated: 2023/08/14 11:55:46 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minirt.h"
#include "rtparsing.h"

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	free_parsing(t_parsing *parse)
{
	if (parse->file_path)
		free(parse->file_path);
	if (parse->line)
		free_tab(parse->line);
	close(parse->fd);
	return (1);
}
