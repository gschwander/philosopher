/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:46:01 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/22 14:40:03 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int ft_philosopher(t_param param)
{
    printf("nbr_of_philo: %lld\n", param.nbr_of_philo);
    printf("time_to_die: %lld\n", param.time_to_die);
    printf("time_to_eat: %lld\n", param.time_to_eat);
    printf("time_to_sleep: %lld\n", param.time_to_sleep);
    printf("nbr_of_times_each_philo_must_eat: %lld\n", param.nbr_of_times_each_philo_must_eat);
    return (0);
}

int main(int argv, char **argc)
{
    t_param param;

    if (argv != 5 && argv != 6)
        return (perror("Wrong number of arguments"), 1);
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
