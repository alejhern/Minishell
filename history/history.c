/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejhern <alejhern@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 23:27:46 by alejhern          #+#    #+#             */
/*   Updated: 2025/06/29 20:11:55 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_history_path(char **env)
{
	char	*home;
	char	*history_file;

	home = ft_getenv("HOME", env);
	if (!home)
		return (NULL);
	history_file = ft_strjoin(home, "/.minishell_history");
	if (!history_file)
		return (NULL);
	return (history_file);
}

int	create_history_file(char **env)
{
	char	*history_file;
	int		fd;

	history_file = get_history_path(env);
	if (!history_file)
		return (-1);
	fd = open(history_file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	free(history_file);
	return (fd);
}

int	history(char **comand, char ***env)
{
	char	*history_file;
	int		fd;
	char	*line;
	int		line_count;

	(void) comand;
	history_file = get_history_path(*env);
	if (!history_file)
		return (perror("No souch history file"), -1);
	fd = open(history_file, O_RDONLY);
	if (fd == -1)
		return (perror(""), 1);
	line_count = 0;
	line = get_next_line(fd);
	while (line && ++line_count)
	{
		ft_printf("  %d %s", line_count, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
