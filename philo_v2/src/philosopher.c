/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:35:22 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/26 15:24:30 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int philosopher(t_param param)
{
    t_data data;
    pthread_mutex_t *forks;
    
    data.param = param;
    if(init_data(&data))
        return(1);
    forks = init_fork(data.param);
    if (!forks)
        return(1);
}