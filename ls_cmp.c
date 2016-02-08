/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_cmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 16:43:41 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/02/08 10:27:02 by gwoodwar         ###   ########.fr       */
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

int				cmp_lexi_rev(t_dlst *lsta, t_dlst *lstb)
{
	t_node		*noda;
	t_node		*nodb;

	noda = C_NODE(t_node, lsta);
	nodb = C_NODE(t_node, lstb);
	return (-(ft_strcmp(noda->namtyp.d_name, nodb->namtyp.d_name)));
}

int				cmp_time(t_dlst *lsta, t_dlst *lstb)
{
	t_node		*noda;
	t_node		*nodb;
	int			res;

	noda = C_NODE(t_node, lsta);
	nodb = C_NODE(t_node, lstb);
	res = (noda->statfile.st_mtimespec.tv_sec
			> nodb->statfile.st_mtimespec.tv_sec ? 0 : 1);
	return (res);
}
