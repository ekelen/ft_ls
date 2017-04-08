#include "ft_ls.h"

int			print_time(t_opt *e, t_ls *entry, t_dir *cwd)
{
	(void)cwd;
	static time_t now;
	time_t sixmonths = ((365 / 2) * 86400);

    now = time(0);
	ft_printf(" %s", entry->time->mmon);
	ft_printf(" %s", entry->time->mdate);
	if ((entry->MT + sixmonths > now && entry->MT < now + sixmonths) \
		|| e->ut)
	{
		ft_printf(" %s", entry->time->mhr);
		if (e->ut)
		{
			ft_printf(":%s %s", entry->time->msec, entry->time->myr);
		}
		ft_putchar(' ');
	}
	else
	{
		ft_printf("  %s ", entry->time->myr);
	}
	return (1);
}

static int	parse_time(char *s_time, t_ls *new, t_opt *e)
{
	size_t t[8] = {4, 6, 8, 9, 11, 15, 20, 23};
	size_t i;

	i = 0;
	(void)e;
	ft_bzero(new->time->mmon, 4);
	ft_bzero(new->time->myr, 5);
	ft_bzero(new->time->mdate, 3);
	ft_bzero(new->time->mhr, 6);
	ft_bzero(new->time->msec, 3);
	
	while (i < ft_strlen(s_time))
	{
		if (i >= t[0] && i <= t[1])
			new->time->mmon[i - t[0]] = s_time[i];
		if (i >= t[2] && i <= t[3])
			new->time->mdate[i - t[2]] = s_time[i];
		if (i >= t[4] && i <= t[5])
			new->time->mhr[i - t[4]] = s_time[i];
		if (i >= t[6] && i <= t[7])
			new->time->myr[i - t[6]] = s_time[i];
		i++;
	}
	ft_strncpy(new->time->msec, s_time + 17, 2);
	free(s_time);
	return (1);
}

int			get_mtime(struct stat stp, t_ls *new, t_opt *e)
{
	char *s_time;
	new->time = (t_time *)malloc(sizeof(t_time));
	if (e->u)
	{
		s_time = ft_strdup(ctime(&stp.st_atime));
		new->time->mnsec = stp.st_atimespec.tv_nsec;
		new->MT = stp.st_atime;
	}
	else
	{
		s_time = ft_strdup(ctime(&stp.st_mtime));
		new->time->mnsec = stp.st_mtimespec.tv_nsec;
		new->MT = stp.st_mtime;
	}
	parse_time(s_time, new, e);
	return (1);
}

