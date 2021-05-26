/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init->c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student->42->fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 15:09:18 by lnoaille          #+#    #+#             */
/*   Updated: 2021/02/23 16:12:50 by lnoaille         ###   ########->fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo * create_philo(t_args_philo args_philo)
{
	t_philo *philo;

	philo = malloc(sizeof(t_philo) * (args_philo.nb_philo + 1));
	init_philo(philo, args_philo);
	return (philo);
}

t_philo *init_philo(t_philo *philo, t_args_philo args_philo)
{
	int i;

	i = 0;
	init_first_philo(&philo[0]);
	//pthread_create(&philo[0].philo_thread, NULL, survive, (void *)(&philo[0]));
	i++;

	while ((i + 1) < args_philo.nb_philo)
	{
		philo[i].auth_write = philo[0].auth_write;
		philo[i].philo_nb = i + 1;
		philo[i].fork_left = philo[i - 1].fork_right;
		philo[i].state = THINKING;
		philo[i].last_time_philo_eaten = 0;
		philo[i].nb_meals_eaten = 0;
		philo[i].fork_right = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philo[i].fork_right, NULL);
		//pthread_create(&philo[i].philo_thread, NULL, survive, (void *)(&philo[i]));
		i++;
	}
	philo[i].auth_write = philo[0].auth_write;
	philo[i].philo_nb = i + 1;
	philo[i].state = THINKING;
	philo[i].last_time_philo_eaten = 0;
	philo[i].nb_meals_eaten = 0;
	philo[i].fork_right = philo[0].fork_left;
	philo[i].fork_left = philo[i - 1].fork_right;
	//pthread_create(&philo[i].philo_thread, NULL, survive, (void *)(&philo[i]));
	launch_all_thread(philo);
	return (philo);
}

void launch_all_thread(t_philo *philo)
{
	int i;

	i = 0;
	while (i < args_philo.nb_philo)
	{
		pthread_create(&philo[i].philo_thread, NULL, survive, (void *)(&philo[i]));
		i++;
	}
}

void init_first_philo(t_philo *philo)
{
	philo->auth_write = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo[0].auth_write, NULL);
	philo->philo_nb = 1;
	philo->state = THINKING;
	philo->last_time_philo_eaten = 0;
	philo->nb_meals_eaten = 0;
	philo->fork_left = malloc(sizeof(pthread_mutex_t));
	philo->fork_right = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->fork_left, NULL);
	pthread_mutex_init(philo->fork_right, NULL);
}