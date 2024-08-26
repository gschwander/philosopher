/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_philosopher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:38:35 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/26 12:39:22 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

pthread_t *ft_philosopher(t_param param)
{
    pthread_t *philosopher;
    int i;

    i = 0;
    ft_alloc_philo(param);
    philosopher = malloc(sizeof(pthread_t) * param.nbr_of_philo);
    if (!philosopher)
        return (perror("Malloc failed"), 1);
    while (i < param.nbr_of_philo)
    {
        pthread_create(&philosopher[i], NULL, philosopher, NULL);
        i++;
    }
    return (philosopher);
}