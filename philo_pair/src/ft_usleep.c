/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 08:14:21 by gschwand          #+#    #+#             */
/*   Updated: 2024/12/10 11:52:50 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// time_since_meal
int	tsm(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (get_current_time() - philo->last_meal > philo->time_to_die)
		return (pthread_mutex_unlock(&philo->meal_lock), 1);
	return (pthread_mutex_unlock(&philo->meal_lock), 0);
}

int	ft_usleep(size_t time, t_philo *philo)
{
	size_t	start;
	// size_t start1;

	start = get_current_time();
	while (get_current_time() - start < time)
	{
		// start1 = get_current_time();
		usleep(100);
		// pthread_mutex_lock(philo->write_lock);
		// printf ("time sleep philo %d %zu\n",philo->id, get_current_time() - start1);
		// pthread_mutex_unlock(philo->write_lock);
		if (philo)
		{
			if (check_dead_flag(philo))
				return (1);
		}
	}
	return (0);
}
