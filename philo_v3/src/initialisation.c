/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:07:36 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/28 16:04:56 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init_data(t_data *data)
{
	data->dead_flag = 0;
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
	data->philo = malloc(sizeof(t_philo) * data->param.nbr_of_philo);
	if (!data->philo)
		return (1);
	return (0);
}

pthread_mutex_t	*init_forks(t_param param)
{
	pthread_mutex_t	*forks;
	size_t			i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * param.nbr_of_philo);
	if (!forks)
		return (NULL);
	while (i < param.nbr_of_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
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
}

int	init_philo(t_data *data, pthread_mutex_t *forks)
{
	size_t	i;

	i = 0;
	data->start_time = get_current_time();
	while (i < data->param.nbr_of_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].start_time = &data->start_time;
		data->philo[i].last_meal = data->start_time;
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
