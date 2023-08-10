/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:37:57 by arivera           #+#    #+#             */
/*   Updated: 2023/08/08 12:30:03 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../lib/libft/inc/libft.h"
# include "../lib/libft/inc/ft_printf.h"
# include "elements.h"

# define AMB "Ambiance: "
# define CAM "Camera: "
# define LIT "Light: "
# define SPH 4
# define CYL 5
# define PLN 6
# define INVALID_ID "Invalid identifier. Valid identifiers: 'A', 'C', 'L'\n"

# define NB_ID "declaration\n"
# define COORD "coordinates\n"
# define COL "colors\n"
# define ORI "orientation\n"
# define RATIO "luminosity ratio\n"
# define FOV "field of view (FOV)\n"
# define NB_INFO "information types\n"
# define NB_COL "number of colors\n"
# define NB_COORD "number of coordinates\n"
# define NB_ORI "number of orientation vectors\n"

# define VACANT "missing identifier "
# define TOO_MANY "too many "
# define INV_NB "incorrect number of "
# define OUT_OF_RANGE "out of range "
# define INV_VAL "invalid value for "

typedef struct  s_parsing
{
	char	*file_path;
	char	**line;
	int		fd;
    int 	amb_count;
    int 	lit_count;
    int 	cam_count;
    int 	line_index;
}               t_parsing;

int 	ft_tablen(char **tab);
int	    parsing(int	argc, char **argv, t_elem *e);
int	    input_error(char *s);
int		print_err_msg(t_parsing *p, char *elem, char *info, char *type);
int		malloc_error(void);
int		input_parsing(int argc, char **argv);
int		file_parsing(t_parsing *parse, t_elem *elem);
int		line_parsing(t_parsing *parse, t_elem *elem, char *line);
int		assign_values(t_parsing *parse, t_elem *elem);
void	free_tab(char **tab);
void	free_parsing(t_parsing *parsing, int exit_rt);
int		ambiance_parsing(t_parsing *p, t_elem *e);
int		float_parse(char *str, float *var);
int		coord_parse(char **coord, t_coord *c);
int		orientation_parse(char **tab, t_vec3 *ori);
int		colors_parse(char **rgb, t_col *col);
int	    camera_parsing(t_parsing *p, t_elem *e);
int	    light_parsing(t_parsing *p, t_elem *e);
long	ft_atol(char *str);

#endif