#include "ft_ls.h"

int		zero_entry(t_ls *new)
{
	if (!new)
		error(1, "zero_entry");
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
	return (1);
}

int		new_entry(t_opt *e, t_dir *cwd, struct stat stp, struct dirent *dp) // make new dir
{
	t_ls *new;

	new = (t_ls *)ft_memalloc(sizeof(t_ls));
	zero_entry(new);
	new->path = ft_catpath(cwd->path, dp->d_name);
	new->name = ft_strdup(dp->d_name);
	get_type(e, cwd, new, &stp);
	sort_entries(e, cwd, &(cwd->tree), new);
	return (1);
}


int		new_file_entry(t_opt *e, struct stat stp, t_dir *cwd, char *s)
{
	t_ls *new;

	new = (t_ls *)ft_memalloc(sizeof(t_ls));
	zero_entry(new);
	new->path = ft_strdup(s);
	new->name = ft_strdup(s);
	new->no_dir = 1;
	get_type(e, cwd, new, &stp);

	sort_entries(e, cwd, &(cwd->tree), new);
	return (1);
}































// 	t_ls	*new;
// 	char	*path;
// 	char	tmp_link[PATH_MAX];

// 	if (!(new = malloc(sizeof(t_ls))))
// 		return(0);
// 	path = ft_catpath(cwd->path, name);
// 	//ft_printf("cwd->path : %s\n", cwd->path);
// 	zero_entry(path, new, name);
// 	new->stp = &stp;
// 	get_type(e, new, cwd);
// 	if (new->etype == 'l')
// 	{
// 		ft_bzero(tmp_link, PATH_MAX);
// 		readlink(new->path, tmp_link, PATH_MAX);
// 		ft_strcpy(new->linkname, " -> ");
// 		ft_strcat(new->linkname, tmp_link);
// 	}
// //	if (!cwd->is_file)
// 		sort_entries(new, &(cwd->entries), e);
// 	// else
// 	// {
// 	// 	get_padding(cwd, new, e);
// 	// 	entry_pr(new, cwd, e);
// 	// }
	

