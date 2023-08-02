/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 19:23:35 by hben-bou          #+#    #+#             */
/*   Updated: 2023/07/27 19:58:46 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **str(char **str)
{
    static int i;
    int j;
    int k;
    int counter;
    char **ptr;

    j = 0;
    counter = 0;
    while(str[i] && str[i][0] == '>')
    {
        if (operator(NULL, str[i]) == 0)
            counter++;
        i++;
    }
    k = i;
    ptr = malloc(sizeof(char *) * (counter + 1));
    if (!ptr)
        return (NULL);
    while (str[k] && str[k][0] != '>')
    {
        if (operator(NULL, str[i]) == 0)
            ptr[j++] = str[k];
        k++;
    }
    ptr[j] = NULL;
    if (str[i][0] == '>')
    {
        while (str[i] && str[i][0] != '|')
            i++;
    }
    return (ptr);
}

int main()
{
    char *args[] = {"ls", "|", "wc", ">", "file", ">", "file1", "|", "ls", "|", "wc", NULL};
    printf("%s\n", str(args));
}