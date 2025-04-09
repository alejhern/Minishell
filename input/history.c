/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:32:53 by pafranco          #+#    #+#             */
/*   Updated: 2025/04/09 18:30:22 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_history(int *size)
{
	char				**history;
	char				*line;
	int					fd;
	int					i;

	i = 0;
	fd = open(".mini_history", O_RDONLY | O_CREAT, 0644);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line != 0)
	{
		ft_append_array((void ***) &history, (void *) line);
		if (history == 0)
			exit(0);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	*size = i;
	return (history);
}

int	add_to_history(char **history, char *line, int size)
{
	ft_append_array((void ***) &history, (void *) line);
	return (size + 1);
}

void	commit_history(char **history, int size)
{
	int					fd;

	fd = open(".mini_history", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		exit(0);
	while (history[size])
	{
		write(fd, history[size], ft_strlen(history[size]));
		size++;
	}
	close(fd);
}
