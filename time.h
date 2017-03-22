#ifndef TIME_H
# define TIME_H

typedef struct	s_time
{
	time_t				mmod;
	char				mmon[4];
	char				myr[5];
	char				mdate[3];
	char				mhr[6];
	unsigned long int 	mnsec;
}				t_time;

#endif