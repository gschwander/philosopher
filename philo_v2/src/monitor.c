/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:28:18 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/26 16:29:05 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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