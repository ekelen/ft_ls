#include "ft_ls.h"

int			print_time(t_opt *e, t_ls *entry)
{
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
			ft_printf(":%s %s", entry->time->msec, entry->time->myr);
		ft_putchar(' ');
	}
	else
		ft_printf("  %s ", entry->time->myr);
	return (1);
}

static int	parse_time(char *s_time, t_ls *new)
{
	ft_bzero(new->time->mmon, 4);
	ft_bzero(new->time->myr, 5);
	ft_bzero(new->time->mdate, 3);
	ft_bzero(new->time->mhr, 6);
	ft_bzero(new->time->msec, 3);
	ft_strncpy(new->time->mmon, s_time + 4, 3);
	ft_strncpy(new->time->mdate, s_time + 8, 2);
	ft_strncpy(new->time->mhr, s_time + 11, 5);
	ft_strncpy(new->time->myr, s_time + 20, 4);
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
		s_time = ft_strdup(ctime(&stp.AMT));
		new->time->mnsec = stp.AMS;
		new->MT = stp.AMT;
	}
	else
	{
		s_time = ft_strdup(ctime(&stp.SMT));
		new->time->mnsec = stp.SMS;
		new->MT = stp.SMT;
	}
	parse_time(s_time, new);
	return (1);
}

