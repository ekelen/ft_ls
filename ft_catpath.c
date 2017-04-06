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

char	*ft_catpath(char *dir, char *name)
{
	char *path;
	size_t dlen;
	size_t nlen;
	int i;

	ft_printf("dir: %s, name: %s\n", dir, name);
	dlen = ft_strlen(dir);
	nlen = ft_strlen(name);
	i = dlen;
	if (dir[i - 1] == '/')
	{
		ft_printf("Found a slash\n");
		dlen--;
	}
	path = malloc(sizeof(char) * (dlen + nlen + 2));
	ft_bzero(path, dlen + nlen + 2);
	ft_strncpy(path, dir, dlen);
	ft_strcat(path, "/");
	ft_strcat(path, name);
	//ft_printf("path: %s\n", path);
	return(path);
}