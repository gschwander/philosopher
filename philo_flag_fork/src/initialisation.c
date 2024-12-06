/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:07:36 by gschwand          #+#    #+#             */
/*   Updated: 2024/12/04 15:32:30 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init_data(t_data *data)
{
	data->dead_flag = 0;
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->sync_start, NULL);
	data->philo = malloc(sizeof(t_philo) * data->param.nbr_of_philo);
	if (!data->philo)
		return (1);
	return (0);
}

// lorsque status est egale a 0 cela signifie que la forchette est libre
t_fork	*init_forks(t_param param)
{
	t_fork	*forks;
	size_t	i;

	i = 0;
	forks = malloc(sizeof(t_fork) * param.nbr_of_philo);
	if (!forks)
		return (NULL);
	while (i < param.nbr_of_philo)
	{
		pthread_mutex_init(&forks[i].mutex, NULL);
		forks[i].status = 0;
		i++;
	}
	return (forks);
}

static void	init_time_philo(t_philo *philo, t_param param)
{
	philo->time_to_die = param.time_to_die;
	philo->time_to_eat = param.time_to_eat;
	philo->time_to_sleep = param.time_to_sleep;
}

static void	init_mutex_philo(t_philo *philo, t_data *data)
{
	philo->dead_lock = &data->dead_lock;
	philo->write_lock = &data->write_lock;
	pthread_mutex_init(&philo->meal_lock, NULL);
	philo->dead = &data->dead_flag;
	philo->sync_start = &data->sync_start;
}

int	init_philo(t_data *data, t_fork *forks)
{
	size_t	i;

	i = 0;
	while (i < data->param.nbr_of_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].eating = 0;
		data->philo[i].meals_eaten = 0;
		init_time_philo(&data->philo[i], data->param);
		data->philo[i].l_fork = &forks[i];
		if (i < data->param.nbr_of_philo - 1)
			data->philo[i].r_fork = &forks[i + 1];
		else
			data->philo[i].r_fork = &forks[0];
		init_mutex_philo(&data->philo[i], data);
		i++;
	}
	return (0);
}
