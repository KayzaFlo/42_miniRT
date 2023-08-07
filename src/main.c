/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:53:46 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/07 12:49:29 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "vector3.h"
#include "color.h"
#include "mathplus.h"
#define WIDTH 1920
#define HEIGHT 1080

void	rendering(mlx_image_t *img);

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

float	sdSphere(t_vec3 p, float r, t_vec3 offset) {
	return v3_length(v3_sub(p, offset)) - r;
}

float sdFloor(t_vec3 p) {
  return p.y + 1.;
}

float	sdScene(t_vec3 p) {
	float sphereLeft = sdSphere(p, 1., v3_new(-2.5, 0, -2));
	float sphereRight = sdSphere(p, 1., v3_new(2.5, 0, -2));
	float res = min(sphereLeft, sphereRight);
	res = min(res, sdFloor(p));
	return res;
}

t_vec3	calcNormal(t_vec3 p) {
    float e = 0.0005; //epsilon
    // float r = 1.0f; // sphere's radius
	return v3_normalize(v3_new(
		sdScene(v3_new(p.x + e, p.y, p.z)) - sdScene(v3_new(p.x - e, p.y, p.z)),
		sdScene(v3_new(p.x, p.y + e, p.z)) - sdScene(v3_new(p.x, p.y - e, p.z)),
		sdScene(v3_new(p.x, p.y, p.z  + e)) - sdScene(v3_new(p.x, p.y, p.z - e))
  	));
}

float	rayMarch(t_vec3 ro, t_vec3 rd)
{
	float depth = 0;

	for (int i = 0; i < 255; i++)
	{
		t_vec3	point = {ro.x + rd.x * depth,
			ro.y + rd.y * depth,
			ro.z + rd.z * depth};
		float d = sdScene(point);
		depth += d;
		if  (d < 0.001f || depth > 100) break;
	}
	return depth;
}

void	rendering(mlx_image_t *img)
{
	// Ray Origin / Camera
	t_vec3 ro;
	ro = v3_new(0, 0, 5);
	// Ray Direction
	t_vec3 ray_direction;

	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			// ecran a normaliser facon uv
			ray_direction = v3_normalize(v3_new(i - WIDTH / 2, (j - HEIGHT / 2) * -1, -1000));
			// Distance hit
			float d = rayMarch(ro, v3_normalize(ray_direction));
			if (d > 100.0f) // Didn't hit
				mlx_put_pixel(img, i, j, 0x9999FFFF);
			else {
				t_vec3	point = v3_new(
					ro.x + ray_direction.x * d,
					ro.y + ray_direction.y * d,
					ro.z + ray_direction.z * d
				);
				t_vec3	normal = calcNormal(point);
				t_vec3	lightPosition = v3_new(2, 2, 4); //Y axis seems inverted ?
				t_vec3	lightDirection = v3_normalize(v3_sub(lightPosition, point));
				float dif = clamp(v3_dot(normal, lightDirection), 0, 1);
				uint32_t color = get_colrgba(255.0f * dif, 25.0f * dif, 155.0f * dif, 255);
				mlx_put_pixel(img, i, j, color);
			}
			// UV Debug
			// mlx_put_pixel(img, i, j, get_colrgba((float)i / WIDTH * 255.0f, (float)j / HEIGHT * 255.0f, 0, 255));
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

	mlx_loop_hook(mlx, ft_hook, img);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
