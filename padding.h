/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 21:40:55 by ekelen            #+#    #+#             */
/*   Updated: 2017/04/10 21:40:56 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PADDING_H
# define PADDING_H

# define PAD cwd->pad

typedef struct	s_pad
{
	size_t			acc;
	size_t			ext;
	size_t			lnk;
	size_t			own;
	size_t			grp;
	size_t			size;
	size_t			mon;
	size_t			dat;
	size_t			timyr;
	size_t			name;
	size_t			min;
	size_t			maj;
}				t_pad;

#endif
