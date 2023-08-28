/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:53:46 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/28 12:12:28 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtrender.h"
#include "rtparsing.h"

t_elem	*elem_init(int argc, char *argv[])
{
	t_elem		*elem;

	elem = (t_elem *)malloc(sizeof(t_elem));
	if (!elem)
		return (ft_putstr_fd("Error\nmalloc error\n", 2), NULL);
	elem->prim_list = 0;
	elem->lit = 0;
	if (parsing(argc, argv, elem))
		return (free_elem(elem), NULL);
	return (elem);
}

void	ft_resize(int width, int height, void *param)
{
	t_screen	*screen;

	screen = (t_screen *)param;
	screen->img = mlx_new_image(screen->mlx, width, height);
	mlx_image_to_window(screen->mlx, screen->img, 0, 0);
	mlx_put_string(screen->mlx, "CAMERA", 10, height - 25);
	mlx_put_string(screen->mlx, "LIGHT", 10, height - 50);
	render(screen->img, screen->elem);
}

int	main(int argc, char *argv[])
{
	t_screen	screen;

	screen.prim = NULL;
	screen.ismovepressed = 0;
	screen.elem = elem_init(argc, argv);
	if (!screen.elem)
		exit(EXIT_FAILURE);
	screen.mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!screen.mlx)
		exit(EXIT_FAILURE);
	screen.img = mlx_new_image(screen.mlx, WIDTH, HEIGHT);
	if (!screen.img || (mlx_image_to_window(screen.mlx, screen.img, 0, 0) < 0))
		exit(EXIT_FAILURE);
	render(screen.img, screen.elem);
	mlx_loop_hook(screen.mlx, ft_hook, &screen);
	mlx_resize_hook(screen.mlx, ft_resize, &screen);
	handle_hooks(&screen);
	mlx_put_string(screen.mlx, "CAMERA", 10, HEIGHT - 25);
	mlx_put_string(screen.mlx, "LIGHT", 10, HEIGHT - 50);
	mlx_loop(screen.mlx);
	mlx_terminate(screen.mlx);
	free_elem(screen.elem);
	if (screen.uvw)
		free(screen.uvw);
	return (EXIT_SUCCESS);
}
