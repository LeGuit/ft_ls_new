/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_stat_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 11:35:39 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/02/08 14:24:23 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft/includes/libft.h"

static void			ft_size_minmajoct(t_info *info)
{
	if ((int)info->maxoct < info->maxmaj + info->maxmin)
		info->maxoct = info->maxmin + info->maxmaj + 2;
	else
		info->maxmaj += (info->maxoct - (info->maxmaj + info->maxmin));
}

static size_t		ft_size_uid(uid_t uuid)
{
	struct passwd	*getuid;

	if (!(getuid = getpwuid(uuid)))
		return (0);
	return (ft_strlen(getuid->pw_name));
}

static size_t		ft_size_gid(gid_t gid)
{
	struct group	*getgid;

	if (!(getgid = getgrgid(gid)))
		return (0);
	return (ft_strlen(getgid->gr_name));
}

static void			ft_save_size(t_info *info)
{
	info->maxlink = ft_size_nb(info->maxlink);
	info->maxoct = ft_size_nb(info->maxoct);
	info->maxmaj = ft_size_nb(info->maxmaj);
	info->maxmin = ft_size_nb(info->maxmin);
}

void				ft_size(t_info *info)
{
	t_node			*tmp;
	t_dlst			*it;
	size_t			sizeguid;

	it = info->headfile.next;
	while (it != &info->headfile)
	{
		tmp = C_NODE(t_node, it);
		info->total += tmp->statfile.st_blocks;
		info->maxlink = MAX(info->maxlink, (size_t)tmp->statfile.st_nlink);
		info->maxoct = MAX(info->maxoct, (size_t)tmp->statfile.st_size);
		sizeguid = ft_size_uid(tmp->statfile.st_uid);
		info->maxusr = MAX(info->maxusr, sizeguid);
		sizeguid = ft_size_gid(tmp->statfile.st_gid);
		info->maxgrp = MAX(info->maxgrp, sizeguid);
		info->maxmaj = MAX(info->maxmaj, MAJOR(tmp->statfile.st_rdev));
		info->maxmin = MAX(info->maxmin, MINOR(tmp->statfile.st_rdev));
		info->maxfile = MAX(info->maxfile, ft_strlen(tmp->namtyp.d_name));
		it = it->next;
	}
	ft_save_size(info);
	ft_size_minmajoct(info);
}
