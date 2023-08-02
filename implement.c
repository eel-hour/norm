/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 22:36:47 by hben-bou          #+#    #+#             */
/*   Updated: 2023/08/02 02:10:57 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pid = 99;

char *join(char *str)
{
    int i;
    int k;
    char *ptr;

    i = 0;
    k = 0;
    while (str[i])
        i++;
    ptr = malloc(sizeof(char) * (i + 6));
    if (!ptr)
        return (NULL);
    i = 0;
    ptr[i++] = '/';
    ptr[i++] = 'b';
    ptr[i++] = 'i';
    ptr[i++] = 'n';
    ptr[i++] = '/';
    while (str[k])
    {
        ptr[i] = str[k];
        i++;
        k++;
    }
    ptr[i] = '\0';
    return (ptr);
}

char *join2(char *str)
{
    int i;
    int k;
    char *ptr;

    i = 0;
    k = 0;
    while (str[i])
        i++;
    ptr = malloc(sizeof(char) * (i + 10));
    if (!ptr)
        return (NULL);
    i = 0;
    ptr[i++] = '/';
    ptr[i++] = 'u';
    ptr[i++] = 's';
    ptr[i++] = 'r';
    ptr[i++] = '/';
    ptr[i++] = 'b';
    ptr[i++] = 'i';
    ptr[i++] = 'n';
    ptr[i++] = '/';
    while (str[k])
    {
        ptr[i] = str[k];
        i++;
        k++;
    }
    ptr[i] = '\0';
    return (ptr);
}

int commands(char **str)
{
    if (!str[0])
        printf("s: command not found\n");
    else
    {
        if (str[0][0] == '\0')
            exit(0);
        else
        {
            if (execve(join(str[0]), str, NULL) == -1)
            {
                if (execve(str[0], str, NULL) == -1)
                    execve(join2(str[0]), str, NULL);
            }
            printf("%s: command not found\n", str[0]);
        }
    }
    exit(127);
    return (0);
}

int init(t_struct *s)
{
    int i;

    i = 0;
    while (environ[i])
        i++;
    s->PATH = malloc(sizeof(char) * 4096);
    // s->expor = malloc(sizeof(char *) * (i + 1));
    if (!s->PATH || !s->expor)
        return (1);
    s->PATH = getcwd(s->PATH, 4096);
    s->expor = environ;
    return (0);
}

void sig_handler(int sig)
{
    // signal(sig, SIG_DFL);
    if (sig == SIGINT)
    {
        rl_redisplay();
        ft_putstr("\n");
        ft_putstr("minishell: ");
        kill(pid, SIGQUIT);
        // rl_on_new_line();
    }
    if (sig == SIGQUIT)
    {
        kill(pid, 3);
        exit(1);
    }
    return ;
}

int main(void)
{
    t_struct *s;
    char **str;
    char *st;

    s = malloc(sizeof(t_struct));
    if (!s)
        return (0);
    init(s);
    signal(SIGINT, sig_handler);
    while (1)
    {
        st = readline("minishell: ");
        if (!st)
            exit(0);
        str = parser(st);
        if (str != NULL)
        {
            add_history(st);
            if(operator(str, NULL))
            {
                if (redirections(str, s) == 1);
                else
                    pipes(str, s, 0);
                // pipe_cmd(str, 1);
            }
        }
        free(st);
        my_free(str);
        system("leaks minishell > file");
        //     else
        //     {
        //         if (builtins(str, s, 1) == 1);
        //         else
        //         {
        //             pid = fork();
        //             if (pid == 0)
        //             {
        //                 commands(str);
        //                 exit(0);
        //             }
        //             wait(&s->exit_status);
        //         }
        //     }
        // }
    }
}

