/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 15:09:18 by lnoaille          #+#    #+#             */
/*   Updated: 2021/06/03 21:42:56 by lnoaille         ###   ########.fr       */
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
		philo[i].forks = philo[0].forks;
		philo[i].auth_write = philo[0].auth_write;
		i++;
	}
	if (args_philo->nb_philo != 1)
	{
		philo[i].auth_write = philo[0].auth_write;
		global_philo_init(&philo[i], args_philo, i);
		philo[i].forks = philo[0].forks;
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
	philo[0].auth_write = sem_open("/authWrite", O_CREAT, 0777, 1);
	philo[0].forks = sem_open("/forks", O_CREAT, 0777, args_philo->nb_philo);
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
