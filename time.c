#include "ft_ls.h"

int			print_time(t_ls *entry, t_dir *cwd)
{
	(void)cwd;
	time_t now;

    now = time(0);
	ft_printf(" %s", entry->mmon);
	ft_printf(" %s", entry->mdate);
	if (ft_abs(now - entry->lastmod) < (31540000 / 2))
		ft_printf(" %s ", entry->mhr);
	else
		ft_printf("  %s ", entry->myr);
	return (1);
}

static int	parse_time(struct stat stp, t_ls *new, t_opt *e)
{
	char stime[100];
	size_t t[8] = {4, 6, 8, 9, 11, 15, 20, 23};
	size_t i;
	i = 0;
    
	ft_bzero(stime, 100);
	(void)e;
	ft_bzero(new->mmon, 4);
	ft_bzero(new->myr, 5);
	ft_bzero(new->mdate, 3);
	ft_bzero(new->mhr, 6);
	ft_strcpy(stime, ctime(&stp.st_mtime));
	new->lastmod = stp.st_mtime;
	while (i < ft_strlen(stime))
	{
		if (i >= t[0] && i <= t[1])
			new->mmon[i - t[0]] = stime[i];
		if (i >= t[2] && i <= t[3])
			new->mdate[i - t[2]] = stime[i];
		if (i >= t[4] && i <= t[5])
			new->mhr[i - t[4]] = stime[i];
		if (i >= t[6] && i <= t[7])
			new->myr[i - t[6]] = stime[i];
		i++;
	}
	return (1);
}

int			get_mtime(struct stat stp, t_ls *new, t_opt *e)
{
	new->hmtime = stp.st_mtime;
	new->m_nsec = stp.st_atimespec.tv_sec;
	parse_time(stp, new, e);
	return (1);
}