/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 11:15:52 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/08 11:33:26 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtprim.h"

uint32_t	hexcol(float r, float g, float b, float a)
{
	r = clamp(r, 0.0f, 255.0f);
	g = clamp(g, 0.0f, 255.0f);
	b = clamp(b, 0.0f, 255.0f);
	a = clamp(a, 0.0f, 255.0f);
	return (
		((uint8_t)r << 24)
		+ ((uint8_t)g << 16)
		+ ((uint8_t)b << 8)
		+ (uint8_t)a
	);
}