/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderingthread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:16:33 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/25 13:32:01 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtrender.h"
# include <pthread.h>

# define T_COUNT 16

typedef struct	s_pixel
{
	// pthread_t	p_id;
	int			id;
	t_elem		*elem;
	mlx_image_t	*img;
}				t_pixel;


void	*routine(void *param)
{
	t_vec3		screen;
	t_vec3		c;
	t_vec3		rd;
	t_vec3		*data;
	t_surface	hit;
	t_pixel		*pix;

	pix = (t_pixel *)param;
	data = get_viewport(pix->elem, pix->elem->cam.fov * M_PI / 180.0f);
	screen.y = -1;
	while (screen.y++ < HEIGHT - 1)
	{
		printf("\e[1;36m\r%05.1f%%\e[0m", (float)screen.y / (HEIGHT - 1) * 100.0f);
		screen.x = -1;
		while (screen.x++ < WIDTH - 1)
		{
			rd = get_rd(data, screen.x, screen.y, pix->elem);
			hit = prim_intersect(pix->elem->cam.coord, rd, pix->elem->prim_list);
			if (hit.sd < 1000)
				c = get_light(pix->elem->cam.coord, rd, pix->elem, hit);
			else
				c = v3_multf(pix->elem->amb.col, pix->elem->amb.ratio);
			// ## Anti Alisasing TEST ##
			// c = v3_add(c, pixelcompute(x - 0.3, y - 0.3, pix->elem));
			// c = v3_add(c, pixelcompute(x - 0.3, y + 0.3, pix->elem));
			// c = v3_add(c, pixelcompute(x + 0.3, y - 0.3, pix->elem));
			// c = v3_add(c, pixelcompute(x + 0.3, y + 0.3, pix->elem));
			// c = v3_multf(c, 0.2);
			// ##                     ##
			mlx_put_pixel(pix->img, screen.x, screen.y, hexcol(c.x * 255, c.y * 255, c.z * 255, 255));
		}
		screen.y += T_COUNT;
	}
	pthread_exit(NULL);
}

void	renderthreaded(mlx_image_t *img, t_elem *elem)
{
	t_pixel		pix[T_COUNT];
	pthread_t	p_id[T_COUNT];
	int	i;

	i = -1;
	while (++i < T_COUNT)
	{
		pix[i].elem = elem;
		pix[i].img = img;
		pix[i].id = i;
		pthread_create(&p_id[i], NULL, routine, &pix[i]);
	}
	i = -1;
	while (++i < T_COUNT)
	{
		pthread_join(p_id[i], NULL);
	}
}
