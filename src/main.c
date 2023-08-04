/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:53:46 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/04 14:44:03 by arivera          ###   ########.fr       */
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

// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// Print the window width and height.
static void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    // MLX allows you to define its core behaviour before startup.
	if (parsing(argc, argv))
		exit (1);
	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!mlx)
		ft_error();

	/* Do stuff */
	
	// Create and display the image.
	mlx_image_t* img = mlx_new_image(mlx, 1000, 1000);
	memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();
	unsigned int	x = 0;
	unsigned int	y = 0;
	while (true)
	{
		if (y == img->height - 100)
			break ;
		mlx_put_pixel(img, x, y, 0x00FF00FF);
		if (x == img->width - 100)
		{
			x = 0;
			y++;
		}
		x++;
	}
	// Even after the image is being displayed, we can still modify the buffer.

	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
