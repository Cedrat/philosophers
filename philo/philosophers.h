/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 17:40:53 by lnoaille          #+#    #+#             */
/*   Updated: 2021/06/09 21:18:19 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>

# define EATING 0
# define SLEEP 1
# define THINKING 2

typedef struct s_args_philo
{
	int					nb_philo;
	unsigned long int	time_to_die;
	unsigned long int	time_to_eat;
	unsigned long int	time_to_sleep;
	int					nb_philo_need_eat;
	int					no_die;
	unsigned long int	init_time;
	unsigned long int	actual_time;

}				t_args_philo;

typedef struct s_philo
{
	int				philo_nb;
	int				state;
	int				last_time_philo_eaten;
	int				last_time_philo_sleep;
	int				last_time_philo_think;
	int				nb_meals_eaten;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*auth_write;
	pthread_t		philo_thread;
	t_args_philo	*global_args;
}				t_philo;

bool				init_global_philo_args(int nb_args, char **arg,
						t_args_philo *global_args);
bool				check_philo_died(t_args_philo *global_philo,
						int time_last_meal);
void				ft_putstr(char *str);
void				put_action(int time, int nb, char *action,
						pthread_mutex_t *auth_write);
unsigned long int	chrono_init(void);
unsigned long int	stamp_time(unsigned long int start_time);
void				*survive(void *args);
int					ft_atoi(char *nb);
void				*check_running(void *philo);
t_philo				*create_philo(t_args_philo *args_philo);
t_philo				*init_philo(t_philo *philo, t_args_philo *args_philo);
void				check_all_alive(t_philo *philos,
						t_args_philo *global_philo);
void				philo_eating(t_philo *philo);
void				philo_thinking(t_philo *philo);
void				philo_sleeping(t_philo *philo);
void				check_eat(t_philo *philo, t_args_philo *global_philo);
void				my_usleep(int time);
void				init_first_philo(t_philo *philo, t_args_philo *args_philo);
void				global_philo_init(t_philo *philo, t_args_philo *args_philo,
						int philo_nb);
void				launch_all_thread(t_philo *philo);
void				cleans_philo(t_philo *philo, t_args_philo *t_args_philo);
int					not_a_positive_number(char *str);
void				ft_putstr_fd(char *str, int fd);
int					check_args(int nb_args, char **arg);
bool				is_malloc_error(void *to_check);
int					check_args(int nb_args, char **arg);
bool				check_nb_args(int nb_args);
void				unlock_mutex(t_philo *philo, t_args_philo *args_philo);
void				*check_malloc_fork(t_philo *philo, int nb_philo);

#endif
