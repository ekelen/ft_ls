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
	else
		return (0);
	 //ft_printf("%c : ", s);
	 //ft_printf("<< e\n");
	return (1);
}


int		init_opts(char *s, t_opt *e)
{
	s++;
	while (*s)
	{
		if (ft_strchr(s, 'a'))
			e->a = 1;
		else if (ft_strchr(s, 't'))
			e->t = 1;
		else if (ft_strchr(s, 'R'))
			e->ur = 1;
		else if (ft_strchr(s, 'r'))
			e->r = 1;
		else if (ft_strchr(s, 'l'))
			e->l = 1;
		else
		{
			if (!(parse_bonus(*s, e)))
			{
				ft_printf(ERR_OPT, *s);
				return (0);
			}
		}
		//ft_printf("-%c ", *s);
		s++;
	}
	return (1);
}

int		zero_opt(t_opt *e)
{
	if (!e)
	{
		return ((ft_printf("ERROR!\n")));
	}
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
	return (1);
}