/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:07:36 by gschwand          #+#    #+#             */
/*   Updated: 2024/12/10 17:25:22 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init_data(t_data *data)
{
	data->dead_flag = 0;
	if (pthread_mutex_init(&data->dead_lock, NULL))
		return (perror("mutex_init"), 1);
	if (pthread_mutex_init(&data->write_lock, NULL))
		return (pthread_mutex_destroy(&data->dead_lock), perror("mutex_init"),
			1);
	if (pthread_mutex_init(&data->sync_start, NULL))
		return (pthread_mutex_destroy(&data->dead_lock),
			pthread_mutex_destroy(&data->write_lock), perror("mutex_init"), 1);
	data->philo = malloc(sizeof(t_philo) * data->param.nbr_of_philo);
	if (!data->philo)
		return (destroy_mutex(data), 1);
	return (0);
}

pthread_mutex_t	*init_forks(t_param param)
{
	pthread_mutex_t	*forks;
	size_t			i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * param.nbr_of_philo);
	if (!forks)
		return (perror("init_forks"), NULL);
	while (i < param.nbr_of_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (destroy_mutex_fork(forks, i), perror("mutex_init"), NULL);
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

static int	init_mutex_philo(t_philo *philo, t_data *data)
{
	philo->dead_lock = &data->dead_lock;
	philo->write_lock = &data->write_lock;
	if (pthread_mutex_init(&philo->meal_lock, NULL))
		return (destroy_mutex_philo(data, philo->id), perror("mutex_init"), 1);
	philo->dead = &data->dead_flag;
	philo->sync_start = &data->sync_start;
	philo->start_time = &data->start_time;
	return (0);
}

int	init_philo(t_data *data, pthread_mutex_t *forks)
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
		if (init_mutex_philo(&data->philo[i], data))
			return (1);
		i++;
	}
	return (0);
}
