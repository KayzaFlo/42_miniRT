/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:14:44 by arivera           #+#    #+#             */
/*   Updated: 2023/08/08 12:01:18 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	input_error(char *s)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(s, 2);
	exit (1);
}

int	print_err_msg(t_parsing *p, char *elem, char *info, char *type)
{
	if (ft_strncmp(type, VACANT, ft_strlen(VACANT)))
		ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(p->file_path, 2);
	if (ft_strncmp(type, VACANT, ft_strlen(VACANT)))
	{
		ft_putstr_fd(": (line: ", 2);
		ft_putnbr_fd(p->line_index, 2);
		ft_putstr_fd(") ", 2);
	}
	else
		ft_putstr_fd(": ", 2);
	ft_putstr_fd(elem, 2);
	ft_putstr_fd(type, 2);
	ft_putstr_fd(info, 2);
	return (1);
}

int		malloc_error(void)
{
	ft_putstr_fd("Error\nmalloc error\n", 2);
	return(1);
}
