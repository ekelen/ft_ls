#include "ft_ls.h"

static void	make_file_dir(t_opt *e, char **s, t_dir *file_cwd)
{
	struct stat stp;
	int i;

	i = 0;
	zero_dir(file_cwd, "");
	file_cwd->file_dir = 1;
	while (i < e->paths)
	{
		if (!(stat(s[i], &stp)) || !((lstat(s[i], &stp))))
		{
			if (!(S_ISDIR(stp.st_mode)) || e->d)
			{
				e->files++;
				new_file_entry(e, stp, file_cwd, s[i]);
			}
			else
				e->dirs++;
		}
		i++;
	}
	get_padding(file_cwd, file_cwd->tree, e);
	return ;
}

int	extract_files(t_opt *e, char **s)
{
	t_dir *file_cwd;
	
	file_cwd = (t_dir *)ft_memalloc(sizeof(t_dir));
	make_file_dir(e, s, file_cwd);
	if (e->r)
		tree_prrv(file_cwd->tree, *file_cwd, e);
	else
		tree_pr(file_cwd->tree, *file_cwd, e);
	tree_del(file_cwd->tree);
	free(file_cwd);
	return (1);
}