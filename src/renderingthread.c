/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderingthread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:16:33 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/22 13:15:42 by fgeslin          ###   ########.fr       */
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
	int		x;
	int		y;
	t_pixel	*pix;
	t_vec3	c;
	t_vec3	rd;

	pix = (t_pixel *)param;
	y = pix->id;
	const float	rfov = pix->elem->cam.fov * M_PI / 180.0f;
	while (y < HEIGHT - 1)
	{
		x = -1;
		while (x++ < WIDTH - 1)
		{
			rd.x = tan(((x - WIDTH / 2) / (float)WIDTH) * rfov);
			rd.y = tan(((y - HEIGHT / 2) * -1 / (float)WIDTH) * rfov);
			rd.z = 1;
			rd = v3_normalize(rd);
			c = pixelcompute(pix->elem->cam.coord, rd, pix->elem);
			// ## Anti Alisasing TEST ##
			// c = v3_add(c, pixelcompute(x - 0.3, y - 0.3, pix->elem));
			// c = v3_add(c, pixelcompute(x - 0.3, y + 0.3, pix->elem));
			// c = v3_add(c, pixelcompute(x + 0.3, y - 0.3, pix->elem));
			// c = v3_add(c, pixelcompute(x + 0.3, y + 0.3, pix->elem));
			// c = v3_multf(c, 0.2);
			// ##                     ##
			mlx_put_pixel(pix->img, x, y, hexcol(c.x * 255, c.y * 255, c.z * 255, 255));
		}
		y += T_COUNT;
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
