#include "ft_ls.h"
#include <stdio.h> // DELETE

t_ls	zero_entry(char *path, t_ls *new, struct dirent *dp)
{
	static int which = 0;
	ft_bzero(new->name, NAME_MAX);
	ft_bzero(new->path, PATH_MAX);
	ft_strcpy(new->name, dp->d_name);
	ft_strcpy(new->path, path);
	ft_bzero(new->uid_name, NAME_MAX);
	ft_bzero(new->grp_name, NAME_MAX);
	ft_bzero(new->linkname, PATH_MAX);
	new->d_ino = dp->d_ino;
	new->right = NULL;
	new->left = NULL;
	new->which = which;
	which++;
	return (*new);
}

int		new_entry(struct stat stp, char *path, struct dirent *dp, t_opt *e, t_dir *cwd)
{
	if (!(path || dp))
		return (0);
	t_ls	*new;
	char	tmp_link[PATH_MAX];

	new = malloc(sizeof(t_ls));
	*new = zero_entry(path, new, dp);
	if (!(get_type(stp, e, new, cwd)))
	{
		ft_printf("stat_init failed.\n");
		return (0);
	}
	if (new->etype == 'l')
	{
		ft_bzero(tmp_link, PATH_MAX);
		readlink(new->path, tmp_link, PATH_MAX);
		ft_strcpy(new->linkname, " -> ");
		ft_strcat(new->linkname, tmp_link);
	}
	if (new->etype == 'd')
		cwd->dir_meta = new;
	sort_entries(new, &(cwd->entries), e);
	return (1);
}

int	dir_init(t_dir *cwd, char *path)
{
	if (!cwd || !path)
	{
		ft_printf("Problem initiating directory.\n");
		return(0);
	}
	ft_bzero(cwd->path, PATH_MAX);
	ft_strcpy(cwd->path, path);
	cwd->n = 0;
	cwd->entries = NULL;
	cwd->left = NULL;
	cwd->right = NULL;
	return (1);
}

int		main(int ac, char **av)
{
	t_opt	e;
	char **args;
	int i;

	zero_opt(&e);
	i = 1;
	args = (char **)malloc(sizeof(char *) * ac + 1);
	if (ac < 2) // 1. If no flags OR path.
	{
		//ft_printf("ac < 2\n");
		args[0] = ft_strdup(".");
		args[1] = 0;
	}
	else // 2. If flags and/or path - get all args
	{
		while (i < ac) // Get all args
		{
			args[i - 1] = ft_strdup(av[i]);
			//ft_printf("Args to parse : %s\n", args[i - 1]);
			i++;
		}
		i = 0;
		while (i < ac - 1 && args[i][0] == '-') // 2a. Check to see how many flags.
		{	
			if (!(init_opts(args[i], &e)))
				return (0);
			i++;
		}
		if (i == ac - 1)
		{
			args[i] = ft_strdup(".");
		}
	}
	eval_args(&e, args, ac);
	return (0);
}
