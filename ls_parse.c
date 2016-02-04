/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:01:43 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/01/20 12:21:12 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		invalid_opt(char option, t_info *info)
{
	if (!(ft_strchr("lRratG", option)))
		return (1);
	if (option == 'l')
		SET(info->opt, OPT_L);
	else if (option == 'R')
		SET(info->opt, OPT_UR);
	else if (option == 'r')
		SET(info->opt, OPT_R);
	else if (option == 'a')
		SET(info->opt, OPT_A);
	else if (option == 't')
		SET(info->opt, OPT_T);
	else if (option == 'G')
		SET(info->opt, OPT_G);
	return (0);
}

int				parse_opt(char *av, t_info *info)
{
	size_t		i;

	if (!av)
		return (0);
	if (av[0] != '-')
		return (0);
	i = 1;
	while (i < ft_strlen(av))
	{
		if (invalid_opt(av[i], info))
			ft_exit_parse(av[i]);
		i++;
	}
	return (1);
}
