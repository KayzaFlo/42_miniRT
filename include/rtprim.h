/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtprim.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:12:39 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/16 14:14:13 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTPRIM_H
# define RTPRIM_H

# include <stdlib.h>
# include <stdint.h>
# include "rtmath.h"
// # include "minirt.h"

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

// sd = signed distance
// n = normal
// col = color
typedef struct s_surface
{
	float	sd;
	t_vec3	n;
	t_vec3	col;
	t_prim	*prim;
}				t_surface;

t_surface	plIntersect(t_vec3 ro, t_vec3 rd, t_pl *pl);
t_surface	elliIntersect( t_vec3 ro, t_vec3 rd, t_vec3 r );
t_surface	cylIntersect(t_vec3 ro, t_vec3 rd, t_cyl *cyl);
t_surface	sphIntersect(t_vec3 ro, t_vec3 rd, t_sph *sph);

#endif
