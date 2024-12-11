/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:20:34 by gschwand          #+#    #+#             */
/*   Updated: 2024/12/11 13:34:25 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	check_args(char **argc)
{
	int	i;
	int	j;

	i = 1;
	while (argc[i])
	{
		j = 0;
		while (argc[i][j])
		{
			if (argc[i][j] < '0' || argc[i][j] > '9')
				return (printf("Arguments must be positive numbers\n"), 1);
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_param	param;

	if (ac != 5 && ac != 6)
		return (printf("Wrong number of arguments\n"), 0);
	if (check_args(av))
		return (1);
	param.nbr_of_philo = ft_atoi(av[1]);
	param.time_to_die = ft_atoi(av[2]);
	param.time_to_eat = ft_atoi(av[3]);
	param.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		param.not_p_must_eat = ft_atoi(av[5]);
	else
		param.not_p_must_eat = 0;
	return (philosopher(param));
}
