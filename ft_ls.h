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
# include <stdio.h> //DELETE
# include <errno.h>
# include <limits.h>
#include <sys/acl.h> //MAYBE DELETE
# include "./printf/includes/ft_printf.h"
# include "./libft/libft.h"
# include "color.h"
# include "time.h"
# include "options.h"
# include "error.h"
# include "padding.h"

typedef struct	s_ls
{
	char				etype;
	struct stat			*stp;
	ino_t				d_ino;
	long 				hlinks;
	size_t				size;
	char				uid_name[NAME_MAX];
	char				grp_name[NAME_MAX];
	char				*path;
	char				*name;
	char				linkname[PATH_MAX];
	int					no_dir;
	int					is_rel;
	int					maj;
	int					min;
	unsigned int		blkct;
	t_color				color;
	t_access			acc;
	char				acl;
	t_time				*time;
	struct s_ls			*right;
	struct s_ls 		*left;
}				t_ls;

typedef struct			s_dir
{
	char				path[PATH_MAX];
	size_t				n;
	t_pad				*pad;
	t_ls				*tree;
	int					file_dir;
	int					contents;
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
	//-G colorized output
	//invent your own (ask if want to list ? search directory ?)
	//-A list all entries except . and ..

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

int						new_entry(t_opt *e, t_dir *cwd, struct stat stp, struct dirent *dp);
int						new_file_entry(t_opt *e, struct stat stp, t_dir *cwd, char *s);
int						zero_dir(t_dir *cwd, char *path);

/*
** Open
*/
int						init_dir_open(t_opt *e, char *d_path, int *first);

/*
** Global/directory settings
*/

int						get_padding(t_dir *cwd, t_ls *ls, t_opt *e);
int						get_total(t_ls *entry, t_dir *cwd);

/*
** Entry metadata
*/

int						get_type(t_opt *e, t_dir *cwd, t_ls *new, struct stat *stp);
int						get_mtime(struct stat stp, t_ls *new, t_opt *e);

/*
** Sort and print
*/

int						sort_entries(t_opt *e, t_dir *cwd, t_ls **tree, t_ls *new);
int						print_time(t_opt *e, t_ls *entry, t_dir *cwd);
void					tree_pr(t_ls *entry, t_dir cwd, t_opt *e);
void					tree_prrv(t_ls *entry, t_dir cwd, t_opt *e);

/*
** Free
*/

void					tree_del(t_ls *tree);
void	free_args(char **args, int i);


#endif
