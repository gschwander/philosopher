/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:46:01 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/26 12:39:48 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int ft_philosopher(t_param param)
{
    pthread_t *philosopher;
    int i;

    i = 0;
    philosopher = ft_alloc_philo(param);
    if (!philosopher)
        return (1);
    
    return (0);
}
// coder une fonction qui va checker les arguments
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
