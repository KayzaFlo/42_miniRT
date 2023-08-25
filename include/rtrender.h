/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtrender.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:16:42 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/25 13:54:24 by fgeslin          ###   ########.fr       */
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

# define T_CAM 1
# define T_LIGHT 2

# define ROTATE 1
# define TRANSLATE 2
# define TL_DST 0.5

typedef struct s_screen
{
	mlx_image_t	*img;
	t_elem		*elem;
	mlx_t		*mlx;
	t_prim		*prim;
	t_vec3		*uvw;
	int			selected;
	int			render;
	int			interaction;
	int			ismovepressed;
}				t_screen;

t_vec3		get_rd(t_vec3 *data, int x, int y, t_elem *elem);
t_vec3		*get_viewport(t_elem *elem, float theta);

int			cam_dir(double cam_ori);
void		ft_hook(void *param);
void		ft_close(void *param);
void		ft_keyhook(mlx_key_data_t keydata, void *param);
void		handle_hooks(t_screen *screen);
void		free_elem(t_elem *e);
int			valid_key(mlx_key_data_t key);

void		camera_interact(mlx_key_data_t keydata, t_screen *s);
void		light_interact(mlx_key_data_t keydata, t_screen *s);
void		ft_get_selection(t_screen *s, int32_t x, int32_t y);
void		ft_hook(void *param);
void		prim_interact(mlx_key_data_t keydata, t_screen *s);
void		sphere_interact(mlx_key_data_t key, t_screen *s, t_sph *sp);
void		cylinder_interact(mlx_key_data_t key, t_screen *s, t_cyl *cyl);
void		plan_interact(mlx_key_data_t key, t_screen *s, t_pl *pl);

void		render(mlx_image_t *img, t_elem *elem);
void		renderthreaded(mlx_image_t *img, t_elem *elem);
t_vec3		get_light(t_vec3 ro, t_vec3 rd, t_elem *elem, t_surface hit);
t_surface	prim_intersect(t_vec3 ro, t_vec3 rd, t_list *prim_list);

uint32_t	hexcol(float r, float g, float b, float a);

#endif
