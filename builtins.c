/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:53:11 by hben-bou          #+#    #+#             */
/*   Updated: 2023/07/31 18:37:52 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void pwd(int fd)
{
    int i;
    char buff[4096];

    i = 0;
    getcwd(buff, 4096);
    while (buff[i])
        write(fd, &buff[i++], 1);
    write(fd, "\n", 1);
}

void cd(char **str)
{
    old_pwd();
    if (str[1] == NULL || (str[1] && str[1][0] == '<' && str[1][1] == '\0') || (str[1][0] == '~' && str[1][1] == '\0'))
    {
        if (chdir(getenv("HOME")) != 0)
            printf("cd: HOME not set\n");
    }
    else if (chdir(str[1]) != 0)
        printf("%s: no such file or directory\n", str[1]);
    new_pwd();
}

void print_env(int type, t_struct *s, int fd)
{
    int k;

    k = 0;
    if (type == ENVIRON)
    {
        while (environ[k])
        {
            if (ft_strcmp(environ[k], "LINE", 4))
                break;
            printf("%s\n", environ[k++]);
        }
    }
    if (type == EXPORT)
        declare_x(s, fd);
}

char *pointer(char **ptr)
{
    char *str;
    int i;
    
    i = 0;
    str = NULL;
    while (ptr[i])
    {
        str = ft_strjoin(str, ptr[i], 2);
        i++;
    }
    return (str);
}

char *pointer1(char **ptr)
{
    char *str;
    int i;
    
    i = 0;
    str = NULL;
    while (ptr[i])
    {
        str = ft_strjoin(str, ptr[i], 4);
        i++;
    }
    return (str);
}

void slash(char **str)
{
    int i;
    int k;
    int trigger;
    char **ptr;

    i = 0;
    trigger = 0;
    while (str[i])
    {
        k = 0;
        ptr = ft_split(str[i], '/');
        while (ptr[k])
        {
            if (ptr[k][0] == '$')
            {
                trigger = 1;
                if (getenv(path(ptr[k])) != NULL)
                    ptr[k] = getenv(path(ptr[k]));
            }
            k++;
        }
        if (trigger == 1)
        {
            str[i] = pointer(ptr);
            trigger = 0;
        }
        i++;
    }
    // free(ptr);
}

void space(char **str)
{
    int i;
    int k;
    int trigger;
    char **ptr;

    i = 0;
    trigger = 0;
    while (str[i])
    {
        k = 0;
        ptr = ft_split(str[i], ' ');
        while (ptr[k])
        {
            if (ptr[k][0] == '$')
            {
                trigger = 1;
                if (getenv(path(ptr[k])) != NULL)
                    ptr[k] = getenv(path(ptr[k]));
            }
            k++;
        }
        if (trigger == 1)
        {
            str[i] = pointer1(ptr);
            trigger = 0;
        }
        i++;
    }
    // free(ptr);
}

void dollar(char **ptr)
{
    slash(ptr);
    space(ptr);
}
