/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flagstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:44:17 by fgeslin           #+#    #+#             */
/*   Updated: 2023/01/03 14:32:07 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static void	addflag(char c, t_flaggrp *flaggrp)
{
	if (c == '-' && !ft_flagcmp(flaggrp, flag_Minus))
		flaggrp->flags += flag_Minus;
	if (c == '0' && !ft_flagcmp(flaggrp, flag_Zero))
		flaggrp->flags += flag_Zero;
	if (c == '.' && !ft_flagcmp(flaggrp, flag_Dot))
		flaggrp->flags += flag_Dot;
	if (c == '#' && !ft_flagcmp(flaggrp, flag_Sharp))
		flaggrp->flags += flag_Sharp;
	if (c == ' ' && !ft_flagcmp(flaggrp, flag_Space))
		flaggrp->flags += flag_Space;
	if (c == '+' && !ft_flagcmp(flaggrp, flag_Plus))
		flaggrp->flags += flag_Plus;
}

static void	reset_flaggrp(t_flaggrp *flaggrp)
{
	flaggrp->flags = 0;
	flaggrp->size = 0;
	flaggrp->dot_size = 0;
}

int	ft_flagstr(t_flaggrp *flaggrp, const char *str)
{
	int	len;

	len = 0;
	reset_flaggrp(flaggrp);
	while (ft_strchr("-0.# +123456789", str[len]))
	{
		if (ft_strchr("-0.# +", str[len]))
		{
			addflag(str[len], flaggrp);
			len++;
		}
		if (ft_strchr(".", str[len - 1]))
		{
			flaggrp->dot_size = ft_atoi(str + len);
			while (ft_strchr("0123456789", str[len]))
				len++;
		}
		if (ft_strchr("123456789", str[len]))
		{
			flaggrp->size = ft_atoi(str + len);
			while (ft_strchr("0123456789", str[len]))
				len++;
		}
	}
	return (len);
}
