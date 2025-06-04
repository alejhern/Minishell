/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amhernandez <alejhern@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 03:27:03 by amhernandez       #+#    #+#             */
/*   Updated: 2025/05/31 03:29:53 by amhernandez      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	*get_output_files(t_list *redirects)
{
	int				*fds;
	t_redirect		*redirect;
	unsigned int	index;

	if (!redirects)
		return (NULL);
	fds = ft_safe_calloc(ft_lstsize(redirects) + 1, sizeof(int));
	index = 0;
	while (redirects)
	{
		redirect = redirects->content;
		if (redirect->is_double)
			fds[index] = open(redirect->path, O_WRONLY | O_CREAT | O_APPEND,
					0644);
		else
			fds[index] = open(redirect->path, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		if (fds[index] == -1)
			ft_perror_exit("Error opening output file");
		redirects = redirects->next;
		if (dup2(fds[index], STDOUT_FILENO) == -1)
			ft_perror_exit("Error redirecting output");
		close(fds[index++]);
	}
	return (fds);
}

static int	get_input_file(t_list *redirects)
{
	int			fd;
	t_redirect	*redirect;

	if (!redirects)
		return (-1);
	redirect = redirects->content;
	fd = open(redirect->path, O_RDONLY);
	if (fd == -1)
		ft_perror_exit("Error opening input file");
	if (dup2(fd, STDIN_FILENO) == -1)
		ft_perror_exit("Error redirecting input");
	close(fd);
	return (fd);
}

void	recover_fds(t_redirects_response response)
{
	if (response.fd_in != -1)
		if (dup2(response.fd_in, STDIN_FILENO) == -1)
			ft_perror_exit("Error redirecting input");
	if (response.fds_out)
	{
		if (dup2(response.save_out, STDOUT_FILENO) == -1)
			ft_perror_exit("Error redirecting output");
		close(response.save_out);
		free(response.fds_out);
	}
}

t_redirects_response	prepare_redirects(t_command *command)
{
	t_redirects_response	response;

	response.fd_in = get_input_file(command->redirect_in);
	response.save_out = dup(STDOUT_FILENO);
	response.fds_out = get_output_files(command->redirect_out);
	if (response.save_out == -1)
		ft_perror_exit("Error saving stdin");
	return (response);
}
