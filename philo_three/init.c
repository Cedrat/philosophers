/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 15:09:18 by lnoaille          #+#    #+#             */
/*   Updated: 2021/06/03 17:39:36 by lnoaille         ###   ########.fr       */
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
	launch_all_process(philo);
	return (philo);
}

void	launch_all_process(t_philo *philo)
{
	int			i;
	int			*pid;
	pthread_t	master_eat;

	i = 0;
	pid = malloc(sizeof(int) * philo->global_args->nb_philo);
	if (philo->global_args->nb_philo_need_eat != -1)
		pthread_create(&master_eat, NULL, all_philo_ate_enough, (void *)philo);
	while (i < philo->global_args->nb_philo)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			survive((void *)&philo[i]);
		i++;
	}
	sem_wait(philo->global_args->one_dead);
	while (i)
	{
		kill(pid[i - 1], SIGINT);
		i--;
	}
	free(pid);
}

void 	init_first_philo(t_philo *philo, t_args_philo *args_philo)
{
	philo[0].auth_write = malloc(sizeof(sem_t));
	philo[0].auth_write = sem_open("/authWrite", O_CREAT, 0777, 1);
	philo[0].forks = malloc(sizeof(sem_t));
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
