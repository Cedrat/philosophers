/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 16:31:15 by lnoaille          #+#    #+#             */
/*   Updated: 2021/05/27 16:31:16 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_args_philo	*args_philo;

	args_philo = malloc(sizeof(t_args_philo));
	if (init_global_philo_args(argc, argv, args_philo) == 0)
		return (0);
	args_philo->actual_time = stamp_time(args_philo->init_time);
	philo = create_philo(args_philo);
	check_running(philo, args_philo);
	// TODO all cleans.
	return (1);
}

bool	init_global_philo_args(int nb_args,
char **arg, t_args_philo *global_args)
{
	global_args->init_time = chrono_init();
	if (nb_args < 5 || nb_args > 6)
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
