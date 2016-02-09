/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_col_disp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 12:59:04 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/02/09 11:59:35 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/ioctl.h>

static void				get_winsize(t_info *info)
{
	struct winsize		screen_size;

	ioctl(0, TIOCGWINSZ, &screen_size);
	info->nbfile = dlst_size(&info->headfile);
	info->col = screen_size.ws_col / info->maxfile;
	if (info->col == 0)
	{
		info->col = 1;
		SET(info->opt, OPT_1);
		print_files(info);
		UNSET(info->opt, OPT_1);
	}
	info->line = MAX(info->nbfile / info->col, 1);
	if (info->nbfile % info->maxfile)
		info->line++;
}

static void				index_dlst(t_dlst *headfile)
{
	t_dlst				*it;
	t_node				*tmp;
	size_t				i;

	it = headfile->next;
	i = 1;
	while (it != headfile)
	{
		tmp = C_NODE(t_node, it);
		tmp->index = i;
		i++;
		it = it->next;
	}
}

static void				print_col_file(t_info *info)
{
	t_dlst				*it;
	t_node				*tmp;
	size_t				line;
	size_t				col;

	it = info->headfile.next;
	line = 0;
	while (++line <= info->line)
	{
		col = 0;
		while (it != &info->headfile)
		{
			tmp = C_NODE(t_node, it);
			if (tmp->index % info->line == line % info->line)
			{
				ft_printf("%-*s ", info->maxfile, tmp->namtyp.d_name);
				if (col++ == info->col)
					break ;
			}
			it = it->next;
		}
		if (line != info->line)
			ft_putchar('\n');
		it = info->headfile.next;
	}
	ft_putchar('\n');
}

void					test_col_file(t_info *info)
{
	get_winsize(info);
	if (info->col == 1)
		return ;
	index_dlst(&info->headfile);
	print_col_file(info);
}
