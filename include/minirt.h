/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 13:58:47 by arivera           #+#    #+#             */
/*   Updated: 2023/08/04 16:39:18 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "../lib/libft/inc/libft.h"
# include "../lib/libft/inc/ft_printf.h"

// parsing

typedef struct  s_parsing
{
    int amb_count;
    int light_count;
    int cam_count;
    int line_index;
}               t_parsing;

int	    parsing(int	argc, char **argv);
void	parsing_error(char *error_msg);
void	parsing_line_err(char *error_msg, t_parsing *parsing);
void	file_parsing(int fd);
void	free_tab(char **tab);

#endif