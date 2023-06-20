/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:26:43 by fgeslin           #+#    #+#             */
/*   Updated: 2023/01/03 13:04:04 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*tl;

	tl = malloc(sizeof(t_list));
	if (!tl)
		return (0);
	tl->content = content;
	tl->next = 0;
	return (tl);
}
