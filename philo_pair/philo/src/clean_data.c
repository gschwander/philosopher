/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:47:57 by gschwand          #+#    #+#             */
/*   Updated: 2024/12/10 17:25:12 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	data_clean(t_data *data, pthread_mutex_t *forks)
{
	size_t	i;

	i = 0;
	while (i < data->param.nbr_of_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < data->param.nbr_of_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&data->philo[i].meal_lock);
		i++;
	}
	free(forks);
	free(data->philo);
	pthread_mutex_destroy(&data->sync_start);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->write_lock);
}

void	destroy_mutex(t_data *data)
{
	pthread_mutex_destroy(&data->sync_start);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->write_lock);
}

void	destroy_mutex_fork(pthread_mutex_t *forks, size_t i)
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&forks[j]);
		j++;
	}
	free(forks);
}

void	destroy_mutex_philo(t_data *data, int id)
{
	size_t	i;

	i = 0;
	destroy_mutex(data);
	while (i < data->param.nbr_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		if (i < (size_t)id)
			pthread_mutex_destroy(&data->philo[i].meal_lock);
		i++;
	}
	free(data->forks);
	free(data->philo);
}

void	philo_join(t_data *data, int id)
{
	size_t	i;

	i = 0;
	pthread_mutex_unlock(&data->sync_start);
	while (i < (size_t)id)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < data->param.nbr_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i].meal_lock);
		i++;
	}
	free(data->forks);
	free(data->philo);
	pthread_mutex_destroy(&data->sync_start);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->write_lock);
}
