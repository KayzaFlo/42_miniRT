/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:48:31 by fgeslin           #+#    #+#             */
/*   Updated: 2023/01/03 14:32:16 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

char	*ft_chrdup(const char src)
{
	char	*dest;

	dest = ft_calloc(2, sizeof(char));
	dest[0] = src;
	return (dest);
}
