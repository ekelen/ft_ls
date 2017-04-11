/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 21:27:14 by ekelen            #+#    #+#             */
/*   Updated: 2017/04/10 21:28:23 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONS_H
# define OPTIONS_H

/*
** MANDATORY FUNCTIONALITY:
**
**    -a : Include directory entries whose names begin with a dot (.).
**    -l : (The lowercase letter ``ell''.)  List in long format.
**				If the output is to a terminal, a total sum for all the file
**				sizes is output on a line before the long listing.
**    -r : Reverse the order of the sort to get reverse lexicographical
**				order or the oldest entries first (or
**				largest files last, if combined with sort by size
**    -R : Recursively list subdirectories encountered.
**	  -t : Sort by time modified (most recently modified first) before
**			sorting the operands by lexicographi-
**			cal order.
**
** BONUS FUNCTIONALITY:
**
**	  -A : List all entries except for . and ...  Always set for the super-user.
**    -d : Directories are listed as plain files (not searched recursively).
**    -g : This option is only available for compatibility with POSIX; it is
**			 used to display the group name
**           in the long (-l) format output (the owner name is suppressed).
**    -G : Enable colorized output.  This option is equivalent to defining
**			CLICOLOR in the environment.
**    -o : List in long format, but omit the group id.
**    -p : Write a slash (`/') after each filename if that file is a directory.
**    -S : Sort files by size
**	  -T : When used with the -l (lowercase letter ``ell'') option, display
**			complete time information for the file, including month, day, hour,
**			minute, second, and year.
**    -u : Use time of last access, instead of last modification of the
**			file for sorting (-t) or long print-
**			ing (-l).
*/

typedef struct		s_opt
{
	int				one;
	int				a;
	int				d;
	int				g;
	int				l;
	int				o;
	int				p;
	int				r;
	int				t;
	int				u;
	int				ua;
	int				ug;
	int				ur;
	int				us;
	int				ut;
	int				paths;
	int				files;
	int				dirs;
	int				errs;
}					t_opt;

typedef struct		s_access
{
	char			ruser;
	char			wuser;
	char			xuser;
	char			rgrp;
	char			wgrp;
	char			xgrp;
	char			roth;
	char			woth;
	char			xoth;
}					t_access;

void				zero_opt(t_opt *e);
int					init_opts(char *s, t_opt *e);

#endif
