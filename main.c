#include "philosophers.h"


void *survive(void *arg)
{
	int time = 0;
	int old_time = -1;
	struct timeval tv;
	t_philo *args;
	
	int sleep_process = 250;
	args = (t_philo *) arg;
	if (args->philo_nb % 2)
		usleep(2000);
	while(args_philo.no_die)
	{
		if (sleep_process != 0)
		{
			usleep(sleep_process);
		}
		//printf("%d\n", args_philo.actual_time - args.last_time_philo_eaten);

		if(args->state == EATING)
		{
			if ((args_philo.actual_time - args->last_time_philo_eaten) > (args_philo.time_to_eat))
			{
				pthread_mutex_unlock(args->fork_left);
				pthread_mutex_unlock(args->fork_right);
				args->state = SLEEP;
				args->last_time_philo_sleep = args_philo.actual_time;
				put_action(args_philo.actual_time, args->philo_nb, "is sleeping\n");
				//printf("%d %d is sleeping\n",time, args->philo_nb);
			}
		}
		else if(args->state == SLEEP)
		{
			if ((args_philo.actual_time - args->last_time_philo_sleep) > (args_philo.time_to_sleep))
			{
				args->state = THINKING;
				args->last_time_philo_think = args_philo.actual_time;
				put_action(args_philo.actual_time, args->philo_nb, "is thinking\n");
			}
		}
		else if(args->state == THINKING)
		{
			if (pthread_mutex_lock(args->fork_left)== 0)
			{
				// if ((args_philo.actual_time - args->last_time_philo_eaten) > (args_philo.time_to_die))
				// {
				// 	args_philo.no_die = 0;
				// 	put_action(args_philo.actual_time, args->philo_nb, "is died\n");
				// }
				if (pthread_mutex_lock(args->fork_right) == 0)
				{
					put_action(args_philo.actual_time, args->philo_nb, "has taken a fork\n");
					args->state = EATING;
					args->last_time_philo_eaten = args_philo.actual_time;
					put_action(args_philo.actual_time, args->philo_nb, "is eating\n");
				}
				else
				{
					pthread_mutex_unlock(args->fork_left);
				}
			}
		}
		// put_action(args.last_time_philo_eaten, args.philo_nb, "is amusing\n");
		// put_action(args_philo.actual_time, args.philo_nb, " REAL TIME\n");
		
	}
	return ((void *)1);
}

void check_alive(t_philo *philo)
{
	int i;

	i = 0;
	//printf("nb philo %d\n",args_philo.nb_philo);
	while (i < args_philo.nb_philo)
	{
		//printf("nb_philo in loop %d\n", philo[i].philo_nb);
		//printf("last_time philo eat %d\n", philo[i].last_time_philo_eaten);
		// printf("actual time %d\n", args_philo.actual_time);
		// printf("time to die %d\n", args_philo.time_to_die);
		if ((args_philo.actual_time - philo[i].last_time_philo_eaten) > args_philo.time_to_die)
		{
			put_action(args_philo.actual_time, philo[i].philo_nb, "died\n");
			args_philo.no_die = 0;
		}
		i++;
	}
}

int main(int argc, char **argv)
{
	args_philo.init_time = chrono_init();
	if (argc < 5)
		return (0);
	t_philo *philo;
	args_philo.nb_philo = ft_atoi(argv[1]);
	args_philo.time_to_die = ft_atoi(argv[2]);
	args_philo.time_to_eat = ft_atoi(argv[3]);
	args_philo.time_to_sleep = ft_atoi(argv[4]);
	args_philo.no_die = 1;
	philo = create_philo(args_philo);
	printf("ceci est un test : %d\n", philo[1].philo_nb);
	// printf("%d\n", args_philo.nb_philo);
	// printf("%d\n", args_philo.time_to_die);
	// printf("%d\n", args_philo.time_to_eat);
	// printf("%d\n", args_philo.time_to_sleep);
	while(args_philo.no_die)
	{
		args_philo.actual_time = stamp_time(args_philo.init_time);
		
		usleep(210);
		check_alive(philo);
	};
	pthread_mutex_destroy(&args_philo.auth_write);
	return (1);
}
