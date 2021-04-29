#include "philosophers.h"

long int timer_sec(long int secondes)
{
	struct timeval tv;
	long int timestart;
	gettimeofday(&tv,NULL);
	timestart = tv.tv_sec;
	while(((tv.tv_sec - timestart)) < (secondes))
		gettimeofday(&tv,NULL);
	return (tv.tv_sec - timestart);
}

long int timer_usec(long int usecondes)
{
	struct timeval tv;
	long int timestart;
	gettimeofday(&tv,NULL);
	timestart = tv.tv_usec;
	while(((tv.tv_usec - timestart)) < (usecondes))
		gettimeofday(&tv,NULL);
	return (tv.tv_usec - timestart);
}
