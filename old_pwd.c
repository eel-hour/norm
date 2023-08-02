/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 01:02:43 by yraiss            #+#    #+#             */
/*   Updated: 2023/07/24 23:03:34 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void old_pwd(void)
{
    int i;
    char oldpwd[4096];
    i = 0;
    getcwd(oldpwd, 4096);
    while (environ[i])
    {
        if (ft_strcmp("OLDPWD", environ[i], 6) == 1)
            environ[i] = ft_strjoin(ft_strdup("OLDPWD="), ft_strdup(oldpwd), 10);
        i++;
    }
    i = 0;
}

void new_pwd(void)
{
    int i;
    char newpwd[4096];

    i = 0;
    getcwd(newpwd, 4096);
    while (environ[i])
    {
        if (ft_strcmp("PWD", environ[i], 3) == 1)
            environ[i] = ft_strjoin(ft_strdup("PWD="), ft_strdup(newpwd), 10);
        i++;
    }
}
