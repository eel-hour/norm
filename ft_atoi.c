/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:53:09 by hben-bou          #+#    #+#             */
/*   Updated: 2023/07/31 01:42:30 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_atoi(char *str)
{
    int i;
    int sign;
    int result;

    
    i = 1;
    sign = 1;
    result = 0;
    // while (str[i])
    // {
        
    // }
    while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '+')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
        result = result * 10 + str[i++] - 48;
    if (result * sign < 0)
        return (1);
    return (result * sign);
}