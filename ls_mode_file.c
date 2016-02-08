/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_mode_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 16:33:21 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/02/08 17:01:16 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		mode_buf2(mode_t st_mode)
{
	if (st_mode & (S_ISUID) && st_mode & (S_IXUSR))
		return ('s');
	else if (st_mode & (S_ISUID))
		return ('S');
	else if (st_mode & (S_IXUSR))
		return ('x');
	else
		return ('-');
}

static char		mode_buf5(mode_t st_mode)
{
	if (st_mode & (S_ISGID) && st_mode & (S_IXGRP))
		return ('s');
	else if (st_mode & (S_ISGID))
		return ('S');
	else if (st_mode & (S_IXGRP))
		return ('x');
	else
		return ('-');
}

static char		mode_buf8(mode_t st_mode)
{
	if (st_mode & (S_ISVTX) && st_mode & (S_IXOTH))
		return ('t');
	else if (st_mode & (S_ISVTX) && st_mode & ~(S_IXOTH))
		return ('T');
	else if (st_mode & (S_IXOTH))
		return ('x');
	else
		return ('-');
}

void			print_mode_file(struct stat statfile, t_node *file)
{
	char		buf[10];

	buf[0] = (statfile.st_mode & (S_IRUSR) ? 'r' : '-');
	buf[1] = (statfile.st_mode & (S_IWUSR) ? 'w' : '-');
	buf[2] = mode_buf2(statfile.st_mode);
	buf[3] = (statfile.st_mode & (S_IRGRP) ? 'r' : '-');
	buf[4] = (statfile.st_mode & (S_IWGRP) ? 'w' : '-');
	buf[5] = mode_buf5(statfile.st_mode);
	buf[6] = (statfile.st_mode & (S_IROTH) ? 'r' : '-');
	buf[7] = (statfile.st_mode & (S_IWOTH) ? 'w' : '-');
	buf[8] = mode_buf8(statfile.st_mode);
	buf[9] = 0;
	if (listxattr(file->path, 0, 0, 0) > 0)
		ft_printf("%s@", buf);
	else
		ft_printf("%s ", buf);
}
