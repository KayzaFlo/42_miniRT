/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:53:46 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/11 15:48:44 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "rtrender.h"
#include "../lib/libft/inc/libft.h"
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../include/minirt.h"

static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	del_prim(void *content)
{
	t_prim	*prim;
	
	prim = (t_prim *)content;
	if (prim->type == PRIM_SPH)
		free((t_sph *)prim->content);
	else if (prim->type == PRIM_CYL)
		free((t_cyl *)prim->content);
	else if (prim->type == PRIM_PLN)
		free((t_pl *)prim->content);
	free(prim);
}

static void ft_hook(void* param)
{
	(void)param;
}

void	del_lit(void *content)
{
	t_lit	*lit;
	
	lit = (t_lit *)content;
	free(content);
}

void	free_elem(t_elem *e)
{
	ft_lstclear(&e->prim_list, del_prim);
	ft_lstclear(&e->lit, del_lit);
	free(e);
}

float	step(float edge, float x) {
	if (x < edge)
		return 0;
	return 1;
}

float	smoothstep(float edge0, float edge1, float x) {
	float	t;
	t = clamp((x - edge0) / (edge1 - edge0), 0, 1);
	return t * t * (3.0 - 2.0 * t);
}

float sphSoftShadow( t_vec3 ro, t_vec3 rd, t_vec3 sph, float r, float k )
{
    t_vec3 oc = v3_sub(ro, sph);
    float b = v3_dot( oc, rd );
    float c = v3_dot( oc, oc ) - r*r;
    float h = b*b - c;

    return (b>0.0) ? step(-0.0001,c) : smoothstep( 0.0, 1.0, h*k/b );
}

t_surface elliIntersect( t_vec3 ro, t_vec3 rd, t_vec3 r )
{
	t_surface	surface;

    t_vec3 r2 = v3_mult(r, r);
    float a = v3_dot( rd, v3_new(rd.x/r2.x, rd.y/r2.y, rd.z/r2.z) );
	float b = v3_dot( ro, v3_new(rd.x/r2.x, rd.y/r2.y, rd.z/r2.z) );
	float c = v3_dot( ro, v3_new(ro.x/r2.x, ro.y/r2.y, ro.z/r2.z) );
	float h = b*b - a*(c-1.0);
	if( h<0.0 )
	{
		surface.sd = -1;
		surface.n = v3_new(-1,-1,-1);
		return surface;
	}
	float t = (-b - sqrt( h ))/a;
	surface.sd = t;
    t_vec3 n = v3_normalize(v3_new((ro.x+t*rd.x)/r2.x, (ro.y+t*rd.y)/r2.y, (ro.z+t*rd.z)/r2.z) );
	surface.n = n;
    return surface;
}

float	cylIntersect(t_vec3 ro, t_vec3 rd, t_vec3 pos, t_vec3 rot, float r, float h)
{
	//caps
	return (0);
}

t_surface sphIntersect(t_vec3 ro, t_vec3 rd, t_vec3 pos, float r)
{
	t_surface	surface;
	
	t_vec3 oc = v3_sub(ro, pos);		// p-c			p-->c
	float b = v3_dot( oc, rd );			// p-c . d		p-->c . p-->d
	float c = v3_dot( oc, oc ) - r*r;	// c
	float h = b*b - c;
	if( h < 0.0 )
	{
		surface.sd = -1;
		surface.n = v3_new(-1,-1,-1);
		return surface;
	}
	surface.sd = - b - sqrt( h );
	surface.n = v3_normalize(v3_sub(v3_add(ro, v3_new(rd.x*surface.sd, rd.y*surface.sd, rd.z*surface.sd)), pos));
	return surface;
}
            
float sphOcclusion(t_vec3 pos, t_vec3 nor, t_vec3 sph , float r)
{
    t_vec3  r3 = v3_sub(sph, pos);
    float l = v3_length(r3);
    return v3_dot(nor,r3)*(r*r)/(l*l*l);
}

