/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 08:26:39 by arivera           #+#    #+#             */
/*   Updated: 2023/08/10 13:56:02 by arivera          ###   ########.fr       */
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

typedef struct	s_amb
{
	float	ratio;
	t_vec3	col;
}				t_amb;

typedef struct	s_cam
{
	t_vec3	coord;
	t_vec3	ori;
	int		fov;
}				t_cam;

typedef struct	s_lit
{
	t_vec3	coord;
	float	ratio;
	t_vec3	col;
}				t_lit;



enum	e_prim
{
	PRIM_SPH = 0,
	PRIM_CYL,
	PRIM_PLN,
	PRIM_ERR
};

typedef struct	s_prim
{
	void			*content;
	enum e_prim			type;
}				t_prim;


typedef struct	s_sph
{
	t_vec3	coord;
	float	dia;
	t_vec3	col;
}				t_sph;

typedef struct	s_cyl
{
	t_vec3	coord;
	t_vec3	norm;
	float	dia;
	float	hgt;
	t_vec3	col;
}				t_cyl;

typedef struct	s_pl
{
	t_vec3	coord;
	t_vec3	ori;
	t_vec3	col;
}				t_pl;

typedef struct	s_elem
{
	t_amb	amb;
	t_cam	cam;
	t_list	*lit;
	t_list	*prim_list;
}				t_elem;

#endif