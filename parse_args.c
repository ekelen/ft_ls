#include "ft_ls.h"

static int		parse_bonus(char s, t_opt *flags)
{
	if (s == 'G')
		flags->ug = 1;
	else if (s == 'g')
		flags->g = 1;
	else if (s == 'p')
		flags->p = 1;
	else if (s == 'S')
		flags->us = 1;
	else if (s == 'o')
		flags->o = 1;
	else
		return (0);
	 ft_printf("%c : ", s);
	 ft_printf("<< FLAGS\n");
	return (1);
}


int		init_opts(char *s, t_opt *flags)
{
	s++;
	while (*s)
	{
		if (ft_strchr(s, 'a'))
			flags->a = 1;
		else if (ft_strchr(s, 't'))
			flags->t = 1;
		else if (ft_strchr(s, 'R'))
			flags->ur = 1;
		else if (ft_strchr(s, 'r'))
			flags->r = 1;
		else if (ft_strchr(s, 'l'))
			flags->l = 1;
		else
		{
			if (!(parse_bonus(*s, flags)))
			{
				ft_printf(ERR_OPT, *s);
				return (0);
			}
		}
		ft_printf("-%c ", *s);
		s++;
	}
	return (1);
}