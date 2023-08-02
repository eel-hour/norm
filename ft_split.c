/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 23:34:08 by hben-bou          #+#    #+#             */
/*   Updated: 2023/07/22 18:48:13 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	countwrd(char *str, char c)
{
	int	i;
	int	k;

	i = 0;
	k = -1;
	while (*str)
	{
		if (*str != c && k < 0)
		{
			k = 1;
			i++;
		}
		if (*str == c)
			k = -1;
		str++;
	}
	return (i);
}


char	*wordalc(char *str, int start, int end)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)malloc(sizeof(char) * (end - start + 1));
	while (start < end)
		ptr[i++] = str[start++];
	ptr[i] = '\0';
	return (ptr);
}

char	**ft_split(char *s, char c)
{
	int	i;
	int	k;
	int		start;
	char	**ptr;

	i = 0;
	k = 0;
	start = -1;
	ptr = (char **)malloc(sizeof(char *) * (countwrd(s, c) + 1));
	if (!ptr)
		return (NULL);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && start < 0)
			start = i;
		else if ((s[i] == c || i == ft_strlen(s)) && start >= 0)
		{
			ptr[k++] = wordalc(s, start, i);
			start = -1;
		}
		i++;
	}
	ptr[k] = 0;
	return (ptr);
}
