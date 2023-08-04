/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:14:44 by arivera           #+#    #+#             */
/*   Updated: 2023/08/04 16:39:09 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	parsing_line_err(char *error_msg, t_parsing *parsing)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("(line:  ", 2);
	ft_putnbr_fd(parsing->line_index, 2);
	ft_putstr_fd("):   ", 2);
	ft_putstr_fd(error_msg, 2);
}

void	parsing_error(char *error_msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error_msg, 2);
	exit (1);
}
