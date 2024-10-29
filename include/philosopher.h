/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:45:17 by gschwand          #+#    #+#             */
/*   Updated: 2024/10/29 11:43:58 by gschwand         ###   ########.fr       */
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
	unsigned long long	nbr_of_philo;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned long long	nbr_of_times_each_philo_must_eat;
}						t_param;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					eating;
	int					meals_eaten;
	size_t				last_meal;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					*dead;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*meal_lock;
}						t_philo;

typedef struct s_data
{
	int					dead_flag;
	t_param				param;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		write_lock;
	t_philo				*philo;
}						t_data;

// memory_philosopher.c
unsigned long long		ft_atoi_ll(char *str);

// init.c
int						init_data(t_data *data, t_param param);
pthread_mutex_t			*init_forks(t_param param);
int						init_philo(t_data *data, t_param param,
							pthread_mutex_t *forks);
size_t					get_current_time(void);
void					ft_usleep(size_t time);

// routine_philo.c
int						routine_philo(t_philo *philo);

// monitor.c
void					*monitor(void *data);

#endif
