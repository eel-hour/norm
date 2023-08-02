/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:03:05 by hben-bou          #+#    #+#             */
/*   Updated: 2023/08/01 02:41:31 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *remove_var(char *str)
{
    int i;
    int k;
    char *ptr;
    
    i = 0;
    k = 0;
    while (str[i] && str[i] != '=')
        i++;
    ptr = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
    if (!ptr)
        return (NULL);
    while (str[i])
        ptr[k++] = str[i++];
    ptr[k] = '\0';
    free(str);
    return (ptr);
}

char *path(char *str)
{
    int i;
    int k;
    char *ptr;

    i = 0;
    k = 0;
    ptr = malloc(sizeof(char) * ft_strlen(str));
    if (!ptr)
        return (NULL);
    i = 1;
    while (str[i])
        ptr[k++] = str[i++];
    ptr[k] = '\0';
    // free(str);
    return (ptr);
}

char *remove_nl(char *str)
{
    int i;
    char *pth;
    char *ptr;
    
    i = 0;
    pth = path(str);
    str = getenv(pth);
    free(pth);
    if (!str)
        return (NULL);
    while (str[i] && str[i] != '\n')
        i++;
    ptr = malloc(sizeof(char) * (i + 1));
    if (!ptr)
        return (NULL);
    i = 0;
    while (str[i] && str[i] != '\n')
    {
        ptr[i] = str[i];
        i++;
    }
    ptr[i] = '\0';
    return (ptr);
}
