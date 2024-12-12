/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:23:01 by gschwand          #+#    #+#             */
/*   Updated: 2024/12/12 13:02:51 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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
	philo->last_meal = get_current_time();
	ft_usleep(philo->time_to_eat, philo);
	pthread_mutex_lock(&philo->meal_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	end_philo(philo);
}

int	ft_sleep(t_philo *philo)
{
	if (check_dead_flag(philo))
		return (1);
	printf_time_philo("%zu %d is sleeping\n", philo);
	if (ft_usleep(philo->time_to_sleep, philo))
		return (1);
	return (0);
}

void	think(t_philo *philo)
{
	printf_time_philo("%zu %d is thinking\n", philo);
}

void	*routine_philo(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	pthread_mutex_lock(philo->sync_start);
	pthread_mutex_unlock(philo->sync_start);
	if (philo->id % 2 == 1)
	{
		think(philo);
		ft_usleep(philo->time_to_eat / 2, philo);
	}
	while (1)
	{
		if (check_dead_flag(philo))
			return (NULL);
		eating(philo);
		if (ft_sleep(philo))
			return (NULL);
		think(philo);
		if (philo->time_to_sleep <= philo->time_to_eat)
			ft_usleep(philo->time_to_eat - philo->time_to_sleep + 10, philo);
	}
	return (NULL);
}
