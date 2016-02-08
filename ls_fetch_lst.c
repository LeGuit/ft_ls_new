/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_fetch_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 18:43:24 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/02/08 10:08:04 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				sort_merge_lst(t_dlst *head, t_info *info)
{
	if (GET(info->opt, OPT_R))
		dlst_merge_sort(head, cmp_lexi_rev);
	else if (GET(info->opt, OPT_T))
		dlst_merge_sort(head, cmp_time);
	else
		dlst_merge_sort(head, cmp_lexi);
}

static void			ft_save(char *dirname, t_node *node, t_dlst *head)
{
	if (!(node->path = (char *)malloc(sizeof(char) * 
					((ft_strlen(dirname)
					  + ft_strlen(node->namtyp.d_name) + 2)))))
		ft_error_malloc();
	ft_strcpy(node->path, dirname);
	ft_strcat(node->path, "/");
	ft_strcat(node->path, node->namtyp.d_name);	   
	if (lstat(node->path, &node->statfile) == -1)
		perror("ft_ls stat error: ");
	dlst_add_tail(&node->dlst, head);
}

void				ft_fetch_lst(DIR *dirp, char *filename, t_dlst *headfile,
		t_dlst *headdir)
{
	t_node			*nodefile;
	t_node			*nodedir;
	struct dirent	*tmp;

	while ((tmp = readdir(dirp)))
	{
		if (tmp->d_name[0] == '.' && !GET(C_NODE(t_info, headfile)->opt, OPT_A))
			continue ;
		if (!(nodefile = (t_node *)malloc(sizeof(t_node))))
			ft_error_malloc();
		nodefile->namtyp = *tmp;
		if (nodefile->namtyp.d_type == DT_DIR
				&& ft_strcmp(".", nodefile->namtyp.d_name)
				&& ft_strcmp("..", nodefile->namtyp.d_name))
		{
			if (!(nodedir = (t_node *)malloc(sizeof(t_node))))
				ft_error_malloc();
			nodedir->namtyp = *tmp;
			ft_save(filename, nodedir, headdir);
		}
		ft_save(filename, nodefile, headfile);
	}
}
