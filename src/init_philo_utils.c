/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:30:44 by gschwand          #+#    #+#             */
/*   Updated: 2024/10/30 09:23:45 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void init_time_philo(t_philo *philo, t_param param)
{
    philo->time_to_die = param.time_to_die;
    philo->time_to_eat = param.time_to_eat;
    philo->time_to_sleep = param.time_to_sleep;
}

void init_mutex_philo(t_philo *philo, t_data *data)
{
    philo->dead_lock = &data->dead_lock;
    philo->write_lock = &data->write_lock;
    philo->meal_lock = &data->meal_lock;
    philo->dead = &data->dead_flag;
}