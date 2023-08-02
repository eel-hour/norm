/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 02:37:06 by hben-bou          #+#    #+#             */
/*   Updated: 2023/07/31 18:44:18 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_equal_sign(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '=')
            return (0);
        i++;
    }
    return (1);
}

void declare_x(t_struct *s, int fd)
{
    int i;
    int k;
    char **str;
    
    i = 0;
    k = 0;
    while (s->expor[i])
    {
        k = 0;
        write(fd, "declare -x ", ft_strlen("declare -x "));
        str = ft_split(s->expor[i], '=');
        while (str[k])
            k++;
        if (str[0])
            write(1, str[0], ft_strlen(str[0]));
        if (k > 1)
        {
            write(fd, "=", 1);
            write(fd, "\"", 1);
            if (str[1])
                write(1, str[1], ft_strlen(str[1]));
            write(fd, "\"", 1);
        }
        write(fd, "\n", 1);
        i++;
    }
}

int till_equal(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    return (i);
}

void export(char *str, t_struct *s)
{
    int i;
    int trigger;
    int counter;
    char **New_env;

    i = 0;
    trigger = 0;
    counter = 0;
    while (environ[counter])
        counter++;
    if (find_equal_sign(str))
        trigger = 1;
    if (str[i] >= '0' && str [i] <= '9')
    {
        printf("export %s not a valid identifier\n", str);
        return;
    }
    s->expor = malloc(sizeof(char *) * (counter + 2));
    New_env = malloc(sizeof(char *) * (counter + 2));
    if (!New_env || !s->expor)
        return ;
    while (environ[i])
    {
        if (ft_strcmp(str, environ[i], till_equal(str)))
        {
            environ[i] = ft_strdup(str);
            s->expor = environ;
            trigger = 10;
            break;
        }
        i++;
    }
    i = 0;
    if (trigger != 10)
    {
        i = 0;
        while (environ[i])
        {
            New_env[i] = ft_strdup(environ[i]);
            i++;
        }
        if (ft_strcmp("LINES", New_env[i - 2], 4))
        {
            New_env[i - 2] = ft_strdup(str);
            New_env[i - 1] = NULL;
        }
        else
        {
            New_env[i] = ft_strdup(str);
            i++;
            New_env[i] = NULL;
        }
        if (trigger == 1)
            s->expor = New_env;
        else
        {
            s->expor = New_env;
            environ = New_env;
        }
    }
}

void unset(char *str)
{
    int i;
    int k;
    int trigger;
    
    i = 0;
    trigger = 0;
    while (environ[i])
    {
        k = 0;
        while (environ[i][k] != '=')
            k++;
        if (ft_strcmp(environ[i], str, k) == 1)
        {
            environ[i] = environ[i + 1];
            trigger = 1;
        }
        if (trigger == 1)
            environ[i] = environ[i + 1];
        i++;
    }
}
