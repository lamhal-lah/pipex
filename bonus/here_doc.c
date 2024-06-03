/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:27:57 by lamhal            #+#    #+#             */
/*   Updated: 2024/03/24 07:18:18 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_end(char *line)
{
	if (!line)
		return (0);
	return (line[ft_strlen(line) - 1] == '\n');
}

int	check_del(char *line, char *del)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	if (ft_strncmp(line, del, ft_strlen(del) +1) == 0)
		return (0);
	return (1);
}

void	read_here_doc(char *limeter, t_pipe *pip)
{
	char	*line;
	char	*delemiter;
	int		true;

	true = 1;
	delemiter = ft_strjoinn(limeter, "\n");
	if (!delemiter)
		(perror("allocation failed"), free_exit(pip, 1));
	ft_putstr_fd("here_doc>", 1);
	line = get_next_line(0);
	while (check_del(line, delemiter))
	{
		ft_putstr_fd(line, pip->fd[1]);
		if ((!line && true == 1) || (line && !check_del(line, delemiter)))
			break ;
		true = check_end(line);
		if (true == 1)
			ft_putstr_fd("here_doc>", 1);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	free(delemiter);
}

void	get_here_doc(char *limeter, t_pipe *pip)
{
	if (pipe(pip->fd) == -1)
		(perror("failed pipe"), free_exit(pip, 1));
	read_here_doc(limeter, pip);
	close(pip->fd[1]);
	if (dup2(pip->fd[0], STDIN_FILENO) == -1)
		(perror("failed dup2"), close(pip->fd[0]), free_exit(pip, 1));
	close(pip->fd[0]);
}

void	check_process_here_doc(int ac, char **av, t_pipe *pip)
{
	if (ft_strncmp("here_doc", av[1], 9) == 0)
	{
		pip->id_cmd = 3;
		pip->true = 1;
		if (ac < 6)
			(perror("fiewer argemeent"), exit (1));
		get_here_doc(av[2], pip);
	}
	else
	{
		pip->id_cmd = 2;
		pip->true = 0;
	}
}
