/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:58:29 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/02/04 16:38:23 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		info_init(t_info *info)
{
	UNSET(info->opt, OPT_ALL);
	dlst_init(&info->headfile);
}

int				main(int ac, char **av)
{
	int			i;
	t_info		info;

	info_init(&info);
	if (ac == 1)
		ft_get_dir(".", &info);
	i = parse_opt(av[1], &info) + 1;
	if (ac == 2 && i == 2)
		ft_get_dir(".", &info);
	else
	{
		SET(info.opt, OPT_MD);
		while (i < ac)
		{
			ft_get_dir(av[i], &info);
			i++;
			if (i != ac)
				ft_putchar('\n');
		}
	}
	return (0);
}
