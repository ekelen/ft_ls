#include "ft_ls.h"

void	open_subdir(t_ls *entry, t_dir cwd, t_opt *e)
{
	if (!entry)
		return ;
	if (entry->left)
		open_subdir(entry->left, cwd, e);
	if (e->ur && entry->etype == 'd' && !entry->is_rel)
	{
		if (!e->l)
			ft_putchar('\n');
		ft_printf("\n%s:\n", entry->path);
		init_open(entry->path, e, cwd);
	}
	if (entry->right)
		open_subdir(entry->right, cwd, e);
}

static int	open_cont(t_opt *e, t_dir *cwd)
{
	if (!e || !cwd)
		return (0);
    if (e->l)
    	ft_printf("total %ld\n", cwd->n);
    get_padding(cwd, cwd->entries, e);
    if (e->r)
    	tree_prrv(cwd->entries, *cwd, e);
    else
    	tree_pr(cwd->entries, *cwd, e);
    free(cwd->pad);
    open_subdir(cwd->entries, *cwd, e);
    return (1);
}

int		init_open(char *s, t_opt *e, t_dir cwd)
{
	DIR 				*dir = NULL;
    struct dirent		*dp;
    struct stat			stp;
    struct stat			ltp;
    char				*path;
    
	if ((dir = opendir(s)) == NULL || !s)
		return (0);
	dir_init(&cwd, s);
	while ((dp = readdir(dir)) != NULL)
    {
    	path = ft_catpath(s, dp->d_name);
    	if (dp->d_name[0] != '.' || e->a)
    	{
	    	if ((stat(path, &stp)) || (lstat(path, &ltp)))
	    	{
				error(-1);
	    	}
			if (S_ISLNK(ltp.st_mode))
			{
				lstat(path, &ltp);
				new_entry(ltp, dp, e, &cwd);
			}
			else
				new_entry(stp, dp, e, &cwd);
		}
		ft_strdel(&path);
    }
    closedir(dir);
    open_cont(e, &cwd);
    return (1);
}