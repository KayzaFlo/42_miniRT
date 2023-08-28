/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flagarg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:03:06 by fgeslin           #+#    #+#             */
/*   Updated: 2023/08/28 12:16:31 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

char	*ft_flagarg(char c, void *ptr, t_flaggrp *flaggrp)
{
	char	*str;
	char	sign;

	sign = 0;
	if (ft_flagcmp(flaggrp, flag_Plus))
		sign = '+';
	else if (ft_flagcmp(flaggrp, flag_Space))
		sign = ' ';
	if (ft_flagcmp(flaggrp, flag_Dot))
	{
		if (*(int *)ptr < 0 && ft_strchr("id", c))
			str = ft_printfun(c, ptr, flaggrp->dot_size + 1, sign);
		else
			str = ft_printfun(c, ptr, flaggrp->dot_size, sign);
		if (!flaggrp->dot_size && !*(int *)ptr && ft_strchr("iduxX", c))
			str[ft_isprint(sign)] = 0;
		return (str);
	}
	else if (ft_flagcmp(flaggrp, flag_Zero))
	{
		if (ft_flagcmp(flaggrp, 8) && *(size_t *)ptr && ft_strchr("xX", c))
			return (ft_printfun(c, ptr, flaggrp->size - 2, -sign));
		return (ft_printfun(c, ptr, flaggrp->size, -sign));
	}
	return (ft_printfun(c, ptr, 0, sign));
}
