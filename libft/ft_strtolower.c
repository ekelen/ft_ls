/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtolower.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 19:50:35 by ekelen            #+#    #+#             */
/*   Updated: 2017/04/10 20:33:57 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtolower(char *s)
{
	int		i;
	char	*s2;

	if (!s)
		return (NULL);
	i = 0;
	s2 = ft_strdup(s);
	while (s2[i])
	{
		*(s2 + i) = ft_tolower(*(s2 + i));
		i++;
	}
	return (s2);
}
