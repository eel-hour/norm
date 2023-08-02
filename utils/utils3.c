/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-hour <eel-hour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 05:34:40 by eel-hour          #+#    #+#             */
/*   Updated: 2023/08/02 05:37:54 by eel-hour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putchar(int c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr(int nbr, int fd)
{
	if (nbr > 9)
	{
		ft_putnbr(nbr / 10, fd);
		ft_putnbr(nbr % 10, fd);
	}
	else
		ft_putchar(nbr + 48, fd);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*ptr;

	i = 0;
	if (!str)
		return (NULL);
	ptr = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!ptr)
		return (NULL);
	while (str[i])
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	ft_strcmp(char *s1, char *s2, int len)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	if (len != -1)
	{
		while (s1[i] == s2[i] && i < len)
		{
			if (!s1[i] || !s2[i])
				break ;
			i++;
		}
		if (i > 0 && i == len)
			return (1);
	}
	else
	{
		while (s1[i] && s1[i] == s2[i])
			i++;
		if (i > 0 && s1[i] == '\0' && s2[i] == '\0')
			return (1);
	}
	return (0);
}
