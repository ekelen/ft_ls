/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_get_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 22:28:25 by ekelen            #+#    #+#             */
/*   Updated: 2017/04/10 22:28:27 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			get_size(t_dir *cwd, t_ls *new, struct stat *stp)
{
	new->blkct = stp->st_blocks;
	new->hlinks = stp->st_nlink;
	if (ft_strequ(new->name, ".") || ft_strequ(new->name, ".."))
		new->is_rel = 1;
	else
		new->is_rel = 0;
	if (new->etype == 'c' || new->etype == 'b')
	{
		new->maj = major(stp->st_rdev);
		new->min = minor(stp->st_rdev);
	}
	else
		new->size = stp->st_size;
	if (!new->no_dir)
		cwd->n += new->blkct;
	return (1);
}

int			get_access(t_ls *new, struct stat *stp)
{
	new->acc.ruser = (stp->st_mode & S_IRUSR) ? 'r' : '-';
	new->acc.wuser = (stp->st_mode & S_IWUSR) ? 'w' : '-';
	new->acc.xuser = (stp->st_mode & S_IXUSR) ? 'x' : '-';
	new->acc.rgrp = (stp->st_mode & S_IRGRP) ? 'r' : '-';
	new->acc.wgrp = (stp->st_mode & S_IWGRP) ? 'w' : '-';
	new->acc.xgrp = (stp->st_mode & S_IXGRP) ? 'x' : '-';
	new->acc.roth = (stp->st_mode & S_IROTH) ? 'r' : '-';
	new->acc.woth = (stp->st_mode & S_IWOTH) ? 'w' : '-';
	new->acc.xoth = (stp->st_mode & S_IXOTH) ? 'x' : '-';
	if (stp->st_mode & S_ISUID)
		new->acc.xuser = new->acc.xuser == '-' ? 'S' : 's';
	if (stp->st_mode & S_ISGID)
		new->acc.xgrp = new->acc.xgrp == '-' ? 'S' : 's';
	if (stp->st_mode & S_IXOTH)
		new->acc.xoth = (stp->st_mode & S_ISVTX) ? 't' : 'x';
	else if (stp->st_mode & S_ISVTX)
		new->acc.xoth = 'T';
	return (1);
}

int			get_acl_link_id(t_ls *new, struct stat *stp)
{
	char tmp[PATH_MAX];

	ft_bzero(new->grp_name, NAME_MAX);
	ft_bzero(new->uid_name, NAME_MAX);
	ft_strcpy(new->grp_name, getgrgid(stp->st_gid)->gr_name);
	ft_strcpy(new->uid_name, getpwuid(stp->st_uid)->pw_name);
	if (listxattr(new->path, NULL, 0, XATTR_NOFOLLOW) > 0)
		new->acl = '@';
	else if (acl_get_file(new->path, ACL_TYPE_EXTENDED))
		new->acl = '+';
	else
		new->acl = ' ';
	if (new->etype == 'l')
	{
		ft_bzero(tmp, PATH_MAX);
		readlink(new->path, tmp, PATH_MAX);
		ft_strcpy(new->linkname, tmp);
	}
	return (1);
}

int			get_type(t_opt *e, t_dir *cwd, t_ls *new, struct stat *stp)
{
	if (S_ISREG(stp->st_mode))
		new->etype = '-';
	else if (S_ISDIR(stp->st_mode))
		new->etype = 'd';
	else if (S_ISCHR(stp->st_mode))
		new->etype = 'c';
	else if (S_ISBLK(stp->st_mode))
		new->etype = 'b';
	else if (S_ISFIFO(stp->st_mode))
		new->etype = 'p';
	else if (S_ISLNK(stp->st_mode))
		new->etype = 'l';
	else if (S_ISSOCK(stp->st_mode))
		new->etype = 's';
	else
		return (0);
	get_access(new, stp);
	get_size(cwd, new, stp);
	get_mtime(*stp, new, e);
	get_acl_link_id(new, stp);
	sort_entries(e, &(cwd->tree), new);
	return (1);
}
