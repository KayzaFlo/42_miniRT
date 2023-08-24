/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtrender.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:16:42 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/24 10:59:45 by fgeslin          ###   ########.fr       */
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

# define ROTATE 1
# define TRANSLATE 2
# define TL_DST 0.5

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
	int			ismovepressed;
}				t_screen;

int			cam_dir(double cam_ori);
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
t_surface	prim_intersect(t_vec3 ro, t_vec3 rd, t_list *prim_list);

uint32_t	hexcol(float r, float g, float b, float a);

//DEBUG
void	v3_print(t_vec3 v);

#endif
