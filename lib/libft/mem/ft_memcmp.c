/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:57:25 by fgeslin           #+#    #+#             */
/*   Updated: 2023/01/03 13:05:54 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*dst_byte;
	const unsigned char	*src_byte;
	size_t				i;

	dst_byte = s1;
	src_byte = s2;
	i = 0;
	while (i < n)
	{
		if (dst_byte[i] != src_byte[i])
			return (dst_byte[i] - src_byte[i]);
		i++;
	}
	return (0);
}
