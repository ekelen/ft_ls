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

char	*ft_catpath(char const *directory, char const *name)
{
	char		*path;
	size_t		len;

	if (!directory || !name)
	{
		ft_printf("Missing s1 or s2\n");
		return (NULL);
	}
	len = ft_strlen(directory) + ft_strlen(name);

	//ft_printf("Length of two strings : %ld\n", len);
	//ft_printf("Length allocated : %ld\n", len + 2);
	path = (char *)malloc(sizeof(char) * (len + 2));
	if (!path)
		return ((void *)0);
	ft_strcpy(path, directory);
	ft_strcat(path, "/");
	ft_strcat(path, name);
	return (path);
}
