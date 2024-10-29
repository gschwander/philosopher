/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 08:14:21 by gschwand          #+#    #+#             */
/*   Updated: 2024/10/29 18:35:49 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_usleep(size_t time, t_philo *philo)
{
    size_t	start;

    start = get_current_time();
    while (get_current_time() - start < time)
    {
        printf("time to sleep %zu\n", time);
        printf("time elapsed %zu\n", get_current_time() - start);
        usleep(100);
        if (philo->dead)
            return (printf ("fuckkkkkkk\n"), 1);
    }
    return (0);
}
