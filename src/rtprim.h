/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtprim.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:12:39 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/09 10:47:40 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTPRIM_H
# define RTPRIM_H

# include <stdlib.h>
# include "rtmath.h"

// sd = signed distance
// col = color
typedef struct s_surface
{
	float	sd;
	t_vec3	col;

}				t_surface;

t_surface	sd_sphere(t_vec3 p, float r, t_vec3 col);
t_surface	sd_box(t_vec3 p, t_vec3 b, t_vec3 col);
// t_surface	sd_cylinder(t_vec3 p, t_vec3 a, t_vec3 b, float r, t_vec3 col);
t_surface	sd_cylinder(t_vec3 p, t_vec3 r, float d, float h, t_vec3 col);
t_surface	sd_plane(t_vec3 p, t_vec3 col);

uint32_t	hexcol(float r, float g, float b, float a);

#endif
