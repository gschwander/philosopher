/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:24:21 by gschwand          #+#    #+#             */
/*   Updated: 2024/12/06 15:36:55 by gschwand         ###   ########.fr       */
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

int	take_first_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	if (fork->status)
	{
		pthread_mutex_unlock(&fork->mutex);
		usleep(1000);
		return (1);
	}
	fork->status = 1;
	pthread_mutex_unlock(&fork->mutex);
	return (0);
}

int	take_second_fork(t_fork *fork, t_fork *first_fork)
{
	pthread_mutex_lock(&fork->mutex);
	if (fork->status)
	{
		pthread_mutex_unlock(&fork->mutex);
		pthread_mutex_lock(&first_fork->mutex);
		first_fork->status = 0;
		pthread_mutex_unlock(&first_fork->mutex);
		usleep(500);
		return (1);
	}
	fork->status = 1;
	pthread_mutex_unlock(&fork->mutex);
	return (0);
}

int	taking_fork(t_philo *philo)
{
	if (check_dead_flag(philo))
		return (1);
	if (take_first_fork(philo->r_fork))
		return (taking_fork(philo));
	if (take_second_fork(philo->l_fork, philo->r_fork))
		return (taking_fork(philo));
	if (check_dead_flag(philo))
		return (1);
	change_stat_meal(philo);
	pthread_mutex_lock(philo->write_lock);
	printf_time_philo("%zu %d has taken a fork\n", *philo->start_time,
		philo->id);
	printf_time_philo("%zu %d has taken a fork\n", *philo->start_time,
		philo->id);
	printf_time_philo("%zu %d is eating\n", *philo->start_time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
	return (0);
}
