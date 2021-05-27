
#include "philosophers.h"

unsigned long int chrono_init(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    unsigned long int start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return (start_time);
}

unsigned long int stamp_time(unsigned long int start_time)
{
    unsigned long int actual_time;
    struct timeval tv;
    gettimeofday(&tv, NULL);

    actual_time = (tv.tv_sec * 1000 + tv.tv_usec / 1000) - start_time;
    return (actual_time);
}
