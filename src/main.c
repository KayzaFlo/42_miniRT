/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:53:46 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/10 13:34:40 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Written by Bruh

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../lib/MLX42/include/MLX42/MLX42.h"
#define WIDTH 700
#define HEIGHT 700

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

static void ft_close(void* param)
{
	mlx_t* mlx = param;

	mlx_close_window(mlx);
	mlx_terminate(mlx);
	exit(EXIT_SUCCESS);
}

void ft_keyhook(mlx_key_data_t keydata, void* param)
{
	// If we PRESS the 'ESC' key, ft_close is called.
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		ft_close(param);
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
		ft_close(param);
}

int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;

    // MLX allows you to define its core behaviour before startup.
	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", false);
	if (!mlx)
		ft_error();

	/* Do stuff */

	// Create and display the image.
	mlx_image_t* img = mlx_new_image(mlx, 256, 256);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

	// Even after the image is being displayed, we can still modify the buffer.
	mlx_put_pixel(img, 0, 0, 0xFF0000FF);

	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_close_hook(mlx, ft_close, mlx);
	mlx_key_hook(mlx, ft_keyhook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
