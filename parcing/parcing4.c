/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-hour <eel-hour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 05:04:03 by eel-hour          #+#    #+#             */
/*   Updated: 2023/08/02 05:04:49 by eel-hour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**double_char_null(void)
{
	char	**returnd;

	returnd = malloc(8);
	returnd[0] = 0;
	return (returnd);
}

char	*joining(char **str)
{
	char	*returnd;
	int		i;

	i = 0;
	returnd = NULL;
	while (str[i])
	{
		returnd = ft_strjoin(returnd, str[i], 4);
		i++;
	}
	return (returnd);
}

char	*shift_back_str(char *str, int nbr)
{
	int	i;

	i = 0;
	if (ft_strlen(str) > nbr && nbr < 1)
		return (NULL);
	i = nbr;
	while (str[i])
	{
		str[i - nbr] = str[i];
		i++;
	}
	str[i - nbr] = str[i];
	return (str);
}

int	error(char *str)
{
	if (single_quotes(str) == 1 || double_quotes(str) == 1 || fw_redir(str) == 1
		|| bw_redir(str) == 1 || piipe(str) == 1 || curshs(str) == 1)
		return (1);
	return (0);
}
