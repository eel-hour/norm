/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-hour <eel-hour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 05:05:25 by eel-hour          #+#    #+#             */
/*   Updated: 2023/08/02 05:14:18 by eel-hour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			while (str[i] == ' ' || str[i] == '\t')
				i++;
		}
		else if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		{
			if (str[i] == '>' && str[i + 1] == '>')
				i++;
			else if (str[i] == '<' && str[i + 1] == '<')
				i++;
			count++;
			i++;
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
				i++;
			count++;
			i++;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
			count++;
			i++;
		}
		else
		{
			count++;
			while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t'
				&& str[i] != '|' && str[i] != '<' && str[i] != '>'
				&& str[i] != '\"' && str[i] != '\'')
				i++;
		}
	}
	return (count);
}

char	*replace_pwd(char *str)
{
	int		i;
	int		trigger;
	char	**returnd;
	char	*join;

	i = 0;
	trigger = 0;
	while (str[i])
	{
		if (str[i] == '$')
			trigger = 1;
		i++;
	}
	if (trigger)
	{
		returnd = ft_spliting(str);
		replacing(returnd);
		join = joining(returnd);
		my_free(returnd);
		if (!join)
			return (NULL);
		return (join);
	}
	return (str);
}

int	check_path2(char **str, int i)
{
	int	k;

	k = i;
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
	i = k;
	return (i);
}

void	check_path(char **str)
{
	int		i;
	int		k;
	char	*ptr;

	i = 0;
	while (str[i])
	{
		if (str[i][0] != '\'' && str[i][ft_strlen(str[i]) - 1] != '\'')
		{
			ptr = replace_pwd(str[i]);
			if (!ptr)
				i = check_path2(str, i);
			else
				str[i] = ptr;
		}
		i++;
	}
}

char	**remove_single(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i][0] == '\'' && str[i][ft_strlen(str[i]) - 1] == '\'')
		{
			j = 0;
			while (str[i][j])
			{
				str[i][j] = str[i][j + 1];
				j++;
			}
			str[i][j - 2] = str[i][j - 1];
		}
		i++;
	}
	return (str);
}
