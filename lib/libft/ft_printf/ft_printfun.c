/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:07:20 by fgeslin           #+#    #+#             */
/*   Updated: 2023/01/03 14:30:58 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

char	*ft_printfun(char c, void *ptr, int zeros, char sign)
{
	if (c == 'c')
		return (ft_chrdup(*(char *)ptr));
	if (c == 's')
	{
		if (*(char **)ptr)
			return (ft_strdup(*(char **)ptr));
		else
			return (ft_strdup("(null)"));
	}
	if (c == 'p')
		return (ft_itoa_ptr(ptr, zeros + 2));
	if (c == 'd' || c == 'i')
		return (ft_itoa_base(*(int *)ptr, "0123456789", zeros, sign));
	if (c == 'u')
		return (ft_itoa_base(*(t_uint *)ptr, "0123456789", zeros, sign));
	if (c == 'x')
		return (ft_itoa_base(*(t_uint *)ptr, "0123456789abcdef", zeros, sign));
	if (c == 'X')
		return (ft_itoa_base(*(t_uint *)ptr, "0123456789ABCDEF", zeros, sign));
	if (c == '%')
		return (ft_strdup("%"));
	return (NULL);
}
