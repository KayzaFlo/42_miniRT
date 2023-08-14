/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 10:08:18 by arivera           #+#    #+#             */
/*   Updated: 2023/08/14 11:55:57 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minirt.h"
#include "rtparsing.h"

static int	verify_file_extension(char *file_path)
{
	char	*tmp;

	tmp = ft_strrchr(file_path, '.');
	if (!tmp)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(file_path, 2);
		ft_putstr_fd(": wrong file type, please use a .rt file\n", 2);
		return (1);
	}
	if (ft_strncmp(tmp, ".rt", 4))
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(file_path, 2);
		ft_putstr_fd(": wrong file type, please use a .rt file\n", 2);
		return (1);
	}
	return (0);
}

static int	open_file(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0 || read(fd, 0, 0) < 0)
		return (-1);
	return (fd);
}

int	input_parsing(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
	{
		if (argc == 1)
			input_error("not enough arguments\nusage: ./miniRT [file]\n");
		if (argc > 2)
			input_error("too many arguments\nusage: ./miniRT [file]\n");
		return (-1);
	}
	if (verify_file_extension(argv[1]))
		return (-1);
	fd = open_file(argv[1]);
	if (fd == -1)
	{
		ft_putstr_fd("Error\ncould not open file: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putchar_fd('\n', 2);
	}
	return (fd);
}
