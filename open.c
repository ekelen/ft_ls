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

void	open_helper(t_opt *e, t_dir *cwd) // send directory off for printing
{
    if (e->l && cwd->contents)
    	ft_printf("total %ld\n", cwd->n);
    get_padding(cwd, cwd->tree, e);
    if (e->r)
    	tree_prrv(cwd->tree, *cwd, e);
    else
    	tree_pr(cwd->tree, *cwd, e);
    //free(PAD);
    if (e->r)
    	open_subdir_rev(e, *cwd, cwd->tree, 0);
    else
    	open_subdir(e, *cwd, cwd->tree, 0);
    return ;
}

void	zero_dir(t_dir *cwd, char *path)
{
	ft_bzero(cwd->path, PATH_MAX);
	ft_strcpy(cwd->path, path);
	cwd->file_dir = 0;
	cwd->n = 0;
	cwd->contents = 0;
	cwd->tree = NULL;
	cwd->left = NULL;
	cwd->right = NULL;
	return ;
}

int		should_open(t_opt *e, struct dirent *dp)
{
	if (dp->d_name[0] == '.')
	{
		if (e->a)
			return(1);
		if (e->ua)
		{
			if (ft_strequ(dp->d_name, ".") || ft_strequ(dp->d_name, ".."))
				return(0);
			return (1);
		}
		return(0);
	}
	else
		return(1);
}

int		dir_open(t_opt *e, t_dir *cwd, DIR *dir)
{
	struct dirent			*dp;
	char					*path;
	struct stat				stp;
	struct stat				ltp;

	while ((dp = readdir(dir)) != NULL)
	{
		if (should_open(e, dp))
		{
			cwd->contents++;
			path = ft_catpath(cwd->path, dp->d_name); // freed (check function)
			if (!(stat(path, &stp)))
			{
				if (!(lstat(path, &ltp)))
				{
					if (S_ISLNK(ltp.st_mode))
					{
						lstat(path, &ltp);
						new_entry(e, cwd, ltp, dp);
					}
					else
						new_entry(e, cwd, stp, dp);
				}
			}
			else
			{
				if (!(lstat(path, &ltp)))
				{
					lstat(path, &ltp);
					new_entry(e, cwd, ltp, dp);
				}
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

	cwd = NULL;
	if (!*first || (*first && e->files))
	{
		ft_printf("\n");
	}
	if (e->dirs > 1 || !*first || e->files || e->errs)
			ft_printf("%s:\n", d_path);
	if ((dir = opendir(d_path)) == NULL || !d_path || !e)
		error("directory error:");
	else
	{
		cwd = (t_dir *)ft_memalloc(sizeof(t_dir)); //not freed
		zero_dir(cwd, d_path);
		dir_open(e, cwd, dir);
	}
	free(cwd);
	return(1);
}