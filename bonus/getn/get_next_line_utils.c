/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:28:33 by lamhal            #+#    #+#             */
/*   Updated: 2024/03/03 20:27:57 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(char *str, char ch)
{
	if (!str)
		return (NULL);
	while (*str)
		if (*str++ == ch)
			return (str);
	if (*str == ch)
		return (str);
	return (NULL);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	char	*s;
	size_t	i;

	i = -1;
	if (!str)
		return (NULL);
	s = malloc(ft_strlen(str) + 1);
	if (!s)
		return (NULL);
	while (str[++i])
		s[i] = str[i];
	s[i] = '\0';
	return (s);
}

char	*ft_strjoin(char *str1, char *str2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!str2)
		return (NULL);
	if (!str1)
		return (ft_strdup(str2));
	i = 0;
	j = 0;
	str = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!str)
		return (NULL);
	while (str1[i])
	{
		str[i] = str1[i];
		i++;
	}
	while (str2[j])
		str[i++] = str2[j++];
	str[i] = '\0';
	free(str1);
	str1 = NULL;
	return (str);
}

char	*extractline(char **str)
{
	size_t	i;
	size_t	j;
	char	*s;
	char	*s1;

	i = 0;
	if (!*str)
		return (NULL);
	while (str[0][i])
		if (str[0][i++] == '\n')
			break ;
	s = malloc(i + 1);
	if (!s)
		return (NULL);
	j = -1;
	while (++j < i)
		s[j] = str[0][j];
	s[j] = '\0';
	if (!str[0][i])
		return (free(*str), *str = NULL, s);
	s1 = ft_strdup(&str[0][i]);
	if (!s1)
		return (free(s), s = NULL);
	return (free(*str), *str = s1, s);
}
