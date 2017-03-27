#ifndef TIME_H
# define TIME_H

# include <time.h>

# define MT time->mtime
# define MS time->mnsec

typedef struct	s_time
{
	time_t				mtime;
	char				mmon[4];
	char				myr[5];
	char				mdate[3];
	char				mhr[6];
	unsigned long int 	mnsec;
}				t_time;

#endif