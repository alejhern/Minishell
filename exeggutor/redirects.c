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

void transfer_output(int *fds, char *output)
{
    if (!fds)
    {
        if (!ft_putendl_fd(output, STDOUT_FILENO))
            ft_perror_exit("Error writing to standard output");
        return ;
    }
    while (*fds)
    {
        if (!ft_putendl_fd(output, *fds))
            ft_perror_exit("Error writing to output file");
        close(*(fds++));
    }
}

int *get_output_files(t_list *redirects)
{
    int				*fds;
    t_redirect		*redirect;
    unsigned int	index;

    if (!redirects)
        return (NULL);
    fds = malloc(sizeof(int) * ft_lstsize(redirects));
    index = 0;
    while (redirects)
    {
        redirect = redirects->content;
        if (redirect->is_double)
            fds[index] = open(redirect->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            fds[index] = open(redirect->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fds[index++] == -1)
            ft_perror_exit("Error opening output file");
        redirects = redirects->next;
    } 
    return (fds);
}

int get_input_file(t_list *redirects)
{
    int        fd;
    t_redirect *redirect;

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
