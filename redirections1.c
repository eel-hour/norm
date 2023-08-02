/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:57:45 by hben-bou          #+#    #+#             */
/*   Updated: 2023/08/02 01:44:29 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print(t_list **list)
{
    t_list *curr;

    curr = *list;
    while (curr)
    {
        printf("%s\n", curr->file);
        curr = curr->next;
    }
}

int insert_node(t_list **linked, char *str, int value)
{
    t_list *node;
    t_list *current;

    if (!str)
        return (1);
    node = malloc(sizeof(t_list));
    node->file = ft_strdup(str);
    node->type = value;
    node->next = NULL;
    if (*linked == NULL)
    {
        *linked = node;
        return (0);
    }
    current = *linked;
    while (current->next)
        current = current->next;
    current->next = node;
    return (0);
}

int create_files11(t_list **linked, char **str)
{
    int i;
    int trigger;

    i = 0;
    trigger = 0;
    while (str[i])
    {
        if (str[i][0] == '>' && str[i][1] == '\0')
        {
            trigger = 1;
            if (str[i + 1])
                insert_node(linked, str[i + 1], IN_FILE);
            if (str[i + 2] && str[i + 2] && str[i + 2][0] == '|')
                insert_node(linked, "DEVIL", 10);
        }
        if (str[i][0] == '>' && str[i][1] == '>' && str[i][2] == '\0')
        {
            trigger = 1;
            if (str[i + 1])
                insert_node(linked, str[i + 1], APPEND_FILE);
            if (str[i + 2] && str[i + 2] && str[i + 2][0] == '|')
                insert_node(linked, "DEVIL", 10);
        }
        if (str[i] && str[i][0] == '<' && str[i][1] == '\0')
        {
            trigger = 1;
            if (str[i + 1])
                insert_node(linked, str[i + 1], OUT_FILE);
            if (str[i + 2] && str[i + 2][0] == '|')
                insert_node(linked, "DEVIL", 10);
        }
        if (str[i] && str[i][0] == '<' && str[i][1] == '<' && str[i][2] == '\0')
        {
            trigger = 1;
            if (str[i + 1])
                insert_node(linked, str[i + 1], HERE_FILE);
            if (str[i + 2] && str[i + 2][0] == '|')
                insert_node(linked, "DEVIL", 10);
        }
        i++;
    }
    if (trigger == 1)
        return (1);
    return (0);
}

char **return_last(char **ptr)
{
    int i;
    int k;
    char **str;

    i = 0;
    k = 0;
    while (ptr[i])
        i++;
    while (i >= 0)
    {
        if (ptr[i] && ptr[i][0])
            k++;
        i--;
    }
    str = malloc(sizeof(char *) * (k + 1));
    if (!str)
        return (NULL);
    while (ptr[i])
    {
        i++;
    }
    k = 0;
    while (i >= 0)
    {
        if (ptr[i] && ptr[i][0] == '|')
            break;
        if (ptr[i])
        {
            str[k++] = ptr[i];
        }
        i--;
    }
    str[k] = NULL;
    return (str);
}

void free_list(t_list *node)
{
    t_list *ls;

    while (node)
    {
        ls = node;
        node = node->next;
        free(ls->file);
        free(node);
    }
}

int redirections(char **str, t_struct *s)
{
    t_list *node;
    t_list *fre;
    int i;
    int id;
    int fd;
    int trigger;
    char *str1;
    char ***ptr;
    
    i = 0;
    node = NULL;
    ptr = pipe_cmd(str);
    if (create_files11(&node, str))
    {
        while (ptr[i])
        {
                while(node)
                {
                    trigger = 0;
                    if (node)
                    {
                        if (node->type == IN_FILE)
                            fd = open(node->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
                        else if (node->type == APPEND_FILE)
                            fd = open(node->file, O_CREAT | O_RDWR | O_APPEND, 0644);
                        else if (node->type == OUT_FILE)
                        {
                            trigger = 4;
                            fd = open(node->file, O_RDWR, 0644);
                            if (ft_strcmp(str[0], "cd", -1))
                            {
                                if (chdir(getenv("HOME")) != 0)
                                    printf("cd: HOME not set");
                            }
                        }
                        else if (node->type == HERE_FILE)
                        {
                            trigger = 1;
                            if (node->next && node->next->type == HERE_FILE)
                                trigger = 3;
                            str1 = heredoc(node->file);
                            fd = open(" ", O_CREAT | O_RDWR | O_TRUNC, 0644);
                            id = fork();
                            if (id == 0)
                            {
                                dup2(fd, 1);
                                printf("%s\n", str1);
                                free(str1);
                                close(fd);
                                exit(0);
                            }
                            wait(NULL);
                        }
                        else if (node->type == 10)
                        {
                            i++;
                            if (node->next)
                                trigger = 2;
                            else
                                fd = 99;
                        }
                    }
                    if (trigger != 2 && trigger != 3)
                    {
                        id = fork();
                        if (id == 0)
                        {
                            if (fd != 99 && (trigger == 0 || trigger == 4))
                            {
                                if (trigger == 4)
                                {
                                    dup2(fd, 0);
                                    close(fd);
                                }
                                else
                                {
                                    dup2(fd, 1);
                                    close(fd);
                                }
                            }
                            if (trigger == 1)
                                pipes(ptr[i], s, 1);
                            else if (trigger == 4)
                                pipes(ptr[i], s, 4);
                            else
                                pipes(ptr[i], s, 0);
                            exit(0);
                        }
                        wait(&s->exit_status);
                        if (trigger == 1)
                            delete_file();
                    }
                    if (node->file)
                        free(node->file);
                    if (node->str)
                        free(node->str);
                    fre = node;
                    node = node->next;
                    free(fre);
                }
                i++;
            }
    }
    else
    {
        id = fork();
        if (id == 0)
        {
            pipes(ptr[i], s, 0);
            exit(0);
        }
        wait(&s->exit_status);
    }
    i = 0;
    while (ptr[i])
        free(ptr[i++]);
    free(ptr);
    return (1);
}



// int redirect(char **str, t_struct *s)
// {
//     int k;

//     k = 0;
//     while (str[k])
//     {
//         if (str[k][0] == '>' || str[k][0] == '<')
//         {
//             if (str[k][0] == '>')
//             {
//                 redirections(str, s);
//                 return (1);
//             }
//             else if (str[k][0] == '<')
//             {
//                 redirection(str, s);
//                 return (2);
//             }
//         }
//         k++;
//     }
//     return (0);
// }


// int main()
// {
//     t_list *list;
//     char *args[] = {"ls", "|", "wc", ">", "file", ">", "file1", ">", "file2", NULL};
//     // t_list *current = list;

//     // while (current->next)
//     // {
//     //     printf("%s\n", current->file);
//     //     current = current->next;
//     // }
//     create_files11(&list, args);
//     print(&list);
// }