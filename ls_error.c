/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 18:20:19 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/02/08 19:17:51 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_exit_parse(char illopt)
{
	ft_putstr_fd("ft_ls : illegal option -- ", 2);
	ft_putchar_fd(illopt, 2);
	ft_putstr_fd("\nusage: ft_ls [-l1SRrat] [file ...]\n", 2);
	exit(0);
}

void			ft_error_dir(char *illdir)
{
	char		*cursor;
	int			i;

	i = ft_strlen(illdir);
	ft_putstr_fd("ft_ls: ", 2);
	cursor = illdir;
	if (ft_strchr(illdir, '/'))
	{
		while (i--)
		{
			if (illdir[i] == '/')
			{
				cursor = &illdir[i];
				break ;
			}
		}
		ft_putstr_fd(cursor + 1, 2);
	}
	else
		ft_putstr_fd(illdir, 2);
	perror(" ");
}

void			ft_error_malloc(void)
{
	perror("ft_ls: ");
	exit(0);
}
