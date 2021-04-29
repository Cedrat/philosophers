#include "philosophers.h"

void *five_sec(void *times)
{
	long int time = (long int)(times);
	timer_sec(time);
	printf("%ld\n", time);
}

int main(int argc, char **argv)
{
	// pthread_t timer_1;
	// pthread_t timer_2;
	//
	// pthread_create(&timer_1, NULL, five_sec, (void *)2);
	// pthread_create(&timer_2, NULL, five_sec, (void *)4);
	// pthread_join(timer_1, NULL);
	// pthread_create(&timer_1, NULL, five_sec, (void *)2);
	// pthread_join(timer_1, NULL);
	//timer_sec(atoi(argv[1]));
	//timer_usec(atoi(argv[1]));
	if (argc < 5)
		return (0);
	t_args_philo args_philo;
	args_philo.nb_philo = ft_atoi(argv[1]);
	args_philo.time_to_die = ft_atoi(argv[2]);
	args_philo.time_to_eat = ft_atoi(argv[3]);
	args_philo.time_to_sleep = ft_atoi(argv[4]);
	create_philo(args_philo);
	printf("%d\n", args_philo.nb_philo);
	printf("%d\n", args_philo.time_to_die);
	printf("%d\n", args_philo.time_to_eat);
	printf("%d\n", args_philo.time_to_sleep);
}
