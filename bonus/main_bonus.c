/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 22:06:30 by lamhal            #+#    #+#             */
/*   Updated: 2024/03/28 14:32:48 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	t_pipe	*pip;

	if (ac < 5)
		(perror("numbe of argment is less than 5"), exit (1));
	pip = (t_pipe *)malloc(sizeof(t_pipe));
	if (!pip)
		(perror("failed allocation"), exit(1));
	get_path(pip, env);
	check_process_here_doc(ac, av, pip);
	while (pip->id_cmd < ac - 2)
	{
		process_commond(av, pip);
		pip->id_cmd++;
	}
	process_last_commond(av, pip);
	close(0);
	while (wait(NULL) != -1)
		;
	free_exit(pip, 0);
}
