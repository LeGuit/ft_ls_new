/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_stat_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 11:35:39 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/02/04 20:24:00 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft/includes/libft.h"

static int			size_nb(int nb)
{
	int				i;

	i = 0;
	while (nb)
	{
		i++;
		nb /= 10;
	}
	return (i);
}

static void			ft_size_minmajoct(t_info *info)
{
	if ((int)info->maxoct < info->maxmaj + info->maxmin)
		info->maxoct = info->maxmin + info->maxmaj + 2;
	else
		info->maxmaj += (info->maxoct - (info->maxmaj + info->maxmin));
}

static int			ft_size_uid(uuid_t uuid)
{
	struct passwd	*getuid;

	if (!(getuid = getpwuid(uuid)))
	{
		perror("ft_ls: ")
		return (0);
	}
	return (ft_strlen(getuid->pw_name));
}

static int			ft_size_gid(gid_t gid)
{
	struct group	*getgid;

	if (!(getuid = getgrgid(gid)))
	{
		perror("ft_ls: ")
		return (0);
	}
	return (ft_strlen(getgid->pw_name));
}

void				ft_size(t_info *info)
{
	t_node			*tmp;
	t_dlst			*it;
	int				sizeguid;

	if (!GET(info->opt, OPT_L))
		return ;
	it = info->headfile.next;
	while (it != &info->headfile)
	{
		tmp = C_NODE(t_node, it);
		info->total += tmp->statfile.st_blocks;
		info->maxlink = MAX(info->maxlink, (size_t)tmp->statfile.st_nlink);
		info->maxoct = MAX(info->maxoct, (size_t)tmp->statfile.st_size);
		sizeguid = ft_size_uid(tmp->statfile->st_uid)
		info->maxusr = MAX(info->maxusr, sizeguid);
		sizeguid = ft_size_gid(tmp->statfile->st_gid);
		info->maxgrp = MAX(info->maxgrp, sizeguid);
		info->maxmaj = MAX(info->maxmaj, MAJOR(tmp->statfile.st_rdev));
		info->maxmin = MAX(info->maxmin, MINOR(tmp->statfile.st_rdev));
		it = it->next;
	}
	info->maxlink = size_nb(info->maxlink);
	info->maxoct = size_nb(info->maxoct);
	info->maxmaj = size_nb(info->maxmaj);
	info->maxmin = size_nb(info->maxmin);
	ft_size_minmajoct(info);
}
