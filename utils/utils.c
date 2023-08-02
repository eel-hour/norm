/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-hour <eel-hour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 23:13:55 by hben-bou          #+#    #+#             */
/*   Updated: 2023/08/02 05:35:18 by eel-hour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

int	builtins(char **str, t_struct *s, int fd)
{
	int		i;
	char	*ptr;
	int		k;

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
			k = 0;
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

void	my_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}
