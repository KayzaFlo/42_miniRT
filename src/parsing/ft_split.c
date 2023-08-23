/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:29:01 by arivera           #+#    #+#             */
/*   Updated: 2023/08/23 16:05:53 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	check_s_vs_cs(char *cs, char s)
{
	int	i;

	i = 0;
	while (cs[i])
	{
		if (cs[i] == s)
			return (1);
		i++;
	}
	return (0);
}

static int	dest_2d_size(char *s, char *cs)
{
	int	i;
	int	nw;
	int	words;

	words = 0;
	nw = 0;
	i = 0;
	while (s[i])
	{
		if (check_s_vs_cs(cs, s[i]) == 0 && nw == 0)
		{
			words++;
			nw = 1;
		}
		else if (check_s_vs_cs(cs, s[i]) == 1)
			nw = 0;
		i++;
	}
	return (words);
}

static char	*ft_strdup_ultra(char *str, char *charset, int *ptrj)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		i++;
	}
	dest = (char *)malloc(sizeof(char) * (i + 1));
	if (dest == 0)
		return (0);
	j = 0;
	while (check_s_vs_cs(charset, str[*ptrj]) == 1)
	{
		(*ptrj)++;
	}
	while (check_s_vs_cs(charset, str[*ptrj]) == 0 && str[*ptrj])
	{
		dest[j] = str[*ptrj];
		(*ptrj)++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

char	**ft_split_ultra(char *str, char *charset)
{
	char	**dest;
	int		i;
	int		j;
	int		*ptrj;
	int		words;

	words = dest_2d_size(str, charset);
	dest = (char **)malloc(sizeof(char *) * (words + 1));
	if (dest == 0)
		return (0);
	i = 0;
	j = 0;
	ptrj = &j;
	while (i < words)
	{
		dest[i] = ft_strdup_ultra(str, charset, ptrj);
		i++;
	}
	dest[i] = 0;
	return (dest);
}
