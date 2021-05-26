/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:45:35 by lnoaille          #+#    #+#             */
/*   Updated: 2021/02/23 14:57:50 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void my_usleep(int time)
{
	int i;
	int decomposition_of_sleep;

	decomposition_of_sleep = 15;
	i = 0;

	while (i < decomposition_of_sleep)
	{
		usleep(time/decomposition_of_sleep);
		i++;
	}
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void  ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

int ft_atoi(char *nb)
{
	int i;
	int int_nb;
	int minus;

	minus = 1;
	int_nb = 0;
	i = 0;
	while(nb[i] == ' ' || nb[i] == '\t' || nb[i] == '\n')
		i++;
	if (nb[i] == '-')
	{
		minus = -1;
		i++;
	}
	while(nb[i])
	{
		int_nb = int_nb * 10 + (nb[i] - '0');
		i++;
	}
	return (int_nb * minus);
}

void put_action(int time, int nb, char *action, pthread_mutex_t *auth_write)
{
	
	char all_action[50];
	int i = 0;

	int power = 0;
	int copy_time;

	copy_time = time;
		
	while (copy_time > 0)
	{
		if (power == 0)
			power = 1;
		else
			power *= 10;
		copy_time /=10;
	}
	if (power == 0)
	{
		all_action[i] = '0';
		power = 0;
		i++;
	}
	while (power >= 1)
	{
		// printf("%d\n", power);
		all_action[i] = (time / (power)) + '0';
		time = time % power;
		i++;
		power /= 10;
	}
	all_action[i] = ' ';
	i++;

	int copy_nb;

	copy_nb = nb;
	power = 0;
	while (copy_nb != 0)
	{
				if (power == 0)
			power = 1;
		else
			power *= 10;
		copy_nb /=10;
	}
	if (power == 0)
	{
		all_action[i] = '0';
		power = 0;
		i++;
	}

	while (power >= 1)
	{
		all_action[i] = (nb / power) + '0';
		nb = nb % power;
		i++;
		power /= 10;
	}
	int p;
	p = 0;

		all_action[i] = ' ';
	i++;
	while(action[p])
	{
		all_action[i] = action[p];
		p++;
		i++;
	}
	all_action[i] = '\0';
	pthread_mutex_lock(auth_write);
	ft_putstr(all_action);
	pthread_mutex_unlock(auth_write);
}