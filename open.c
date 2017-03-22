#include "ft_ls.h"

void	open_rec(t_ls *entry, t_dir cwd, t_opt *e)
{
	if (!entry)
		return ;
	if (entry->left)
		open_rec(entry->left, cwd, e);
	if (e->ur && entry->etype == 'd' && !entry->parentchild)
	{
		if (!e->l)
			ft_putchar('\n');
		ft_printf("\n%s:\n", entry->path);
		init_open(entry->path, e, cwd);
	}
	if (entry->right)
		open_rec(entry->right, cwd, e);
}

int		init_open(char *s, t_opt *e, t_dir cwd)
{
	DIR 				*dir = NULL;
    struct dirent		*dp;
    struct stat			stp;
    struct stat			ltp;
    char				path[PATH_MAX];
    int					res = 0;
    
	if ((dir = opendir(s)) == NULL || !s)
		return (0);
	dir_init(&cwd, s);
	while ((dp = readdir(dir)) != NULL)
    {
    	ft_bzero(path, PATH_MAX);
    	ft_strcpy(path, s);
    	ft_strcat(path, "/");
    	ft_strcat(path, dp->d_name);
    	if ((res = stat(path, &stp)) || (lstat(path, &ltp)))
		{
			ft_printf("Problem with path %s (%s) : %d\n", path, dp->d_name, errno);
			break ;
		}
		if (S_ISLNK(ltp.st_mode))
		{
				lstat(path, &ltp);
				new_entry(ltp, path, dp, e, &cwd);
		}
		else
			new_entry(stp, path, dp, e, &cwd);
    }
    
    closedir(dir);
    if (e->l)
    	ft_printf("total %ld\n", cwd.n);
    get_padding(&cwd, cwd.entries);
    if (e->r)
    	tree_prrv(cwd.entries, cwd, e);
    else
    	tree_pr(cwd.entries, cwd, e);
    free(cwd.pad);
    open_rec(cwd.entries, cwd, e);
    return (1);
}