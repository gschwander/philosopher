/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 08:14:21 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/04 11:13:43 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// time_since_meal 
int	tsm(t_philo *philo)
{
	if (get_current_time() - philo->last_meal > philo->time_to_die)
		return (1);
	return (0);
}

int	ft_usleep(size_t time, t_philo *philo)
{
	size_t	start;

	start = get_current_time();
	while (get_current_time() - start < time)
	{
		usleep(100);
		if (philo)
		{
			if (*philo->dead)
				return (1);
		}
	}
	return (0);
}
