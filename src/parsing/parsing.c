/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 13:58:02 by arivera           #+#    #+#             */
/*   Updated: 2023/08/04 15:42:06 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static int	open_file(char *file_path)
{
	int	fd;
	
	fd = open(file_path, O_RDONLY);
	if (fd < 0 || read(fd, 0, 0) < 0)
		return (0);
	return (fd);
}

static int	verify_file_extension(char *file_path)
{
	char	*tmp;

	tmp = ft_strrchr(file_path, '.');
	if (!tmp)
		return (1);
	if (ft_strncmp(tmp, ".rt", 4))
		return (1);
	return (0);
}

int	parsing(int	argc, char **argv)
{
	int	fd;
	
	if (argc != 2)
	{
		if (argc == 1)
			parsing_error("not enough arguments\nusage: ./miniRT [file]\n");
		if (argc > 2)
			parsing_error("too many arguments\nusage: ./miniRT [file]\n");
	}
	if (verify_file_extension(argv[1]))
		parsing_error("wrong file type. please use a .rt file\n");
	fd = open_file(argv[1]);
	if (!fd)
		parsing_error("could not open file\n");
	file_parsing(fd);
	close(fd);
	return (0);
}
