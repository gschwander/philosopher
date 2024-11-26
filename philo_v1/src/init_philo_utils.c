/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:30:44 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/25 15:22:32 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int check_if_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	if (philo->eating)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (0);
	}
	pthread_mutex_lock(philo->meal_lock);
	return (1);
}

size_t check_eaten(t_philo *philo)
{
	int m;
	pthread_mutex_lock(philo->meal_lock);
	m = philo->meals_eaten;
	pthread_mutex_unlock(philo->meal_lock);
	return(m);
}

int check_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	init_time_philo(t_philo *philo, t_param param)
{
	philo->time_to_die = param.time_to_die;
	philo->time_to_eat = param.time_to_eat;
	philo->time_to_sleep = param.time_to_sleep;
}

void	init_mutex_philo(t_philo *philo, t_data *data)
{
	philo->dead_lock = &data->dead_lock;
	philo->write_lock = &data->write_lock;
	philo->meal_lock = &data->meal_lock;
	philo->dead = &data->dead_flag;
}
