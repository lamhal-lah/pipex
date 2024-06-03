/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 22:12:58 by lamhal            #+#    #+#             */
/*   Updated: 2024/03/28 14:33:50 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*find_fullcmd(char *cmd, t_pipe *pip)
{
	int		i;
	char	*commond;
	char	*full_cmd;

	i = 0;
	commond = ft_strjoinn("/", cmd);
	if (!commond)
		(perror("failed allocation"), free(cmd), free_exit(pip, 1));
	while (pip->path[i])
	{
		full_cmd = ft_strjoinn(pip->path[i], commond);
		if (!full_cmd)
			(perror("failed allocatin"), free(cmd), free(commond),
				free_exit(pip, 1));
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

void	ft_exute_command(char *cmd, t_pipe *pip)
{
	char	**cmds;
	char	*full_cmd;

	cmds = ft_split(cmd, 1);
	if (!cmds)
		(perror("allocation failed "), free_exit(pip, 1));
	if (*cmd == '.')
		(execve(cmd, cmds, NULL), perror("cmd"), free_exit(pip, 1));
	if (*cmd == '/')
		(execve(cmds[0], cmds, NULL), perror(cmd), free_exit(pip, 1));
	full_cmd = find_fullcmd(cmds[0], pip);
	if (!full_cmd)
		(perror("cmd"), free_exit(pip, 1));
	execve(full_cmd, cmds, NULL);
	(perror("cmd"), free(full_cmd), free_exit(pip, 1));
}

void	process_child(char **av, t_pipe *pip)
{
	int	fd;

	close(pip->fd[0]);
	if (pip->id_cmd == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			(close(pip->fd[1]), perror("failed open"), free_exit(pip, 1));
		if (dup2(fd, STDIN_FILENO) == -1)
			(perror("failed dup2"), close(fd), close(pip->fd[1]),
				free_exit(pip, 1));
		close(fd);
	}
	if (dup2(pip->fd[1], STDOUT_FILENO) == -1)
		(perror("failed dup2"), close(pip->fd[1]), free_exit(pip, 1));
	close(pip->fd[1]);
	ft_exute_command(av[pip->id_cmd], pip);
}

void	process_commond(char **av, t_pipe *pip)
{
	pid_t	pid;

	if (pipe(pip->fd) == -1)
		(perror("failed pipe"), free_exit(pip, 1));
	pid = fork();
	if (pid < 0)
		(perror("failed fork"), close(pip->fd[0]), close(pip->fd[1]),
			free_exit(pip, 1));
	if (pid == 0)
		process_child(av, pip);
	if (dup2(pip->fd[0], STDIN_FILENO) == -1)
		(perror("failed dup2"), close(pip->fd[1]), close(pip->fd[0]),
			free_exit(pip, 1));
	(close(pip->fd[1]), close(pip->fd[0]));
}

void	process_last_commond(char **av, t_pipe *pip)
{
	pid_t	pid;
	int		fd;

	pid = fork();
	if (pid == -1)
		(perror("failed fork"), free_exit(pip, 1));
	if (pid == 0)
	{
		if (pip->true == 1)
			fd = open(av[pip->id_cmd + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(av[pip->id_cmd + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			(perror("failed open"), free_exit(pip, 1));
		if (dup2(fd, STDOUT_FILENO) == -1)
			(perror("failed dup2"), close(fd), free_exit(pip, 1));
		close(fd);
		ft_exute_command(av[pip->id_cmd], pip);
	}
}
