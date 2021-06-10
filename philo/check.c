/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 16:10:42 by lnoaille          #+#    #+#             */
/*   Updated: 2021/06/10 15:06:47 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*check_running(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *) philos;
	if (philo->global_args->nb_philo_need_eat != -1)
	{
		while (philo->global_args->no_die)
		{
			philo->global_args->actual_time = stamp_time(
					philo->global_args->init_time);
			check_eat(philo, philo->global_args);
			check_all_alive(philo, philo->global_args);
			usleep(200);
		}
	}
	else
	{
		while (philo->global_args->no_die)
		{
			philo->global_args->actual_time = stamp_time(
					philo->global_args->init_time);
			check_all_alive(philo, philo->global_args);
			usleep(200);
		}
	}
	return ((void *)1);
}

void	check_all_alive(t_philo *philo, t_args_philo *global_philo)
{
	int	i;

	i = 0;
	while (i < global_philo->nb_philo && global_philo->no_die)
	{
		if (check_philo_died(global_philo, philo[i].last_time_philo_eaten))
		{
			usleep(1000);
			put_action(philo,
				philo[i].philo_nb, "died\n", philo[i].auth_write);
			global_philo->no_die = 0;
			if (philo->global_args->nb_philo == 1)
			{
				pthread_mutex_unlock(philo[0].fork_right);
				pthread_mutex_unlock(philo[0].fork_left);
			}
		}
		i++;
	}
}

bool	check_philo_died(t_args_philo *global_philo, int time_last_meal)
{
	if ((global_philo->actual_time - time_last_meal)
		> global_philo->time_to_die)
		return (1);
	return (0);
}

void	check_eat(t_philo *philo, t_args_philo *global_philo)
{
	int	i;
	int	nb_philo_eaten_enough;

	i = 0;
	nb_philo_eaten_enough = 0;
	while (i < global_philo->nb_philo)
	{
		if (global_philo->nb_philo_need_eat < philo->nb_meals_eaten)
			nb_philo_eaten_enough++;
		i++;
	}
	if (nb_philo_eaten_enough == global_philo->nb_philo)
	{
		global_philo->no_die = 0;
		usleep(2000);
		pthread_mutex_lock(philo->auth_write);
		ft_putstr("All the philosophers had eat enough\n");
	}
}

void	*check_malloc_fork(t_philo *philo, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (philo[i].fork_right == NULL)
			return (NULL);
		i++;
	}
	if (nb_philo == 1 && philo[0].fork_right == NULL)
		return (NULL);
	return ((void *)1);
}
