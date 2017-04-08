#include "ft_ls.h"

static int		parse_bonus(char s, t_opt *e)
{
	if (s == 'G')
		e->ug = 1;
	else if (s == 'g')
		e->g = 1;
	else if (s == 'p')
		e->p = 1;
	else if (s == 'S')
		e->us = 1;
	else if (s == 'o')
		e->o = 1;
	else if (s == '1')
		e->one = 1;
	else
		return (0);
	return (1);
}

int		init_opts(char *s, t_opt *e)
{
	static int hyphen_as_arg = 1;
	s++;
	while (*s)
	{
		if (*s == 'a')
			e->a = 1;
		else if (*s == '-')
		{
			if (hyphen_as_arg && *(s + 1))
				usage_err(*s);
			if (!hyphen_as_arg)
				return(0);
			hyphen_as_arg = 0;
		}
		else if (*s == 't')
			e->t = 1;
		else if (*s == 'R')
			e->ur = 1;
		else if (*s == 'r')
			e->r = 1;
		else if (*s == 'l')
			e->l = 1;
		else
		{
			if (!(parse_bonus(*s, e)))
				usage_err(*s);
		}
		s++;
	}
	return (1);
}

int		zero_opt(t_opt *e)
{
	if (!e)
		error(1, "./ft_ls");
	e->one = 0;
	e->a = 0;
	e->g = 0;
	e->l = 0;
	e->o = 0;
	e->p = 0;
	e->r = 0;
	e->ug = 0;
	e->ur = 0;
	e->us = 0;
	e->t = 0;
	e->files = 0;
	e->dirs = 0;
	e->errs = 0;
	return (1);
}

