#include "ft_ls.h"


// static int		new_padding(struct stat stp, t_dir *cwd)
// {
// 	if (stp.st_nlink > cwd->padding.max_hlinks)
// 		cwd->padding.max_hlinks += stp.st_nlink - cwd->padding.max_hlinks;
// 	return (1);
// }

static int		init_padding(t_dir *cwd, t_ls *ls)
{
	if (ls->left)
		init_padding(cwd, ls->left);
	if (ft_numlen(ls->hlinks) > cwd->padding->lnk)
		cwd->padding->lnk = ft_numlen(ls->hlinks); // + 1
	if (ft_strlen(ls->uid_name) > cwd->padding->own)
		cwd->padding->own = ft_strlen(ls->uid_name); // + 1
	if (ft_strlen(ls->grp_name) > cwd->padding->grp)
		cwd->padding->grp = ft_strlen(ls->grp_name); // + 2
	if (ft_numlen(ls->size) > cwd->padding->size)
		cwd->padding->size = ft_numlen(ls->size); // + 2
	if (ls->right)
		init_padding(cwd, ls->right);
	return (1);
}	

int				get_padding(t_dir *cwd, t_ls *ls)
{
	cwd->padding = malloc(sizeof(t_padding));
	cwd->padding->acc = 10;
	cwd->padding->ext = 1;
	cwd->padding->lnk = 0;
	cwd->padding->own = 0;
	cwd->padding->grp = 0;
	cwd->padding->size = 0;
	cwd->padding->mon = 4;
	cwd->padding->dat = 3;
	cwd->padding->timyr = 5;
	init_padding(cwd, ls);
	//ft_printf("padding for this directory for links : %d\n", cwd->padding->lnk);
	//ft_printf("padding for this directory for size : %d\n", cwd->padding->size);
	return (1);
}

// -rwxr-xr-x   1 ekelen  october    4096 Nov  9 11:50 ._lib
// -rwxr-xr-x   1 ekelen  october    4096 Nov  9 11:50 ._locale
// -rw-r--r--   1 ekelen  october    4096 Nov  9 11:50 ._qt.conf
// -rw-r--r--   1 ekelen  october    4096 Nov  9 11:50 ._site.pyc
// -rw-r--r--@  1 ekelen  october    1589 Apr  9  2016 __boot__.py
// -rwxr-xr-x@  1 ekelen  october     559 Mar  3  2014 __error__.sh
// -rw-r--r--@  1 ekelen  october  143827 Apr  9  2016 anki.icns
// -rw-r--r--@  1 ekelen  october      87 Jun  1  2011 ankiqtmac.py
// -rw-r--r--@  1 ekelen  october   15269 Apr  9  2016 ankiweb.certs
// drwxr-xr-x@  2 ekelen  october    4096 Apr  9  2016 audio
// drwxr-xr-x@  2 ekelen  october    4096 Apr  9  2016 imageformats
// drwxr-xr-x@  3 ekelen  october    4096 Apr  9  2016 include
// drwxr-xr-x@  3 ekelen  october    4096 Apr  9  2016 lib
// drwxr-xr-x@ 59 ekelen  october    4096 Apr  9  2016 locale
// -rw-r--r--@  1 ekelen  october      63 Apr  9  2016 qt.conf
// -rw-r--r--@  1 ekelen  october    3380 Mar  3  2014 site.pyc







// static int		ft_catpath(char *s, char *path, struct dirent *dp)
// {
// 	if (!s || !path || !dp)
// 	{
// 		return (0);
// 	}
	
// 	ft_bzero(path, PATH_MAX);
// 	ft_strcpy(path, s);
// 	ft_strcat(path, "/");
// 	ft_strcat(path, dp->d_name);
// 	return (1);
// }

// int		get_padding(char *s, t_opt *e, t_dir *cwd)
// {
// 	DIR 				*dir = NULL;
//     struct dirent		*dp;
//     struct stat			stp;
//     struct stat			ltp;
//     char				path[PATH_MAX];
   
// 	if ((dir = opendir(s)) == NULL || !s)
// 		return (0);
// 	init_padding(&(cwd->padding));
// 	while ((dp = readdir(dir)) != NULL)
//     {
//     	ft_catpath(s, path, dp);
//     	if ((stat(path, &stp)) || (lstat(path, &ltp)))
// 		{
// 			ft_printf("Problem with path %s (%s) : %d\n", path, dp->d_name, errno);
// 			break ;
// 		}
// 		else
// 		{
// 			if (S_ISLNK(ltp.st_mode))
// 			{
// 				lstat(path, &ltp);
// 				new_padding(ltp, cwd);
// 			}
// 			else
// 				new_padding(stp, cwd);
// 		}
// 		if (S_ISDIR(stp.st_mode) && !ft_strequ(dp->d_name, ".") && !ft_strequ(dp->d_name, ".."))
// 		{
			
// 			get_padding(path, e, cwd);
// 		}
//     }
//     ft_printf("cwd->padding->max_hlinks for %s : %d\n", path, cwd->padding.max_hlinks);
//     closedir(dir);
//     return (1);
// }