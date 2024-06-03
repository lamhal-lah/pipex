/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:31:20 by lamhal            #+#    #+#             */
/*   Updated: 2024/03/23 15:25:28 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*a1;
	unsigned char	*a2;

	a1 = (unsigned char *)s1;
	a2 = (unsigned char *)s2;
	i = 0;
	while (a1[i] && a2[i] && a1[i] == a2[i] && i < n)
	{
		i++;
	}
	if (i == n)
		return (0);
	return (a1[i] - a2[i]);
}

size_t	ft_strlen(const	char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*txt;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	i = 0;
	txt = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!txt)
		return (NULL);
	while (s1[j])
		txt[i++] = s1[j++];
	j = 0;
	while (s2[j])
		txt[i++] = s2[j++];
	txt[i] = '\0';
	return (txt);
}

void	free_exit(t_pipe *xpipe, int n)
{
	int	i;

	i = 0;
	while (xpipe->path[i])
		free(xpipe->path[i++]);
	free(xpipe->path);
	free(xpipe);
	exit(n);
}

void	get_path( t_pipe *pipe, char **env)
{
	int		i;

	i = 0;
	if (!env || !*env)
	{
		pipe->path = ft_split("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", 0);
		if (!pipe->path)
			(perror("failed allocation"), free(pipe), exit(1));
		return ;
	}
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			pipe->path = ft_split(env[i] + 5, 0);
			if (!pipe->path)
				(perror("failed allocation"), free(pipe), exit(1));
			return ;
		}
		i++;
	}
	write (2, "path not found\n", 16);
	free(pipe);
	exit (1);
}
