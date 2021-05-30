/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 18:15:08 by lnoaille          #+#    #+#             */
/*   Updated: 2021/05/30 18:18:43 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(int nb_args, char **arg)
{
	int	i;

	i = 1;
	if (check_nb_args(nb_args) == 0)
		return (0);
	while (i < (nb_args))
	{
		if (not_a_positive_number(arg[i]))
		{
			ft_putstr_fd("Error :\nArgument \"", 2);
			ft_putstr_fd(arg[i], 2);
			ft_putstr_fd("\" is not a positive number\n", 2);
			return (0);
		}
		i++;
	}
	if (ft_atoi(arg[1]) == 0)
	{
		ft_putstr_fd("Error :\n Explain me. How do you launch a "
			"simulation with zero philosophers ?\n", 2);
		return (0);
	}
	return (1);
}

bool	check_nb_args(int nb_args)
{
	if (nb_args < 5 || nb_args > 6)
	{
		ft_putstr_fd("Error :\nthe number of argument is invalid\n", 2);
		return (0);
	}
	return (1);
}
