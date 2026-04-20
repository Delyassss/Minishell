/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:01:40 by ildaboun          #+#    #+#             */
/*   Updated: 2025/07/01 06:11:49 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_command_back(t_command **head, t_command *new_cmd)
{
	t_command	*tmp;

	if (!*head)
		*head = new_cmd;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
	}
}

static void	multi_herdoc(t_command *cmd, t_parser *parser
	, t_token *tokens, int i)
{
	cmd->heredocers[i] = ft_strdup(tokens->value, parser->gc);
	if (cmd->heredocers[i] && ft_strchr(cmd->heredocers[i], '\x01'))
		cmd->heredocers[i] = remove_edge_chars('\x01', cmd->heredocers[i],
				parser);
	cmd->heredocers[i + 1] = NULL;
	return ;
}

static void	remove_no_printable(t_command *cmd, t_parser *parser)
{
	int	i;

	i = 0;
	if (cmd->cmd && ft_strchr(cmd->cmd, '\x01'))
		cmd->cmd = remove_edge_chars('\x01', cmd->cmd, parser);
	while (cmd->args && cmd->args[i])
	{
		if (ft_strchr(cmd->args[i], '\x01'))
			cmd->args[i] = remove_edge_chars('\x01', cmd->args[i], parser);
		i++;
	}
	i = -1;
	while (cmd->env_args && cmd->env_args[++i])
	{
		if (ft_strchr(cmd->env_args[i], '\x01'))
			cmd->env_args[i] = remove_edge_chars('\x01', cmd->env_args[i],
					parser);
	}
	if (cmd->heredoc)
		cmd->heredoc = remove_edge_chars('\x01', cmd->heredoc, parser);
}

static void	new_cmd(t_command *cmd, t_parser *parser, t_token **start_ptr)
{
	int		i;
	t_token	*start;

	i = 0;
	start = *start_ptr;
	if (reset(0, 0))
		return ;
	while (start && start->type != TOKEN_PIPE)
	{
		if (reset(0, 0))
			return ;
		help_cmd(parser, start, cmd);
		if (start->type == TOKEN_HEREDOC_DELIMITER)
		{
			multi_herdoc(cmd, parser, start, i);
			i++;
		}
		start = start->next;
	}
	*start_ptr = start;
	splitted(cmd, parser);
}

t_command	*parse_tokens(t_token *tokens, t_parser *parser)
{
	t_command	*head;
	t_command	*cmd;
	t_token		*start;

	head = NULL;
	start = tokens;
	while (start)
	{
		if (reset(0, 0))
			return (NULL);
		cmd = init_command(parser->gc);
		new_cmd(cmd, parser, &start);
		remove_no_printable(cmd, parser);
		add_command_back(&head, cmd);
		if (start && start->type == TOKEN_PIPE)
		{
			start = start->next;
			parser->last_cmd++;
		}
	}
	parser->belong_to_export = false;
	parser->cmd_export = false;
	return (head);
}
