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
	char				linkname[PATH_MAX];
	int					opendir;		//fd
	int					error;
	int					which;
	int					clic;
	char				slashtrail;
	int					parentchild;
	t_color				color;
	t_access			acc;
	//unsigned int		blkct;

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
	int			ug;	// color output
	int			p;	// add trailing slash to directories
	int			us; // sort by size
	t_ls		*tree;
}				t_opt;





char					*ft_catpath(char const *directory, char const *name);
int						ft_ustrcmp(char *s1, char *s2);
int			get_type(struct stat stp, char *path, struct dirent *dp, t_ls *new);

#endif



	// DIR 			*dir;
 //    struct dirent	*dp;
 //    struct stat		stp;
 //    char			*s3;
 //    t_ls			*tree;

    
 //    tree = NULL;
	// dir = opendir(s);
	// while (dir) 
	// {
	//     if ((dp = readdir(dir)) != NULL) 
	//     {
	//     	if (stat((s3 = ft_strjoin(s, dp->d_name)), &stp) < 0)
	// 		{
	// 			ft_printf("Stat problem\n");
	// 			return ;
	// 		}
	// 		// if (S_ISDIR(stp.st_mode))
	// 		// 	rec_check(s3);
	// 	    get_new(stp, s, dp, &tree);
	//     }
	//     else 
	//    	{
	//    		tree_pr(tree);
	//         closedir(dir);
	//         return ;
	//     }
	// }


// if (d_type == DT_UNKNOWN)
//     		check_type_macros(sb.st_mode);
//     if S_ISREG(sb.st_mode)
// // is it a regular file?

// S_ISDIR(m)

// // directory?

// S_ISCHR(m)

// // character device?

// S_ISBLK(m)

// // block device?

// S_ISFIFO(m)

// // FIFO (named pipe)?

// S_ISLNK(m)

// // symbolic link? (Not in POSIX.1-1996.)

// S_ISSOCK(m)

// socket? (Not in POSIX.1-1996.)
