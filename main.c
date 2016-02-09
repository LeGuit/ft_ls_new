/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:58:29 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/02/09 13:08:49 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		info_init(t_info *info)
{
	UNSET(info->opt, OPT_ALL);
	dlst_init(&info->headfile);
	info->flush = 0;
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
	else
		ft_ls(ac, av, i, &info);
	return (0);
}
