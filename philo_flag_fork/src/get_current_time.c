/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_time.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 08:10:52 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/28 15:51:25 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (perror("gettimeofday() error\n"), 0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	printf_time_philo(char *str, size_t start_time, size_t nb)
{
	printf(str, get_current_time() - start_time, nb);
}
