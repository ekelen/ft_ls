#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <time.h>
# include <stdio.h> //DELETE
# include <errno.h>
# include <limits.h>
# include "./printf/includes/ft_printf.h"
# include "./libft/libft.h"

# define FG_BLACK		"\x1b[30m"
# define FG_RED			"\x1b[31m"
# define FG_GREEN		"\x1b[32m"
# define FG_YELLOW		"\x1b[33m"
# define FG_BLUE		"\x1b[34m"
# define FG_MAGENTA		"\x1b[35m"
# define FG_CYAN		"\x1b[36m"
# define FG_DEFAULT		"\x1b[0m"

# define BG_BLACK		"\x1b[40m"
# define BG_RED			"\x1b[41m"
# define BG_GREEN		"\x1b[42m"
# define BG_YELLOW		"\x1b[43m"
# define BG_BLUE		"\x1b[44m"
# define BG_MAGENTA		"\x1b[45m"
# define BG_CYAN		"\x1b[46m"
# define BG_DEFAULT		"\x1b[49m"

# define FBG_DEFAULT	"\x1b[49m\x1b[20m"



typedef struct			s_color
{
	char	fg[7];
	char	bg[7];
}				t_color;

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


	//ft_printf("Test\n");

	//-l, -R, -a, -r and -t
	//l = "long"
	//-a = include things with a dot
	//-t == sort by time
	//-r == reverse order
	//-R == recursively list subdirectories encountered

	//BONUS TODO:
	//-h (uses unit instead of size)
	//-m (stream output across the page, separated by commas)
	//-p (add a slash after each directory found
	//-S sort files by size
	//-o same as -l but without group id
	//-G colorized output
	//invent your own (ask if want to list ? search directory ?)
	//-A list all entries except . and ..

typedef struct	s_ls
{
	//mode_t				mode;		//entry type ?
	char				etype;
	//int					data;		//test data
	ino_t				d_ino;		// serial number ..?
	//int					self;
	//int					parent;
	//ino_t		st_ino;
	//int					last_access; //time_t - time of last mod to file - STAT
	unsigned long int 	last_access_msec; // nanoseconds of last mod - STAT
	long 				hlinks; 		// (int) number of HARD links to file. how many directories have entries. (?)
	off_t				size;			// signed int type - how big file is
	unsigned int		filemode;		//also file mode?
	int					group_id;		//sys/types.h gid_t
	int					device_t;		//sys/types.h device ID
	int					user_id;		//sys/types.h userid
	char				uid_name[NAME_MAX];
	char				grp_name[NAME_MAX];
	char				mtime[NAME_MAX];
	int					hmtime;
	char				path[PATH_MAX];
	char				name[NAME_MAX];
	char				*dirpath;
	char				linkname[PATH_MAX];
	int					opendir;		//fd
	int					error;
	int					which;
	int					clic;
	char				slashtrail;
	int					parentchild;
	t_color				color;
	t_access			acc;
	unsigned int		blkct;

	struct s_ls			*right;
	struct s_ls 		*left;
}				t_ls;

typedef struct			s_dir
{
	char	path[PATH_MAX];
	//char	name[NAME_MAX];
	t_ls	*tree;
}						t_dir;

typedef struct	s_opt
{
	int			a;
	int			g;
	int			l;
	int			o;  // same as l but no group
	int			p;	// add trailing slash to directories
	int			r;	// reverse
	int			t;	// time
	int			ug;	// color output
	int			ur;	// recursive
	
	
	
	int			us; // sort by size
}				t_opt;




char					*ft_catpath(char const *directory, char const *name);
int						ft_ustrcmp(char *s1, char *s2);
int			get_type(struct stat stp, t_opt *e, t_ls *new);

#endif
