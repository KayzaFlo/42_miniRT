/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_values.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivera <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 12:38:34 by arivera           #+#    #+#             */
/*   Updated: 2023/08/09 17:04:56 by arivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

typedef void*	(*t_primparse) (t_parsing *p);
typedef int		(*t_identifier_parsing) (t_parsing *p, t_elem *e);

typedef struct s_primfun
{
	char			*name;
	enum e_prim		type;
	t_primparse		fun;
}				t_primfun;

static void	elem_parsing2(t_parsing *p, t_prim *new_prim)
{
	const t_primfun	prims[] = {
	{"sp", PRIM_SPH, sphere_parsing},
	{"cy", PRIM_CYL, cylinder_parsing},
	{"pl", PRIM_PLN, plan_parsing}
	};
	unsigned long	i;

	i = 0;
	while (i < sizeof(prims) / sizeof(prims[0]))
	{
		if (!ft_strncmp(p->line[0], prims[i].name, ft_strlen(prims[i].name)))
		{
			new_prim->content = prims[i].fun(p);
			new_prim->type = prims[i].type;
			return ;
		}
		i++;
	}
}

static int	elem_parsing(t_parsing *p, t_elem *e)
{
	t_list	*new_elem;
	t_prim	*new_prim;

	new_prim = malloc(sizeof(t_prim));
	if (!new_prim)
		return (p->err.malloc_err = 1, 1);
	elem_parsing2(p, new_prim);
	if (!new_prim->content)
		return (free(new_prim), 1);
	new_elem = ft_lstnew(new_prim);
	if (!new_elem)
		return (p->err.malloc_err = 1, 1);
	ft_lstadd_back(&e->prim_list, new_elem);
	return (0);
}

typedef struct s_identifiants
{
	char					*name;
	t_identifier_parsing	fun;
}			t_identifiants;

int	assign_values(t_parsing *parse, t_elem *elem)
{
	const t_identifiants	id[] = {
	{"A", ambiance_parsing},
	{"C", camera_parsing},
	{"L", light_parsing}
	};
	int						i;
	int						parse_err;

	parse_err = 0;
	i = 0;
	while (i < 3)
	{
		if (!ft_strncmp(parse->line[0], id[i].name, ft_strlen(id[i].name) + 1))
		{
			parse_err = id[i].fun(parse, elem);
			return (parse_err);
		}
		i++;
	}
	parse_err = elem_parsing(parse, elem);
	return (parse_err);
}
