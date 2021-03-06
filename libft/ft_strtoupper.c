/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoupper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 19:50:35 by ekelen            #+#    #+#             */
/*   Updated: 2017/04/10 20:35:55 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtoupper(char *s)
{
	int i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		*(s + i) = ft_toupper(*(s + i));
		i++;
	}
	return (s);
}
