/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:58:29 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/02/09 11:25:59 by gwoodwar         ###   ########.fr       */
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
	i = 1;
	while (parse_opt(av[i], &info))
		i++;
	if (ft_strequ(av[i], "--"))
		i++;
	if (ac == i)
		ft_get_dir(".", &info);
//	else if (ac - i == 1)
//		ft_get_dir(av[i], &info);
	else
		ft_ls(ac, av, i, &info);/*
		save_sort_av(av, ac, i);
		SET(info.opt, OPT_MD);
		while (i < ac)
		{
			ft_putstr(av[i]);
			ft_putstr(":\n");
			ft_get_dir(av[i], &info);
			i++;
			if (i != ac)
				ft_putchar('\n');
		}*/
	return (0);
}
