/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:07:41 by ildaboun          #+#    #+#             */
/*   Updated: 2025/06/28 02:11:00 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	env_arg(t_command *cmd, t_token *start, t_parser *parser)
{
	int		i;
	char	**new_args;

	i = 0;
	if (reset(0, 0))
		return ;
	if (cmd->env_args)
		while (cmd->env_args[i])
			i++;
	new_args = (char **) d_gc_malloc(parser->gc, sizeof(char *) * (i + 2));
	if (malloc_double_fail(new_args) || reset(0, 0))
		return ;
	i = 0;
	while (cmd->env_args && cmd->env_args[i])
	{
		new_args[i] = cmd->env_args[i];
		i++;
	}
	new_args[i++] = ft_strdup(start->value, parser->gc);
	new_args[i] = NULL;
	cmd->env_args = new_args;
	return ;
}

static void	help_add(t_command *cmd, t_token *start, t_parser *parser)
{
	if (!cmd->cmd && (start->type == TOKEN_STRING)
		&& (!start->expanded || start->was_quoted))
	{
		cmd->cmd = ft_strdup(start->value, parser->gc);
		if (cmd->cmd && start->dont_split_quoted)
			cmd->dont_split_cmd = true;
	}
}

void	add_arg(t_command *cmd, t_token *start, t_parser *parser)
{
	char	**new_args;
	int		i;

	i = 0;
	if (reset(0, 0))
		return ;
	help_add(cmd, start, parser);
	if (cmd->args)
		while (cmd->args[i])
			i++;
	new_args = (char **) d_gc_malloc(parser->gc, sizeof(char *) * (i + 2));
	if (malloc_double_fail(new_args) || reset(0, 0))
		return ;
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	if (*start->value || (!*start->value && !start->expanded)
		|| (!*start->value && start->was_quoted))
		new_args[i++] = ft_strdup(start->value, parser->gc);
	new_args[i] = NULL;
	cmd->args = new_args;
}

void	help_cmd(t_parser *parser, t_token *start, t_command *cmd)
{
	if (reset(0, 0))
		return ;
	else if (start->type == TOKEN_STRING)
		add_arg(cmd, start, parser);
	else if (start->type == TOKEN_ENV_VAR)
		env_arg(cmd, start, parser);
	else if (start->type == TOKEN_REDIR_IN
		|| start->type == TOKEN_REDIR_HEREDOC)
		handle_input_redirection(cmd, start, parser);
	else if (start->type == TOKEN_REDIR_OUT
		|| start->type == TOKEN_REDIR_APPEND)
		handle_output_redirection(cmd, start, parser);
}
