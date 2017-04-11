/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 21:40:33 by ekelen            #+#    #+#             */
/*   Updated: 2017/04/10 21:40:36 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		dev_pad(t_dir *cwd, t_ls *ls)
{
	if (ls->etype == 'b' || ls->etype == 'c')
	{
		if (ft_numlen(ls->size) >= PAD.size)
			PAD.size = ft_numlen(ls->size);
		if (ft_numlen(ls->min) >= PAD.min)
			PAD.min = ft_numlen(ls->min);
		if (ft_numlen(ls->maj) >= PAD.maj)
			PAD.maj = ft_numlen(ls->maj);
		if (PAD.size <= PAD.maj + PAD.min + 1)
			PAD.size = PAD.maj + PAD.min + 1;
		return (1);
	}
	return (0);
}

static int		init_pad(t_dir *cwd, t_ls *ls, t_opt *e)
{
	if (!ls)
		return (0);
	if (ls->left)
		init_pad(cwd, ls->left, e);
	if (e->l)
	{
		if (ft_numlen(ls->hlinks) >= PAD.lnk)
			PAD.lnk = ft_numlen(ls->hlinks);
		if (ft_strlen(ls->uid_name) >= PAD.own)
			PAD.own = ft_strlen(ls->uid_name);
		if (ft_strlen(ls->grp_name) >= PAD.grp)
			PAD.grp = ft_strlen(ls->grp_name);
		if (!(dev_pad(cwd, ls)))
		{
			if (ft_numlen(ls->size) >= PAD.size)
				PAD.size = ft_numlen(ls->size);
		}
	}
	if (ls->right)
		init_pad(cwd, ls->right, e);
	return (1);
}

int				get_padding(t_dir *cwd, t_ls *ls, t_opt *e)
{
	PAD.ext = 1;
	PAD.lnk = 0;
	PAD.own = 0;
	PAD.grp = 0;
	PAD.size = 0;
	PAD.mon = 4;
	PAD.dat = 3;
	PAD.timyr = 5;
	PAD.min = 0;
	PAD.maj = 0;
	init_pad(cwd, ls, e);
	return (1);
}
