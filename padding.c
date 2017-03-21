#include "ft_ls.h"


static int		new_padding(struct stat stp, char *path, t_dir *cwd)
{
	(void)path;
	if (stp.st_nlink > cwd->padding.max_hlinks)
		cwd->padding.max_hlinks += stp.st_nlink - cwd->padding.max_hlinks;
	return (1);
}

static int		init_padding(t_padding *p)
{
	p->max_hlinks = 0;
	return (1);
}	

static int		ft_catpath(char *s, char *path, struct dirent *dp)
{
	if (!s || !path || !dp)
		return (0);	
	ft_bzero(path, PATH_MAX);
	ft_strcpy(path, s);
	ft_strcat(path, "/");
	ft_strcat(path, dp->d_name);
	return (1);
}

int		get_padding(char *s, t_opt *e, t_dir *cwd)
{
	DIR 				*dir = NULL;
    struct dirent		*dp;
    struct stat			stp;
    struct stat			ltp;
    char				path[PATH_MAX];
   
	if ((dir = opendir(s)) == NULL || !s)
		return (0);
	init_padding(&(cwd->padding));
	while ((dp = readdir(dir)) != NULL)
    {
    	ft_catpath(s, path, dp);
    	if ((stat(path, &stp)) || (lstat(path, &ltp)))
		{
			ft_printf("Problem with path %s (%s) : %d\n", path, dp->d_name, errno);
			break ;
		}
		else
		{
			if (S_ISLNK(ltp.st_mode))
			{
				lstat(path, &ltp);
				new_padding(ltp, path, cwd);
			}
			else
				new_padding(stp, path, cwd);
		}
		if (S_ISDIR(stp.st_mode) && !ft_strequ(dp->d_name, ".") && !ft_strequ(dp->d_name, ".."))
		{
			ft_printf("cwd->padding->max_hlinks for %s : %d\n", path, cwd->padding.max_hlinks);
			get_padding(path, e, cwd);
		}
    }
    closedir(dir);
    return (1);
}