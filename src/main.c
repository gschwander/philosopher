/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:46:01 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/22 13:10:19 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int main(int argv, char **argc)
{
    t_param param;

    if (argv != 5 || argv != 6)
        return (perror("Wrong number of arguments"), 1);
    param.nbr_of_philo = argc[1];
    param.time_to_die = argc[2];
    param.time_to_eat = argc[3];
    param.time_to_sleep = argc[4];
    if (argv == 6)
        param.nbr_of_times_each_philo_must_eat = argc[5];
    else
        param.nbr_of_times_each_philo_must_eat = -1;
    ft_philosopher(param);
}
