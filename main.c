/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:47:12 by pafranco          #+#    #+#             */
/*   Updated: 2025/03/13 22:19:50 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	int				useless;

	if (argv)
		useless = 1 + 1;
	else
		useless = 1 + 1;
	if (useless == 3)
		printf("🤯");
	parser_input(argc == 1);
}
