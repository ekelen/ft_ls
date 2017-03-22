# include "ft_ls.h"

char		*ft_strexclude(char *orig, char *excl)
{
	char *s;
	size_t olen;
	size_t exclen;

	olen = ft_strlen(orig);
	exclen = ft_strlen(excl);
	s = ft_strsub(orig, 0, olen - exclen);
	return (s);
}

int		get_blkct(struct stat stp, t_ls *new, t_dir *cwd)
{
	new->blkct = stp.st_blocks;
	cwd->n += new->blkct;
	return(1);
}



int			get_parentchild(t_ls *new, t_opt *e)
{
	(void)e;
	if (ft_strequ(new->name, ".") || ft_strequ(new->name, ".."))
		new->parentchild = 1;
	else
		new->parentchild = 0;
	return (1);
}

int			get_color(t_ls *new, t_opt *e)
{
	if (e->ug)
	{
		if (new->etype == 'd')
			ft_strcpy(new->color.fg, FG_BLU);
		else if (new->etype == '-' && (new->acc.xuser == 'x' || new->acc.xgrp == 'x' || new->acc.xoth == 'x'))
			ft_strcpy(new->color.fg, FG_RED);
		else if (new->etype == 'l')
			ft_strcpy(new->color.fg, FG_PNK);
	}
	return (1);
}

int			get_size(struct stat stp, t_ls *new, t_opt *e)
{
	(void)e;
	new->size = stp.st_size;
	return (1);
}

int			get_grp_name(struct stat stp, t_ls *new, t_opt *e)
{
	ft_bzero(new->grp_name, NAME_MAX);
	if (!e->o)
	{
		struct group *grp;
		grp = getgrgid(stp.st_gid);
		ft_strcpy(new->grp_name, grp->gr_name);
	}
	return (1);

}

int			get_uid_name(struct stat stp, t_ls *new, t_opt *e)
{
	(void)e;
	struct passwd *pwd;
	pwd = getpwuid(stp.st_uid);
	ft_strcpy(new->uid_name, pwd->pw_name);
	return (1);
}

int			count_links(struct stat stp, t_ls *new, t_opt *e)
{
	(void)e;
	new->hlinks = stp.st_nlink;
	return (1);
}

int			get_access(struct stat stp, t_ls *new, t_opt *e)
{
	(void)e;
	new->acc.ruser = (stp.st_mode & S_IRUSR) ? 'r' : '-';
	new->acc.wuser = (stp.st_mode & S_IWUSR) ? 'w' : '-';
	new->acc.xuser = (stp.st_mode & S_IXUSR) ? 'x' : '-';
	new->acc.rgrp = (stp.st_mode & S_IRGRP) ? 'r' : '-';
	new->acc.wgrp = (stp.st_mode & S_IWGRP) ? 'w' : '-';
	new->acc.xgrp = (stp.st_mode & S_IXGRP) ? 'x' : '-';
	new->acc.roth = (stp.st_mode & S_IROTH) ? 'r' : '-';
	new->acc.woth = (stp.st_mode & S_IWOTH) ? 'w' : '-';
	new->acc.xoth = (stp.st_mode & S_IXOTH) ? 'x' : '-';
	return (1);
}

int			get_dirname(t_ls *new, t_opt *e)
{
	(void)e;
	new->dirpath = ft_strexclude(new->path, new->name);
	return (0);
}

int			get_type(struct stat stp, t_opt *e, t_ls *new, t_dir *cwd)
{
	if (S_ISREG(stp.st_mode))
		new->etype = '-';
	else if (S_ISDIR(stp.st_mode))
		new->etype = 'd';
	else if (S_ISCHR(stp.st_mode))
		new->etype = 'c';
	else if (S_ISBLK(stp.st_mode))
		new->etype = 'b';
	else if (S_ISFIFO(stp.st_mode))
		new->etype = 'p';
	else if (S_ISLNK(stp.st_mode))
		new->etype = 'l';
	else if (S_ISSOCK(stp.st_mode))
		new->etype = 's';
	else
	{
		ft_printf("No mode type found; aborting.\n");
		return (0);
	} 
	get_dirname(new, e);
	get_access(stp, new, e);
	count_links(stp, new, e);
	get_uid_name(stp, new, e);
	get_blkct(stp, new, cwd);
	get_grp_name(stp, new, e);
	get_size(stp, new, e);
	get_mtime(stp, new, e);
	get_color(new, e);
	get_parentchild(new, e);
	return(1);
}



