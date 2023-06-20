/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:24:59 by fgeslin           #+#    #+#             */
/*   Updated: 2023/01/03 13:03:46 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*nextdel;

	if (!lst || !del)
		return ;
	nextdel = 0;
	while (*lst)
	{
		nextdel = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = nextdel;
	}
}
