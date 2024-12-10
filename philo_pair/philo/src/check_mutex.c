/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:33:16 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/28 14:11:39 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

size_t	check_eaten(t_philo *philo)
{
	size_t	m;

	pthread_mutex_lock(&philo->meal_lock);
	m = philo->meals_eaten;
	pthread_mutex_unlock(&philo->meal_lock);
	return (m);
}

int	check_eating_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (philo->eating)
		return (pthread_mutex_unlock(&philo->meal_lock), 1);
	return (pthread_mutex_unlock(&philo->meal_lock), 0);
}

int	check_dead_flag(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	return (pthread_mutex_unlock(philo->dead_lock), 0);
}
