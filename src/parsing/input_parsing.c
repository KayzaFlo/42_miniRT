/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 10:08:18 by arivera           #+#    #+#             */
/*   Updated: 2023/08/08 11:38:42 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minirt.h"

static int	verify_file_extension(char *file_path)
{
	char	*tmp;

	tmp = ft_strrchr(file_path, '.');
	if (!tmp)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("wrong file type. please use a .rt file\n", 2);
		exit (1);
	}
	if (ft_strncmp(tmp, ".rt", 4))
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("wrong file type. please use a .rt file\n", 2);
		exit (1);
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
	}
	if (verify_file_extension(argv[1]))
		input_error("wrong file type. please use a .rt file\n");
	fd = open_file(argv[1]);
	if (!fd)
	{
		ft_putstr_fd("Error\ncould not open file: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putchar_fd('\n', 2);
		exit (1);
	}
	return (fd);
}
