/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 20:31:41 by ekelen            #+#    #+#             */
/*   Updated: 2017/04/10 20:31:43 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_numlen(unsigned int nbr)
{
	size_t num_len;

	num_len = 1;
	while (nbr >= 10)
	{
		nbr /= 10;
		num_len++;
	}
	return (num_len);
}
