
#include "philosophers.h"

int chrono_init(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    int start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return (start_time);
}

int stamp_time(int start_time)
{
    int actual_time;
    struct timeval tv;
    gettimeofday(&tv, NULL);

    actual_time = (tv.tv_sec * 1000 + tv.tv_usec / 1000) - start_time;
    return (actual_time);
}
