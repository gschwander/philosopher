/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:23:01 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/26 16:46:15 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void eating(t_philo *philo)
{
    pthread_mutex_lock(philo->l_fork);
    pthread_mutex_lock(philo->r_fork);
    if (check_dead_flag(philo))
        return (end_philo(philo));
    pthread_mutex_lock(philo->write_lock);
    pthread_mutex_lock(&philo->meal_lock);
    philo->eating = 1;
    pthread_mutex_unlock(&philo->meal_lock);
    
    philo->last_meal = get_current_time();
    printf("%zu %d has taken a fork\n", get_current_time()- *philo->start_time, philo->id);
    printf("%zu %d has taken a fork\n", get_current_time()- *philo->start_time, philo->id);
    printf("%zu %d is eating\n", get_current_time() - *philo->start_time, philo->id);

    pthread_mutex_lock(philo->meal_lock);
    philo->meals_eaten ++;
    pthread_mutex_unlock(philo->meal_lock);
    
}

int ft_sleep(t_philo *philo)
{
    
}

void think(t_philo *philo)
{
    
}

void	*routine_philo(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (1)
	{
		if (check_dead_flag(philo))
			return (NULL);
		eating(philo);
		if (ft_sleep(philo))
			return (NULL);
		think(philo);
	}
	return (NULL);
}