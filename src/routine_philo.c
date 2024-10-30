/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 08:36:38 by gschwand          #+#    #+#             */
/*   Updated: 2024/10/30 09:20:56 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void think(t_philo *philo)
{
    pthread_mutex_lock(philo->write_lock);
    printf("%zu ms %d is thinking\n", get_current_time() - *philo->start_time, philo->id);
    pthread_mutex_unlock(philo->write_lock);
}

void eating(t_philo *philo)
{
    pthread_mutex_lock(philo->r_fork);
    pthread_mutex_lock(philo->l_fork);
    pthread_mutex_lock(philo->write_lock);
    philo->eating = 1;
    philo->last_meal = get_current_time();
    printf("%zu ms %d has taken a fork\n", get_current_time() - *philo->start_time, philo->id);
    printf("%zu ms %d has taken a fork\n", get_current_time() - *philo->start_time, philo->id);
    printf("%zu ms %d is eating\n", get_current_time() - *philo->start_time, philo->id);
    pthread_mutex_unlock(philo->write_lock);
    ft_usleep(philo->time_to_eat, philo);
    philo->meals_eaten++;
    philo->eating = 0;
    pthread_mutex_unlock(philo->r_fork);
    pthread_mutex_unlock(philo->l_fork);
}

static int ft_sleep(t_philo *philo)
{
    pthread_mutex_lock(philo->write_lock);
    printf("%zu ms %d is sleeping\n", get_current_time() - *philo->start_time, philo->id);
    pthread_mutex_unlock(philo->write_lock);
    if (ft_usleep(philo->time_to_sleep, philo))
        return (1);
    return (0);
}

void *routine_philo(void *p)
{
    t_philo *philo;
    philo = (t_philo *)p;
    while (1)
    {
        if (*philo->dead)
            return (NULL);
        eating(philo);
        if (ft_sleep(philo))
            return (NULL);
        think(philo);
    }
    return (NULL);
}
