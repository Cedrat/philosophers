#include "philosophers.h"

void	*survive(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	philo->forks = sem_open("/forks", 0);
	philo->global_args->one_dead = sem_open("/oneDead", 0);
	philo->global_args->ate_enough = sem_open("/meals", 0);
	pthread_create(&philo->philo_thread, NULL, check_running, (void *)philo);
	pthread_detach(philo->philo_thread);
	if (philo->philo_nb % 2)
		usleep(5000);
	while (philo->global_args->no_die)
	{
		if (philo->state == EATING)
			philo_thinking(philo);
		else if (philo->state == SLEEP)
			philo_sleeping(philo);
		else if (philo->state == THINKING)
			philo_eating(philo);
		usleep(1000);
		philo->global_args->actual_time = stamp_time(
				philo->global_args->init_time);
	}
	return ((void *)1);
}

void	philo_eating(t_philo *philo)
{
	if (philo->global_args->no_die)
	{
		sem_wait(philo->forks);
		put_action(philo->global_args->actual_time, philo->philo_nb,
			"has taken a fork\n", philo->auth_write);
		sem_wait(philo->forks);
		philo->state = EATING;
		philo->last_time_philo_eaten = philo->global_args->actual_time;
		put_action(philo->global_args->actual_time, philo->philo_nb,
			"is eating\n", philo->auth_write);
		usleep(philo->global_args->time_to_eat * 750);
	}
}

void	philo_thinking(t_philo *philo)
{
	if ((philo->global_args->actual_time - philo->last_time_philo_eaten)
		> (philo->global_args->time_to_eat))
	{
		sem_post(philo->forks);
		sem_post(philo->forks);
		philo->nb_meals_eaten++;
		philo->state = SLEEP;
		philo->last_time_philo_sleep = philo->global_args->actual_time;
		put_action(philo->global_args->actual_time, philo->philo_nb,
			"is sleeping\n", philo->auth_write);
		usleep(philo->global_args->time_to_sleep * 750);
	}
}

void	philo_sleeping(t_philo *philo)
{
	if ((philo->global_args->actual_time - philo->last_time_philo_sleep)
		> (philo->global_args->time_to_sleep))
	{
		philo->state = THINKING;
		philo->last_time_philo_think = philo->global_args->actual_time;
		put_action(philo->global_args->actual_time, philo->philo_nb,
			"is thinking\n", philo->auth_write);
	}
}
