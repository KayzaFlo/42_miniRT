/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:48:26 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/07 11:07:22 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;


t_vec3	v3_new(float x, float y, float z);
float	v3_dot(t_vec3 v1, t_vec3 v2);
float	v3_length(t_vec3 v);
t_vec3	v3_normalize(t_vec3 v);
t_vec3	v3_add(t_vec3 v1, t_vec3 v2);
t_vec3	v3_sub(t_vec3 v1, t_vec3 v2);
t_vec3	v3_mult(t_vec3 v1, t_vec3 v2);
