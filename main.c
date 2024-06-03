/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:10:43 by lamhal            #+#    #+#             */
/*   Updated: 2024/03/29 15:00:04 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pipe	*xpipe;

	if (ac != 5)
		(perror(" ac is not 5"), exit (1));
	xpipe = malloc(sizeof(t_pipe));
	if (!xpipe)
		(perror("allocation failed"), exit(1));
	pipex(av, env, xpipe);
	wait(NULL);
	wait(NULL);
	free_exit(xpipe, 0);
}
