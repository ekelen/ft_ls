#include "ft_ls.h"

static int		should_open(t_opt *e, struct dirent *dp)
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


static void		dir_open_stat(t_opt *e, t_dir *cwd, char *path, struct dirent *dp)
{
	struct stat				stp;
	struct stat				ltp;

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
	return ;
}

static int		dir_open(t_opt *e, t_dir *cwd, DIR *dir)
{
	struct dirent			*dp;
	char					*path;

	while ((dp = readdir(dir)) != NULL)
	{
		if (should_open(e, dp))
		{
			cwd->contents++;
			path = ft_catpath(cwd->path, dp->d_name); // freed (check function)
			dir_open_stat(e, cwd, path, dp);
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
		cwd = (t_dir *)ft_memalloc(sizeof(t_dir));
		zero_dir(cwd, d_path);
		dir_open(e, cwd, dir);
		tree_del(cwd->tree);
	}
	free(cwd);
	return(1);
}