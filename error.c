/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 20:40:01 by ekelen            #+#    #+#             */
/*   Updated: 2017/04/10 20:40:03 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		usage_err(char c)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("\nusage: ./ft_ls ", 2);
	ft_putstr_fd(VALID_OPT, 2);
	ft_putstr_fd(" [file ...]\n", 2);
	exit(1);
}

void		error(char *s)
{
	ft_printf("ft_ls: ");
	perror(s);
}

void		print_errors(t_opt *e, char **s)
{
	int			i;
	struct stat stp;

	i = 0;
	while (i < e->paths)
	{
		if ((stat(s[i], &stp)) && ((lstat(s[i], &stp))))
		{
			e->errs++;
			error(s[i]);
		}
		i++;
	}
	return ;
}
