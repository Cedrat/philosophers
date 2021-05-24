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
#include <unistd.h>

#define EATING 0
#define SLEEP 1
#define THINKING 2



typedef struct s_philo
{
	int philo_nb;
	int state;
	int last_time_philo_eaten;
	int last_time_philo_sleep;
	int last_time_philo_think;
	pthread_mutex_t *fork_left;
	pthread_mutex_t *fork_right;
	pthread_t philo_thread;
}				t_philo;

typedef struct s_args_philo
{
	int nb_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int no_die;
	int init_time;
	int actual_time;
	t_philo **philo;
}				t_args_philo;

void put_action(int time, int nb, char *action);
int chrono_init(void);
int stamp_time(int start_time);
long int	timer_usec(long int usecondes);
long int	timer_sec(long int secondes);
void *five_sec(void *times);
void *survive(void *args);
int 		ft_atoi(char *nb);
t_philo * create_philo(t_args_philo args_philo);
int init_philo(t_philo *philo, t_args_philo args_philo);



#endif
