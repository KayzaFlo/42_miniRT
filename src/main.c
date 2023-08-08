/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:53:46 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/08 12:36:26 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Written by Bruh

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../include/minirt.h"
#define WIDTH 256
#define HEIGHT 256

static void	check_values_xd(t_elem e)
{
	printf("amb ratio: %f\n", e.amb.ratio);
	printf("amb col r: %d\n", e.amb.col.r);
	printf("amb col g: %d\n", e.amb.col.g);
	printf("amb col b: %d\n", e.amb.col.b);
	
	printf("lit coord x: %f\n", e.lit.coord.x);
	printf("lit coord y: %f\n", e.lit.coord.y);
	printf("lit coord z: %f\n", e.lit.coord.z);
	printf("lit ratio: %f\n", e.lit.ratio);
	printf("lit col r: %d\n", e.lit.col.r);
	printf("lit col g: %d\n", e.lit.col.g);
	printf("lit col b: %d\n", e.lit.col.b);
	
	printf("cam coord x: %f\n", e.cam.coord.x);
	printf("cam coord y: %f\n", e.cam.coord.y);
	printf("cam coord z: %f\n", e.cam.coord.z);
	printf("cam ori x: %f\n", e.cam.ori.x);
	printf("cam ori y: %f\n", e.cam.ori.y);
	printf("cam ori z: %f\n", e.cam.ori.z);
	printf("cam FOV: %d\n", e.cam.fov);
}

int main(int argc, char *argv[])
{
	t_elem		elem;

	if (parsing(argc, argv, &elem))
		return(1);
	else
		printf("succesful parsing!\n");
	check_values_xd(elem);
	return (EXIT_SUCCESS);
}
