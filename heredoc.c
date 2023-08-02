/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:58:01 by hben-bou          #+#    #+#             */
/*   Updated: 2023/08/02 00:29:04 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_strjoin(char *s1, char *s2, int type)
{
    int i;
    int k;
    char *ptr;

    i = 0;
    k = 0;
    if (!s1)
    {
        s1 = malloc(sizeof(char));
        s1[0] = '\0';
    }
    if (type >= 1 && type <= 3)
    {
        ptr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
    }
    else
        ptr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    if (!s1 || !s2 || !ptr)
        return (NULL);
    while (s1[i])
    {
        ptr[i] = s1[i];
        i++;
    }
    if (s1[0] != '\0' && type == 1)
        ptr[i++] = '\n';
    if (type == 2 && s1[0] != '\0')
        ptr[i++] = '/';
    if (type == 3 && s1[0] != '\0')
        ptr[i++] = ' ';
    while (s2[k])
        ptr[i++] = s2[k++];
    ptr[i] = '\0';
    free(s1);
    return (ptr);
}

void handler(int sig)
{
    (void)sig;
    rl_replace_line("minishell: ", 1);
    signal(sig, SIG_IGN);
    exit(1); 
}

void delete_file(void)
{
    int id;
    char *args[] = {"/bin/rm", "-rf", " ", NULL};
    id = fork();
    if (id == 0)
        execve(args[0], args, NULL);
    wait(NULL);
}

char *heredoc(char *str)
{
    int read_bytes;
    char *ptr ;
    char *s;

    read_bytes = -1;
    ptr = malloc(sizeof(char) * INT_MAX);
    s = NULL;
    if (!ptr)
        return (NULL);
    signal(SIGINT, handler);
    while (1)
    {
        write(1, "heredoc> ", 9);
        read_bytes = read(0, ptr, INT_MAX);
        ptr[read_bytes - 1] = '\0';
        if (ptr[0] == '$' && getenv(path(ptr)))
            ptr = remove_nl(getenv(path(ptr)));
        else if (ptr[0] == '$' && ptr[1] && getenv(path(ptr)) == NULL)
            ptr[0] = '\0';
        if (ft_strcmp(str, ptr, -1))
            break;
        s = ft_strjoin(s, ptr, 1);
    }
    free(ptr);
    return (s);
}
