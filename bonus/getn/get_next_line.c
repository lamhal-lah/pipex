/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:17:09 by lamhal            #+#    #+#             */
/*   Updated: 2024/01/09 17:13:35 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*str;
	static char	*text;
	ssize_t		n ;

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (free(text), text = NULL);
	if (ft_strchr(text, '\n'))
		return (extractline(&text));
	str = malloc((size_t)BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	str[0] = 0;
	while (!ft_strchr(str, '\n'))
	{
		n = read(fd, str, BUFFER_SIZE);
		str[n] = 0;
		if (n == 0)
			break ;
		text = ft_strjoin(text, str);
		if (!text)
			break ;
	}
	free(str);
	str = NULL;
	return (extractline(&text));
}
