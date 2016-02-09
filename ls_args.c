/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 09:20:53 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/02/09 11:29:03 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ls_fetch_in_arg(char *filename, t_dlst *headfile,
		t_dlst *headdir, t_dlst *headerror)
{
	t_node		*node;

	if (!(node = (t_node *)malloc(sizeof(t_node))))
		ft_error_malloc();
	ft_strcpy(node->namtyp.d_name, filename);
	if (!(node->path = (char *)malloc(sizeof(char) * ft_strlen(filename) + 1)))
		ft_error_malloc();
	ft_strcpy(node->path, filename);
	if (lstat(node->path, &node->statfile) == -1)
		dlst_add_tail(&node->dlst, headerror);
	if (S_ISREG(node->statfile.st_mode))
		dlst_add_tail(&node->dlst, headfile);
	else
		dlst_add_tail(&node->dlst, headdir);
}

static void		launch_dir_lst(t_dlst *headdir, t_info *info)
{
	t_dlst		*it;
	t_node		*tmp;

	sort_merge_lst(headdir, info);
	it = headdir->next;
	tmp = C_NODE(t_node, it);
	clear_head(&info->headfile);
	while (it != headdir)
	{
		tmp = C_NODE(t_node, it);
		if (!dlst_is_singular(headdir))
		{
			if (it != headdir->next)
				ft_printf("\n%s:\n", tmp->namtyp.d_name);
			else
				ft_printf("%s:\n", tmp->namtyp.d_name);
		}
		ft_get_dir(tmp->path, info);
		it = it->next;
	}
	clear_head(headdir);
}

static void		print_args(t_info *info, t_dlst *headdir)
{
	t_node		*tmp;
	t_dlst		*it;

	it = info->headfile.next;
	if (GET(info->opt, OPT_L) || GET(info->opt, OPT_1))
	{
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
	else
		test_col_file(info);
	if (!dlst_empty(headdir))
		ft_putchar('\n');
}

void			ft_ls(int ac, char **av, int i, t_info *info)
{
	t_dlst		headdir;
	t_dlst		headerror;

	dlst_init(&headdir);
	dlst_init(&headerror);
	dlst_init(&info->headfile);
	reset_max_info(info);
	if (ac - 1 > 1)
		SET(info->opt, OPT_MD);
	while (i < ac)
	{
		ls_fetch_in_arg(av[i], &info->headfile, &headdir, &headerror);
		i++;
	}
	if (!dlst_empty(&headerror))
		flush_headerror(&headerror);
	if (!dlst_empty(&info->headfile))
	{
		sort_merge_lst(&info->headfile, info);
		print_args(info, &headdir);
	}
	launch_dir_lst(&headdir, info);
}
