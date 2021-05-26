#include "philosophers.h"


void check_all_alive(t_philo *philo)
{
	int i;

	i = 0;
	while (i < args_philo.nb_philo)
	{
		if (check_philo_died(philo[i].last_time_philo_eaten))
		{
			put_action(args_philo.actual_time, philo[i].philo_nb, "died\n", philo[i].auth_write);
			args_philo.no_die = 0;
		}
		i++;
	}
}

bool check_philo_died(int time_last_meal)
{
	if ((args_philo.actual_time - time_last_meal) > args_philo.time_to_die)
		return (1);
	return (0);
}

void check_eat(t_philo *philo)
{
	int i;
	int nb_philo_eaten_enough;

	i = 0;
	nb_philo_eaten_enough = 0;

	while(i < args_philo.nb_philo)
	{
		if (args_philo.nb_philo_need_eat <= philo->nb_meals_eaten)
			nb_philo_eaten_enough++;
		i++;
	}
	if (nb_philo_eaten_enough == i)
	{
		args_philo.no_die = 0;
		pthread_mutex_lock(philo->auth_write);
		ft_putstr("All the philosophers had eat enough\n");
		pthread_mutex_unlock(philo->auth_write);
	}
}
int main(int argc, char **argv)
{
	t_philo *philo;

	if (init_global_philo_args(argc, argv) == 0)
		return (0);
	philo = create_philo(args_philo);
	check_running(philo);
	// TODO all cleans.
	return (1);
}

bool init_global_philo_args(int nb_args, char **arg)
{
	args_philo.init_time = chrono_init();
	if (nb_args < 5 || nb_args > 6)
		return (0);
	args_philo.nb_philo = ft_atoi(arg[1]);
	args_philo.time_to_die = ft_atoi(arg[2]);
	args_philo.time_to_eat = ft_atoi(arg[3]);
	args_philo.time_to_sleep = ft_atoi(arg[4]);
	args_philo.nb_philo_need_eat = -1;
	if (nb_args == 6)
	{
		args_philo.nb_philo_need_eat = ft_atoi(arg[5]);
	}
	args_philo.no_die = 1;
	return (1);
}

void check_running(t_philo * philo)
{
	if (args_philo.nb_philo_need_eat != -1)
	{
		while(args_philo.no_die)
		{
			args_philo.actual_time = stamp_time(args_philo.init_time);
			check_all_alive(philo);
			check_eat(philo);
			usleep(200);
		}
	}
	else
	{
		while(args_philo.no_die)
		{
			args_philo.actual_time = stamp_time(args_philo.init_time);
			usleep(210);
			check_all_alive(philo);
		}
	}
}