/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtrender.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:16:42 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/10 13:21:11 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTRENDER_H
# define RTRENDER_H

#include <stdio.h>
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "rtmath.h"
#include "rtprim.h"
#include "../include/minirt.h"

#define WIDTH 1280
#define HEIGHT 720

void	render(mlx_image_t *img, t_elem *elem);

#endif
