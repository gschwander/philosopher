/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:28:29 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/04 11:07:34 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init_philo(t_data *data, t_param param, pthread_mutex_t *forks)
{
	size_t	i;

	i = 0;
	while (i < param.nbr_of_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].start_time = &data->start_time;
		data->philo[i].eating = 0;
		data->philo[i].meals_eaten = 0;
		data->philo[i].last_meal = get_current_time();
		if (data->philo[i].last_meal == 0)
			return (1);
		init_time_philo(&data->philo[i], param);
		data->philo[i].r_fork = &forks[i];
		if (i < param.nbr_of_philo - 1)
			data->philo[i].l_fork = &forks[i + 1];
		else
			data->philo[i].l_fork = &forks[0];
		init_mutex_philo(&data->philo[i], data);
		i++;
	}
	return (0);
}

pthread_mutex_t	*init_forks(t_param param)
{
	pthread_mutex_t	*forks;
	size_t			i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * param.nbr_of_philo);
	if (!forks)
		return (perror("Malloc failed"), NULL);
	while (i < param.nbr_of_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

int	init_data(t_data *data, t_param param)
{
	data->dead_flag = 0;
	data->start_time = get_current_time();
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
	data->philo = malloc(sizeof(t_philo) * param.nbr_of_philo);
	if (!data->philo)
		return (perror("Malloc failed"), 1);
	return (0);
}
