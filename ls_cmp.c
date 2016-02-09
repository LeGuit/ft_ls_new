/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_cmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 16:43:41 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/02/09 12:16:40 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				cmp_lexi(t_dlst *lsta, t_dlst *lstb)
{
	t_node		*noda;
	t_node		*nodb;

	noda = C_NODE(t_node, lsta);
	nodb = C_NODE(t_node, lstb);
	return (ft_strcmp(noda->namtyp.d_name, nodb->namtyp.d_name));
}

int				cmp_time(t_dlst *lsta, t_dlst *lstb)
{
	t_node		*noda;
	t_node		*nodb;
	int			res;

	noda = C_NODE(t_node, lsta);
	nodb = C_NODE(t_node, lstb);
	if (noda->statfile.st_mtimespec.tv_sec < 0)
		return (1);
	if (noda->statfile.st_mtimespec.tv_sec
			== nodb->statfile.st_mtimespec.tv_sec)
		return (ft_strcmp(noda->namtyp.d_name, nodb->namtyp.d_name));
	res = (noda->statfile.st_mtimespec.tv_sec
			> nodb->statfile.st_mtimespec.tv_sec ? 0 : 1);
	return (res);
}

int				cmp_size(t_dlst *lsta, t_dlst *lstb)
{
	t_node		*noda;
	t_node		*nodb;
	int			res;

	noda = C_NODE(t_node, lsta);
	nodb = C_NODE(t_node, lstb);
	if (noda->statfile.st_size == nodb->statfile.st_size)
		return (ft_strcmp(noda->namtyp.d_name, nodb->namtyp.d_name));
	res = (noda->statfile.st_size > nodb->statfile.st_size ? 0 : 1);
	return (res);
}
