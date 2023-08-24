/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtparsing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:37:57 by arivera           #+#    #+#             */
/*   Updated: 2023/08/24 16:46:20 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTPARSING_H
# define RTPARSING_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "libft.h"
# include "ft_printf.h"
# include "rtelem.h"

# define ISSPACE " \t\n\v\f\r"
# define AMB "Ambiance: "
# define CAM "Camera: "
# define LIT "Light: "
# define SPH "Sphere: "
# define CYL "Cylinder: "
# define PLN "Plan: "
# define INV_ID "Invalid identifier. "

# define VAL_ID "Valid identifiers: A, C, L, sp, cy, pl.\n"
# define HGT "invalid value for height.\n"
# define DIA "invalid value for diameter.\n"
# define FOV "invalid value for FOV.\n"
# define ORI "invalid value(s) for orientation.\n"
# define NORM "invalid value(s) for normalized vectors.\n"
# define COORD "invalid value(s) for coordinates.\n"
# define COL "invalid value(s) for colors.\n"
# define TOO_MANY "declared too many times.\n"
# define RATIO "invalid value(s) for ratio.\n"
# define WRONG_NB_INFO "wrong number of info.\n"
# define VACANT "missing identifier.\n"

typedef struct s_err
{
	char	*elem;
	char	*info;
	int		malloc_err;
}				t_err;

typedef struct s_parsing
{
	char	*file_path;
	char	**line;
	int		fd;
	int		amb_count;
	int		lit_count;
	int		cam_count;
	int		line_index;
	t_err	err;
}				t_parsing;

int		ft_tablen(char **tab);
int		parsing(int argc, char **argv, t_elem *e);
int		input_error(char *s);
void	print_err_msg(t_parsing *p, int vacant);
int		input_parsing(int argc, char **argv);
void	free_elem(t_elem *e);
int		file_parsing(t_parsing *parse, t_elem *elem);
int		assign_values(t_parsing *parse, t_elem *elem);
void	free_tab(char **tab);
int		free_parsing(t_parsing *parsing);
int		ambiance_parsing(t_parsing *p, t_elem *e);
int		float_parse(char *str, double *var);
int		coord_parse(char *str, t_vec3 *c, t_parsing *p);
int		vec3_parse(char *vectors, t_vec3 *vec, t_parsing *p);
int		colors_parse(char *line, t_vec3 *col, t_parsing *p);
int		camera_parsing(t_parsing *p, t_elem *e);
int		light_parsing(t_parsing *p, t_elem *e);
long	ft_atol(char *str);
void	*sphere_parsing(t_parsing *p);
void	*cylinder_parsing(t_parsing *p);
void	*plan_parsing(t_parsing *p);
int		ft_isspace(char c);
int		int_parse(char *s, int	*value);
char	**ft_split_ultra(char *str, char *charset);

#endif