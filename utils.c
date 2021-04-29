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
