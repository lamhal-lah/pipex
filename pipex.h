/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:04:24 by lamhal            #+#    #+#             */
/*   Updated: 2024/03/29 14:58:02 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_pipe
{
	char	**path;
	int		fd[2];
}	t_pipe;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char *str, int n);
char	*ft_strjoin(char const *s1, char const *s2);
void	get_path(t_pipe *pipe, char **env);
void	free_exit(t_pipe *xpipe, int n);
void	pipex(char **av, char **env, t_pipe *xpipe);

#endif