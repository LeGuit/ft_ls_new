/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 13:10:11 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/02/04 19:27:54 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_LS_H
# define _FT_LS_H

# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <stdio.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <dirent.h>
# include "libft/includes/libft.h"

# define OPT_L				(1u << 0)
# define OPT_UR				(1u << 1)
# define OPT_R				(1u << 2)
# define OPT_A				(1u << 3)
# define OPT_T				(1u << 4)
# define OPT_G				(1u << 5)
# define OPT_ALL			((1u << 6) - 1)
# define OPT_MD				(1u << 7)
# define BUF_LINK_SIZE		128
# define PATH_SIZE			4096
# define MAJOR(dev)			((int)(((unsigned int)(dev) >> 24) & 0xFF))
# define MINOR(dev)			((int)((dev) & 0xFFFFFF))

typedef struct		s_info
{
	t_dlst			headfile;
	int				opt;
	size_t			maxlink;
	size_t			maxoct;
	size_t			maxusr;
	size_t			maxgrp;
	size_t			total;
	int				maxmaj;
	int				maxmin;
}					t_info;

typedef	struct		s_node
{
	t_dlst			dlst;
	char			*path;
	struct dirent	namtyp;
	struct stat		statfile;
}					t_node;

void				ft_get_dir(char *filename, t_info *info);
void				ft_fetch_lst(DIR *dirp, char *filename, t_dlst *headfile,
					t_dlst *headdir);
void				clear_head(t_dlst *head);
void				sort_merge_lst(t_dlst *head, t_info *info);
int					parse_opt(char *av, t_info *info);
void				ft_size(t_info *info);
void				ft_padding(t_info *info);
void				ft_exit_parse(char illopt);
void				ft_error_dir(void);
void				ft_error_malloc(void);
void				print_files(t_info *info);
void				print_stat(t_node *file, t_info *info);
void				print_filename(t_node *tmp, t_info *info);
void				get_color(t_info *info, t_node *node);
int					cmp_lexi(t_dlst *lsta, t_dlst *lstb);
int					cmp_lexi_rev(t_dlst *lsta, t_dlst *lstb);
int					cmp_time(t_dlst *lsta, t_dlst *lstb);
void				free_node(t_node *node);
void				reset_max_info(t_info *info);

//DEBUG
void				print_info(t_info *info);
void				print_max(t_info *info);
void				print_dir(t_dlst *headdir);
#endif
