/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:06:17 by fgeslin           #+#    #+#             */
/*   Updated: 2023/01/03 13:04:39 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	get_wc(const char *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != sep)
			if (str[i + 1] == '\0' || str[i + 1] == sep)
				count++;
		i++;
	}
	return (count);
}

static int	fill_word(char **tab, int count, char *word)
{
	int	i;

	i = -1;
	count--;
	tab[count] = word;
	if (!tab[count])
	{
		while (++i < count)
			free(tab[i]);
		free(tab);
		return (-1);
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		shift;
	int		len;
	int		count;

	if (!s)
		return (NULL);
	tab = malloc((get_wc(s, c) + 1) * sizeof(*tab));
	if (tab == NULL)
		return (NULL);
	shift = 0;
	count = 0;
	while (count < get_wc(s, c))
	{
		len = 0;
		while (s[shift] == c && s[shift])
			shift++;
		while (s[shift + len] != c && s[shift + len])
			len++;
		if (fill_word(tab, ++count, ft_substr(s, shift, len)) == -1)
			return (NULL);
		shift += len;
	}
	tab[count] = NULL;
	return (tab);
}
