/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 16:10:42 by lnoaille          #+#    #+#             */
/*   Updated: 2021/05/28 15:27:12 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_running(t_philo *philo, t_args_philo *global_philo)
{
	if (global_philo->nb_philo_need_eat != -1)
	{
		while (global_philo->no_die)
		{
			global_philo->actual_time = stamp_time(global_philo->init_time);
			check_eat(philo, global_philo);
			check_all_alive(philo, global_philo);
			usleep(200);
		}
	}
	else
	{
		while (global_philo->no_die)
		{
			global_philo->actual_time = stamp_time(global_philo->init_time);
			check_all_alive(philo, global_philo);
			usleep(200);
		}
	}
}

void	check_all_alive(t_philo *philo, t_args_philo *global_philo)
{
	int	i;

	i = 0;
	while (i < global_philo->nb_philo && global_philo->no_die)
	{
		if (check_philo_died(global_philo, philo[i].last_time_philo_eaten))
		{
			global_philo->no_die = 0;
			usleep(2000);
			put_action(global_philo->actual_time,
				philo[i].philo_nb, "died\n", &philo[i].auth_write);
			pthread_mutex_lock(&philo[i].auth_write);
			global_philo->no_die = 0;
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
		if (global_philo->nb_philo_need_eat <= philo->nb_meals_eaten)
			nb_philo_eaten_enough++;
		i++;
	}
	if (nb_philo_eaten_enough == i)
	{
		global_philo->no_die = 0;
		usleep(2000);
		pthread_mutex_lock(&philo->auth_write);
		ft_putstr("All the philosophers had eat enough\n");
	}
}
