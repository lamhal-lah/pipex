/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 21:33:45 by lamhal            #+#    #+#             */
/*   Updated: 2024/03/18 09:04:58 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_space(char c, int n)
{
	if ((c == ' ' || c == '\t') && n == 1)
		return (1);
	if (c == ':' && n == 0)
		return (1);
	return (0);
}

static int	count_words(char *str, int n)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (is_space(*str, n))
			str++;
		if (*str)
			count++;
		while (!is_space(*str, n) && *str)
			str++;
	}
	return (count);
}

void	ft_free(char **str, int n)
{
	while (n--)
		free(str[n]);
	free(str);
}

static char	*ft_word(char *str, int n, int *l)
{
	int		i;
	char	*word;

	i = 0;
	while (!is_space(str[i], n) && str[i])
		i++;
	*l = i;
	word = malloc(i + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (!is_space(str[i], n) && str[i])
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char *str, int n)
{
	char	**strs;
	int		i;
	int		l;
	int		cnt;

	i = 0;
	if (!str)
		return (NULL);
	cnt = count_words(str, n);
	strs = (char **)malloc((cnt + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	while (i < cnt)
	{
		while (is_space(*str, n))
			str++;
		strs[i] = ft_word(str, n, &l);
		if (strs[i] == NULL)
			return (ft_free(strs, i), NULL);
		i++;
		str += l;
	}
	strs[i] = NULL;
	return (strs);
}
