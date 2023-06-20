/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:18:35 by fgeslin           #+#    #+#             */
/*   Updated: 2023/01/03 14:22:28 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	ft_initbuf(t_buf *buf, int fd, char **str, ssize_t *start)
{
	if (!(buf->str))
	{
		buf->str = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buf->str)
			return (-1);
		buf->readlen = read(fd, buf->str, BUFFER_SIZE);
		if (buf->readlen <= 0)
		{
			free (buf->str);
			buf->str = NULL;
			return (-1);
		}
	}
	*str = NULL;
	*start = buf->ind;
	return (0);
}

static char	*ft_clearbuf(t_buf *buf, char **str)
{
	free (buf->str);
	buf->str = NULL;
	if (buf->readlen == -1)
	{
		free (*str);
		*str = NULL;
		return (NULL);
	}
	return (*str);
}

char	*get_next_line(int fd)
{
	static t_buf	buf = {0, 0, 0};
	ssize_t			start;
	char			*str;

	if (ft_initbuf(&buf, fd, &str, &start) == -1)
		return (NULL);
	while (buf.ind <= buf.readlen)
	{
		if (buf.ind == buf.readlen)
		{
			str = ft_strnjoin(str, buf.str + start, buf.ind - start);
			buf.readlen = read(fd, buf.str, BUFFER_SIZE);
			buf.ind = 0;
			start = 0;
			if (buf.readlen <= 0)
				return (ft_clearbuf(&buf, &str));
			buf.str[buf.readlen] = 0;
		}
		if (buf.str[buf.ind] == '\n')
			break ;
		buf.ind++;
	}
	return (ft_strnjoin(str, buf.str + start, ++buf.ind - start));
}
