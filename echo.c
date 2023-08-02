/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 21:07:19 by hben-bou          #+#    #+#             */
/*   Updated: 2023/07/31 22:44:18 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void between_quotes(char *str, int fd)
{
    int i;
    i = 1;
    while (str[i] && str[i] != '\'')
        write(fd, &str[i++], 1);
}

int flag(char *str)
{
    int i;
    
    i = 0;
    if (str[0] == '-')
    {
        i++;
        while (str[i] == 'n')
        {
            i++;
        }
        if (str[i - 1] == 'n' && str[i] == '\0')
            return (1);
    }
    return (0);
}

void echo(char **str, t_struct *s, int fd)
{
    int i;
    int trigger;
    int k;
    
    i = 1;
    trigger = 0;
    while (flag(str[i]))
    {
        trigger = 1;
        i++;
    }
    while (str[i])
    {
        if (operator(NULL, str[i]) == 1 && (!str[i][1] || !str[i][2]))
            break;
        k = 0;
        if (str[i][0] == '\'')
            between_quotes(str[i], fd);
        else
        {
            while (str[i][k])
            {
                if (str[i][k] == '$' && str[i][k + 1] == '?')
                {
                    s->exit_status = s->exit_status >> 8;
                    ft_putnbr(s->exit_status, fd);
                    k += 2;
                }
                else
                {
                    write(fd, &str[i][k], 1);
                    k++;
                }
            }
        }
        i++;
    }
    if (trigger != 1)
        write(fd, "\n", 1);
}
