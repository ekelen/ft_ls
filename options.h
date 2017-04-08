#ifndef OPTIONS_H
# define OPTIONS_H

typedef struct	s_opt
{
	int				one;
	int				a;
	int				d;  // directories treated as files, not directories to be searched
	int				g;
	int				l;
	int				o;
	int				p;	// add trailing slash to directories
	int				r;	// reverse
	int				t;	// time
	int				u;  //access time
	int				ua; // hide . ..
	int				ug;	// color output
	int				ur;	// recursive
	int				us; // sort by size
	int				ut; // show full time in -l format
	int				files;
	int				dirs;
	int				errs;
}				t_opt;

typedef struct s_access
{
	char				ruser;
	char				wuser;
	char				xuser;
	char				rgrp;
	char				wgrp;
	char				xgrp;
	char				roth;
	char				woth;
	char				xoth;
}				t_access;

int						zero_opt(t_opt *e);
int						init_opts(char *s, t_opt *e);

#endif
