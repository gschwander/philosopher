/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:30:44 by gschwand          #+#    #+#             */
/*   Updated: 2024/10/29 16:32:54 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void init_time_philo(t_philo *philo, t_param param)
{
    philo->time_to_die = param.time_to_die;
    philo->time_to_eat = param.time_to_eat;
    philo->time_to_sleep = param.time_to_sleep;
}
