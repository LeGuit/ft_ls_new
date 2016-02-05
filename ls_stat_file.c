/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_stat_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 11:35:16 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/02/05 14:22:51 by gwoodwar         ###   ########.fr       */
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

static void		print_mode_file(struct stat statfile, t_node *file)
{
	char		buf[10];
	char		bufxat[4096];

	buf[0] = (statfile.st_mode & (S_IRUSR) ? 'r' : '-');
	buf[1] = (statfile.st_mode & (S_IWUSR) ? 'w' : '-');
	buf[2] = (statfile.st_mode & (S_IXUSR) ? 'x' : '-');
	buf[3] = (statfile.st_mode & (S_IRGRP) ? 'r' : '-');
	buf[4] = (statfile.st_mode & (S_IWGRP) ? 'w' : '-');
	buf[5] = (statfile.st_mode & (S_IXGRP) ? 'x' : '-');
	buf[6] = (statfile.st_mode & (S_IROTH) ? 'r' : '-');
	buf[7] = (statfile.st_mode & (S_IWOTH) ? 'w' : '-');
	if (statfile.st_mode & (S_ISVTX))
		buf[8] = 's';
	else if (statfile.st_mode & (S_IXOTH))
		buf[8] = 'x';
	else
		buf[8] = '-';
	buf[9] = 0;
	if (listxattr(file->path, bufxat, 4096, XATTR_NOFOLLOW))
		ft_printf("%s@", buf);
	else
		ft_printf("%s ", buf);
}

static void		print_time(struct stat statfile)
{
	char		buf[19];
	char		*ptrctime;
	time_t		ltime;

	ptrctime = ctime(&statfile.st_mtimespec.tv_sec);
	time(&ltime);
	if (ABS(ltime - statfile.st_mtimespec.tv_sec) < 1552000)
	{
		ft_strncpy(buf, ptrctime + 4, 12);
		buf[12] = 0;
	}
	else
	{
		ft_strncpy(buf, ptrctime + 4, 7);
		buf[7] = ' ';
		buf[8] = 0;
		ft_strncat(buf, ptrctime + 20, 4);
		buf[12] = 0;
	}
	ft_printf("%s ", buf);
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
			//	ft_printf("%s%s\033[39m -> %s\n", tmp->color, filename, buf);
			ft_printf("%s -> %s\n", file->namtyp.d_name, buf);
		}
		else
			ft_printf(/*%s%s*/"%s\n"/*\033[39m\033[49m\n",
					tmp->background, tmp->color*/, file->namtyp.d_name);
	}
	else
		ft_printf(/*%s%s*/"%s\n"/*\033[39m\033[49m\n",
				tmp->background, tmp->color*/, file->namtyp.d_name);
}

void			print_stat(t_node *file, t_info *info)
{
	print_type_file(file->statfile);
	print_mode_file(file->statfile, file);
	ft_printf(" %*d ", info->maxlink, file->statfile.st_nlink);
	ft_printf("%-*s  ", info->maxusr, getpwuid(file->statfile.st_uid)->pw_name);
	if (getgrgid(file->statfile.st_gid))
		ft_printf("%-*s  ", info->maxgrp, getgrgid(file->statfile.st_gid)->gr_name);
	else
		ft_printf("%-*d  ", info->maxgrp, file->statfile.st_gid);
	if (S_ISBLK(file->statfile.st_mode) || S_ISCHR(file->statfile.st_mode))
		ft_printf("%*ld, %*ld ", info->maxmaj,
				MAJOR(file->statfile.st_rdev), info->maxmin, MINOR(file->statfile.st_rdev));
	else
		ft_printf("%*d ", info->maxoct, file->statfile.st_size);
	print_time(file->statfile);
	print_filename(file, info);
}
