/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:20:05 by arivera           #+#    #+#             */
/*   Updated: 2023/08/06 14:05:01 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include <stdbool.h>

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

void	free_parsing(t_parsing *parse, int exit_rt)
{
	if (parse->file_path)
		free(parse->file_path);
	if (parse->line)
		free_tab(parse->line);
	close(parse->fd);
	if (exit_rt)
		exit (1);
}
