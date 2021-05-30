/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 15:09:18 by lnoaille          #+#    #+#             */
/*   Updated: 2021/05/30 18:20:00 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*create_philo(t_args_philo *args_philo)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * (args_philo->nb_philo + 1));
	if (philo == NULL)
		return (philo);
	init_philo(philo, args_philo);
	return (philo);
}

t_philo	*init_philo(t_philo *philo, t_args_philo *args_philo)
{
	int	i;

	i = 1;
	global_philo_init(&philo[0], args_philo, 0);
	init_first_philo(&philo[0], args_philo);
	while ((i + 1) < args_philo->nb_philo)
	{
		global_philo_init(&philo[i], args_philo, i);
		philo[i].fork_left = philo[i - 1].fork_right;
		philo[i].auth_write = philo[0].auth_write;
		philo[i].fork_right = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philo[i].fork_right, NULL);
		i++;
	}
	if (args_philo->nb_philo != 1)
	{
		philo[i].auth_write = philo[0].auth_write;
		global_philo_init(&philo[i], args_philo, i);
		philo[i].fork_right = philo[0].fork_left;
		philo[i].fork_left = philo[i - 1].fork_right;
	}
	if (check_malloc_fork(philo, args_philo->nb_philo) == 0)
		return (NULL);
	launch_all_thread(philo);
	return (philo);
}

void	launch_all_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->global_args->nb_philo)
	{
		pthread_create(&philo[i].philo_thread,
			NULL, survive, (void *)(&philo[i]));
		pthread_detach(philo[i].philo_thread);
		i++;
	}
}

void 	init_first_philo(t_philo *philo, t_args_philo *args_philo)
{
	philo[0].auth_write = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo[0].auth_write, NULL);
	philo[0].fork_left = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo[0].fork_left, NULL);
	if (args_philo->nb_philo == 1)
	{
		pthread_mutex_lock(philo[0].fork_left);
	}
	philo[0].fork_right = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo[0].fork_right, NULL);
}

void	global_philo_init(t_philo *philo, t_args_philo *args_philo,
int philo_nb)
{
	philo->philo_nb = philo_nb + 1;
	philo->state = THINKING;
	philo->last_time_philo_eaten = 0;
	philo->nb_meals_eaten = 0;
	philo->global_args = args_philo;
}
