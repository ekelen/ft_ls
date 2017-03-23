#include "ft_ls.h"

int		zero_entry(char *path, t_ls *new, struct dirent *dp)
{
	if (!path || !new || !dp)
		return(0);
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
	return (1);
}

int		new_entry(struct stat stp, struct dirent *dp, t_opt *e, t_dir *cwd)
{
	t_ls	*new;
	char	*path;
	char	tmp_link[PATH_MAX];

	new = malloc(sizeof(t_ls));
	path = ft_catpath(cwd->path, dp->d_name);
	zero_entry(path, new, dp);
	new->stp = &stp;
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
	sort_entries(new, &(cwd->entries), e);
	return (1);
}