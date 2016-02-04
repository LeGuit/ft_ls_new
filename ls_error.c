/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 18:20:19 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/02/04 14:43:09 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_exit_parse(char illopt)
{
	ft_putstr_fd("ft_ls : illegal option -- ", 2);
	ft_putchar_fd(illopt, 2);
	ft_putstr_fd("\nusage: ft_ls [-lRratG] [file ...]\n", 2);
	exit(0);
}

void			ft_error_dir(void)
{
	perror("ft_ls: ");
}
