/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_clear_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 18:48:13 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/02/04 17:12:46 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				clear_head(t_dlst *head)
{
	t_dlst			*it;
	t_node			*tmp;

	it = head->next;
	while (it != head)
	{
		tmp = C_NODE(t_node, it);
		free(tmp->path);
		dlst_del_entry(it);
		it = head->next;
	}
}
