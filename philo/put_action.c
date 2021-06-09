/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 15:05:01 by lnoaille          #+#    #+#             */
/*   Updated: 2021/06/09 21:20:52 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned int	give_number_power_of_ten(unsigned int nb)
{
	int	power;

	power = 0;
	while (nb > 0)
	{
		if (power == 0)
			power = 1;
		else
			power *= 10;
		nb /= 10;
	}
	return (power);
}

unsigned int	putnbr_in_str(char *str, unsigned int nb, unsigned int pos)
{
	int	power;

	power = give_number_power_of_ten(nb);
	if (power == 0)
	{
		str[pos] = '0';
		pos++;
	}
	while (power >= 1)
	{
		str[pos] = (nb / (power)) + '0';
		nb = nb % power;
		pos++;
		power /= 10;
	}
	return (pos);
}

unsigned int	addstr_to_str(char *str, char *str_to_add, unsigned int pos)
{
	int	p;

	p = 0;
	while (str_to_add[p])
	{
		str[pos] = str_to_add[p];
		p++;
		pos++;
	}
	str[pos] = '\0';
	return (pos);
}

unsigned int	addspace_to_str(char *str, unsigned int pos)
{
	str[pos] = ' ';
	pos++;
	return (pos);
}

void	put_action(int time, int nb, char *action, pthread_mutex_t *auth_write)
{
	char	all_action[50];
	int		i;

	i = 0;
	i = putnbr_in_str(all_action, time, i);
	i = addspace_to_str(all_action, i);
	i = putnbr_in_str(all_action, nb, i);
	i = addspace_to_str(all_action, i);
	i = addstr_to_str(all_action, action, i);
	pthread_mutex_lock(auth_write);
	ft_putstr(all_action);
	pthread_mutex_unlock(auth_write);
}
