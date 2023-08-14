/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtrender.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:16:42 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/14 14:27:31 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTRENDER_H
# define RTRENDER_H

# include <stdio.h>
# include "MLX42.h"
# include "rtprim.h"
# include "rtelem.h"

# define WIDTH 1280
# define HEIGHT 720

typedef struct	s_screen
{
	mlx_image_t	*img;
	t_elem		*elem;
}				t_screen;

void		ft_hook(void* param);
void		ft_close(void* param);
void		ft_keyhook(mlx_key_data_t keydata, void* param);
void		free_elem(t_elem *e);

void		render(mlx_image_t *img, t_elem *elem);
void		renderthreaded(mlx_image_t *img, t_elem *elem);
t_vec3		pixelcompute(float x, float y, t_elem *elem);

uint32_t	hexcol(float r, float g, float b, float a);

#endif
