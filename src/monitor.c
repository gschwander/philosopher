/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:40:28 by gschwand          #+#    #+#             */
/*   Updated: 2024/10/29 11:49:16 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void *monitor(t_data *data)
{
    int i;

    while (1)
    {
        i = 0;
        while (i < data->param.nbr_of_philo)
        {
            if (data->philo[i].eating == 0 && get_current_time() - data->philo[i].last_meal > data->philo[i].time_to_die)
            {
                pthread_mutex_lock(data->philo[i].dead_lock);
                data->dead_flag = 1;
                pthread_mutex_lock(data->write_lock);
                printf("%zu %d died\n", get_current_time(), data->philo[i].id);
                pthread_mutex_unlock(data->write_lock);
                pthread_mutex_unlock(data->philo[i].dead_lock);
            }
            i++;
        }
    }
}
