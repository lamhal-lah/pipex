/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:13:51 by lamhal            #+#    #+#             */
/*   Updated: 2024/05/27 15:31:11 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_fullcmd(char *cmd, t_pipe *xpipe)
{
	int		i;
	char	*commond;
	char	*full_cmd;

	i = 0;
	commond = ft_strjoin("/", cmd);
	if (!commond)
		(perror("failed allocation"), free(cmd), free_exit(xpipe, 1));
	while (xpipe->path[i])
	{
		full_cmd = ft_strjoin(xpipe->path[i], commond);
		if (!full_cmd)
			(perror("failed allocatin"), free(cmd), free(commond),
				free_exit(xpipe, 1));
		if (access(full_cmd, F_OK) == 0 && access(full_cmd, X_OK) == 0)
		{
			free(commond);
			return (full_cmd);
		}
		free(full_cmd);
		i++;
	}
	free(commond);
	return (NULL);
}

void	ft_exute_command(char *cmd, t_pipe *xpipe)
{
	char	**cmds;
	char	*full_cmd;

	cmds = ft_split(cmd, 1);
	if (!cmds)
		(perror("allocation failed "), free_exit(xpipe, 1));
	if (*cmd == '.')
		(execve(cmd, cmds, NULL), perror("cmd"), free_exit(xpipe, 1));
	if (*cmd == '/')
		(execve(cmds[0], cmds, NULL), perror("cmd"), free_exit(xpipe, 1));
	full_cmd = find_fullcmd(cmds[0], xpipe);
	if (!full_cmd)
		(perror("cmd"), free_exit(xpipe, 1));
	execve(full_cmd, cmds, NULL);
	(perror("cmd"), free(full_cmd), free_exit(xpipe, 1));
}

void	first_child(char **av, t_pipe *xpipe)
{
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		(close(xpipe->fd[0]), close(xpipe->fd[1]), perror("failed open"),
			free_exit(xpipe, 1));
	close(xpipe->fd[0]);
	if (dup2(fd, STDIN_FILENO) == -1)
		(perror("failed dup2"), close(xpipe->fd[1]), close(fd),
			free_exit(xpipe, 1));
	close(fd);
	if (dup2(xpipe->fd[1], STDOUT_FILENO) == -1)
		(perror("failed dup2"), close(xpipe->fd[1]), close(fd),
			free_exit(xpipe, 1));
	//close(xpipe->fd[0]);
	close(xpipe->fd[1]);
	ft_exute_command(av[2], xpipe);
}

void	second_child(char **av, t_pipe *xpipe)
{
	int		fd;

	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		(close(xpipe->fd[0]), close(xpipe->fd[1]), perror("failed open"),
			free_exit(xpipe, 1));
	//close(xpipe->fd[1]);
	if (dup2(fd, STDOUT_FILENO) == -1)
		(perror("dup2"), close(xpipe->fd[0]), close(fd), free_exit(xpipe, 1));
	close(fd);
	if (dup2(xpipe->fd[0], STDIN_FILENO) == -1)
		(perror("dup2"), close(xpipe->fd[0]), close(fd), free_exit(xpipe, 1));
	//close(xpipe->fd[0]);
	ft_exute_command(av[3], xpipe);
}

void	pipex(char **av, char **env, t_pipe *xpipe)
{
	pid_t	pid[2];

	get_path(xpipe, env);
	if (pipe(xpipe->fd) == -1)
		(perror("pipe failed"), free_exit(xpipe, 1));
	pid[0] = fork();
	if (pid[0] == -1)
		(perror("fork faild"), (close(xpipe->fd[0])), close(xpipe->fd[1]),
			free_exit(xpipe, 1));
	if (pid[0] == 0)
		first_child(av, xpipe);
	pid[1] = fork();
	if (pid[1] == -1)
		(perror("fork faild"), close(xpipe->fd[0]), close(xpipe->fd[1]),
			free_exit(xpipe, 1));
	if (pid[1] == 0)
		second_child(av, xpipe);
	(close(xpipe->fd[0]), close(xpipe->fd[1]));
	if (close(15) == -1)
		printf ("HHHH\n");
}
