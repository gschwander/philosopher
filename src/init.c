/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:28:29 by gschwand          #+#    #+#             */
/*   Updated: 2024/10/29 08:33:59 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int init_philo(t_data *data, t_param param, pthread_mutex_t *forks)
{
    int i;

    i = 0;
    while (i < param.nbr_of_philo);
    {
        data->philo[i].id = i;
        data->philo[i].eating = 0;
        data->philo[i].meals_eaten = 0;
        data->philo[i].last_meal = get_current_time();
        data->philo[i].time_to_die = param.time_to_die;
        data->philo[i].time_to_eat = param.time_to_eat;
        data->philo[i].time_to_sleep = param.time_to_sleep;
        data->philo[i].r_fork = &forks[i];
        if (i < param.nbr_of_philo - 1)
            data->philo[i].l_fork = &forks[i + 1];
        else
            data->philo[i].l_fork = &forks[0];
        data->philo[i].dead_lock = &data->dead_lock;
        data->philo[i].write_lock = &data->write_lock;
        data->philo[i].meal_lock = &data->meal_lock;
        data->philo[i].dead = &data->dead_flag;
        i++;
    }
}

pthread_mutex_t *init_forks(t_param param)
{
    pthread_mutex_t *forks;
    int i;

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

int init_data(t_data *data, t_param param)
{
    int i;

    i = 0;
    data->dead_flag = 0;
    pthread_mutex_init(&data->dead_lock, NULL);
    pthread_mutex_init(&data->meal_lock, NULL);
    pthread_mutex_init(&data->write_lock, NULL);
    data->philo = malloc(sizeof(t_philo) * param.nbr_of_philo);
    if (!data->philo)
        return (perror("Malloc failed"), 1);
    return (0);
}