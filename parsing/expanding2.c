/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 23:29:35 by ildaboun          #+#    #+#             */
/*   Updated: 2025/06/26 16:08:42 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr_set(const char *s, const char *set)
{
	const char	*p;

	while (*s)
	{
		p = set;
		while (*p)
		{
			if (*s == *p)
				return ((char *)s);
			p++;
		}
		s++;
	}
	return (NULL);
}

static int	var_helper_one(char *after_dollar, int *i,
					char *buffer, t_parser *parser)
{
	if (!ft_alpha(after_dollar[0]) && (after_dollar[0] != '?')
		&& (after_dollar[0] != '_')
		&& !parser->dont_expand_delimiter)
	{
		if (!after_dollar[0] || after_dollar[0] == '\''
			|| after_dollar[0] == '\"' || after_dollar[0] == '$'
			|| !ft_isalnum(after_dollar[0]))
		{
			parser->dollar_before = false;
			if (!after_dollar[0] || after_dollar[0] == '\''
				|| after_dollar[0] == '\"' || after_dollar[0] == '$')
				buffer[parser->j++] = '$';
			else
			{
				buffer[parser->j++] = '$';
				if (after_dollar[0] != '\\')
					buffer[parser->j++] = after_dollar[0];
			}
		}
		return ((*i)++, 0);
	}
	return (1);
}

static void	after_expanding(char *after_dollar, char *buffer, t_parser *parser)
{
	char	*var_value;
	int		n;

	n = 0;
	var_value = get_the_expanded_value(after_dollar, parser->my_strenv, parser);
	if (var_value)
	{
		if (!ft_strcmp(var_value, "\0") && ft_strcmp(buffer, "\0"))
			parser->dollar_before = false;
		parser->in_expand = true;
		if (parser->quotes)
			var_value = insert_char_edges('\x01', var_value, parser);
		while (var_value[n])
		{
			if ((var_value[n] && !parser->quotes && ft_isspace(var_value[n])))
				buffer[parser->j++] = var_value[n];
			while (var_value[n] && !parser->quotes && ft_isspace(var_value[n]))
				n++;
			if (!var_value[n])
				break ;
			buffer[parser->j++] = var_value[n++];
		}
	}
}

static void	quotes_before(t_parser *parser, const char *input, int i)
{
	if (i > 0 && !parser->closed_quotes
		&& (input[i - 1] == '\'' || input[i - 1] == '\"'))
	{
		parser->quotes = 2;
		parser->quoted = 2;
	}
}

int	var_expanding(int *i, const char *input, char *buffer, t_parser *parser)
{
	char	*after_dollar;
	int		n;
	int		j;

	n = 0;
	j = 0;
	if (!ft_strchr(input, '$'))
		return (0);
	parser->dollar_before = true;
	parser->dollar = true;
	quotes_before(parser, input, *i);
	after_dollar = ft_substr(input, *i + 1, ft_strlen(input), parser->gc);
	if (malloc_fail(after_dollar))
		return (1);
	if (!var_helper_one(after_dollar, i, buffer, parser))
		return (0);
	while (after_dollar[j] && (ft_isalnum(after_dollar[j])
			|| after_dollar[j] == '_'))
		j++;
	after_expanding(after_dollar, buffer, parser);
	if (parser->itoa_done)
		j++;
	parser->itoa_done = false;
	(*i) += j;
	return (0);
}
