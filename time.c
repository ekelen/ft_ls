#include "ft_ls.h"

int			print_time(t_ls *entry, t_dir *cwd)
{
	(void)cwd;
	time_t now;

    now = time(0);
	ft_printf(" %s", entry->time->mmon);
	ft_printf(" %s", entry->time->mdate);
	if (ft_abs(now - entry->time->mmod) < (31540000 / 2))
		ft_printf(" %s ", entry->time->mhr);
	else
		ft_printf("  %s ", entry->time->myr);
	free(entry->time);
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
	free(s_time);
	return (1);
}

int			get_mtime(struct stat stp, t_ls *new, t_opt *e)
{
	//char s_time[25];
	char *s_time;

	//s_time = malloc(sizeof(25));
	s_time = ft_strdup(ctime(&stp.st_mtime));
	new->time = (t_time *)malloc(sizeof(t_time));
	//new->time = NULL;
	new->time->mnsec = stp.st_atimespec.tv_sec;
	new->time->mmod = stp.st_mtime;
	//ft_strcpy(s_time, ctime(&stp.st_mtime));
	//ft_printf("%s\n", ctime(&stp.st_mtime));
	parse_time(s_time, new, e);
	return (1);
}