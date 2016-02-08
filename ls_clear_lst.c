/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_clear_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 18:48:13 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/02/08 21:52:47 by gwoodwar         ###   ########.fr       */
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
		free(tmp);
		it = head->next;
	}
	dlst_init(head);
}

void				clear_tab(char **tab)
{
	int				i;

	i = 0;
	while (tab[i] != 0)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
