/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_float_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 11:42:12 by arivera           #+#    #+#             */
/*   Updated: 2023/08/22 13:26:45 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minirt.h"
#include "rtparsing.h"

static int	ft_is_valid_float(char *s)
{
	int	i;
	int	digit;
	int	len;

	i = 0;
	digit = 0;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '-')
		i++;
	len = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && s[i] != '.')
			return (0);
		if (s[i++] == '.')
			digit++;
		if (!digit)
			len++;
	}
	if (digit > 1 || len > 10)
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
	float	sign;

	prec = 0.0;
	fract = 1.0;
	sign = 1.0;
	ret = (float)ft_atoi(str);
	if (ret < 0)
		sign = -1.0;
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
		ret += prec * sign;
	}
	return (ret);
}

int	float_parse(char *str, double *var)
{
	if (!ft_is_valid_float(str))
		return (1);
	*var = ft_strtof(str);
	return (0);
}

static int	valid_int(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (ft_isspace(s[i]) == 1)
		i++;
	if (s[i] == '-')
		i++;
	while (s[i] == '0')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
		len++;
	}
	if (len > 10)
		return (0);
	if (ft_atol(s) > INT32_MAX || ft_atol(s) < INT32_MIN)
		return (0);
	return (1);
}

int	int_parse(char *s, int	*value)
{
	if (!valid_int(s))
		return (1);
	*value = ft_atoi(s);
	return (0);
}
