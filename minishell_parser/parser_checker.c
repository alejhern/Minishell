/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:54:58 by pafranco          #+#    #+#             */
/*   Updated: 2025/03/04 15:42:55 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Things to check:
//
//	unfinishe quotes
//	unfinished or empty parenthesis
//	more than 2 & or | (&&& |||)
//	& alone
//	empty conditionals (echo && && cat) (trailing conditional maybe apply here_doc or similar)
//	more than two redirection signs (<<</>>>) 
