/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_cmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 16:43:41 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/02/04 17:22:44 by gwoodwar         ###   ########.fr       */
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

	noda = C_NODE(t_node, lsta);
	nodb = C_NODE(t_node, lstb);
	return (ctime(&noda->statfile.st_mtimespec.tv_sec) - 
			ctime(&nodb->statfile.st_mtimespec.tv_sec));
}
