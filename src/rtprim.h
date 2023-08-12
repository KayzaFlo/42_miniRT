/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtprim.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:12:39 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/11 15:28:58 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTPRIM_H
# define RTPRIM_H

# include <stdlib.h>
# include <stdint.h>
# include "rtmath.h"
#include "../include/minirt.h"

// sd = signed distance
// n = normal
// col = color
typedef struct s_surface
{
	float	sd;
	t_vec3	n;
	t_vec3	col;

}				t_surface;

t_surface	plIntersect(t_vec3 ro, t_vec3 rd, t_pl *pl);
t_surface	elliIntersect( t_vec3 ro, t_vec3 rd, t_vec3 r );
t_surface	cylIntersect(t_vec3 ro, t_vec3 rd, t_cyl *cyl);
t_surface	sphIntersect(t_vec3 ro, t_vec3 rd, t_sph *sph);

uint32_t	hexcol(float r, float g, float b, float a);

#endif
