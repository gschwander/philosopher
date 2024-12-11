/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:05:34 by gschwand          #+#    #+#             */
/*   Updated: 2024/12/11 17:31:45 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	change_stat_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (philo->eating == 1)
		philo->eating = 0;
	else
		philo->eating = 1;
	pthread_mutex_unlock(&philo->meal_lock);
}

int	taking_first_fork(pthread_mutex_t *ff, t_philo *philo)
{
	pthread_mutex_lock(ff);
	if (check_dead_flag(philo))
	{
		pthread_mutex_unlock(ff);
		return (1);
	}
	printf_time_philo("%zu %d has taken a fork\n", philo);
	return (0);
}

int	taking_fork(pthread_mutex_t *ff, pthread_mutex_t *sf, t_philo *philo)
{
	if (taking_first_fork(ff, philo))
		return (1);
	pthread_mutex_lock(sf);
	change_stat_meal(philo);
	if (check_dead_flag(philo))
	{
		pthread_mutex_unlock(ff);
		pthread_mutex_unlock(sf);
		return (1);
	}
	printf_time_philo("%zu %d has taken a fork\n", philo);
	printf_time_philo("%zu %d is eating\n", philo);
	return (0);
}

void	end_philo(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	change_stat_meal(philo);
}
