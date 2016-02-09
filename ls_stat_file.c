/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_stat_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 11:35:16 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/02/09 14:00:30 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft/includes/libft.h"

static void		print_type_file(struct stat statfile)
{
	if (S_ISREG(statfile.st_mode))
		ft_putchar('-');
	else if (S_ISSOCK(statfile.st_mode))
		ft_putchar('s');
	else if (S_ISLNK(statfile.st_mode))
		ft_putchar('l');
	else if (S_ISFIFO(statfile.st_mode))
		ft_putchar('p');
	else if (S_ISCHR(statfile.st_mode))
		ft_putchar('c');
	else if (S_ISDIR(statfile.st_mode))
		ft_putchar('d');
	else if (S_ISBLK(statfile.st_mode))
		ft_putchar('b');
}

static void		print_year(struct stat statfile)
{
	char		buf[19];
	char		*ptrctime;

	ptrctime = ctime(&statfile.st_mtimespec.tv_sec);
	if ((int)statfile.st_mtimespec.tv_sec > 0)
	{
		ft_strncpy(buf, ptrctime + 4, 7);
		buf[7] = ' ';
		buf[8] = 0;
		ft_strncat(buf, ptrctime + 20, 4);
		buf[12] = 0;
	}
	else
	{
		ft_strcpy(buf, "Jan  1  10000\0");
	}
	ft_printf("%s ", buf);
}

static void		print_time(struct stat statfile)
{
	char		buf[19];
	char		*ptrctime;
	time_t		ltime;

	ptrctime = ctime(&statfile.st_mtimespec.tv_sec);
	time(&ltime);
	if (ABS(ltime - statfile.st_mtimespec.tv_sec) < 15552000
			&& statfile.st_mtimespec.tv_sec > 0)
	{
		ft_strncpy(buf, ptrctime + 4, 12);
		buf[12] = 0;
		ft_printf("%s ", buf);
	}
	else
		print_year(statfile);
}

void			print_filename(t_node *file, t_info *info)
{
	char		buf[BUF_LINK_SIZE];

	ft_bzero(buf, BUF_LINK_SIZE);
	if (GET(info->opt, OPT_L))
	{
		if (S_ISLNK(file->statfile.st_mode))
		{
			readlink(file->path, buf, BUF_LINK_SIZE - 1);
			ft_printf("%s -> %s\n", file->namtyp.d_name, buf);
		}
		else
			ft_printf("%s\n", file->namtyp.d_name);
	}
	else
		ft_printf("%s\n", file->namtyp.d_name);
}

void			print_stat(t_node *file, t_info *info)
{
	print_type_file(file->statfile);
	print_mode_file(file->statfile, file);
	ft_printf(" %*d ", info->maxlink, file->statfile.st_nlink);
	if (getpwuid(file->statfile.st_uid))
		ft_printf("%-*s  ", info->maxusr,
				getpwuid(file->statfile.st_uid)->pw_name);
	else
		ft_printf("%-*d  ", info->maxusr, file->statfile.st_uid);
	if (getgrgid(file->statfile.st_gid))
		ft_printf("%-*s  ", info->maxgrp,
				getgrgid(file->statfile.st_gid)->gr_name);
	else
		ft_printf("%-*d  ", info->maxgrp, file->statfile.st_gid);
	if (S_ISBLK(file->statfile.st_mode) || S_ISCHR(file->statfile.st_mode))
		ft_printf("%*ld, %*ld ", info->maxmaj,
				MAJOR(file->statfile.st_rdev),
				info->maxmin, MINOR(file->statfile.st_rdev));
	else
		ft_printf("%*d ", info->maxoct, file->statfile.st_size);
	print_time(file->statfile);
	print_filename(file, info);
}
