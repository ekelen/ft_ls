/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 21:23:54 by ekelen            #+#    #+#             */
/*   Updated: 2017/04/10 21:25:57 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	open_subdir(t_opt *e, t_dir cwd, t_ls *entry, int first)
{
	if (!entry)
		return ;
	if (entry->left)
		open_subdir(e, cwd, entry->left, first);
	if (e->ur && entry->etype == 'd' && !entry->is_rel)
		init_dir_open(e, entry->path, &first);
	if (entry->right)
		open_subdir(e, cwd, entry->right, first);
}

static void	open_subdir_rev(t_opt *e, t_dir cwd, t_ls *entry, int first)
{
	if (!entry)
		return ;
	if (entry->right)
		open_subdir_rev(e, cwd, entry->right, first);
	if (e->ur && entry->etype == 'd' && !entry->is_rel)
		init_dir_open(e, entry->path, &first);
	if (entry->left)
		open_subdir_rev(e, cwd, entry->left, first);
}

void		open_helper(t_opt *e, t_dir *cwd)
{
	if (e->l && cwd->contents)
		ft_printf("total %ld\n", cwd->n);
	get_padding(cwd, cwd->tree, e);
	if (e->r)
		tree_prrv(cwd->tree, *cwd, e);
	else
		tree_pr(cwd->tree, *cwd, e);
	if (e->r)
		open_subdir_rev(e, *cwd, cwd->tree, 0);
	else
		open_subdir(e, *cwd, cwd->tree, 0);
	return ;
}
