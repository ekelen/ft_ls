#include "ft_ls.h"

void		zero_entry(t_ls *new)
{
	ft_bzero(new->uid_name, NAME_MAX);
	ft_bzero(new->grp_name, NAME_MAX);
	ft_bzero(new->linkname, PATH_MAX);
	new->no_dir = 0;
	new->is_rel = 0;
	new->maj = 0;
	new->min = 0;
	new->blkct = 0;
	new->left = NULL;
	new->right = NULL;
	return ;
}

void		new_entry(t_opt *e, t_dir *cwd, struct stat stp, struct dirent *dp)
{
	t_ls *new;

	new = (t_ls *)ft_memalloc(sizeof(t_ls));
	zero_entry(new);
	new->path = ft_catpath(cwd->path, dp->d_name);
	new->name = ft_strdup(dp->d_name);
	get_type(e, cwd, new, &stp);
	sort_entries(e, cwd, &(cwd->tree), new);
	return ;
}


void		new_file_entry(t_opt *e, struct stat stp, t_dir *cwd, char *s)
{
	t_ls *new;

	new = (t_ls *)ft_memalloc(sizeof(t_ls));
	zero_entry(new);
	new->path = ft_strdup(s);
	new->name = ft_strdup(s);
	new->no_dir = 1;
	get_type(e, cwd, new, &stp);
	sort_entries(e, cwd, &(cwd->tree), new);
	return ;
}