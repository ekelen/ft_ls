#include "ft_ls.h"

void	open_subdir(t_opt *e, t_dir cwd, t_ls *entry, int first) // after printing one dir, call recursion
{
	if (!entry)
		return ;
	if (entry->left)
		open_subdir(e, cwd, entry->left, first);
	if (e->ur && entry->etype == 'd' && !entry->is_rel)
	{
		init_dir_open(e, entry->path, &first);
	}
	if (entry->right)
		open_subdir(e, cwd, entry->right, first);
}

void	open_subdir_rev(t_opt *e, t_dir cwd, t_ls *entry, int first) // after printing one dir, call recursion
{
	if (!entry)
		return ;
	if (entry->right)
		open_subdir_rev(e, cwd, entry->right, first);
	if (e->ur && entry->etype == 'd' && !entry->is_rel)
	{
		init_dir_open(e, entry->path, &first);
	}
	if (entry->left)
		open_subdir_rev(e, cwd, entry->left, first);
}

static int	open_helper(t_opt *e, t_dir *cwd) // send directory off for printing
{
	if (!e || !cwd)
		return (0);
    if (e->l)
    	ft_printf("total %ld\n", cwd->n);
    get_padding(cwd, cwd->tree, e);
    //ft_printf("cwd->pad->lnk %d\n", cwd->pad->lnk);
    if (e->r)
    	tree_prrv(cwd->tree, *cwd, e);
    else
    	tree_pr(cwd->tree, *cwd, e);
    free(cwd->pad);
    if (e->r)
    	open_subdir_rev(e, *cwd, cwd->tree, 0);
    else
    	open_subdir(e, *cwd, cwd->tree, 0);


    return (1);
}

int	zero_dir(t_dir *cwd, char *path)
{
	if (!cwd || !path)
		return(0);
	ft_bzero(cwd->path, PATH_MAX);
	ft_strcpy(cwd->path, path);
	cwd->pad = NULL;
	cwd->file_dir = 0;
	cwd->n = 0;
	return (1);
}

int		dir_open(t_opt *e, t_dir *cwd, DIR *dir)
{
	struct dirent			*dp;
	char					*path;
	struct stat				stp;
	struct stat				ltp;

	while ((dp = readdir(dir)) != NULL)
	{
		if (dp->d_name[0] != '.' || e->a)
		{
			//ft_printf("cwd->path : %s, dp->d_name: %s\n", cwd->path, dp->d_name);
			path = ft_catpath(cwd->path, dp->d_name); // freed (check function)
			//ft_printf("path : %s\n", path);
			if ((stat(path, &stp) || (lstat(path, &ltp))))
				error(1, "dir_open ERROR");
			else
			{
				if (S_ISLNK(ltp.st_mode))
				{
					//ft_printf("Found symlink.\n", dp->d_name);
					lstat(path, &ltp);
					//ft_printf("path : %s\n", path);
					new_entry(e, cwd, ltp, dp);
				}
				else
					new_entry(e, cwd, stp, dp);
			}
			ft_strdel(&path);
		}
	}
	closedir(dir);
	open_helper(e, cwd);
	return(1);
}

int		init_dir_open(t_opt *e, char *d_path, int *first)
{
	DIR						*dir;
	t_dir					*cwd;
	//ft_printf("d_path : %s\n");

	if (!*first || (*first && e->files))
	{
		ft_printf("\n");
	}
	if (e->dirs > 1 || !*first || e->files || e->errs)
			ft_printf("%s:\n", d_path);
	if ((dir = opendir(d_path)) == NULL || !d_path || !e)
		error(1, "INIT_OPEN ERROR");
	else
	{
		cwd = (t_dir *)ft_memalloc(sizeof(t_dir)); //not freed
		zero_dir(cwd, d_path);
		dir_open(e, cwd, dir);
	}

	return(1);
}