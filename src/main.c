/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:53:46 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/16 16:18:03 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtrender.h"
#include "rtparsing.h"

static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	t_elem		*elem;
	mlx_t		*mlx;
	mlx_image_t	*img;

	// PARSING
	elem = (t_elem *)malloc(sizeof(t_elem));
	if (!elem)
		return (ft_putstr_fd("Error\nmalloc error\n", 2), 1);
	elem->prim_list = 0;
	elem->lit = 0;
	if (parsing(argc, argv, elem))
		return (free_elem(elem), 1);
	// MLX & IMG SETUP
	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!mlx)
		ft_error();
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();
	// RENDER LOOP
	t_screen	screen;
	screen.img = img;
	screen.elem = elem;
	screen.render = true;
	screen.mlx = mlx;
	screen.prim = 0;
	// renderthreaded(screen.img, screen.elem);
	mlx_loop_hook(mlx, ft_hook, &screen);
	handle_hooks(&screen);
	mlx_put_string(mlx, "CAMERA", 10, HEIGHT - 25);
	mlx_put_string(mlx, "LIGHT", 10, HEIGHT - 50);
	mlx_loop(mlx);
	// QUIT
	mlx_terminate(mlx);
	free_elem(elem);
	return (EXIT_SUCCESS);
}
