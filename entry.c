#include "ft_ls.h"

int	dir_init(t_dir *cwd, char *path, int is_file)
{
	if (!cwd || !path || cwd->is_file)
		return(0);
	//ft_printf("dir path : %s\n", path);
	ft_bzero(cwd->path, PATH_MAX);
	ft_strcpy(cwd->path, path);
	cwd->is_file = is_file ? 1 : 0;
	cwd->n = 0;
	cwd->pad = NULL;
	cwd->entries = NULL;
	cwd->left = NULL;
	cwd->right = NULL;
	return (1);
}


int		zero_entry(char *path, t_ls *new, char *name)
{
	if (!path || !new)
		return(0);
	ft_bzero(new->name, NAME_MAX);
	ft_bzero(new->path, PATH_MAX);
	ft_bzero(new->uid_name, NAME_MAX);
	ft_bzero(new->grp_name, NAME_MAX);
	ft_bzero(new->linkname, PATH_MAX);
	ft_strcpy(new->name, name);
	ft_strcpy(new->path, path);
	new->is_rel = 0;
	new->maj = 0;
	new->min = 0;
	new->blkct = 0;
	new->right = NULL;
	new->left = NULL;
	return (1);
}

int		new_entry(struct stat stp, char *name, t_opt *e, t_dir *cwd)
{
	t_ls	*new;
	char	*path;
	char	tmp_link[PATH_MAX];

	if (!(new = malloc(sizeof(t_ls))))
		return(0);
	path = ft_catpath(cwd->path, name);
	//ft_printf("cwd->path : %s\n", cwd->path);
	zero_entry(path, new, name);
	new->stp = &stp;
	get_type(e, new, cwd);
	if (new->etype == 'l')
	{
		ft_bzero(tmp_link, PATH_MAX);
		readlink(new->path, tmp_link, PATH_MAX);
		ft_strcpy(new->linkname, " -> ");
		ft_strcat(new->linkname, tmp_link);
	}
//	if (!cwd->is_file)
		sort_entries(new, &(cwd->entries), e);
	// else
	// {
	// 	get_padding(cwd, new, e);
	// 	entry_pr(new, cwd, e);
	// }
	return (1);
}
