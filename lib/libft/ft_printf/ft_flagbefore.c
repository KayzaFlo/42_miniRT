/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flagbefore.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:03:06 by fgeslin           #+#    #+#             */
/*   Updated: 2023/01/03 14:32:11 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static int	ft_flagdot(char c, char *str, t_flaggrp *flaggrp, int count)
{
	if (c == 's')
	{
		if (flaggrp->dot_size < count)
			count = flaggrp->dot_size;
		else
			flaggrp->dot_size = count;
		str[count] = 0;
	}
	else
		if (!ft_flagcmp(flaggrp, flag_Zero))
			flaggrp->flags += flag_Zero;
	return (count);
}

int	ft_flagbefore(char c, char *str, void *ptr, t_flaggrp *flaggrp)
{
	int	count;

	count = ft_strlen(str);
	if (c == 'c' && !*str)
		count++;
	if (flaggrp)
	{
		if (ft_flagcmp(flaggrp, flag_Dot))
			count = ft_flagdot(c, str, flaggrp, count);
		if (ft_flagcmp(flaggrp, flag_Sharp) && *(unsigned int *)ptr)
			count += 2;
		while (!ft_flagcmp(flaggrp, flag_Minus) && count < flaggrp->size)
		{
			ft_putchar_fd(' ', 1);
			count++;
		}
		if (ft_flagcmp(flaggrp, flag_Sharp) && *(unsigned int *)ptr)
			ft_printf("0%c", c);
	}
	if (c == 'c' && !*str)
		ft_putchar_fd('\0', 1);
	return (count);
}
