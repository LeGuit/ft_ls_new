/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 09:20:53 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/02/09 09:43:05 by gwoodwar         ###   ########.fr       */
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
		ft_errro_malloc();
	ft_strcpy(node->path, filename);
	if (lstat(node->path, &node->statfile) == -1)
		dlst_add_tail(&node->dlst, headerror);
	if (S_IREG(node->statfile.st_mode))
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
	while (it != headdir)
	{
		tmp = C_NODE(t_node, it);
		ft_get_dir(tmp->path, info);
		it = it->next;
	}
	clear_head(headdir);
}

void			ft_ls(int ac, char **av, int i, t_info *info)
{
	t_dlst		headdir;
	t_dlst		headerror;

	dlst_init(&headdir);
	dlst_init(&headerror);
	dlst_init(&info->headfile);
	while (i < ac)
	{
		ls_fetch_in_arg(av[i], &info->headfile, &headdir, &headerror);
		i++;
	}
	if (!dlst_empty(headerror))
		flush_headerror(headerror);
	sort_merge_lst(&info->headfile, info);
	print_files(info);
	clear_head(&info->headfile);
	launch_dir_lst(&headdir, info);
}
