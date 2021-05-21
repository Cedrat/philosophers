#include "philosophers.h"

	t_args_philo args_philo;

void *five_sec(void *times)
{
	long int time = (long int)(times);
	timer_sec(time);
	return ((void *)time);
}

void *survive(void *arg)
{
	int time = 0;
	int old_time = -1;
	struct timeval tv;
	t_philo args;
	
	int sleep_process = 0;
	args = *(t_philo *) arg;
	while(args_philo.no_die)
	{
		if (sleep_process != 0)
		{
			usleep(sleep_process);
		}
		gettimeofday(&tv, NULL);
		// if ((tv.tv_usec / 1000) < time)
		// 	time += tv.tv_usec / 1000;
		// else
			time = (tv.tv_usec / 1000);

		//printf("time = %d\n", time);
		if(args.state == EATING)
		{
			if ((time - args.last_time_philo_eaten) > (args_philo.time_to_eat))
			{
				args.state = SLEEP;
				args.last_time_philo_sleep = time;
				printf("%d %d is sleeping\n",time - args_philo.init_time, args.philo_nb);
				sleep_process = args_philo.time_to_eat / 10;
			}
		}
		else if(args.state == SLEEP)
		{
			if ((time - args.last_time_philo_sleep) > (args_philo.time_to_sleep))
			{
				args.state = THINKING;
				args.last_time_philo_think = time;
				printf("%d %d is thinking\n",time - args_philo.init_time, args.philo_nb);
			}
		}
		else if(args.state == THINKING)
		{
			args.state = EATING;
			args.last_time_philo_eaten = time;
			printf("%d %d is eating\n",time - args_philo.init_time, args.philo_nb);
		}
		if ((time - args.last_time_philo_eaten) > (args_philo.time_to_die))
		{
			args_philo.no_die = 0;
			printf("%d %d is died\n",time - args_philo.init_time, args.philo_nb);
		}
	}
	return ((void *)1);
}

int main(int argc, char **argv)
{
	struct timeval tv;
	gettimeofday(&tv, 0);
	args_philo.init_time = tv.tv_usec/1000;
	if (argc < 5)
		return (0);
	args_philo.nb_philo = ft_atoi(argv[1]);
	args_philo.time_to_die = ft_atoi(argv[2]);
	args_philo.time_to_eat = ft_atoi(argv[3]);
	args_philo.time_to_sleep = ft_atoi(argv[4]);
	args_philo.no_die = 1;
	create_philo(args_philo);
	// printf("%d\n", args_philo.nb_philo);
	// printf("%d\n", args_philo.time_to_die);
	// printf("%d\n", args_philo.time_to_eat);
	// printf("%d\n", args_philo.time_to_sleep);
	while(args_philo.no_die)
	{};
	return (1);
}
