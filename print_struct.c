/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 18:17:02 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/02/04 17:36:41 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			print_info(t_info *info)
{
	ft_putendl("\nOptions :");
	ft_putendl("lRrat");
	PRINT(info->opt, OPT_L);
	PRINT(info->opt, OPT_UR);
	PRINT(info->opt, OPT_R);
	PRINT(info->opt, OPT_A);
	PRINT(info->opt, OPT_T);
	ft_putchar('\n');
}

void			print_max(t_info *info)
{
	ft_printf("maxlink: %d\n", info->maxlink);
	ft_printf("maxoct : %d\n", info->maxoct);
	ft_printf("maxusr : %d\n", info->maxusr);
	ft_printf("maxgrp : %d\n\n", info->maxgrp);
}

void			print_dir(t_dlst *headdir)
{
	t_dlst		*it;

	it = headdir->next;
	while (it != headdir)
	{
		ft_printf("Dirname in headdir: %s\n", C_NODE(t_node, it)->namtyp.d_name);
		ft_printf("Dirpath in headdir: %s\n", C_NODE(t_node, it)->path);
		it = it->next;
	}
}

void			print_files(t_info *info)
{
	t_node		*tmp;
	t_dlst		*it;

	it = info->headfile.next;
	if (GET(info->opt, OPT_L))
		ft_printf("total %d\n", info->total);
	while (it != &info->headfile)
	{
		tmp = C_NODE(t_node, it);
		if (!GET(info->opt, OPT_A) && tmp->namtyp.d_name[0] == '.')
		{
			it = it->next;
			continue ;
		}
		if (GET(info->opt, OPT_L))
			print_stat(tmp, info);
		else
			print_filename(tmp, info);
		it = it->next;
	}
}
