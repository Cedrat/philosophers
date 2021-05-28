/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:45:35 by lnoaille          #+#    #+#             */
/*   Updated: 2021/05/28 15:05:32 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	my_usleep(int time)
{
	int	i;
	int	decomposition_of_sleep;

	decomposition_of_sleep = 15;
	i = 0;
	while (i < decomposition_of_sleep)
	{
		usleep(time / decomposition_of_sleep);
		i++;
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

int	ft_atoi(char *nb)
{
	int	i;
	int	int_nb;
	int	minus;

	minus = 1;
	int_nb = 0;
	i = 0;
	while (nb[i] == ' ' || nb[i] == '\t' || nb[i] == '\n')
		i++;
	if (nb[i] == '-')
	{
		minus = -1;
		i++;
	}
	while (nb[i])
	{
		int_nb = int_nb * 10 + (nb[i] - '0');
		i++;
	}
	return (int_nb * minus);
}
