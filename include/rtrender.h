/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtrender.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:16:42 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/22 14:12:15 by arivera          ###   ########.fr       */
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

// # define MOD_SP "W, A, S, D, Space, Left Ctrl to move the selected sphere"
// # define MOD_CAM "W, A, S, D, Space, Left Ctrl to move the camera"

// values for s_screen->interaction

# define ROTATE 1
# define TRANSLATE 2
# define TRANSLATE_DIST 0.5

typedef struct	s_screen
{
	mlx_image_t	*img;
	t_elem		*elem;
	mlx_t		*mlx;
	t_prim		*prim;
	int			render;
	int			light;
	int			cam;
	int			interaction;
}				t_screen;

void		ft_hook(void* param);
void		ft_close(void* param);
void		ft_keyhook(mlx_key_data_t keydata, void* param);
void		handle_hooks(t_screen *screen);
void		free_elem(t_elem *e);

void		camera_interact(mlx_key_data_t keydata, t_screen *s);
void		light_interact(mlx_key_data_t keydata, t_screen *s);
void		ft_get_selection(t_screen *s, int32_t x, int32_t y);
void 		ft_hook(void* param);
void		prim_interact(mlx_key_data_t keydata, t_screen *s);

void		render(mlx_image_t *img, t_elem *elem);
void		renderthreaded(mlx_image_t *img, t_elem *elem);
t_vec3		pixelcompute(t_vec3 ro, t_vec3 rd, t_elem *elem);
t_surface	primIntersect(t_vec3 ro, t_vec3 rd, t_list *prim_list);

uint32_t	hexcol(float r, float g, float b, float a);

#endif
