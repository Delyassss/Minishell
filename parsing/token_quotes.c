/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:27:48 by ildaboun          #+#    #+#             */
/*   Updated: 2025/06/28 00:03:08 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	quotes_ending(int i, const char *input, char quote_char,
	t_parser *parser)
{
	if (input[i] == quote_char)
	{
		parser->closed_quotes = true;
		parser->quotes = 0;
		return (1);
	}
	return (0);
}

void	handle_quoted_string(int *i, const char *input,
	char *buffer, t_parser *parser)
{
	char	quote_char;

	quote_char = input[*i];
	(*i)++;
	while (input[*i])
	{
		if (quotes_ending(*i, input, quote_char, parser))
			break ;
		else if ((quote_char == '"' && input[*i] == '$')
			&& !parser->dont_expand_delimiter)
		{
			parser->in_quotes = true;
			if (var_expanding(i, input, buffer, parser))
				return ;
			if (quotes_ending(*i, input, quote_char, parser))
				break ;
			(*i)++;
		}
		else
			buffer[parser->j++] = input[(*i)++];
	}
	if (!parser->herdoc_loop)
		char_vs_char(input[*i], quote_char);
}

static	int	helper(int *k, char *str, t_parser *parser)
{
	if (str[*k + 1] == '\'' || str[*k + 1] == '\"')
	{
		parser->quoted = 2;
		parser->quotes = 2;
		(*k)++;
		return (1);
	}
	return (0);
}

static	void	no_quotes(int *k, char *str, int *j, t_parser *parser)
{
	if (str[*k] == '$' && !parser->dont_expand_delimiter)
	{
		if (helper(k, str, parser))
			return ;
		parser->j = *j;
		if (var_expanding(k, str, parser->buffer, parser))
			return ;
		*j = parser->j;
		if (str[*k])
			(*k)++;
	}
	else
	{
		if (str[*k] == '$' && parser->dont_expand_delimiter)
		{
			if (helper(k, str, parser))
				return ;
		}
		if (str[*k] == '\\' && str[*k + 1])
			(*k)++;
		parser->buffer[(*j)++] = str[(*k)++];
		parser->j = *j;
	}
}

void	fill_word_buffer(int *k, char *str, int *j, t_parser *parser)
{
	if (str[*k] == '\'' || str[*k] == '\"')
	{
		parser->quoted = 2;
		parser->quotes = 2;
		parser->j = *j;
		handle_quoted_string(k, str, parser->buffer, parser);
		*j = parser->j;
		if (str[*k])
			(*k)++;
		if (ft_isspace(str[*k]) && parser->empty_after_expand)
		{
			add_token("", TOKEN_STRING, parser);
			parser->empty_after_expand = false;
		}
	}
	else
		no_quotes(k, str, j, parser);
}
