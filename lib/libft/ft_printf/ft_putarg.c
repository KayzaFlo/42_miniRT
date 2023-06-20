/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putarg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 10:32:13 by fgeslin           #+#    #+#             */
/*   Updated: 2023/01/03 14:30:49 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_putarg(char c, void *ptr, t_flaggrp *flaggrp)
{
	char	*str;
	int		count;

	if (flaggrp)
		str = ft_flagarg(c, ptr, flaggrp);
	else
		str = ft_printfun(c, ptr, 0, 0);
	if (!str)
		return (-1);
	count = ft_flagbefore(c, str, ptr, flaggrp);
	ft_putstr_fd(str, 1);
	free(str);
	count = ft_flagafter(count, flaggrp);
	return (count);
}
