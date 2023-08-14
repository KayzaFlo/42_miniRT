/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderingthread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:16:33 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/14 14:07:55 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtrender.h"
# include <pthread.h>

typedef struct	s_pixel
{
	// pthread_t	p_id;
	int			id;
	t_elem		*elem;
	mlx_image_t	*img;
}				t_pixel;


void	*routine(void *param)
{
	t_pixel	*pix;
	t_vec3	c;
	int	x;
	int	y;

	pix = (t_pixel *)param;
	y = pix->id;
	while (y < HEIGHT - 1)
	{
		x = -1;
		while (x++ < WIDTH - 1)
		{
			c = pixelcompute(x, y, pix->elem);
			// ## Anti Alisasing TEST ##
			// c = v3_add(c, pixelcompute(x - 0.3, y - 0.3, pix->elem));
			// c = v3_add(c, pixelcompute(x - 0.3, y + 0.3, pix->elem));
			// c = v3_add(c, pixelcompute(x + 0.3, y - 0.3, pix->elem));
			// c = v3_add(c, pixelcompute(x + 0.3, y + 0.3, pix->elem));
			// c = v3_multf(c, 0.2);
			// ##                     ##
			mlx_put_pixel(pix->img, x, y, hexcol(c.x * 255, c.y * 255, c.z * 255, 255));
		}
		y += 10;
	}
	pthread_exit(NULL);
}

void	renderthreaded(mlx_image_t *img, t_elem *elem)
{
	t_pixel		pix[10];
	pthread_t	p_id[10];
	int	i;

	i = -1;
	while (++i < 10)
	{
		pix[i].elem = elem;
		pix[i].img = img;
		pix[i].id = i;
		pthread_create(&p_id[i], NULL, routine, &pix[i]);
	}
	i = -1;
	while (++i < 10)
	{
		pthread_join(p_id[i], NULL);
	}
}
