/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 08:14:27 by hben-bou          #+#    #+#             */
/*   Updated: 2023/07/30 18:33:28 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *read_file(int fd)
{
    int read_bytes;
    char *ptr;

    read_bytes = -1;
    ptr = malloc(sizeof(char) * INT_MAX);
    if (!ptr)
        return (NULL);
    read_bytes = read(fd, ptr, INT_MAX);
    if (!ptr[0])
    {
        free(ptr);
        return (NULL);
    }
    ptr[read_bytes - 1] = '\0';
    return (ptr);
}

// char *gnl(char *str)
// {
//     static int i;
//     int j;
//     int k;
//     char *ptr;

//     j = 0;
//     k = i;
//     while (str[i] && str[i][0] != '\n')
//     {
//         j++;
//         i++;
//     }
//     if (!str[i])
//     {
//         i = 0;
//         return (NULL);
//     }
//     if (str[i][0] == '\n')
//         i++;
//     ptr = malloc(sizeof(char) * (j + 1));
//     if (!ptr)
//         return (NULL);
//     j = 0;
//     while (str[k] && str[k][0] != '\n')
//         ptr[j++] = str[k++];
//     ptr[j] = NULL;
//     return (ptr);
// }

char **direct_cmd(char **ptr)
{
    int i;
    char **str;

    i = 0;
    while (ptr[i] && operator(NULL, ptr[i]) != 2)
        i++;
    str = malloc(sizeof(char *) * (i + 1));
    if (!str)
        return (NULL);
    i = 0;
    while (ptr[i] && operator(NULL, ptr[i]) != 2)
    {
        str[i] = ptr[i];
        i++;
    }
    str[i] = NULL;
    return (str);
}


char **left_direct(char **ptr)
{
    int i;
    int j;
    int k;
    char **str;
    char **str1;
    
    i = 0;
    j = 0;
    k = 0;
    str = direct_cmd(ptr);
    while (str[k])
        k++;
    str1 = malloc(sizeof(char *) * (k + i + 1));
    if (!str1)
        return (NULL);
    k = 0;
    while (str[i])
        str1[i++] = ptr[k++];
    k = 3;
    while (j < redirection_counter(ptr))
    {
        str1[i] = ptr[k];
        i++;
        j++;
        k += 2;
    }
    printf("%s\n", str[0]);
    str1[i] = NULL;
    return (str1);
}

char **herereturn(char **ptr, int trigger)
{
    int i;
    int k;
    char **str;
    
    i = 0;
    k = 0;
    while (ptr[i])
        i++;
    if (!ptr[i])
        i--;
    while (ptr[i] && ptr[i][0] != '|' && i != 0)
    {
        k++;
        i--;
    }
    if (i == 0 && ptr[i])
        k++;
    if (i == -1)
        i++;
    if (ptr[i] && ptr[i][0] == '|')
        i++;
    str = malloc(sizeof(char *) * (k + 2));
    if (!str)
        return (NULL);
    k = 0;
    while (ptr[i] && ptr[i][0] != '<' && ptr[i][1] != '<' && ptr[i][2] == '\0')
    {
        str[k++] = ptr[i++];
    }
    if (trigger != 1)
        str[k++] = ft_strdup(" ");
    str[k] = NULL;
    return (str);
}

int *create_file2(char **ptr, t_struct *s)
{
    int i;
    int k;
    int id;
    int *fd;
    char *str;
    
    i = 0;
    k = 0;
    fd = malloc(sizeof(int) * redirection_counter(ptr));
    while (ptr[k] && ptr[k][0] != '<')
        k++;
    k++;
    while (i < redirection_counter(ptr))
    {
        if (ptr[k - 1][0] == '<' && ptr[k - 1][1] == '\0')
            fd[i] = open(ptr[k], O_RDWR, 06444);
        if (ptr[k - 1][0] == '<' && ptr[k - 1][1] == '<')
        {
            id = fork();
            if (id == 0)
            {
                str = heredoc(ptr[k]);
                fd[i] = open(" ", O_CREAT | O_RDWR | O_TRUNC, 0644);
                write(fd[i], str, ft_strlen(str));
                write(fd[i], "\n", 1);
                exit(0);
            }
            wait(&s->exit_status);
        }
        k += 2;
        i++;
    }
    // char **args = herereturn(ptr);
    // id = fork();
    // if (id == 0)
    // {
    //     commands(args);
    //     exit(0);
    // }
    // wait(&s->exit_status);
    // id = fork();
    // if (id == 0)
    // {
    //     char *argrs[] = {"/bin/rm", "-rf", " ", NULL};
    //     execve(argrs[0], argrs, NULL);
    //     exit(0);
    // }
    // wait(NULL);
    return (fd);
}

