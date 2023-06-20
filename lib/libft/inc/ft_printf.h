/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:11:20 by fgeslin           #+#    #+#             */
/*   Updated: 2023/01/03 14:30:28 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"

enum e_Flag {
	flag_Minus = 1,
	flag_Zero = 2,
	flag_Dot = 4,
	flag_Sharp = 8,
	flag_Space = 16,
	flag_Plus = 32,
	flag_Last = flag_Plus
};

typedef struct s_flaggrp
{
	enum e_Flag	flags;
	int			size;
	int			dot_size;
}	t_flaggrp;

typedef unsigned int	t_uint;

int		ft_printf(const char *str, ...);

int		ft_putarg(char c, void *ptr, t_flaggrp *flaggrp);
char	*ft_printfun(char c, void *ptr, int zeros, char sign);

char	*ft_itoa_base(long int nb, char *base, int zeros, char sign);
char	*ft_itoa_ptr(void *ptr, int zeros);
char	*ft_chrdup(const char src);

int		ft_flagstr(t_flaggrp *flaggrp, const char *str);
int		ft_flagcmp(t_flaggrp *flaggrp, enum e_Flag flag);
char	*ft_flagarg(char c, void *ptr, t_flaggrp *flaggrp);
int		ft_flagbefore(char c, char *str, void *ptr, t_flaggrp *flaggrp);
int		ft_flagafter(int count, t_flaggrp *flaggrp);

#endif
