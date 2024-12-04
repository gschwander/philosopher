/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:45:17 by gschwand          #+#    #+#             */
/*   Updated: 2024/12/04 15:32:41 by gschwand         ###   ########.fr       */
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
	size_t			nbr_of_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			not_p_must_eat;
}					t_param;

typedef struct	s_fork
{
	pthread_mutex_t mutex;
	int			status;
}				t_fork;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	size_t			meals_eaten;
	size_t			*start_time;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				*dead;
	pthread_mutex_t *sync_start;
	t_fork	*r_fork;
	t_fork	*l_fork;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	meal_lock;
}					t_philo;

typedef struct s_data
{
	int				dead_flag;
	t_param			param;
	size_t			start_time;
	pthread_mutex_t sync_start;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philo;
}					t_data;

// philosopher.c
int					philosopher(t_param param);

// atoi.c
size_t				ft_atoi(char *str);

// initialisation.c
int					init_philo(t_data *data, t_fork *forks);
t_fork		*init_forks(t_param param);
int					init_data(t_data *data);

// get_current_time.c
size_t	get_current_time(void);
void printf_time_philo(char *str, size_t start_time, size_t nb);

// routine_philo.c
void	*routine_philo(void *p);

// check_mutex.c
int check_dead_flag(t_philo *philo);
int check_eating_flag(t_philo *philo);
size_t check_eaten(t_philo *philo);

// monitor.c
void	*ft_monitor(void *d);

// ft_usleep.c
int	ft_usleep(size_t time, t_philo *philo);
int	tsm(t_philo *philo);


#endif