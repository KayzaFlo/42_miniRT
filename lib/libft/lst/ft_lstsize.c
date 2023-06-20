/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:40:24 by fgeslin           #+#    #+#             */
/*   Updated: 2023/01/03 13:03:07 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_lstsize(t_list *lst)
{
	int	ind;

	if (!lst)
		return (0);
	ind = 1;
	while (lst->next)
	{
		ind++;
		lst = lst->next;
	}
	return (ind);
}
