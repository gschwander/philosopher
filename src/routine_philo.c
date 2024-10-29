/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 08:36:38 by gschwand          #+#    #+#             */
/*   Updated: 2024/10/29 09:38:50 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void think(t_philo *philo)
{
    pthread_mutex_lock(philo->write_lock);
    printf("%zu %d is thinking\n", get_current_time(), philo->id);
    pthread_mutex_unlock(philo->write_lock);
}

void lock_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->r_fork);
    pthread_mutex_lock(philo->write_lock);
    printf("%zu %d has taken a fork\n", get_current_time(), philo->id);
    pthread_mutex_unlock(philo->write_lock);
    pthread_mutex_lock(philo->l_fork);
    pthread_mutex_lock(philo->write_lock);
    printf("%zu %d has taken a fork\n", get_current_time(), philo->id);
    pthread_mutex_unlock(philo->write_lock);
}

void eating(t_philo *philo)
{
    lock_forks(philo);
    philo->eating = 1;
    pthread_mutex_lock(philo->write_lock);
    philo->last_meal = get_current_time();
    printf("%zu %d is eating\n", get_current_time(), philo->id);
    pthread_mutex_unlock(philo->write_lock);
    ft_usleep(philo->time_to_eat);
    philo->meals_eaten++;
    philo->eating = 0;
    pthread_mutex_unlock(philo->r_fork);
    pthread_mutex_unlock(philo->l_fork);
}

void ft_sleep(t_philo *philo)
{
    pthread_mutex_lock(philo->write_lock);
    printf("%zu %d is sleeping\n", get_current_time(), philo->id);
    pthread_mutex_unlock(philo->write_lock);
    ft_usleep(philo->time_to_sleep);
}

int routine_philo(t_philo *philo)
{
    while (1)
    {
        think(philo);
        eating(philo);
        ft_sleep(philo);
    }
    return (0);
}
