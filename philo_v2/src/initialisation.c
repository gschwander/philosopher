/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:07:36 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/26 15:29:42 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int init_data(t_data *data)
{
    data->dead_flag = 0;
    pthread_mutex_init(&data->dead_lock, NULL);
    pthread_mutex_init(&data->write_lock, NULL);
    data->philo = malloc(sizeof(t_philo) * data->param.nbr_of_philo);
    if (!data->philo)
        return (1);
    return(0);
}

pthread_mutex_t *init_forks(t_param param)
{
    pthread_mutex_t *forks;
    int i;

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