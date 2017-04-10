/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ustrcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 21:32:45 by ekelen            #+#    #+#             */
/*   Updated: 2016/12/08 16:25:25 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_ustrcmp(char *s1, char *s2)
{
	int difference;
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	difference = (*(unsigned char *)s1 - *(unsigned char *)s2);
	return (difference);
}
