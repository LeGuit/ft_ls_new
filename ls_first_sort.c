/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_first_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 21:24:17 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/02/08 22:05:58 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		**save_reg_files(int ac, char **av, int i)
{
	struct stat	tmp;
	char		**res;
	int			j;

	res = (char **)malloc(sizeof(char *) * ac);
	j = 0;
	while (j++ < ac)
		res[j] = 0;
	j = 0;
	while (i < ac)
	{
		stat(av[i], &tmp);
		if (S_ISREG(tmp.st_mode))
		{
			res[j] = (char *)malloc(sizeof(char) * ft_strlen(av[i]));
			ft_strcpy(res[j], av[i]);
			j++;
		}
		i++;
	}
	return (res);
}

static char		**save_noreg_files(int ac, char **av, int i)
{
	struct stat	tmp;
	char		**res;
	int			j;

	res = (char **)malloc(sizeof(char *) * ac);
	j = 0;
	while (j++ < ac)
		res[j] = 0;
	j = 0;
	while (i < ac)
	{
		stat(av[i], &tmp);
		if (!S_ISREG(tmp.st_mode))
		{
			res[j] = (char *)malloc(sizeof(char) * ft_strlen(av[i]));
			ft_strcpy(res[j], av[i]);
			j++;
		}
		i++;
	}
	return (res);
}

void			ft_ls(int ac, char **av, int i, t_info *info)
{
	char		**tab;

	tab = save_reg_files(ac, av, i);
	sort_tab(tab);
	print_rfiles(tab);
	clear_tab(tab);
	tab = save_noreg_files(ac, av, i);
	sort_tab(tab);
	i = 0;
	while (tab[i] != 0)
	{
		ft_putstr(tab[i]);
		ft_putstr(":\n");
		ft_get_dir(tab[i], info);
		if (tab[i + 1] != 0)
			ft_putchar('\n');
		i++;
	}
	clear_tab(tab);
}
