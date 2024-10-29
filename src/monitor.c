/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:40:28 by gschwand          #+#    #+#             */
/*   Updated: 2024/10/29 18:17:39 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int time_since_meal(t_philo *philo)
{
    if (get_current_time() - philo->last_meal > philo->time_to_die)
        return (1);
    return (0);
}

void *ft_monitor(void *d)
{
    t_data *data;
    data = (t_data *)d;
    size_t i;

    while (1)
    {
        i = 0;
        while (i < data->param.nbr_of_philo)
        {
            if (!data->philo[i].eating && time_since_meal(&data->philo[i]))
            {
                pthread_mutex_lock(data->philo[i].dead_lock);
                data->dead_flag = 1;
                pthread_mutex_lock(&data->write_lock);
                printf("%zu ms %d died\n", get_current_time()- data->start_time, data->philo[i].id);
                pthread_mutex_unlock(&data->write_lock);
                pthread_mutex_unlock(data->philo[i].dead_lock);
                return (NULL);
            }
            i++;
        }
    }
}
