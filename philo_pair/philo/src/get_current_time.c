/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_time.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 08:10:52 by gschwand          #+#    #+#             */
/*   Updated: 2024/12/11 17:36:25 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (perror("gettimeofday() error\n"), 0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	printf_time_philo(char *str, t_philo *philo)
{
	pthread_mutex_lock(philo->write_lock);
	if (!check_dead_flag(philo))
		printf(str, get_current_time() - *philo->start_time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
}

void	printf_time_philo_dead(char *str, t_philo *philo)
{
	pthread_mutex_lock(philo->write_lock);
	printf(str, get_current_time() - *philo->start_time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
}
