/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:15:18 by fgeslin           #+#    #+#             */
/*   Updated: 2023/01/03 14:32:05 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static int	get_mag_base(long int nb, int base_len)
{
	int	count;

	count = 1;
	if (nb < 0)
		nb = -nb;
	while (nb >= base_len)
	{
		nb /= base_len;
		count++;
	}
	return (count);
}

static void	checksign(char *str, long int *nb, int *zeros, char sign)
{
	if (sign && *nb >= 0)
	{
		if (sign > 0)
			*str = sign;
		else
		{
			*str = -sign;
			(*zeros)--;
		}
	}
	if (*nb < 0)
	{
		*str = '-';
		(*nb) *= -1;
		(*zeros)--;
	}
}

char	*ft_itoa_base(long int nb, char *base, int zeros, char sign)
{
	char	*str;
	int		base_len;
	int		len;

	base_len = ft_strlen(base);
	len = (get_mag_base(nb, base_len));
	if (sign || nb < 0)
	{
		len++;
		zeros++;
	}
	if (len > zeros)
		str = ft_calloc(len + 1, sizeof(char));
	else
		str = ft_calloc(zeros + 1, sizeof(char));
	checksign(str, &nb, &zeros, sign);
	while (len < zeros)
		len++;
	while (--len >= 0)
	{
		if (!str[len])
			str[len] = base[nb % base_len];
		nb = nb / base_len;
	}
	return (str);
}
