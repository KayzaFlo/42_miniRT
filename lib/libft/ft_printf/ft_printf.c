/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:18:24 by fgeslin           #+#    #+#             */
/*   Updated: 2023/01/03 14:31:54 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"
#include <stdarg.h>

static int	print_all(const char *str, va_list ap, void *arg, t_flaggrp *flagg)
{
	int	i;
	int	len;

	len = 0;
	while (*str)
	{
		i = 0;
		if (*str == '%')
		{
			if (*(str + 1) == 0)
				return (len);
			i = ft_flagstr(flagg, str + 1);
			if (ft_strchr("cspdiuxX%", str[i + 1]))
			{
				if (str[i + 1] != '%')
					arg = va_arg (ap, void *);
				len += ft_putarg(str[i + 1], &arg, flagg);
				i++;
			}
		}
		else
			len += ft_putarg('c', (void *)(str + i), NULL);
		str += i + 1;
	}
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list		ap;
	void		*cur_arg;
	int			len;
	t_flaggrp	*flaggrp;

	cur_arg = (char *)str;
	va_start(ap, str);
	len = 0;
	flaggrp = ft_calloc(1, sizeof(*flaggrp));
	len = print_all(str, ap, cur_arg, flaggrp);
	va_end(ap);
	free(flaggrp);
	return (len);
}
