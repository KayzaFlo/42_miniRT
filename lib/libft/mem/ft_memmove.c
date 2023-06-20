/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:49:55 by fgeslin           #+#    #+#             */
/*   Updated: 2023/01/03 14:11:49 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_byte;
	size_t			i;

	if (!dst || !src)
		return (NULL);
	dst_byte = dst;
	i = -1;
	if (dst > src)
		while (++i < len)
			dst_byte[len - 1 - i] = ((unsigned char *)src)[len - 1 - i];
	else
		while (++i < len)
			dst_byte[i] = ((unsigned char *)src)[i];
	return (dst);
}
