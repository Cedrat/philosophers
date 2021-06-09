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
	pthread_mutex_unlock(philo[0].fork_right);
	pthread_mutex_unlock(philo[0].fork_left);
	return ((void *)1);
}

void	philo_eating(t_philo *philo)
{
	if (philo->global_args->nb_philo % 2)
	{
		pthread_mutex_lock(philo->fork_left);
		pthread_mutex_lock(philo->fork_right);
	}
	else
	{
		pthread_mutex_lock(philo->fork_right);
		pthread_mutex_lock(philo->fork_left);
	}
	if (philo->global_args->no_die)
	{
		if (philo->global_args->no_die)
		put_action(philo, philo->philo_nb,
			"has taken a fork\n", philo->auth_write);
		philo->state = EATING;
		philo->last_time_philo_eaten = philo->global_args->actual_time;
		if (philo->global_args->no_die)
		put_action(philo, philo->philo_nb,
			"is eating\n", philo->auth_write);
		usleep(philo->global_args->time_to_eat / 2);
	}
}

void	philo_thinking(t_philo *philo)
{
	if ((philo->global_args->actual_time - philo->last_time_philo_eaten)
		> (philo->global_args->time_to_eat))
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		philo->nb_meals_eaten++;
		philo->state = SLEEP;
		philo->last_time_philo_sleep = philo->global_args->actual_time;
		if (philo->global_args->no_die)
			put_action(philo, philo->philo_nb,
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
		if (philo->global_args->no_die)
		put_action(philo, philo->philo_nb,
			"is thinking\n", philo->auth_write);
	}
}
