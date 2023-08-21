/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:53:46 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/21 15:29:58 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtrender.h"
#include "rtparsing.h"

void ft_hook(void* param)
{
	static int	i = 0;
	t_screen	*screen;

	if (i > 0)
		return ;
	screen = (t_screen *)param;
	screen->elem->cam.coord.z -= 0.1f;
	render(screen->img, screen->elem);
	// renderthreaded(screen->img, screen->elem);
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
