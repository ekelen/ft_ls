/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 20:38:23 by ekelen            #+#    #+#             */
/*   Updated: 2017/04/10 21:17:22 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		zero_entry(t_ls *new)
{
	new->etype = '0';
	new->hlinks = 0;
	new->size = 0;
	ft_bzero(new->uid_name, NAME_MAX);
	ft_bzero(new->grp_name, NAME_MAX);
	new->path = NULL;
	new->name = NULL;
	ft_bzero(new->linkname, PATH_MAX);
	new->no_dir = 0;
	new->is_rel = 0;
	new->maj = 0;
	new->min = 0;
	new->blkct = 0;
	new->time = NULL;
	new->left = NULL;
	new->right = NULL;
	return ;
}

t_ls		*new_entry(t_dir *cwd, struct dirent *dp)
{
	t_ls *new;

	new = (t_ls *)ft_memalloc(sizeof(t_ls));
	zero_entry(new);
	new->path = ft_catpath(cwd->path, dp->d_name);
	new->name = ft_strdup(dp->d_name);
	new->no_dir = 0;
	return (new);
}

t_ls		*new_file_entry(t_dir *cwd, char *s)
{
	t_ls *new;

	(void)cwd;
	new = (t_ls *)ft_memalloc(sizeof(t_ls));
	zero_entry(new);
	new->path = ft_strdup(s);
	new->name = ft_strdup(s);
	new->no_dir = 1;
	return (new);
}

void		zero_dir(t_dir *cwd, char *path)
{
	ft_bzero(cwd->path, PATH_MAX);
	ft_strcpy(cwd->path, path);
	cwd->file_dir = 0;
	cwd->n = 0;
	cwd->contents = 0;
	cwd->tree = NULL;
	return ;
}
