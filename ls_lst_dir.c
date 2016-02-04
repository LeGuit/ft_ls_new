/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lst_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 16:16:16 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/02/04 19:43:30 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			ls_recurs(t_info *info, t_dlst *headdir)
{
	t_dlst			*it;

	if (!GET(info->opt, OPT_UR))
		return ;
	if (dlst_empty(headdir))
		return ;
	it = headdir->next;
	while (it != headdir)
	{
		ft_printf("\n%s:\n", C_NODE(t_node, it)->path);
		ft_get_dir(C_NODE(t_node, it)->path, info);
		it = it->next;
	}
}

void				ft_get_dir(char *filename, t_info *info)
{
	DIR				*dirp;
	t_dlst			headdir;

	reset_max_info(info);
	dlst_init(&headdir);
	if (!(dirp = opendir(filename)))
		ft_error_dir();
	else
	{
		ft_fetch_lst(dirp, filename, &info->headfile, &headdir);
		closedir(dirp);
		ft_size(info);
		sort_merge_lst(&info->headfile, info);
		sort_merge_lst(&headdir, info);
		print_files(info);
		clear_head(&info->headfile);
		ls_recurs(info, &headdir);
		clear_head(&headdir);
	}
}
