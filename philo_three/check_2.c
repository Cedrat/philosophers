/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 17:02:11 by lnoaille          #+#    #+#             */
/*   Updated: 2021/06/03 17:38:17 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*all_philo_ate_enough(void *philos)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *) philos;
	i = philo->global_args->nb_philo;
	while (i)
	{
		sem_wait(philo->global_args->ate_enough);
		i--;
	}
	sem_wait(philo->auth_write);
	ft_putstr("All the philosophers ate enough\n");
	sem_post(philo->global_args->one_dead);
	return ((void *)1);
}

int	check_eat(t_philo *philo, t_args_philo *global_philo)
{
	if (global_philo->nb_philo_need_eat <= philo->nb_meals_eaten)
	{
		sem_post(global_philo->ate_enough);
		return (1);
	}
	return (0);
}

void	*check_malloc_fork(t_philo *philo, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (philo[i].forks == NULL)
			return (NULL);
		i++;
	}
	return ((void *)1);
}
