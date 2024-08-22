/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:45:17 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/22 14:35:58 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_param {
    unsigned long long nbr_of_philo;
    unsigned long long time_to_die;
    unsigned long long time_to_eat;
    unsigned long long time_to_sleep;
    unsigned long long nbr_of_times_each_philo_must_eat;
} t_param;

// typedef struct s_data {
    
// };

unsigned long long ft_atoi_ll(char *str);

#endif
