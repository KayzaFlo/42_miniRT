/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_basics.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:48:50 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/23 16:52:51 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtmath.h"

t_vec3	v3_new(double x, double y, double z)
{
	t_vec3	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_vec3	v3_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3	add;

	add.x = v1.x + v2.x;
	add.y = v1.y + v2.y;
	add.z = v1.z + v2.z;
	return (add);
}

t_vec3	v3_sub(t_vec3 v1, t_vec3 v2)
{
	t_vec3	sub;

	sub.x = v1.x - v2.x;
	sub.y = v1.y - v2.y;
	sub.z = v1.z - v2.z;
	return (sub);
}

t_vec3	v3_mult(t_vec3 v1, t_vec3 v2)
{
	t_vec3	mult;

	mult.x = v1.x * v2.x;
	mult.y = v1.y * v2.y;
	mult.z = v1.z * v2.z;
	return (mult);
}

t_vec3	v3_multf(t_vec3 v, double f)
{
	t_vec3	mult;

	mult.x = v.x * f;
	mult.y = v.y * f;
	mult.z = v.z * f;
	return (mult);
}
