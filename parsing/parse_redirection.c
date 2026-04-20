/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:34:12 by ildaboun          #+#    #+#             */
/*   Updated: 2025/06/28 02:10:43 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_if_quoted(t_command *cmd, char *str)
{
	char	c;

	if (reset(0, 0))
		return ;
	c = str[0];
	if (c == '\'' || c == '"' || ft_strchr(str, '\'' ) || ft_strchr(str, '"'))
	{
		cmd->should_we_expand_herdoc = false;
	}
	else
	{
		cmd->should_we_expand_herdoc = true;
	}
}

static	void	heredoc_token(t_command *cmd, t_token *start, t_parser *parser)
{
	if (start->next->deli_quoted)
		cmd->quoted_delim = true;
	start->next->type = TOKEN_HEREDOC_DELIMITER;
	cmd->stdin_type = TOKEN_REDIR_HEREDOC;
	cmd->there_is_heredoc = true;
	cmd->heredoc = ft_strdup(start->next->value, parser->gc);
	if (ft_strchr(cmd->heredoc, '\x01'))
		cmd->heredoc = remove_edge_chars('\x01', cmd->heredoc, parser);
	check_if_quoted(cmd, cmd->heredoc);
}

void	handle_input_redirection(t_command *cmd, t_token *tokens,
	t_parser *parser)
{
	t_token_type	type_a;
	t_token			*start;
	int				fd;

	if (reset(0, 0))
		return ;
	type_a = tokens->type;
	start = tokens;
	if (start->next && type_a == TOKEN_REDIR_IN
		&& start->next->type == TOKEN_STRING)
	{
		cmd->infile = ft_strdup(start->next->value, parser->gc);
		if (ft_strchr(cmd->infile, '\x01'))
			cmd->infile = remove_edge_chars('\x01', cmd->infile, parser);
		fd = parser_open_file(cmd->infile, 0, parser);
		start->next->type = TOKEN_INFILE;
		cmd->there_is_infile = true;
		cmd->stdin_type = TOKEN_INFILE;
	}
	else if (start->next && type_a == TOKEN_REDIR_HEREDOC
		&& start->next->type == TOKEN_STRING)
		heredoc_token(cmd, start, parser);
}

void	handle_output_redirection(t_command *cmd, t_token *tokens,
t_parser *parser)
{
	t_token			*start;
	int				fd;

	if (reset(0, 0))
		return ;
	start = tokens;
	cmd->append = 1;
	if (start->next && start->next->type == TOKEN_STRING)
	{
		start->next->type = TOKEN_OUTFILE;
		if (start->type == TOKEN_REDIR_APPEND)
			cmd->append = 2;
		cmd->outfile = ft_strdup(start->next->value, parser->gc);
		if (ft_strchr(cmd->outfile, '\x01'))
			cmd->outfile = remove_edge_chars('\x01', cmd->outfile, parser);
		cmd->there_is_outfile = true;
		fd = parser_open_file(cmd->outfile, cmd->append, parser);
		close(fd);
	}
}

void	handle_redirection(int *i, char *input, t_parser *parser)
{
	if (reset(0, 0))
		return ;
	if (input[*i] == '>')
	{
		parser->redir_out = true;
		if (redir_helper(i, input, parser) == 1)
			return ;
	}
	else if (input[*i] == '<')
	{
		parser->redir_in = true;
		if (redir_helper_two(i, input, parser) == 1)
			return ;
	}
}
