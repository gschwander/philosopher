/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:45:17 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/09 14:18:11 by gschwand         ###   ########.fr       */
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

typedef struct s_philo {
    pthread_t thread;
    int     id;
    int     eating;
    int     meals_eaten;
    size_t  last_meal;
    size_t  time_to_die;
    size_t  time_to_eat;
    size_t  time_to_sleep;
    pthread_mutex_t *r_fork;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *dead_lock;
    pthread_mutex_t *write_lock;
    pthread_mutex_t *meal_lock; 
}           t_philo;

typedef struct s_data {
    int     dead_flag;
    pthread_mutex_t dead_lock;
    pthread_mutex_t meal_lock;
    pthread_mutex_t write_lock;
    t_philo *philo; 
}       t_data;

// memory_philosopher.c
unsigned long long ft_atoi_ll(char *str);

#endif
