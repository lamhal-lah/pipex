/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 22:07:31 by lamhal            #+#    #+#             */
/*   Updated: 2024/03/22 17:02:51 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "./getn/get_next_line.h"

typedef struct s_pipe
{
	char	**path;
	pid_t	fd[2];
	int		id_cmd;
	int		true;
}	t_pipe;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char *str, int n);
char	*ft_strjoinn(char *s1, char *s2);
void	ft_putstr_fd(char *str, int fd);
void	free_exit(t_pipe *pip, int n);
void	get_path( t_pipe *xpipe, char **env);
void	check_process_here_doc(int ac, char **av, t_pipe *pip);
void	process_commond(char **av, t_pipe *pip);
void	process_last_commond(char **av, t_pipe *pip);

#endif