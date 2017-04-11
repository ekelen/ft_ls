/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 14:14:12 by ekelen            #+#    #+#             */
/*   Updated: 2017/04/10 20:37:00 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COLOR_H
# define FT_COLOR_H

# define FG_BLK		"\x1b[30m"
# define FG_RED		"\x1b[31m"
# define FG_GRN		"\x1b[32m"
# define FG_YEL		"\x1b[33m"
# define FG_BLU		"\x1b[34m"
# define FG_PNK		"\x1b[35m"
# define FG_CYN		"\x1b[36m"
# define FG_RESET	"\x1b[0m"

# define BG_BLK		"\x1b[40m"
# define BG_RED		"\x1b[41m"
# define BG_GRN		"\x1b[42m"
# define BG_YEL		"\x1b[43m"
# define BG_BLU		"\x1b[44m"
# define BG_PNK		"\x1b[45m"
# define BG_CYN		"\x1b[46m"
# define BG_RESET	"\x1b[49m"

# define FBG_RESET	"\x1b[49m\x1b[20m"

typedef struct			s_color
{
	char	fg[7];
	char	bg[7];
}						t_color;

#endif
