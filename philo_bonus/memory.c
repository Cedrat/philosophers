/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 17:13:24 by lnoaille          #+#    #+#             */
/*   Updated: 2021/05/30 18:07:54 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_malloc_error(void *to_check)
{
	if (to_check == NULL)
	{
		ft_putstr_fd("Error :\n Malloc failed\n", 2);
		return (1);
	}
	return (0);
}
