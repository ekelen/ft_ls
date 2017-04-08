#ifndef TIME_H
# define TIME_H

# include <time.h>

# define MT time->mtime
# define MS time->mnsec
# define SMT st_mtime
# define AMT st_atime
# define SMS st_mtimespec.tv_nsec
# define AMS st_atimespec.tv_nsec

typedef struct	s_time
{
	time_t				mtime;
	char				mmon[4];
	char				myr[5];
	char				mdate[3];
	char				mhr[6];
	char				msec[3];
	unsigned long int 	mnsec;
}				t_time;

#endif