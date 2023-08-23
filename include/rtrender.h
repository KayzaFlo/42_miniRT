/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtrender.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:16:42 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/23 16:28:55 by fgeslin          ###   ########.fr       */
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
t_vec3		pixelcompute(t_vec3 ro, t_vec3 rd, t_elem *elem);

uint32_t	hexcol(float r, float g, float b, float a);

//DEBUG
void	v3_print(t_vec3 v);

#endif
