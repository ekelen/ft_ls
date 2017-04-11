/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 22:13:21 by ekelen            #+#    #+#             */
/*   Updated: 2017/04/10 22:13:22 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				rev_args(t_opt *e, char **s)
{
	int i;
	int j;

	if (!(s) || !e->paths)
		error("rev_args");
	i = 0;
	j = e->paths - 1;
	while (s[i])
	{
		if (i != j)
			str_switch(&s[j], &s[i]);
		i++;
		j--;
	}
	return (1);
}

static void		sort_args_stp(t_opt *e, char **s, int i)
{
	struct stat		stp;
	struct stat		stp2;

	if ((!(stat(s[i], &stp)) && !(stat(s[i + 1], &stp2))) \
				|| (!(lstat(s[i], &stp) && !(lstat(s[i + 1], &stp2)))))
	{
		if (e->us)
		{
			if (stp.st_size < stp2.st_size)
				str_switch(&s[i], &s[i + 1]);
		}
		else if (e->t)
		{
			if (stp.SMT < stp2.SMT)
				str_switch(&s[i], &s[i + 1]);
			else if (stp.SMT == stp2.SMT && stp.SMS < stp2.SMS)
				str_switch(&s[i], &s[i + 1]);
		}
	}
	return ;
}

int				sort_args(t_opt *e, char **s)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (j < e->paths)
	{
		i = 0;
		while (i + 1 < e->paths - j)
		{
			sort_args_stp(e, s, i);
			i++;
		}
		j++;
	}
	if (e->r)
		rev_args(e, s);
	extract_files(e, s);
	return (1);
}

int				sort_args_ascii(t_opt *e, char **s)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < e->paths)
	{
		i = 0;
		while (i + 1 < e->paths - j)
		{
			if (ft_ustrcmp(s[i], s[i + 1]) > 0)
				str_switch(&s[i], &s[i + 1]);
			i++;
		}
		j++;
	}
	print_errors(e, s);
	sort_args(e, s);
	return (1);
}
