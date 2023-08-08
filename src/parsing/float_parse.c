/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 11:42:12 by arivera           #+#    #+#             */
/*   Updated: 2023/08/08 12:41:57 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static int	ft_strlen_int_float(char *s)
{
	int	i;
	int	neg;
	int	zeros;

	neg = 0;
	i = 0;
	zeros = 0;
	if (s[i] == '-')
	{
		neg = 1;
		i++;
	}
	while (s[i] == '0')
	{
		i++;
		zeros++;
	}
	while (s[i] && s[i] != '.')
	{
		i++;
	}
	return (i - neg - zeros);
}

static int	ft_is_valid_float(char *s)
{
	int	i;
	int	digit;

	i = 0;
	digit = 0;
	if (!s)
		return (1);
	if (s[i] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && s[i] != '.')
			return (0);
		if (s[i] == '.')
			digit++;
		i++;
	}
	if (digit > 1 || (ft_strlen_int_float(s) > 10))
		return (0);
	if (ft_atol(s) > INT32_MAX || ft_atol(s) < INT32_MIN)
		return (0);
	return (1);
}

static float	ft_strtof(char *str)
{
	float	ret;
	float	prec;
	float	fract;

	prec = 0.0;
	fract = 1.0;
	ret = (float)ft_atoi(str);
	while (*str && *str != '.')
		str++;
	if (*str++ == '.')
	{
		while (*str >= '0' && *str <= '9')
		{
			fract *= 10.0;
			prec += (*str - '0') / fract;
			str++;
		}
		ret += prec;
	}
	return (ret);
}

int	float_parse(char *str, float *var)
{
	if (!ft_is_valid_float(str))
		return (1);
	*var = ft_strtof(str);
	return (0);
}
