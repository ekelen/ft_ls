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
	char **args;
	int i;

	i = 1;
	args = (char **)malloc(sizeof(char *) * ac);
	if (ac < 2)
		args[0] = ft_strdup(".");
	while (i < ac)
	{
		args[i - 1] = ft_strdup(av[i]);
		i++;
	}
	eval_args(args, ac);
	return (0);
}
