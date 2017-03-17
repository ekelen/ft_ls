#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <time.h>
# include <stdio.h> //DELETE
# include "./printf/includes/ft_printf.h"
# include "./libft/libft.h"

typedef struct	s_ls
{
	mode_t				mode;		//entry type ?
	int					data;		//test data
	ino_t				d_ino;
	//ino_t		st_ino;
	int					last_access; //time_t - time of last mod to file - STAT
	unsigned long int 	last_access_msec; // nanoseconds of last mod - STAT
	int 				hlinks; 		// (int) number of HARD links to file. how many directories have entries. (?)
	off_t				size;			// signed int type - how big file is
	unsigned int		filemode;		//also file mode?
	int					group_id;		//sys/types.h gid_t
	int					device_t;		//sys/types.h device ID
	int					user_id;		//sys/types.h userid
	// char				*path;			//current path name
	// char				*name;			//we'll see
	char				path[255];
	char				name[255];
	int					opendir;		//fd
	int					error;
	struct s_ls			*right;
	struct s_ls 		*left;
}				t_ls;

typedef struct	s_opt
{
	int			ur;
	int			r;
	int			t;
	int			a;
	int			l;
}				t_opt;

#endif
