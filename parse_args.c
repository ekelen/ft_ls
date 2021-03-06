/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 21:43:23 by ekelen            #+#    #+#             */
/*   Updated: 2017/04/10 21:43:50 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		parse_bonus_2(t_opt *e, char *s)
{
	if (*s == 'S')
		e->us = 1;
	else if (*s == 'T')
		e->ut = 1;
	else if (*s == 'o')
	{
		e->l = 1;
		e->o = 1;
	}
	else if (*s == '1')
	{
		if (!ft_strchr("gl", *s))
			e->l = 0;
		e->one = 1;
	}
	else if (*s == 'u')
		e->u = 1;
	else
		return (0);
	return (1);
}

static int		parse_bonus(t_opt *e, char *s)
{
	if (*s == 'A')
		e->ua = 1;
	else if (*s == 'G')
		e->ug = 1;
	else if (*s == 'g')
	{
		e->l = 1;
		e->g = 1;
	}
	else if (*s == 'd')
		e->d = 1;
	else if (*s == 'p')
		e->p = 1;
	else if (!parse_bonus_2(e, s))
		return (0);
	return (1);
}

static int		init_opts_2(char *s, t_opt *e)
{
	if (*s == 'a')
		e->a = 1;
	else if (*s == 't')
		e->t = 1;
	else if (*s == 'R')
		e->ur = 1;
	else if (*s == 'r')
		e->r = 1;
	else if (*s == 'l')
		e->l = 1;
	else
		return (0);
	return (1);
}

int				init_opts(char *s, t_opt *e)
{
	static int hyphen_as_arg = 1;

	s++;
	while (*s)
	{
		if (*s == '-')
		{
			if (hyphen_as_arg && *(s + 1))
				usage_err(*s);
			if (!hyphen_as_arg)
				return (0);
			hyphen_as_arg = 0;
		}
		else if (!(init_opts_2(s, e)))
		{
			if (!(parse_bonus(e, s)))
				usage_err(*s);
		}
		s++;
	}
	return (1);
}

void			zero_opt(t_opt *e)
{
	e->one = 0;
	e->a = 0;
	e->d = 0;
	e->g = 0;
	e->l = 0;
	e->o = 0;
	e->p = 0;
	e->r = 0;
	e->ug = 0;
	e->ur = 0;
	e->us = 0;
	e->ut = 0;
	e->t = 0;
	e->u = 0;
	e->paths = 0;
	e->files = 0;
	e->dirs = 0;
	e->errs = 0;
	return ;
}
