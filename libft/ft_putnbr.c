/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 09:57:08 by ekelen            #+#    #+#             */
/*   Updated: 2016/12/09 16:02:52 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	long	n_long;

	n_long = n;
	if (n_long < 0)
	{
		ft_putchar('-');
		n_long = -n_long;
	}
	if (n_long >= 10)
	{
		ft_putnbr(n_long / 10);
		ft_putnbr(n_long % 10);
	}
	else
		ft_putchar(n_long + '0');
}
