/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:40:41 by fgeslin           #+#    #+#             */
/*   Updated: 2023/01/03 14:32:03 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static char	*new_str(int len, const char *init)
{
	char			*str;

	str = ft_calloc(len + 1, sizeof(char));
	ft_strlcat(str, init, ft_strlen(init) + 1);
	return (str);
}

static void	populate_strptr(char *str, unsigned char *ptr, int i, char *base)
{
	int				j;
	unsigned char	c;

	j = --i;
	while (j > 1)
	{
		c = ptr[(i - j) / 2];
		if ((i - j) % 2)
			str[j] = base[c / 16];
		else
			str[j] = base[c - c / 16 * 16];
		j--;
	}
}

char	*ft_itoa_ptr(void *ptr, int zeros)
{
	unsigned char	*ptr_chr;
	char			*str;
	int				len;
	int				i;

	ptr_chr = ptr;
	len = sizeof(ptr);
	while (!ptr_chr[len - 1] && len > 1)
		len--;
	i = len * 2 + 2;
	if (ptr_chr[len - 1] < 16)
		i--;
	if (zeros > i)
	{
		str = new_str(zeros, "0x");
		ft_memset(str + 2, '0', zeros - 2);
		populate_strptr(str + zeros - i, ptr_chr, i, "0123456789abcdef");
	}
	else
	{
		str = new_str(i, "0x");
		populate_strptr(str, ptr_chr, i, "0123456789abcdef");
	}
	return (str);
}
