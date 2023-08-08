/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:53:46 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/08 12:44:13 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "rtrender.h"
#include "../lib/libft/inc/libft.h"

static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

static void ft_hook(void* param)
{
	(void)param;
}

int	main(int argc, char const *argv[])
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	(void)argc;
	(void)argv;
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!mlx)
		ft_error();
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	ft_memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();
	render(img);
	mlx_loop_hook(mlx, ft_hook, img);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
