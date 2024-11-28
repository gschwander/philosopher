/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:23:01 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/28 16:53:25 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int taking_fork(pthread_mutex_t *first_fork, pthread_mutex_t *second_fork, t_philo *philo)
{
	pthread_mutex_lock(first_fork);
	pthread_mutex_lock(philo->write_lock);
	if (check_dead_flag(philo))
	{
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(philo->write_lock);
		return (1);
	}
	printf_time_philo("%zu %d has taken a fork\n", *philo->start_time,
	philo->id);
	pthread_mutex_unlock(philo->write_lock);
	pthread_mutex_lock(second_fork);
	pthread_mutex_lock(philo->write_lock);
	if (check_dead_flag(philo))
	{
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(philo->write_lock);
		pthread_mutex_unlock(second_fork);
		return (1);
	}
	printf_time_philo("%zu %d has taken a fork\n", *philo->start_time,
	philo->id);
	printf_time_philo("%zu %d is eating\n", *philo->start_time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
	return (0);
}

static void	end_philo(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

static void	eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (taking_fork(philo->l_fork, philo->r_fork, philo))
			return ;
	}
	else
	{
		if (taking_fork(philo->r_fork, philo->l_fork, philo))
			return ;
	}
	if (check_dead_flag(philo))
		return (end_philo(philo));
	ft_usleep(philo->time_to_eat, philo);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	end_philo(philo);
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
