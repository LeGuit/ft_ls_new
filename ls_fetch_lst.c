/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_fetch_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 18:43:24 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/02/04 18:59:05 by gwoodwar         ###   ########.fr       */
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

static void			ft_save(char *dirname, t_node *node, t_dlst *headdir,
							t_dlst *headfile)
{
	if (!(node->path = (char *)malloc(sizeof(char) * 
					((ft_strlen(dirname)
					  + ft_strlen(node->namtyp.d_name) + 2)))))
		exit(0);
	ft_strcpy(node->path, dirname);
	ft_strcat(node->path, "/");
	ft_strcat(node->path, node->namtyp.d_name);	   
	if (lstat(dirname, &node->statfile) == -1)
		perror("ft_ls stat error: ");
	if (node->namtyp.d_type == DT_DIR && ft_strcmp(".", node->namtyp.d_name)
			&& ft_strcmp("..", node->namtyp.d_name))
		dlst_add_tail(&node->dlst, headdir);
	dlst_add_tail(&node->dlst, headfile);
}

void				ft_fetch_lst(DIR *dirp, char *filename, t_dlst *headfile,
		t_dlst *headdir)
{
	t_node			*node;
	struct dirent	*tmp;

	while ((tmp = readdir(dirp)))
	{
		if (tmp->d_name[0] == '.' && !GET(C_NODE(t_info, headfile)->opt, OPT_A))
			continue ;
		if (!(node = (t_node *)malloc(sizeof(t_node))))
			exit(0);
		node->namtyp = *tmp;
		ft_save(filename, node, headdir, headfile);
	}
}
