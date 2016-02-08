/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 11:52:34 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/02/08 13:12:16 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
void			get_color(t_info *info, t_node *node)
{
	ft_strcpy(node->color, C_RES);
	if (!GET(info->opt, OPT_G))
		return ;
	if (S_ISSOCK(node->statfile.st_mode))
		ft_putchar('s');
	else if (S_ISLNK(node->statfile.st_mode))
		ft_strcpy(node->color, C_MAG);
	else if (S_ISFIFO(node->statfile.st_mode))
		ft_strcpy(node->color, C_YEL);
	else if (S_ISCHR(node->statfile.st_mode))
		ft_strcpy(node->color, C_BLU);
	else if (S_ISDIR(node->statfile.st_mode))
		ft_strcpy(node->color, C_LCYA);
	else if (S_ISBLK(node->statfile.st_mode))
		ft_strcpy(node->color, C_BLU);
	else if (node->statfile.st_mode & S_IXUSR
			&& node->statfile.st_mode & S_IXGRP
			&& node->statfile.st_mode & S_IXOTH)
		ft_strcpy(node->color, C_RED);
	ft_strcpy(node->background, B_RES);
	if (S_ISCHR(node->statfile.st_mode))
		ft_strcpy(node->background, C_BLU);
	else if (S_ISBLK(node->statfile.st_mode))
		ft_strcpy(node->background, C_BLU);
}
*/

void			reset_max_info(t_info *info)
{
	info->maxlink = 0;
	info->maxoct = 0;
	info->maxusr = 0;
	info->maxgrp = 0;
	info->total = 0;
	info->maxmaj = 0;
	info->maxmin = 0;
	info->maxfile = 0;
}
