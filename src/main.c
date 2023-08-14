/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:53:46 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/14 14:07:39 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtrender.h"
#include "rtparsing.h"

typedef struct	s_screen
{
	mlx_image_t	*img;
	t_elem		*elem;
}				t_screen;


static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	del_prim(void *content)
{
	t_prim	*prim;
	
	prim = (t_prim *)content;
	if (prim->type == PRIM_SPH)
		free((t_sph *)prim->content);
	else if (prim->type == PRIM_CYL)
		free((t_cyl *)prim->content);
	else if (prim->type == PRIM_PLN)
		free((t_pl *)prim->content);
	free(prim);
}

static void ft_hook(void* param)
{
	static int	i = 0;
	t_screen	*screen;

	if (i > 0)
		return ;
	screen = (t_screen *)param;
	screen->elem->cam.coord.z -= 0.1f;
	// render(screen->img, screen->elem);
	renderthreaded(screen->img, screen->elem);
	// i++;
}

void	del_lit(void *content)
{
	t_lit	*lit;
	
	lit = (t_lit *)content;
	free(lit);
}

void	free_elem(t_elem *e)
{
	ft_lstclear(&e->prim_list, del_prim);
	ft_lstclear(&e->lit, del_lit);
	free(e);
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
	mlx_loop(mlx);
	// QUIT
	mlx_terminate(mlx);
	free_elem(elem);
	return (EXIT_SUCCESS);
}
