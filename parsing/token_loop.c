/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:38:57 by ildaboun          #+#    #+#             */
/*   Updated: 2025/07/01 06:32:25 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_token(char *value, t_token_type type, t_parser *parser)
{
	t_token	*new_token;

	new_token = ft_lstnew(value, type, parser);
	if (!new_token)
	{
		write(2, "Error: can't create a new token\n", 32);
		reset(1, 1);
		return ;
	}
	ft_lstadd_back(&(parser->token_head), new_token);
	return ;
}

static void	process_token(char *str, int *k, t_parser *parser)
{
	if (reset(0, 0))
		return ;
	if (ft_isspace(str[*k]))
		(*k)++;
	else if (str[*k] == '|')
	{
		add_token("|", TOKEN_PIPE, parser);
		(*k)++;
	}
	else if ((str[*k] == '>' || str[*k] == '<'))
		handle_redirection(k, str, parser);
	else
		handle_word(k, str, parser);
	return ;
}

static int	number_of_pipes(t_parser *parser)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = parser->token_head;
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	tokenizer_loop(char *input, t_parser *parser)
{
	int		k;
	int		i;

	k = 0;
	i = 0;
	if (reset(0, 0))
		return ;
	while (input[k])
	{
		process_token(input, &k, parser);
		i = number_of_pipes(parser);
		if (i > 0)
			exit_code(1, 0);
		if (syntax_error(0, 0) || reset(0, 0))
			return ;
	}
}
