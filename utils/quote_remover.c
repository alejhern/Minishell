/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:37:00 by pafranco          #+#    #+#             */
/*   Updated: 2025/06/03 21:35:52 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_quotes(char *str)
{
	int			i;
	int			n;
	int			util;

	i = 0;
	n = 0;
	util = 0;
	while (str[i])
	{
		if (str[i] == '\'' && util == 0)
		{
			util = 1;
			n++;
		}
		else if (str[i] == '\"' && util == 0)
		{
			n++;
			util = 2;
		}
		else if ((util == 1 && str[i] == '\'') || (util == 2 && str[i] == '\"'))
			util = 0;
		i++;
	}
	return (n);
}

char	*quote_remover(char *str, char *aux)
{
	int			i;
	int			j;
	int			util;

	i = 0;
	j = 0;
	util = 0;
	aux = (char *) ft_calloc(sizeof(char), ft_strlen(str) - count_quotes(str) + 1);
	while (str[i] != 0)
	{
		if (str[i] == '\'' && util == 0)
			util = 1;
		else if (str[i] == '\"' && util == 0)
			util = 2;
		else if ((util == 1 && str[i] == '\'') || (util == 2 && str[i] == '\"'))
			util = 0;
		else
		{
			aux[j] = str[i];
			j++;
		}
		i++;
	}
	return (free(str), aux);
}
