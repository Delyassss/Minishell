/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 23:45:18 by ildaboun          #+#    #+#             */
/*   Updated: 2025/06/30 02:51:28 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_helper(int *i, char *input, t_parser *parser)
{
	if (input[*i + 1] == '>')
	{
		if (input[*i + 2] == '>')
		{
			ft_putstr_fd("minishell: syntax error near unexpected token '>'\n",
				2);
			exit_code(1, 258);
			syntax_error(1, 1);
			return (1);
		}
		add_token(">>", TOKEN_REDIR_APPEND, parser);
		*i += 2;
	}
	else
	{
		add_token(">", TOKEN_REDIR_OUT, parser);
		(*i)++;
	}
	return (0);
}

int	redir_helper_two(int *i, char *input, t_parser *parser)
{
	if (input[*i + 1] == '<')
	{
		parser->dont_expand_delimiter = true;
		parser->delimiter = true;
		if (input[*i + 2] == '<')
		{
			ft_putstr_fd("minishell: syntax error near unexpected token '<<'\n",
				2);
			syntax_error(1, 1);
			exit_code(1, 258);
			return (1);
		}
		add_token("<<", TOKEN_REDIR_HEREDOC, parser);
		*i += 2;
	}
	else
	{
		add_token("<", TOKEN_REDIR_IN, parser);
		(*i)++;
	}
	return (0);
}
