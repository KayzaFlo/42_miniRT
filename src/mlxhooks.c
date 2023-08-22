/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:53:46 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/22 14:03:07 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtrender.h"
#include "rtparsing.h"

void	v3_print(t_vec3 v);

void ft_hook(void* param)
{
	static int	i = 0;
	t_screen	*screen;

	if (i > 0)
		return ;
	screen = (t_screen *)param;
	((t_sph *)(((t_prim *)(screen->elem->prim_list->content))->content))->coord = v3_roty(
		v3_new(0, 0, 0),
		((t_sph *)(((t_prim *)(screen->elem->prim_list->content))->content))->coord, 
		1
	);
	screen->elem->cam.coord.z -= 0.1f;
	// screen->elem->cam.coord = v3_rotx(v3_new(0, 0, 0), screen->elem->cam.coord, 10);
	screen->elem->cam.coord = v3_roty(v3_new(0, 0, -5), screen->elem->cam.coord, 1);
	// screen->elem->cam.coord = v3_rotz(v3_new(0, 0, 0), screen->elem->cam.coord, 10);
	// v3_print(screen->elem->cam.coord);
	// render(screen->img, screen->elem);
	renderthreaded(screen->img, screen->elem);
	// i++;
}

void ft_close(void* param)
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
