/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:35:22 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/27 15:48:34 by gschwand         ###   ########.fr       */
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
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&data->philo[i].meal_lock);
		i++;
	}
	free(forks);
	free(data->philo);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->write_lock);
}

static void start_exec_philo(t_philo *philo, size_t nbr_of_philo)
{
    size_t i;

    i = 0;
    while (i < nbr_of_philo)
	{
		pthread_create(&philo[i].thread, NULL, routine_philo, &philo[i]);
		i++;
	}
}

static void start_monitor(t_data *data)
{
    pthread_t   monitor;

    pthread_create(&monitor, NULL, ft_monitor, data);
	pthread_join(monitor, NULL);
}

int philosopher(t_param param)
{
    t_data data;
    pthread_mutex_t *forks;
    
    data.param = param;
    if(init_data(&data))
        return(1);
    forks = init_forks(data.param);
    if (!forks)
        return(1);
    init_philo(&data, forks);
    start_exec_philo(data.philo, data.param.nbr_of_philo);
    start_monitor(&data);
    data_clean(&data, forks);
	return (0);
}
