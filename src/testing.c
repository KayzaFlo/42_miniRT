/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:54:10 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/04 16:05:56 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "vector3.h"

void	v3_print(t_vec3 v)
{
	printf("[%.4f, %.4f, %.4f]\n", v.x, v.y, v.z);
}

int main()
{
	t_vec3 zero = {0, 0, 0};
	t_vec3 one = {1, 1, 1};
	t_vec3 cam = {0, 3, -5};
	t_vec3 light = {2, 2, 4};
	t_vec3 dir = {-2, -2, -4};

	printf("Adds:\n");
		v3_print(v3_add(zero, dir));
		v3_print(v3_add(light, cam));
		v3_print(v3_add(light, dir));
	printf("Subs:\n");
		v3_print(v3_sub(zero, dir));
		v3_print(v3_sub(light, cam));
		v3_print(v3_sub(light, dir));
	printf("Mults:\n");
		v3_print(v3_mult(zero, dir));
		v3_print(v3_mult(light, cam));
		v3_print(v3_mult(light, dir));
	printf("Dots:\n");
		printf("%f\n", v3_dot(zero, dir));
		printf("%f\n", v3_dot(one, cam));
		printf("%f\n", v3_dot(light, dir));
		printf("%f\n", v3_dot(dir, dir));
	printf("Length:\n");
		printf("%f\n", v3_length(zero));
		printf("%f\n", v3_length(one));
		printf("%f\n", v3_length(light));
		printf("%f\n", v3_length(dir));
	printf("Normalized:\n");
		v3_print(v3_normalize(zero));
		v3_print(v3_normalize(one));
		v3_print(v3_normalize(light));
		v3_print(v3_normalize(dir));
	return 0;
}
