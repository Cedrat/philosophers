#include "philosophers.h"

void	*survive(void *arg)
{
	t_philo	*philo;
	int		sleep_process;

	philo = (t_philo *) arg;
	sleep_process = philo->global_args->nb_philo * 10;
	if ((philo->global_args->nb_philo % 2) == 0 && philo->philo_nb % 2)
		usleep(sleep_process);
	while (philo->global_args->no_die)
	{
		if (philo->state == EATING)
			philo_thinking(philo);
		else if (philo->state == SLEEP)
			philo_sleeping(philo);
		else if (philo->state == THINKING)
			philo_eating(philo);
		usleep(1000);
	}
	return ((void *)1);
}

void	philo_eating(t_philo *philo)
{
	dprintf(2, "here\n");

	sem_wait(philo->forks);
	sem_wait(philo->forks);
	dprintf(2, "here\n");
	if (philo->global_args->no_die)
	{
		put_action(philo->global_args->actual_time, philo->philo_nb,
			"has taken a fork\n", philo->auth_write);
		philo->state = EATING;
		philo->last_time_philo_eaten = philo->global_args->actual_time;
		put_action(philo->global_args->actual_time, philo->philo_nb,
			"is eating\n", philo->auth_write);
		usleep(philo->global_args->time_to_eat / 2);
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
		usleep(philo->global_args->time_to_sleep / 2);
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
