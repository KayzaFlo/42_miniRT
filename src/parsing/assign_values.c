/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_values.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 12:38:34 by arivera           #+#    #+#             */
/*   Updated: 2023/08/08 12:24:33 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	assign_values(t_parsing *parse, t_elem *elem)
{
	int	parse_err;

	parse_err = 0;
	if (!ft_strncmp(parse->line[0], "A", 2))
		parse_err = ambiance_parsing(parse, elem);
	else if (!ft_strncmp(parse->line[0], "C", 2))
		parse_err = camera_parsing(parse, elem);
	else if (!ft_strncmp(parse->line[0], "L", 2))
		parse_err = light_parsing(parse, elem);
	return (parse_err);
}
