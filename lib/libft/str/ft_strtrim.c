/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:37:10 by fgeslin           #+#    #+#             */
/*   Updated: 2023/01/03 13:05:13 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	setcmp(char c, const char *set)
{
	int	i;

	i = -1;
	while (set[++i])
		if (c == set[i])
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (setcmp(s1[start], set) == 1 && s1[start])
		start++;
	while (setcmp(s1[end], set) == 1 && end > 0)
		end--;
	if (end == 0)
		start = 1;
	str = malloc((end - start + 2) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	while (++i + start <= end)
		str[i] = s1[i + start];
	str[i] = 0;
	return (str);
}
