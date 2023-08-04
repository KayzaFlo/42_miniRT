/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:53:46 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/04 17:35:02 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Written by Bruh

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "vector3.h"
#define WIDTH 1920
#define HEIGHT 1080

void	v3_print(t_vec3 v) { printf("[%.4f, %.4f, %.4f]\n", v.x, v.y, v.z); }

static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

static void ft_hook(void* param)
{
	(void)param;
}

float sdSphere(t_vec3 p, float r) {
	t_vec3 offset = {0, 0, 0};
	p.x -= offset.x;
	p.y -= offset.y;
	p.z -= offset.z;
	return v3_length(p) - r;
}

float rayMarch(t_vec3 ro, t_vec3 rd)
{
	float depth = 0;

	for (int i = 0; i < 255; i++)
	{
		t_vec3	point = {ro.x + rd.x * depth,
			ro.y + rd.y * depth,
			ro.z + rd.z * depth};
		float d = sdSphere(point, 1);
		depth += d;
		if  (d < 0.001f || depth > 100) break;
	}
	return depth;
}

void	rendering(mlx_image_t *img)
{
	// Ray Origin
	t_vec3 ro = {0, 0, 5};
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			// Ray Direction
			// ecran a normaliser facon uv
			t_vec3 ray_direction = {
				i - WIDTH / 2,
				j - HEIGHT / 2,
				-1000};
			ray_direction = v3_normalize(ray_direction);
			// Distance hit
			float d = rayMarch(ro, v3_normalize(ray_direction));
			if (d > 100.0f) // Didn't hit
				mlx_put_pixel(img, i, j, 0x9999FFFF);
			else {
				t_vec3	point = {
					ro.x + ray_direction.x * d,
					ro.y + ray_direction.y * d,
					ro.z + ray_direction.z * d };
				t_vec3 lightPosition = {2, -2, 4}; //Y axis seems inverted ?
				t_vec3 lightDirection = v3_normalize(lightPosition);
				float dif = v3_dot(point, lightDirection);
				if (dif < 0)
					dif = 0;
				else if (dif > 1)
					dif = 1;
				uint32_t color = ((uint8_t)(255.0f * dif) << 24) +
						((uint8_t)(25.0f * dif) << 16) +
						((uint8_t)(155.0f * dif) << 8) +
						(uint8_t)255;
				mlx_put_pixel(img, i, j, color);
			}
		}
	}
}

int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;

	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!mlx)
		ft_error();


	mlx_image_t* img = mlx_new_image(mlx, 1920, 1080);
	memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

	rendering(img);

	mlx_loop_hook(mlx, ft_hook, NULL);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
