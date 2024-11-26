/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:45:17 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/26 15:14:52 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_param
{
	size_t	nbr_of_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	not_p_must_eat;
} t_param;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					eating;
	size_t				meals_eaten;
	size_t				*start_time;
	size_t				last_meal;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					*dead;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		meal_lock;
}						t_philo;

typedef struct s_data
{
	int					dead_flag;
	t_param				param;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		write_lock;
	t_philo				*philo;
}	t_data;

// philosopher.c
int	philosopher(t_param param);

// atoi.c
size_t	ft_atoi(char *str);



#endif