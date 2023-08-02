/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-hour <eel-hour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 05:02:38 by eel-hour          #+#    #+#             */
/*   Updated: 2023/08/02 05:02:59 by eel-hour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fw_redir(char *str)
{
	int	i;
	int	redir;

	i = 0;
	redir = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>' && redir == 0)
		{
			if (str[i + 1] == '>')
				i++;
			redir++;
		}
		else if ((str[i] >= 33 && str[i] <= 126) && str[i] != 62 && str[i] != 34
			&& str[i] != 39 && str[i] != ' ' && str[i] != '|'
			&& str[i] != '\t' && redir == 1)
			redir--;
		i++;
	}
	if (redir == 0)
		return (0);
	else
		return (1);
}

int	bw_redir(char *str)
{
	int	i;
	int	redir;

	i = 0;
	redir = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '<' && redir == 0)
		{
			if (str[i + 1] == '<')
				i++;
			redir++;
		}
		else if ((str[i] >= 33 && str[i] <= 126) && str[i] != 60 && str[i] != 34
			&& str[i] != 39 && str[i] != ' ' && str[i] != '|'
			&& str[i] != '\t' && redir == 1)
			redir--;
		i++;
	}
	if (redir == 0)
		return (0);
	else
		return (1);
}

int	single_quotes(char *str)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && quotes == 0)
			quotes++;
		else if (str[i] == '\'' && quotes == 1)
			quotes--;
		i++;
	}
	if (quotes == 0)
		return (0);
	else
		return (1);
}

int	curshs(char *str)
{
	int	i;
	int	cr;

	i = 0;
	cr = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '{' && cr == 0)
			cr++;
		else if (str[i] == '}' && cr == 1)
			cr--;
		i++;
	}
	if (cr == 0)
		return (0);
	else
		return (1);
}

int	piipe(char *str)
{
	int	i;
	int	pp;

	i = 0;
	pp = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\0' && str[i] == '|' && str[i + 1] == '|')
			return (1);
		else if (str[i] == '|' && pp == 0)
			pp++;
		else if ((str[i] >= 33 && str[i] <= 126) && str[i] != 60 && str[i] != 62
			&& str[i] != ' ' && str[i] != '\t' && pp == 1)
			pp--;
		i++;
	}
	if (pp == 0)
		return (0);
	else
		return (1);
}
