/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 21:16:42 by ekelen            #+#    #+#             */
/*   Updated: 2017/04/10 21:16:44 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <errno.h>
# include <limits.h>
# include <sys/acl.h>
# include "./printf/includes/ft_printf.h"
# include "./libft/libft.h"
# include "color.h"
# include "time.h"
# include "options.h"
# include "error.h"
# include "padding.h"

typedef struct		s_ls
{
	char			etype;
	long			hlinks;
	size_t			size;
	char			uid_name[NAME_MAX];
	char			grp_name[NAME_MAX];
	char			*path;
	char			*name;
	char			linkname[PATH_MAX];
	int				no_dir;
	int				is_rel;
	int				maj;
	int				min;
	unsigned int	blkct;
	t_color			color;
	t_access		acc;
	char			acl;
	t_time			*time;
	struct s_ls		*right;
	struct s_ls		*left;
}					t_ls;

typedef struct		s_dir
{
	char			path[PATH_MAX];
	size_t			n;
	t_pad			pad;
	t_ls			*tree;
	int				file_dir;
	int				contents;
}					t_dir;

/*
** Utilities
*/

char				*ft_catpath(char *dir, char *name);
char				*ft_strexclude(char *path, char *name);
int					str_switch(char **s1, char **s2);
void				place_left(t_ls *new, t_ls **tt, t_ls *tn);
void				place_right(t_ls *new, t_ls **tt, t_ls *tn);

/*
** Initialize objects
*/

t_ls				*new_entry(t_dir *cwd, struct dirent *dp);
t_ls				*new_file_entry(t_dir *cwd, char *s);
void				zero_dir(t_dir *cwd, char *path);

/*
** Eval args
*/

int					sort_args_ascii(t_opt *e, char **s);
int					extract_files(t_opt *e, char **s);

/*
** Open
*/

int					init_dir_open(t_opt *e, char *d_path, int *first);
void				print_errors(t_opt *e, char **s);
void				open_helper(t_opt *e, t_dir *cwd);

/*
** Global/directory settings
*/

int					get_padding(t_dir *cwd, t_ls *ls, t_opt *e);
int					get_total(t_ls *entry, t_dir *cwd);

/*
** Entry metadata
*/

int					get_type(t_opt *e, t_dir *cwd, t_ls *new, struct stat *stp);
int					get_mtime(struct stat stp, t_ls *new, t_opt *e);
int					get_color(t_ls *new, t_opt *e);

/*
** Sort and print
*/

void				sort_entries(t_opt *e, t_ls **tree, t_ls *new);
int					print_time(t_opt *e, t_ls *entry);
void				tree_pr(t_ls *entry, t_dir cwd, t_opt *e);
void				tree_prrv(t_ls *entry, t_dir cwd, t_opt *e);
void				pr_str(char *print, size_t width, int align);
void				pr_dec(size_t print, size_t width, size_t align);

/*
** Free
*/

void				tree_del(t_ls *tree);
void				free_args(char **args, int i);

#endif