t_surface plIntersect(t_vec3 ro, t_vec3 rd, t_vec3 pos, t_vec3 n)
{
	t_surface	surface;

	float	a = v3_dot(v3_sub(ro, pos), n);
	float	b = v3_dot(rd, n);
	if (b == 0)
	{
		surface.sd = -1;
		surface.n = v3_new(-1,-1,-1);
		return surface;
	}
	surface.sd = a / b;
	surface.n = n;
	return surface;
}

void	raytracing(mlx_image_t *img, t_elem *elem)
{
	t_vec3	cam = elem->cam.coord;

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			t_vec3	rd = v3_normalize(v3_new(x - WIDTH / 2, (y - HEIGHT / 2) * -1, -600));
			t_vec3	sph_pos = v3_new(0, 0, 0);
			t_vec3	sph2_pos = v3_new(-1, 1, 0);
			float	sph_rad = 1;
			t_lit	*light = (t_lit *)(elem->lit->content);
			t_vec3	light_pos = light->coord;
			t_vec3	light_dir;
			t_vec3	col = v3_new(.2, .2, .2);
			float	tmin = 1e10;
			t_vec3	norm;
			float	occ = 1.0;

			t_list		*list = elem->prim_list;
			while (list)
			{
				t_prim	*prim = (t_prim *)(list->content);
				t_vec3	hitpoint;
				t_surface	d;

				t_pl	*pl;
				t_sph	*sph;

				if (prim->type == PRIM_PLN) {
					pl = (t_pl *)(prim->content);
					d = plIntersect(cam, rd, pl->coord, pl->ori);
				}
				if (prim->type == PRIM_SPH) {
					sph = (t_sph *)(prim->content);
					d = sphIntersect(cam, rd, sph->coord, sph->dia / 2);
				}
				if (d.sd > 0 && d.sd < tmin)
				{
					tmin = d.sd;
					hitpoint = v3_add(cam, v3_new(rd.x * d.sd, rd.y * d.sd, rd.z * d.sd));
					light_dir = v3_normalize(v3_sub(light_pos, hitpoint));
					norm = d.n;
				}
				list = list->next;
			}
				// ** PRIM TEST **
				t_vec3	hitpoint;
				t_surface	d;
				d = elliIntersect(v3_sub(cam, v3_new(-4, 0, -4)), rd, v3_new(2, 1, 1));
				if (d.sd > 0 && d.sd < tmin)
				{
					tmin = d.sd;
					hitpoint = v3_add(cam, v3_new(rd.x * d.sd, rd.y * d.sd, rd.z * d.sd));
					light_dir = v3_normalize(v3_sub(light_pos, hitpoint));
					norm = d.n;
				}
				// ***************
			if (tmin < 1000)
			{
				t_vec3	pos = v3_add(cam, v3_new(rd.x * tmin, rd.y * tmin, rd.z * tmin));

				float	r;
				r = clamp(v3_dot(norm, light_dir), 0, 1);
				r *= sphSoftShadow(pos, light_dir, sph_pos, sph_rad, 2.0);		// TEST smooth shadow
				// r *= sphIntersect(pos, light_dir, sph_pos, sph_rad).sd < 0 ? 1 : 0;
				// col = v3_new(r, r ,r);
				col = norm;		//DEBUG NORMAL
			}
			col = v3_new(sqrtf(col.x), sqrtf(col.y) ,sqrtf(col.z));
			mlx_put_pixel(img, x, y, hexcol(col.x * 255, col.y * 255, col.z * 255, 255));
		}
	}
	
}

int main(int argc, char *argv[])
{
	t_elem		*elem;
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!mlx)
		ft_error();
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	ft_memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

	elem = (t_elem *)malloc(sizeof(t_elem));
	if (!elem)
		return (ft_putstr_fd("Error\nmalloc error\n", 2), 1);
	elem->prim_list = 0;
	elem->lit = 0;
	if (parsing(argc, argv, elem))
		return (free_elem(elem), 1);
	raytracing(img, elem);
	// render(img, elem);
	// free_elem(elem);

	mlx_loop_hook(mlx, ft_hook, img);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
