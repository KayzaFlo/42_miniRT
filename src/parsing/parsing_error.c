/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:14:44 by arivera           #+#    #+#             */
/*   Updated: 2023/08/14 11:56:08 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minirt.h"
#include "rtparsing.h"

int	input_error(char *s)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(s, 2);
	return (1);
}

void	print_err_msg(t_parsing *p, int vacant)
{
	if (p->err.info)
	{
		if (ft_strncmp(p->err.info, VACANT, ft_strlen(VACANT) + 1))
			ft_putstr_fd("Error\n", 2);
	}
	if (p->err.malloc_err)
	{
		ft_putstr_fd("malloc error\n", 2);
		return ;
	}
	if (p->err.info == NULL)
		return ;
	ft_putstr_fd(p->file_path, 2);
	if (!vacant)
	{
		ft_putstr_fd(": (line ", 2);
		ft_putnbr_fd(p->line_index, 2);
		ft_putstr_fd("): ", 2);
	}
	else
		ft_putstr_fd(": ", 2);
	ft_putstr_fd(p->err.elem, 2);
	ft_putstr_fd(p->err.info, 2);
}
