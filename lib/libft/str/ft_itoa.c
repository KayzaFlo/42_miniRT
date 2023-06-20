/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:54:50 by fgeslin           #+#    #+#             */
/*   Updated: 2023/01/03 13:06:20 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	get_len(int n)
{
	int	mag;

	mag = 1;
	while (n > 9 || n < -9)
	{
		mag++;
		n /= 10;
	}
	if (n < 0)
		return (mag + 2);
	return (mag + 1);
}

static char	setchar(int n)
{
	if (n < 0)
		return (-(n % 10) + '0');
	else
		return (n % 10 + '0');
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		i;

	len = get_len(n);
	str = malloc(len * sizeof(char));
	if (str == 0)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	i = len - 2;
	while (n > 9 || n < -9)
	{
		str[i] = setchar(n);
		n /= 10;
		i--;
	}
	str[i] = setchar(n);
	str[len - 1] = 0;
	return (str);
}
