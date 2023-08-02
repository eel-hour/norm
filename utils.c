/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 23:13:55 by hben-bou          #+#    #+#             */
/*   Updated: 2023/08/02 01:38:36 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

int is_alpha(int c)
{
    if (c >= 'a'  && c <= 'z')
        return (1);
    else if (c >= 'A'  && c <= 'Z')
        return (1);
    return (0);
}
void ft_putstr(char *str)
{
    int i;
    
    i = 0;
    while (str[i])
        write(1, &str[i++], 1);
}

int ptr_len(char **str)
{
    int i;

    i = 0;
    while (str[i++]);
    return (i);
}

int is_acceptable(int c)
{
    if (c >= 'a' && c <= 'z')
        return(1);
    if (c >= 'A' && c <= 'Z')
        return (1);
    if (c == '|' || c == '>' || c == '<')
        return (1);
    return (0);    
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void ft_putchar(int c, int fd)
{
    write(fd, &c, 1);
}

void ft_putnbr(int nbr, int fd)
{
    if (nbr > 9)
    {
        ft_putnbr(nbr / 10, fd);
        ft_putnbr(nbr % 10, fd);
    }
    else
        ft_putchar(nbr + 48, fd);
}

char *ft_strdup(char *str)
{
    int i;
    char *ptr;
    
    i = 0;
    if (!str)
        return (NULL);
    ptr = malloc(sizeof(char) * (ft_strlen(str) + 1));
    if (!ptr)
        return (NULL);
    while (str[i])
    {
        ptr[i] = str[i];
        i++;
    }
    ptr[i] = '\0';
    return (ptr);
    
}

int ft_strcmp(char *s1, char *s2, int len)
{
    int i;

    i = 0;
    if (!s1 || !s2)
        return (0);
    if (len != -1)
    {
        while (s1[i] == s2[i] && i < len)
        {
            if (!s1[i] || !s2[i])
                break;
            i++;
        }
        if (i > 0 && i == len)
            return (1);
    }
    else
    {
        while (s1[i] && s1[i] == s2[i])
            i++;
        if (i > 0 && s1[i] == '\0' && s2[i] == '\0')
            return (1);
    }
    return (0);
}

int builtins(char **str, t_struct *s, int fd)
{
    int i;
    char *ptr;
    
    i = 1;
    if (ft_strcmp("exit", str[0], -1))
    {
        if (is_alpha(str[1][0]))
        {
            printf("exit: %s numeric argument required\n", str[1]);
            return (1);
        }
        exit(ft_atoi(str[1]));
    }
    if (ft_strcmp("cd", str[0], -1))
    {
        cd(str);
        return (1);
    }
    else if (ft_strcmp("env", str[0], -1))
    {
        print_env(ENVIRON, s, fd);
        return (1);
    }
    else if (ft_strcmp("pwd", str[0], -1) || ft_strcmp("PWD", str[0], -1))
    {
        pwd(fd);
        return (1);
    }
    else if (ft_strcmp("echo", str[0], -1) || ft_strcmp("ECHO", str[0], -1))
    {
        if (!str[1])
            write(fd, "\n", 1);
        else
            echo(str, s, fd);
        return (1);
    }
    else if (ft_strcmp("$HOME", str[0], -1))
    {
        if (chdir(getenv("HOME")) != 0)
            printf("cd: HOME not set\n");
        return (1);
    }
    else if (ft_strcmp("$PATH", str[0], -1))
    {
        chdir(s->PATH);
        return (1);
    }
    else if (ft_strcmp("export", str[0], -1))
    {
        if (!str[1])
            declare_x(s, fd);
        while (str[i])
        {
            int k = 0;
            while (str[i][k])
                k++;
            if (!str[i][k] && str[i][k - 1] == '=')
            {
                ptr = ft_strjoin(str[i], str[i + 1], 10);
                export(ptr, s);
                i += 2;
            }
            else
                export(str[i++], s);
        }
        return (1);
    }
    else if (ft_strcmp("unset", str[0], -1))
    {
        while (str[i])
            unset(str[i++]);
        return (1);
    }
    return (0);
}

void my_free(char **str)
{
    int i;

    i = 0;
    while (str[i])
        free(str[i++]);
    free(str);
}
