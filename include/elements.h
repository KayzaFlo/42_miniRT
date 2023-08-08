/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 08:26:39 by arivera           #+#    #+#             */
/*   Updated: 2023/08/07 15:54:02 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENTS_H
# define ELEMENTS_H

typedef struct	s_vec3
{
	float	x;
	float	y;
	float	z;
}				t_vec3;

typedef struct	s_col
{
	int	r;
	int	g;
	int	b;
}				t_col;

typedef struct	s_coord
{
	float	x;
	float	y;
	float	z;
}				t_coord;

typedef struct	s_amb
{
	float	ratio;
	t_col	col;
}				t_amb;

typedef struct	s_cam
{
	t_coord	coord;
	t_vec3	ori;
	int		fov;
}				t_cam;

typedef struct	s_lit
{
	t_coord	coord;
	float	ratio;
	t_col	col;
}				t_lit;



typedef enum	e_prim
{
	PRIM_SPH = 0,
	PRIM_CYL,
	PRIM_PLN,
	PRIM_ERR
}				t_prim;

typedef struct	s_prim_list
{
	void			*content;
	t_prim			type;
	struct s_list	*next;
}				t_prim_list;


typedef struct	s_sph
{
	t_coord			coord;
	float			dia;
	t_col			col;
}				t_sph;

typedef struct	s_cyl
{
	t_coord			coord;
	t_vec3			norm;
	int				dia;
	int				hgt;
	t_col			col;
}				t_cyl;

typedef struct	s_pl
{
	t_coord			coord;
	t_vec3			ori;
	t_col			col;
}				t_pl;

typedef struct	s_elem
{
	t_amb	amb;
	t_lit	lit;
	t_cam	cam;
	t_sph	*sph;
	int		nb_sph;
	t_cyl	*cyl;
	int		nb_cyl;
	t_pl	*pl;
	int		nb_pln;
}				t_elem;

#endif