/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 15:09:18 by lnoaille          #+#    #+#             */
/*   Updated: 2021/02/23 16:12:50 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo * create_philo(t_args_philo args_philo)
{
	t_philo *philo;

	philo = malloc(sizeof(t_philo) * args_philo.nb_philo);

	init_philo(philo, args_philo);
	return (philo);
}

int init_philo(t_philo *philo, t_args_philo args_philo)
{
	int i;

	i = 0;
	philo[0].philo_nb = i + 1;
	philo[i].state = THINKING;
	philo[i].last_time_philo_eaten = 0;
	philo[0].fork_left = malloc(sizeof(pthread_mutex_t));
	philo[0].fork_right = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo[0].fork_left, NULL);
	pthread_mutex_init(philo[0].fork_right, NULL);
	pthread_create(&philo[0].philo_thread, NULL, survive, (void *)(&philo[0]));
	// printf("philo %d was created\n", philo[0].philo_nb);
	i++;

	while ((i + 1) < args_philo.nb_philo)
	{
		philo[i].philo_nb = i + 1;
		philo[i].fork_left = philo[i - 1].fork_right;
		philo[i].state = THINKING;
		philo[i].last_time_philo_eaten = 0;
		philo[i].fork_right = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philo[i].fork_right, NULL);
		pthread_create(&philo[i].philo_thread, NULL, survive, (void *)(&philo[i]));
		// printf("philo %d was created\n", philo[i].philo_nb);
		i++;
	}
	philo[i].philo_nb = i + 1;
	philo[i].state = THINKING;
	philo[i].last_time_philo_eaten = 0;
	philo[i].fork_right = philo[0].fork_left;
	philo[i].fork_left = philo[i - 1].fork_right;
	//pthread_mutex_init(philo[i].fork_left, NULL);
	pthread_create(&philo[i].philo_thread, NULL, survive, (void *)(&philo[i]));
	//printf("philo %d was created\n", philo[i].philo_nb);
	return (1);
}
