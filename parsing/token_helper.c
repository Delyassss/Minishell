/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:39:38 by ildaboun          #+#    #+#             */
/*   Updated: 2025/07/01 16:24:28 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_ambiguous(t_parser *parser, char *buf)
{
	char	**split;

	if (parser->in_expand && (parser->redir_out || parser->redir_in))
	{
		parser->buffers[parser->track_ambiguous] = ft_strdup(buf, parser->gc);
		if (!*buf)
		{
			parser->track_ambiguous++;
		}
		else
		{
			split = ft_split(buf, " \t\n\v\f\r", parser->gc);
			if (arr_len(split) > 1)
			{
				parser->track_ambiguous++;
			}
		}
	}
	parser->redir_out = false;
	parser->redir_in = false;
}

void	print_ambiguous(t_parser *parser)
{
	int	i;

	i = 0;
	if (!parser->track_ambiguous)
		return ;
	while (i < parser->track_ambiguous)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		i++;
	}
}

static void	final_step_after_expanding(t_parser *parser, char *buffer, int j)
{
	if (!ft_strcmp(buffer, "export"))
		parser->cmd_export = true;
	if (!ft_strcmp(buffer, "export") || !beta_ident(buffer))
		parser->belong_to_export = true;
	if (beta_ident(buffer) && !parser->belong_to_export
		&& !check_if_exist(parser->env, buffer))
		add_token(buffer, TOKEN_ENV_VAR, parser);
	else if ((j > 0 || !*buffer))
		add_token(buffer, TOKEN_STRING, parser);
	if (buffer && ft_strchr_set(buffer, " \t\n\v\f\r") && parser->in_expand)
		parser->split_later
		[parser->track_split++] = ft_strdup(buffer, parser->gc);
	handle_ambiguous(parser, buffer);
	parser->in_quotes = false;
	parser->needs_expansion = false;
	parser->in_expand = false;
	parser->no_buffer_needed = false;
	parser->dont_expand_delimiter = false;
	parser->delimiter = false;
}

void	handle_word(int *k, char *str, t_parser *parser)
{
	int	j;

	j = 0;
	parser->quoted = 0;
	parser->quotes = 0;
	if (reset(0, 0))
		return ;
	parser->buffer = gc_malloc(parser->gc, ft_strlen(str) + 5000000);
	if (malloc_fail(parser->buffer))
		return ;
	ft_memset(parser->buffer, 0, ft_strlen(str) + 500000);
	parser->save_k = *k;
	while (str[*k] && !ft_isspace(str[*k]) && str[*k] != '|'
		&& str[*k] != '<' && str[*k] != '>')
		fill_word_buffer(k, str, &j, parser);
	final_step_after_expanding(parser, parser->buffer, j);
}
