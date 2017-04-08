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
	s_time = ft_strdup(ctime(&stp.st_mtime));
	new->time = (t_time *)malloc(sizeof(t_time));
	new->time->mnsec = stp.st_mtimespec.tv_nsec;
	new->MT = stp.st_mtime;
	parse_time(s_time, new, e);
	return (1);
}

// printtime(time_t ftime)
// {
// 	char longstring[80];
// 	static time_t now;
// 	const char *format;
// 	static int d_first = -1;

// #ifndef __APPLE__
// 	if (d_first < 0)
// 		d_first = (*nl_langinfo(D_MD_ORDER) == 'd');
// #endif /* __APPLE__ */
// 	if (now == 0)
// 		now = time(NULL);

// #define	SIXMONTHS	((365 / 2) * 86400)
// 	if (f_sectime)
// 		/* mmm dd hh:mm:ss yyyy || dd mmm hh:mm:ss yyyy */
// 		format = d_first ? "%e %b %T %Y " : "%b %e %T %Y ";
// 	else if (ftime + SIXMONTHS > now && ftime < now + SIXMONTHS)
// 		/* mmm dd hh:mm || dd mmm hh:mm */
// 		format = d_first ? "%e %b %R " : "%b %e %R ";
// 	else
// 		/* mmm dd  yyyy || dd mmm  yyyy */
// 		format = d_first ? "%e %b  %Y " : "%b %e  %Y ";
// 	strftime(longstring, sizeof(longstring), format, localtime(&ftime));
// 	fputs(longstring, stdout);
// }
