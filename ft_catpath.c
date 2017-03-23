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

	dlen = ft_strlen(dir);
	nlen = ft_strlen(name);
	path = malloc(sizeof(char) * (dlen + nlen + 2));
	ft_bzero(path, dlen + nlen + 2);
	ft_strcpy(path, dir);
	ft_strcat(path, "/");
	ft_strcat(path, name);
	return(path);
}