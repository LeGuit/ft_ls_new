/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:58:29 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/02/08 20:58:06 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		info_init(t_info *info)
{
	UNSET(info->opt, OPT_ALL);
	dlst_init(&info->headfile);
}

static void		save_sort_av(char **av, int ac, int i)
{
	char		*tmp;
	int			j;

	while (i < ac)
	{
		j = i + 1;
		while (j < ac)
		{
			if (ft_strcmp(av[i], av[j]) > 0)
			{
				tmp = av[i];
				av[i] = av[j];
				av[j] = tmp;
			}
			j++;
		}
		i++;
	}
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
	{
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
		}
	}
	return (0);
}
