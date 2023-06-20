/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flagcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:44:49 by fgeslin           #+#    #+#             */
/*   Updated: 2023/01/03 14:32:09 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_flagcmp(t_flaggrp *flaggrp, enum e_Flag flag)
{
	enum e_Flag	max;
	enum e_Flag	cmp;

	max = flag_Last;
	cmp = flaggrp->flags;
	while (max > 0)
	{
		if (cmp >= max)
		{
			if (max == flag)
				return (1);
			cmp -= max;
		}
		max /= 2;
	}
	return (0);
}
