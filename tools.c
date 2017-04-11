/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 13:34:04 by ekelen            #+#    #+#             */
/*   Updated: 2016/12/10 16:18:23 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	place_left(t_ls *new, t_ls **tt, t_ls *tn)
{
	(*tt) = (*tt)->left;
	if (!(*tt))
		tn->left = new;
}

void	place_right(t_ls *new, t_ls **tt, t_ls *tn)
{
	(*tt) = (*tt)->right;
	if (!(*tt))
	{
		tn->right = new;
	}
}

char	*ft_catpath(char *dir, char *name)
{
	char *path;
	size_t dlen;
	size_t nlen;
	int i;

	dlen = ft_strlen(dir);
	nlen = ft_strlen(name);
	i = dlen;
	if (dir[i - 1] == '/')
		dlen--;
	path = malloc(sizeof(char) * (dlen + nlen + 2));
	ft_bzero(path, dlen + nlen + 2);
	ft_strncpy(path, dir, dlen);
	ft_strcat(path, "/");
	ft_strcat(path, name);
	return(path);
}

char	*ft_strexclude(char *path, char *name)
{
	char *s;
	size_t plen;
	size_t nlen;

	plen = ft_strlen(path);
	nlen = ft_strlen(name);
	s = ft_strsub(path, 0, plen - nlen);
	return (s);
}

int 	str_switch(char **s1, char **s2)
{
	char *tmp;

	tmp = ft_strdup(*s1);
	ft_strdel(s1);
	*s1 = ft_strdup(*s2);
	ft_strdel(s2);
	*s2 = ft_strdup(tmp);
	ft_strdel(&tmp);
	return(1);
}