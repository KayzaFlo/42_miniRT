/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flagafter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:03:06 by fgeslin           #+#    #+#             */
/*   Updated: 2023/01/03 14:32:14 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_flagafter(int count, t_flaggrp *flaggrp)
{
	if (flaggrp)
	{
		while (ft_flagcmp(flaggrp, flag_Minus) && count < flaggrp->size)
		{
			ft_putchar_fd(' ', 1);
			count++;
		}
	}
	return (count);
}
