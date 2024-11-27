/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:28:18 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/27 15:37:44 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	exection_death(t_data *data, size_t i)
{
	pthread_mutex_lock(data->philo[i].dead_lock);
	pthread_mutex_lock(&data->write_lock);
	printf("%zu %d died\n", get_current_time() - data->start_time,
		data->philo[i].id);
	data->dead_flag = 1;
	pthread_mutex_unlock(data->philo[i].dead_lock);
	pthread_mutex_unlock(&data->write_lock);
	return (1);
}

void	ft_monitor_no_limit_eat(t_data *data)
{
	size_t	i;

	while (1)
	{
		i = 0;
		while (i < data->param.nbr_of_philo)
		{
			if (!check_eating_flag(&data->philo[i]) && tsm(&data->philo[i]))
			{
				if (exection_death(data, i))
					return ;
			}
			i++;
		}
	}
}

int	check_nbr_of_meals(t_data *data, size_t j)
{
	size_t	i;

	i = 0;
	while (i < data->param.nbr_of_philo)
	{
		if (check_eaten(&data->philo[i]) < data->param.not_p_must_eat)
			return (0);
		i++;
	}
	pthread_mutex_lock(data->philo[j].dead_lock);
	data->dead_flag = 1;
	pthread_mutex_unlock(data->philo[j].dead_lock);
	return (1);
}

void	ft_monitor_limit_eat(t_data *data)
{
	size_t	i;

	while (1)
	{
		i = 0;
		while (i < data->param.nbr_of_philo)
		{
			if (check_eaten(&data->philo[i]) >= data->param.not_p_must_eat)
			{
				if (check_nbr_of_meals(data, i))
					return ;
			}
			else if (!check_eating_flag(&data->philo[i]) && (tsm(&data->philo[i])))
			{
				if (exection_death(data, i))
					return ;
			}
			i++;
		}
	}
}

void	*ft_monitor(void *d)
{
	t_data	*data;

	data = (t_data *)d;
	if (!data->param.not_p_must_eat)
		ft_monitor_no_limit_eat(data);
	else
		ft_monitor_limit_eat(data);
	return (NULL);
}