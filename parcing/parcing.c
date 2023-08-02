/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-hour <eel-hour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:06:23 by eel-hour          #+#    #+#             */
/*   Updated: 2023/08/02 05:48:36 by eel-hour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replacing(char **str)
{
	int		i;
	int		k;
	char	*ptr;
	char	*pth;

	i = 0;
	k = 0;
	while (str[i])
	{
		pth = path(str[i]);
		if (str[i][0] == '$' && str[i][1] == '\0')
			;
		else if ((ft_strlen(str[i]) >= 2 && str[i][0] == '$'
			&& (str[i][1] == '?' || str[i][1] == '-')))
			;
		else if (ft_strlen(str[i]) >= 2 && str[i][0] == '$'
				&& ft_isdigit(str[i][1]) == 1)
		{
			if (shift_back_str(str[i], 2))
				str[i] = shift_back_str(str[i], 2);
		}
		else if (ft_strlen(str[i]) >= 5 && str[i][0] == '$' && str[i][1] == 'P'
				&& str[i][2] == 'A' && str[i][3] == 'T' && str[i][4] == 'H'
				&& str[i][5] == '\0')
			;
		else if (str[i][0] == '$' && getenv(pth) != NULL)
		{
			ptr = remove_nl(str[i]);
			if (ptr)
			{
				free(str[i]);
				str[i] = ptr;
			}
		}
		else if (str[i][0] == '$')
		{
			k = i;
			while (str[i])
			{
				if (i == k)
					free(str[i]);
				str[i] = str[i + 1];
				i++;
			}
			i = k;
			i--;
		}
		free(pth);
		i++;
	}
}

char	**parser(char *str)
{
	t_parsing	data;
	int			isecond;
	int			trig;
	int			i;

	if (error(str) == 1)
	{
		printf("parsing error!\n");
		return (NULL);
	}
	if (count(str) == 0)
		return (NULL);
	data.parsed = malloc(sizeof(char *) * (count(str) + 1));
	i = 0;
	data.k = 0;
	isecond = 0;
	trig = 0;
	data.cursh = 0;
	data.paran = 0;
	while (str[i])
	{
		data.sub_a = 0;
		data.sub_b = 0;
		trig = 0;
		if (str[i] == '{')
		{
			data.cursh++;
			i++;
		}
		if (str[i] == '(')
		{
			data.paran++;
			i++;
		}
		else if (str[i] == ' ' || str[i] == '\t')
		{
			while (str[i] == ' ' || str[i] == '\t')
				i++;
		}
		else if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		{
			data.sub_a = i;
			if (str[i] == '>' && str[i + 1] == '>')
				i++;
			else if (str[i] == '<' && str[i + 1] == '<')
				i++;
			i++;
			data.sub_b = i;
		}
		else if (str[i] == '\"')
		{
			i++;
			data.sub_a = i;
			while (str[i] != '\"')
				i++;
			data.sub_b = i;
			i++;
		}
		else if (str[i] == '\'')
		{
			data.sub_a = i;
			isecond = i;
			isecond++;
			while (str[isecond] != '\'')
			{
				if (str[isecond] == '$')
					trig = 1;
				isecond++;
			}
			if (trig)
			{
				i++;
				while (str[i] != '\'')
					i++;
				data.sub_b = i;
				i++;
			}
			else
			{
				i++;
				data.sub_a = i;
				while (str[i] != '\'')
					i++;
				data.sub_b = i;
				i++;
			}
		}
		else
		{
			data.sub_a = i;
			while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t'
				&& str[i] != '>' && str[i] != '<' && str[i] != '|'
				&& str[i] != '\"' && str[i] != '\'')
				i++;
			if (data.cursh == 1 && (str[i - 1] == '}' || str[i - 1] == ')')
				&& data.paran == 1 && (str[i - 2] == '}' || str[i - 2] == ')'))
			{
				data.paran--;
				data.cursh--;
				data.sub_b = i - 2;
			}
			else if (data.cursh == 1 && str[i - 1] == '}')
			{
				data.cursh--;
				data.sub_b = i - 1;
			}
			else if (data.paran == 1 && str[i - 1] == ')')
			{
				data.paran--;
				data.sub_b = i - 1;
			}
			else
				data.sub_b = i;
		}
		if ((data.sub_b - data.sub_a) > 0 && data.k < count(str))
		{
			data.parsed[data.k] = ft_substr(str, data.sub_a, data.sub_b
					- data.sub_a);
			data.k++;
		}
	}
	data.parsed[data.k] = NULL;
	check_path(data.parsed);
	return (data.parsed);
}
