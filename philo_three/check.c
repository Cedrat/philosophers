/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 16:10:42 by lnoaille          #+#    #+#             */
/*   Updated: 2021/06/03 17:28:56 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*check_running(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *) philos;
	if (philo->global_args->nb_philo_need_eat != -1)
	{
		check_with_meals(philo);
	}
	else
	{
		check_with_no_meals(philo);
	}
	return ((void *)1);
}

void	check_with_no_meals(t_philo *philo)
{
	while (philo->global_args->no_die)
	{
		philo->global_args->actual_time = stamp_time(
				philo->global_args->init_time);
		check_all_alive(philo, philo->global_args);
		usleep(1000);
	}
}

void	check_with_meals(t_philo *philo)
{
	bool	check_meal;

	check_meal = 0;
	while (philo->global_args->no_die)
	{
		philo->global_args->actual_time = stamp_time(
				philo->global_args->init_time);
		if (check_meal == 0)
			check_meal = check_eat(philo, philo->global_args);
		check_all_alive(philo, philo->global_args);
		usleep(1000);
	}
}

void	check_all_alive(t_philo *philo, t_args_philo *global_philo)
{
	if (check_philo_died(global_philo, philo->last_time_philo_eaten))
	{
		global_philo->no_die = 0;
		usleep(2000);
		put_action(global_philo->actual_time,
			philo->philo_nb, "died\n", philo->auth_write);
		sem_wait(philo->auth_write);
		sem_post(philo->global_args->one_dead);
		global_philo->no_die = 0;
	}
}

bool	check_philo_died(t_args_philo *global_philo, int time_last_meal)
{
	if ((global_philo->actual_time - time_last_meal)
		> global_philo->time_to_die)
		return (1);
	return (0);
}
