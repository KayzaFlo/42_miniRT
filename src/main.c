/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:53:46 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/14 14:28:44 by fgeslin          ###   ########.fr       */
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
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
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
	mlx_loop_hook(mlx, ft_hook, &screen);
	mlx_close_hook(mlx, ft_close, mlx);
	mlx_key_hook(mlx, ft_keyhook, mlx);
	mlx_loop(mlx);
	// QUIT
	mlx_terminate(mlx);
	free_elem(elem);
	return (EXIT_SUCCESS);
}
