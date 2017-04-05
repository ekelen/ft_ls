#include "ft_ls.h"

void	open_subdir(t_opt *e, t_dir cwd, t_ls *entry, int first) // after printing one dir, call recursion
{
	int parent = 0;
	if (!entry)
		return ;
	if (entry->left)
		open_subdir(e, cwd, entry->left, first);
	if (e->ur && entry->etype == 'd' && !entry->is_rel)
	{
		init_dir_open(e, entry->path, &first, &parent);
	}
	if (entry->right)
		open_subdir(e, cwd, entry->right, first);
}

static int	open_helper(t_opt *e, t_dir *cwd) // send directory off for printing
{
	if (!e || !cwd)
		return (0);
    if (e->l)
    	ft_printf("total %ld\n", cwd->n);
    get_padding(cwd, cwd->tree, e);
    if (e->r)
    	tree_prrv(cwd->tree, *cwd, e);
    else
    	tree_pr(cwd->tree, *cwd, e);
    free(cwd->pad);
    open_subdir(e, *cwd, cwd->tree, 0);


    return (1);
}

int	zero_dir(t_dir *cwd, char *path, int *parent)
{
	if (!cwd || !path)
		return(0);
	ft_bzero(cwd->path, PATH_MAX);
	ft_strcpy(cwd->path, path);
	cwd->parent = parent ? 1 : 0;
	cwd->n = 0;
	*parent = 0;
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
			path = ft_catpath(cwd->path, dp->d_name); // freed (check function)
			//ft_printf("path : %s\n", path);
			if ((stat(path, &stp) || (lstat(path, &ltp))))
				error(1, "dir_open ERROR");
			else
			{
				if (S_ISLNK(ltp.st_mode))
				{
					lstat(path, &ltp);
					//ft_printf("path : %s\n", path);
					new_entry(e, cwd, ltp, dp);
				}
				else
					//ft_printf("path : %s\n", path);
					new_entry(e, cwd, stp, dp);
			}
			ft_strdel(&path);
		}
	}
	closedir(dir);
	open_helper(e, cwd);
	return(1);
}



int		init_dir_open(t_opt *e, char *d_path, int *first, int *parent)
{
	DIR						*dir;
	t_dir					*cwd;

	if ((dir = opendir(d_path)) == NULL || !d_path || !e)
		error(1, "INIT_OPEN ERROR");
	else
	{
		cwd = (t_dir *)ft_memalloc(sizeof(t_dir)); //not freed
		zero_dir(cwd, d_path, parent);
		if (!*first || (*first && e->files))
		{
			ft_printf("\n");
		}
		if (e->dirs || !*first || e->files)
			ft_printf("%s:\n", cwd->path);
		dir_open(e, cwd, dir);
	}

	return(1);
}


















// void	open_subdir(t_ls *entry, t_dir cwd, t_opt *e)
// {
// 	if (!entry)
// 		return ;
// 	if (entry->left)
// 		open_subdir(entry->left, cwd, e);
// 	if (e->ur && entry->etype == 'd' && !entry->is_rel)
// 	{
// 		ft_printf("\n%s:\n", entry->path);
// 		init_open(entry->path, e, cwd);
// 	}
// 	if (entry->right)
// 		open_subdir(entry->right, cwd, e);
// }

// static int	open_cont(t_opt *e, t_dir *cwd)
// {
	// if (!e || !cwd)
	// 	return (0);
  //   if (e->l)
  //   	ft_printf("total %ld\n", cwd->n);
  //   get_padding(cwd, cwd->entries, e);
  //   if (e->r)
  //   	tree_prrv(cwd->entries, *cwd, e);
  //   else
  //   	tree_pr(cwd->entries, *cwd, e);
  //   free(cwd->pad);
  //   open_subdir(cwd->entries, *cwd, e);
  //   return (1);
// }










	// DIR 				*dir = NULL;
  //   struct dirent		*dp;
  //   struct stat			stp;
  //   struct stat			ltp;
  //   char						*path;
	//
	// if ((dir = opendir(s)) == NULL || !s || !e)
	// 	error(1, "OPENDIR ERROR");
	// dir_init(&cwd, s, 0);
	// while ((dp = readdir(dir)) != NULL)
  //   {
  //   	path = ft_catpath(cwd.path, dp->d_name);
  //   	if (dp->d_name[0] != '.' || e->a)
  //   	{
	//     	if ((stat(path, &stp)) || (lstat(path, &ltp)))
	//     		error(1, "STAT ERROR");
	// 			if (S_ISLNK(ltp.st_mode))
	// 			{
	// 				lstat(path, &ltp);
	// 				new_entry(ltp, dp->d_name, e, &cwd);
	// 			}
	// 			else
	// 				new_entry(stp, dp->d_name, e, &cwd);
	// 		}
	// 	ft_strdel(&path);
  //   }
  //   closedir(dir);
  //   open_cont(e, &cwd);
    //return (1);
