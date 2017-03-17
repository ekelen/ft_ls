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
	ino_t				d_ino;		// serial number ..?
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