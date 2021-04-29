/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 17:40:53 by lnoaille          #+#    #+#             */
/*   Updated: 2021/02/23 16:10:54 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <sys/time.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_args_philo
{
	int nb_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
}				t_args_philo;

typedef struct s_philo
{
	int philo_nb;
	pthread_mutex_t fork_left;
	pthread_mutex_t fork_right;
	pthread_t philo_thread;
}				t_philo;

long int	timer_usec(long int usecondes);
long int	timer_sec(long int secondes);
void *five_sec(void *times);
int 		ft_atoi(char *nb);
int create_philo(t_args_philo args_philo);
int init_philo(t_philo *philo, t_args_philo args_philo);



#endif
