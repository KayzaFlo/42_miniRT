/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtelem.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 08:26:39 by arivera           #+#    #+#             */
/*   Updated: 2023/08/24 16:49:54 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTELEM_H
# define RTELEM_H

# include "rtmath.h"
# include "rtprim.h"
# include "libft.h"

typedef struct s_amb
{
	double	ratio;
	t_vec3	col;
}				t_amb;

typedef struct s_cam
{
	t_vec3	coord;
	t_vec3	ori;
	int		fov;
}				t_cam;

typedef struct s_lit
{
	t_vec3	coord;
	double	ratio;
	t_vec3	col;
}				t_lit;

typedef struct s_elem
{
	t_amb	amb;
	t_cam	cam;
	t_list	*lit;
	t_list	*prim_list;
	int		render;
}				t_elem;

#endif