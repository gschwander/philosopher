/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:31:35 by gschwand          #+#    #+#             */
/*   Updated: 2024/10/29 17:39:07 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int ft_is_digit(char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

size_t ft_atoi(char *str)
{
    int i;
    size_t res;

    i = 0;
    res = 0;
    while (str[i] && ft_is_digit(str[i]) == 1)
    {
        res = res * 10 + str[i] - '0';
        i++;
    }
    return (res);
}
