/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amhernandez <alejhern@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:29:18 by amhernandez       #+#    #+#             */
/*   Updated: 2025/06/12 23:29:24 by amhernandez      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	*get_output_files(t_list *redirects, int *error)
{
	int				*fds;
	t_redirect		*redirect;
	unsigned int	it;

	if (!redirects)
		return (NULL);
	fds = ft_safe_calloc(ft_lstsize(redirects) + 1, sizeof(int));
	it = 0;
	*error = 1;
	while (redirects)
	{
		redirect = redirects->content;
		if (redirect->is_double)
			fds[it] = open(redirect->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fds[it] = open(redirect->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fds[it] == -1)
			perror(redirect->path);
		redirects = redirects->next;
		if (dup2(fds[it], STDOUT_FILENO) == -1)
			ft_perror_exit("Error redirecting output");
		close(fds[it++]);
	}
	*error = 0;
	return (fds);
}

static int	get_input_file(t_list *redirects, int *error)
{
	int			fd;
	t_redirect	*redirect;

	if (!redirects)
		return (-1);
	redirect = redirects->content;
	fd = open(redirect->path, O_RDONLY);
	if (fd == -1)
	{
		ft_printf_fd(STDERR_FILENO, "no such file or directory: %s\n",
			redirect->path);
		*error = 1;
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		ft_perror_exit("Error redirecting input");
	return (fd);
}

void	recover_fds(t_redirs_manage *manage)
{
	if (manage->fd_in != -1)
	{
		if (dup2(manage->fd_in, STDIN_FILENO) == -1)
			ft_perror_exit("Error redirecting input");
		close(manage->fd_in);
	}
	if (manage->fds_out)
	{
		if (dup2(manage->save_out, STDOUT_FILENO) == -1)
			ft_perror_exit("Error redirecting output");
		close(manage->save_out);
		free(manage->fds_out);
	}
}

void	prepare_redirects(t_redirs_manage *manage, t_command *command,
		int *error)
{
	manage->pipes[0] = -1;
	manage->pipes[1] = -1;
	manage->fd_in = get_input_file(command->redirect_in, error);
	if (manage->fd_in == -1 && manage->is_pipe && manage->forced_pipe)
	{
		manage->fd_in = open("/dev/null", O_RDONLY);
		if (dup2(manage->fd_in, STDIN_FILENO) == -1)
			ft_perror_exit("");
	}
	manage->save_out = dup(STDOUT_FILENO);
	manage->fds_out = get_output_files(command->redirect_out, error);
	if (*error)
	{
		manage->fds_out = NULL;
		manage->save_out = -1;
		return ;
	}
	if (manage->save_out == -1)
		ft_perror_exit("Error saving stdin");
}
