/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:33:16 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/26 16:37:08 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int check_dead_flag(t_philo *philo)
{
    pthread_mutex_lock(philo->dead_lock);
    if (*philo->dead)
        return (pthread_mutex_unlock(philo->dead_lock), 1);
    return (pthread_mutex_unlock(philo->dead_lock), 0);
}