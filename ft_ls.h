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
# include "color.h"
# include "time.h"
# include "options.h"
# include "error.h"
# include "env_padding.h"

typedef struct	s_ls
{
	char				etype;
	struct stat			*stp;
	ino_t				d_ino;		// serial number ..?
	//ino_t		st_ino;
	//int					last_access; //time_t - time of last mod to file - STAT
	long 				hlinks; 		// (int) number of HARD links to file. how many directories have entries. (?)
	off_t				size;			// signed int type - how big file is
	//unsigned int		filemode;		//also file mode?
	int					group_id;		//sys/types.h gid_t
	int					device_t;		//sys/types.h device ID
	int					user_id;		//sys/types.h userid
	char				uid_name[NAME_MAX];
	char				grp_name[NAME_MAX];

	char				path[PATH_MAX];
	char				name[NAME_MAX];
	char				*dirpath;
	char				linkname[PATH_MAX];
	int					parentchild;
	t_color				color;
	t_access			acc;
	t_time				*time;
	unsigned int		blkct;
	struct s_ls			*right;
	struct s_ls 		*left;
}				t_ls;

typedef struct			s_dir
{
	char				path[PATH_MAX];
	size_t				n;
	t_pad				*pad;
	t_ls				*entries;
	struct s_dir		*right;
	struct s_dir		*left;
}						t_dir;





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

// char					*ft_catpath(char const *directory, char const *name);

/*
** Utilities
*/

int						ft_abs(int a);
int						ft_ustrcmp(char *s1, char *s2);
size_t					ft_numlen(unsigned int nbr);
char					*ft_catpath(char *dir, char *name);

/*
** Initialize objects
*/

int						dir_init(t_dir *cwd, char *path);
int						new_entry(struct stat stp, struct dirent *dp, t_opt *e, t_dir *cwd);

/*
** Open
*/
int						init_open(char *s, t_opt *e, t_dir cwd);
void					open_rec(t_ls *entry, t_dir cwd, t_opt *e);

/*
** Global/directory settings
*/ 

int						get_padding(t_dir *cwd, t_ls *ls, t_opt *e);
int						eval_args(t_opt *e, char **s, int ac);
int						get_total(t_ls *entry, t_dir *cwd);

/*
** Entry metadata
*/

int						get_type(struct stat stp, t_opt *e, t_ls *new, t_dir *cwd);
int						get_mtime(struct stat stp, t_ls *new, t_opt *e);

/*
** Sort and print
*/

int						sort_entries(t_ls *new, t_ls **tree, t_opt *e);
int						print_time(t_ls *entry, t_dir *cwd);
void					tree_pr(t_ls *entry, t_dir cwd, t_opt *e);
void					tree_prrv(t_ls *entry, t_dir cwd, t_opt *e);

//void 	meta_pr(t_dir *tree, t_opt *e);
//int		sort_dirs_time(t_dir *new, t_dir **tree);
//int		sort_dirs_ascii(t_dir *new, t_dir **tree);
//int		move_cwd(t_opt *e, t_dir *cwd, t_dir **root);


#endif
