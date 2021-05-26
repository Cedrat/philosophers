#include "philosophers.h"

void *survive(void *arg)
{
	t_philo *philo;
	int sleep_process;
    
    sleep_process = args_philo.nb_philo * 10;
	philo = (t_philo *) arg;
	if ((args_philo.nb_philo % 2) == 0 && philo->philo_nb % 2)
		usleep(sleep_process);
	while(args_philo.no_die)
	{
		if(philo->state == EATING)
            philo_thinking(philo);
		else if(philo->state == SLEEP)
			philo_sleeping(philo);
		else if(philo->state == THINKING)
			philo_eating(philo);
        usleep(sleep_process);
	}
	return ((void *)1);
}

void philo_eating(t_philo *philo)
{
    if (args_philo.nb_philo % 2)
    {
        pthread_mutex_lock(philo->fork_left);
        pthread_mutex_lock(philo->fork_right);
        put_action(args_philo.actual_time, philo->philo_nb, "has taken a fork\n", philo->auth_write);
        philo->state = EATING;
        philo->last_time_philo_eaten = args_philo.actual_time;
        put_action(args_philo.actual_time, philo->philo_nb, "is eating\n", philo->auth_write);
    }
    else
    {
        pthread_mutex_lock(philo->fork_right);
        pthread_mutex_lock(philo->fork_left);
        put_action(args_philo.actual_time, philo->philo_nb, "has taken a fork\n", philo->auth_write);
        philo->state = EATING;
        philo->last_time_philo_eaten = args_philo.actual_time;
        put_action(args_philo.actual_time, philo->philo_nb, "is eating\n", philo->auth_write);
    }
}
void philo_thinking(t_philo *philo)
{
    if ((args_philo.actual_time - philo->last_time_philo_eaten) > (args_philo.time_to_eat))
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		philo->nb_meals_eaten++;
		philo->state = SLEEP;
		philo->last_time_philo_sleep = args_philo.actual_time;
    	put_action(args_philo.actual_time, philo->philo_nb, "is sleeping\n", philo->auth_write);
    }
}

void philo_sleeping(t_philo *philo)
{
    if ((args_philo.actual_time - philo->last_time_philo_sleep) > (args_philo.time_to_sleep))
	{
		philo->state = THINKING;
		philo->last_time_philo_think = args_philo.actual_time;
		put_action(args_philo.actual_time, philo->philo_nb, "is thinking\n", philo->auth_write);
	}
}
