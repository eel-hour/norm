/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:55:28 by hben-bou          #+#    #+#             */
/*   Updated: 2023/07/30 22:44:19 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int operator(char **str, char *str1)
{
    int i;

    i = 0;
    if (str1)
    {
        if (str1[0] == '>' && str1[1] == '\0')
            return (2);
        if (str1[0] == '>' && str1[1] == '>' && str1[2] == '\0')
            return (2);
        if (str1[0] == '<' && str1[1] == '\0')
            return (2);
        if (str1[0] == '<' && str1[1] == '<' && str1[2] == '\0')
            return (2);
        if (str1[0] == '|' && str1[1] == '\0')
            return (3);
        i++;
    }
    else
    {
        while (str[i])
        {
            if (str[i][0] == '>' && str[i][1] == '\0')
                return (2);
            if (str[i][0] == '>' && str[i][1] == '>' && str[i][2] == '\0')
                return (2);
            if (str[i][0] == '<' && str[i][1] == '\0')
                return (2);
            if (str[i][0] == '<' && str[i][1] == '<' && str[i][2] == '\0')
                return (2);
            if (str[i][0] == '|' && str[i][1] == '\0')
                return (2);
            i++;
        }
    }
    return (0);
}

char **cmds(char **str)
{
    static int i;
    int j;
    int k;
    int counter;
    char **ptr;

    j = 0;
    counter = 0;
    k = i;
    if (!str[i])
    {
        i = 0;
        return (NULL);
    }
    while (str[i] && operator(NULL, str[i]) != 2)
    {
        if (operator(NULL, str[i]) == 0 || operator(NULL, str[i]) == 3)
            counter++;
        i++;
    }
    if (str[i] != NULL)
    {
        while (str[i] && str[i][0] != '|')
        {
            i++;
        }
        if (str[i])
            i++;
    }
    ptr = malloc(sizeof(char *) * (counter + 1));
    if (!ptr)
        return (NULL);
    while (str[k] && operator(NULL, str[k]) != 2)
    {
        if (operator(NULL, str[k]) == 0 || operator(NULL, str[k]) == 3)
        {
            ptr[j] = str[k];
            j++;
        }
        k++;
    }
    ptr[j] = NULL;
    return (ptr);
}

char **xd(char **ptr)
{
    static int i;
    int k;
    int counter;
    char **str;
    
    k = i;
    counter = 0;
    if (!ptr[i])
    {
        i = 0;
        return (NULL);
    }
    while (ptr[i] && ptr[i][0] != '|')
    {
        i++;
        counter++;
    }
    if (ptr[i] && ptr[i][0] == '|')
        i++;
    str = malloc(sizeof(char *) * (counter + 1));
    if (!str)
        return (NULL);
    counter = 0;
    while (ptr[k] && ptr[k][0] != '|')
        str[counter++] = ptr[k++];
    str[counter] = NULL;
    return (str);
}

char ***pipe_cmd(char **str)
{
    int i;
    int counter;
    char ***ptr;
    char **cmd;
    
    i = 0;
    counter = 1;
    cmd = cmds(str);
    if (!str)
        return (NULL);
    while (str[i])
    {
        if (operator(NULL, str[i]) == 2)
            counter++;
        i++;
    }
    ptr = malloc(sizeof(char **) * (counter + 1));
    if (!ptr)
        return (NULL);
    i = 0;
    while (cmd)
    {
        ptr[i++] = cmd;
        cmd = cmds(str);
    }
    ptr[i] = NULL;
    return (ptr);
}

char **join1(char **ptr)
{
    int i;
    char **str;

    i = 0;
    while (ptr[i])
        i++;
    str = malloc(sizeof(char *) * (i + 2));
    if (!str)
        return (NULL);
    i = 0;
    while (ptr[i])
    {
        str[i] = ptr[i];
        i++;
    }
    str[i++] = ft_strdup(" ");
    str[i] = NULL;
    return (str);
}

int pipes(char **ptr, t_struct *s, int trigger)
{
    int fd[2];
    int id;
    int fd1;
    char **cmd;
    char **cmd1;
    
    fd1 = 0;
    if (trigger == 1)
    {
        id = fork();
        if (id == 0)
        {
            if (builtins(herereturn(ptr, 0), s, 1))
                exit(0);
            else
                commands(herereturn(ptr, 0));
        }
        wait(&s->exit_status);
        return (0);
    }
    if (trigger == 4)
    {
        id = fork();
        if (id == 0)
        {
            if (builtins(herereturn(ptr, 1), s, 1))
                exit(0);
            else
                commands(herereturn(ptr, 1));
        }
        wait(&s->exit_status);
        return (0);
    }
    else
    {
        cmd = xd(ptr);
        while (cmd)
        {
            cmd1 = xd(ptr);
            pipe(fd);
            id = fork();
            if (id == 0)
            {
                dup2(fd1, 0);
                if (cmd1)
                    dup2(fd[1], 1);
                close(fd[0]);
                if (builtins(cmd, s, 1))
                    exit(0);
                else
                    commands(cmd);
            }
            wait(&s->exit_status);
            close(fd[1]);
            fd1 = fd[0];
            cmd = cmd1;
        }
        return (0);
    }
    exit(1);
    return (0);
}


// int main()
// {
//     int i = 0;
//     int k;
//     char ***ptr;
//     char *args[] = {"ls", "|", "wc", ">", "file", "|", "ls", "|", "grep", "here", NULL};

//     ptr = pipe_cmd(args);
//     while (ptr[i])
//     {
//         k = 0;
//         while (ptr[i][k])
//             printf("%s\n", ptr[i][k++]);
//         printf("-------------\n");
//         i++;
//     }
// }