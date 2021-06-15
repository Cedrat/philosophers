/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 16:31:15 by lnoaille          #+#    #+#             */
/*   Updated: 2021/05/31 16:30:05 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_args_philo	*args_philo;

	unlink_sem();
	args_philo = malloc(sizeof(t_args_philo));
	if (is_malloc_error(args_philo))
		return (0);
	if (init_global_philo_args(argc, argv, args_philo) == 0)
	{
		free(args_philo);
		return (0);
	}
	args_philo->actual_time = stamp_time(args_philo->init_time);
	philo = create_philo(args_philo);
	if (is_malloc_error(philo))
	{
		free(args_philo);
		return (0);
	}
	check_running(philo, args_philo);
	unlink_sem();
	usleep(20000);
	cleans_philo(philo);
	return (1);
}

bool	init_global_philo_args(int nb_args,
char **arg, t_args_philo *global_args)
{
	global_args->init_time = chrono_init();
	if (check_args(nb_args, arg) == 0)
		return (0);
	global_args->nb_philo = ft_atoi(arg[1]);
	global_args->time_to_die = ft_atoi(arg[2]);
	global_args->time_to_eat = ft_atoi(arg[3]);
	global_args->time_to_sleep = ft_atoi(arg[4]);
	global_args->nb_philo_need_eat = -1;
	if (nb_args == 6)
	{
		global_args->nb_philo_need_eat = ft_atoi(arg[5]);
	}
	global_args->no_die = 1;
	return (1);
}

void	cleans_philo(t_philo *philo)
{
	free(philo[0].global_args);
	free(philo);
}

void	unlink_sem(void)
{
	sem_close("/forks");
	sem_close("/authWrite");
	sem_unlink("/forks");
	sem_unlink("/authWrite");
}
