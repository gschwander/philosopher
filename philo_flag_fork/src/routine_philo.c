/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:23:01 by gschwand          #+#    #+#             */
/*   Updated: 2024/12/06 15:24:54 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	end_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork->mutex);
	philo->r_fork->status = 0;
	pthread_mutex_unlock(&philo->r_fork->mutex);
	pthread_mutex_lock(&philo->l_fork->mutex);
	philo->l_fork->status = 0;
	pthread_mutex_unlock(&philo->l_fork->mutex);
}

static void	eating(t_philo *philo)
{
	if (taking_fork(philo))
		return ;
	pthread_mutex_lock(philo->write_lock);
	pthread_mutex_unlock(philo->write_lock);
	ft_usleep(philo->time_to_eat, philo);
	pthread_mutex_lock(&philo->meal_lock);
	pthread_mutex_lock(philo->write_lock);
	pthread_mutex_unlock(philo->write_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	end_philo(philo);
	change_stat_meal(philo);
}

int	ft_sleep(t_philo *philo)
{
	if (!check_dead_flag(philo))
	{
		pthread_mutex_lock(philo->write_lock);
		printf("%zu %d is sleeping\n", get_current_time() - *philo->start_time,
			philo->id);
		pthread_mutex_unlock(philo->write_lock);
	}
	if (check_dead_flag(philo))
		return (1);
	if (ft_usleep(philo->time_to_sleep, philo))
		return (1);
	return (0);
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(philo->write_lock);
	printf("%zu %d is thinking\n", get_current_time() - *philo->start_time,
		philo->id);
	pthread_mutex_unlock(philo->write_lock);
}

void	*routine_philo(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	pthread_mutex_lock(philo->sync_start);
	pthread_mutex_unlock(philo->sync_start);
	while (1)
	{
		if (check_dead_flag(philo))
			return (NULL);
		eating(philo);
		if (ft_sleep(philo))
			return (NULL);
		think(philo);
	}
	return (NULL);
}
