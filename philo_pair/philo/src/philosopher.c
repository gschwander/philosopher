/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:35:22 by gschwand          #+#    #+#             */
/*   Updated: 2024/12/12 12:58:52 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	one_philo(t_param param)
{
	size_t	start;

	if (param.nbr_of_philo == 1)
	{
		start = get_current_time();
		printf("%zu 1 has taken a fork\n", get_current_time() - start);
		ft_usleep(param.time_to_die, NULL);
		printf("%zu 1 died\n", get_current_time() - start);
		return (1);
	}
	return (0);
}

static int	start_exec_philo(t_data *data, size_t nbr_of_philo)
{
	size_t	i;

	i = 0;
	pthread_mutex_lock(&data->sync_start);
	while (i < nbr_of_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, routine_philo,
				&data->philo[i]))
			return (philo_join(data, i), perror("start_exec_philo"), 1);
		i++;
	}
	return (0);
}

static int	start_monitor(t_data *data)
{
	pthread_t	monitor;
	size_t		i;

	i = 0;
	data->start_time = get_current_time();
	while (i < data->param.nbr_of_philo)
	{
		data->philo[i].last_meal = data->start_time;
		i++;
	}
	if (pthread_create(&monitor, NULL, ft_monitor, data))
	{
		data_clean(data, data->forks);
		perror("start_monitor");
		return (1);
	}
	pthread_mutex_unlock(&data->sync_start);
	pthread_join(monitor, NULL);
	return (0);
}

int	philosopher(t_param param)
{
	t_data			data;
	pthread_mutex_t	*forks;

	data.param = param;
	if (one_philo(param))
		return (0);
	if (init_data(&data))
		return (1);
	forks = init_forks(data.param);
	if (!forks)
		return (destroy_mutex(&data), free(data.philo), 1);
	data.forks = forks;
	if (init_philo(&data, forks))
		return (1);
	if (start_exec_philo(&data, data.param.nbr_of_philo))
		return (1);
	if (start_monitor(&data))
		return (1);
	data_clean(&data, forks);
	return (0);
}
