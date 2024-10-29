/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:46:01 by gschwand          #+#    #+#             */
/*   Updated: 2024/10/29 07:38:44 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int ft_philosopher(t_param param)
{
    t_data  data;
    pthread_mutex_t *forks;
    
    if(init_data(&data, param))
        return (1);
    forks = init_forks(param);
    if (!forks)
        return (1);
    init_philo(&data, param, forks);
}

static int check_args(char **argc)
{
    int i;
    int j;

    i = 1;
    while (argc[i])
    {
        j = 0;
        while (argc[i][j])
        {
            if (argc[i][j] < '0' || argc[i][j] > '9')
                return (perror("Arguments must be positive numbers"), 1);
            j++;
        }
        i++;
    }
    return (0);
}

// coder une fonction qui va checker les arguments
int main(int argv, char **argc)
{
    t_param param;

    if (argv != 5 && argv != 6)
        return (perror("Wrong number of arguments"), 1);
    if (check_args(argc))
        return (1);
    param.nbr_of_philo = ft_atoi_ll(argc[1]);
    param.time_to_die = ft_atoi_ll(argc[2]);
    param.time_to_eat = ft_atoi_ll(argc[3]);
    param.time_to_sleep = ft_atoi_ll(argc[4]);
    if (argv == 6)
        param.nbr_of_times_each_philo_must_eat = ft_atoi_ll(argc[5]);
    else
        param.nbr_of_times_each_philo_must_eat = -1;
    ft_philosopher(param);
}
