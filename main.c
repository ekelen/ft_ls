#include "ft_ls.h"


// int		new_entry(struct stat stp, struct dirent *dp, t_opt *e, t_dir *cwd)
// {
// 	t_ls	*new;
// 	char	*path;
// 	char	tmp_link[PATH_MAX];

// 	new = malloc(sizeof(t_ls));
// 	path = ft_catpath(cwd->path, dp->d_name);
// 	zero_entry(path, new, dp);
// 	new->stp = &stp;
// 	if (!(get_type(e, new, cwd)))
// 	{
// 		ft_printf("stat_init failed.\n");
// 		return (0);
// 	}
// 	if (new->etype == 'l')
// 	{
// 		ft_bzero(tmp_link, PATH_MAX);
// 		readlink(new->path, tmp_link, PATH_MAX);
// 		ft_strcpy(new->linkname, " -> ");
// 		ft_strcat(new->linkname, tmp_link);
// 	}
// 	sort_entries(new, &(cwd->entries), e);
// 	return (1);
// }

// int		handle_file(t_dir *cwd, char *s, struct stat *stp)
// {
// 	new_file_entry(stp)
// 	return(1);
// }

int		eval_args(t_opt *e, char **s)
{
	
	t_dir		*cwd;
	t_dir		*root;
	int			i;
	struct stat 	stp;
	int			err;

	cwd = malloc(sizeof(t_dir));
	root = NULL;
	i = 0;
	while (s[i][0] == '-')
		i++;
	if ((err = stat(s[i], &stp)) != 0)
		error(err, "EVAL STAT ERROR");
	if (!(S_ISDIR(stp.st_mode)))
	{
		dir_init(cwd, ".", 1);
		new_entry(stp, s[i], e, cwd);
	}
	else
	{
		//ft_printf("s : %s\n", s[i]);
		if (!(dir_init(cwd, s[i], 0)))
		{
			//ft_printf("dir init failed.\n");
			ft_printf(ERR_FILE, s[i]);
		}
		if(!(init_open(s[i], e, *cwd)))
			ft_printf(ERR_FILE, s[i]);
	}
	return (1);
}

int		main(int ac, char **av)
{
	t_opt	e;
	char 	**args;
	int 	i;

	zero_opt(&e);
	i = 1;
	args = (char **)malloc(sizeof(char *) * ac + 1);
	if (ac < 2)
	{
		args[0] = ft_strdup(".");
		args[1] = 0;
	}
	else
	{
		while (i < ac)
		{
			args[i - 1] = ft_strdup(av[i]);
			i++;
		}
		i = 0;
		while (i < ac - 1 && args[i][0] == '-')
		{	
			if (!(init_opts(args[i], &e)))
				return (1);
			i++;
		}
		if (i == ac - 1)
		{
			args[i] = ft_strdup(".");
		}
	}
	eval_args(&e, args);
	return (0);
}
