/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:51:41 by fgeslin           #+#    #+#             */
/*   Updated: 2023/01/03 13:04:51 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	shift;

	shift = ft_strlen(dst);
	if (shift >= dstsize)
	{
		return (dstsize + ft_strlen(src));
	}
	i = 0;
	while (src[i] != '\0' && shift + i < dstsize - 1)
	{
		dst[shift + i] = src[i];
		i++;
	}
	dst[shift + i] = '\0';
	return (shift + ft_strlen(src));
}
